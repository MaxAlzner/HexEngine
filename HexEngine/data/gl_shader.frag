#version 130

in vec2 tex_coord;
in vec4 vertex_ls;
in vec3 vertex_ss;
in vec3 view_ss;

in vec4 vertex_def;
in vec3 normal_def;

in vec3 directionalLight_ss;
in vec3 pointLight4_ss[4];

out vec4 outColor;

uniform sampler2D color_map;
uniform sampler2D normal_map;
uniform sampler2D specular_map;
uniform sampler2D luminance_map;

uniform sampler2D depth_map;
uniform sampler2D position_map;
uniform sampler2D ao_map;
uniform sampler2D shadow_map;

uniform sampler2D leftEye_map;
uniform sampler2D rightEye_map;

uniform vec4 directionalLight_color;
uniform vec4 pointLight4_color[4];
uniform vec3 pointLight4_falloff[4];
uniform int numOfPointLights;

uniform vec2 screen_size;
uniform float shadow_size;
uniform vec2[36] random_filter;
uniform float gamma;
uniform vec4 leftEye_color;
uniform vec4 rightEye_color;

uniform int flag;

uniform float gaussian_weights_7x7[49] = 
float[49](
	0.000001, 0.000020, 0.000171, 0.000352, 0.000171, 0.000020, 0.000001, 
	0.000020, 0.000722, 0.006262, 0.012865, 0.006262, 0.000722, 0.000020, 
	0.000171, 0.006262, 0.054300, 0.111555, 0.054300, 0.006262, 0.000171, 
	0.000352, 0.012865, 0.111555, 0.229183, 0.111555, 0.012865, 0.000352, 
	0.000171, 0.006262, 0.054300, 0.111555, 0.054300, 0.006262, 0.000171, 
	0.000020, 0.000722, 0.006262, 0.012865, 0.006262, 0.000722, 0.000020, 
	0.000001, 0.000020, 0.000171, 0.000352, 0.000171, 0.000020, 0.000001
);
uniform float gaussian_weights_5x5[25] = 
float[25](
	0.000722, 0.006262, 0.012865, 0.006262, 0.000722, 
	0.006262, 0.054300, 0.111555, 0.054300, 0.006262, 
	0.012865, 0.111555, 0.229183, 0.111555, 0.012865, 
	0.006262, 0.054300, 0.111555, 0.054300, 0.006262, 
	0.000722, 0.006262, 0.012865, 0.006262, 0.000722
);

const float ambient_intensity = 0.2;
const float roughness = 0.6;
const float ref_index = 1.2;
const float r = 5.2;

const vec3 reinhard = vec3(0.2126, 0.7152, 0.0722);
const float middle_gray = 0.18;
const float white_cutoff = 0.8;

const float nearZ = 1.0;
const float farZ = 24.0;

float average(vec3 v)
{
	return (v.r + v.g + v.b) / 3.;
}
float gray(vec3 color)
{
	return clamp((0.2126 * color.r) + (0.7152 * color.g) + (0.0722  * color.b), 0., 1.);
}
float luminance(vec3 color)
{
	return clamp((0.2126 * pow(color.r, gamma)) + (0.7152 * pow(color.g, gamma)) + (0.0722  * pow(color.b, gamma)), 0., 1.);
}
float gr(float a, float b)
{
	return exp(1. - abs(a - b));
}

vec3 unpack_normal(in vec2 coord)
{
	return normalize((texture(normal_map, coord).rgb * 2.) - 1.);
}
float read_depth(in vec2 coord)
{
	float depth = average(texture(depth_map, coord).rgb);
	//return depth;
	float d = (2.0 * nearZ) / ((farZ + nearZ) - (depth * (farZ - nearZ)));
	return clamp(d, 0., 1.);
}

float occlusion(in vec2 coord, in vec3 normal, in vec3 p)
{
	float depth = read_depth(coord);
	vec3 r = unpack_normal(coord);
	vec3 v = vec3(coord, depth) - p;

	float atten = 1. / (1. + length(v));
	return max(dot(r, normal), 0.) * atten;
}

vec4 anaglyphic_3d()
{
	float leftEye_value = gray(texture(leftEye_map, tex_coord).rgb);
	float rightEye_value = gray(texture(rightEye_map, tex_coord).rgb);
	vec4 leftChannel = leftEye_color * leftEye_value;
	vec4 rightChannel = rightEye_color * rightEye_value;
	vec4 g = vec4(0.);
	g += leftChannel * 0.5;
	g += rightChannel * 0.5;
	return g;
}

#define OCCLUSION(x, y) \
do {\
	vec2 coord = tex_coord + (incr * vec2(x, y));\
	float d = read_depth(coord);\
	vec3 r = unpack_normal(coord);\
	vec3 v = vec3(coord, d) - vec3(tex_coord, depth);\
	float atten = 1. / (1. + length(v));\
	ao += max(dot(r, normal), 0.) * atten;\
	k += 1.;\
} while (false)
vec4 ambient_occlusion()
{
	float depth = read_depth(tex_coord);
	vec3 normal = unpack_normal(tex_coord);

	vec2 incr = 2.8 / screen_size;
	vec3 p = vec3(tex_coord, depth);
	
	float ao = 0.;
	float k = 0.;

#if 1
	ao += occlusion(tex_coord + (incr * vec2( 1.,  1.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2(-1.,  1.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2( 1., -1.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2(-1., -1.)), normal, p);
	
	ao += occlusion(tex_coord + (incr * vec2( 0., -2.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2( 0.,  2.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2(-2.,  0.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2( 2.,  0.)), normal, p);
	
	ao += occlusion(tex_coord + (incr * vec2( 3.,  3.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2(-3.,  3.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2( 3., -3.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2(-3., -3.)), normal, p);
	
	ao += occlusion(tex_coord + (incr * vec2( 0., -4.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2( 0.,  4.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2(-4.,  0.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2( 4.,  0.)), normal, p);
	
	ao += occlusion(tex_coord + (incr * vec2( 5.,  5.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2(-5.,  5.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2( 5., -5.)), normal, p);
	ao += occlusion(tex_coord + (incr * vec2(-5., -5.)), normal, p);

	ao /= 20.;
#else
	OCCLUSION( 1.,  1.);
	OCCLUSION(-1.,  1.);
	OCCLUSION( 1., -1.);
	OCCLUSION(-1., -1.);
	
	OCCLUSION( 0., -2.);
	OCCLUSION( 0.,  2.);
	OCCLUSION(-2.,  0.);
	OCCLUSION( 2.,  0.);

	OCCLUSION( 3.,  3.);
	OCCLUSION(-3.,  3.);
	OCCLUSION( 3., -3.);
	OCCLUSION(-3., -3.);
	
	OCCLUSION( 0., -4.);
	OCCLUSION( 0.,  4.);
	OCCLUSION(-4.,  0.);
	OCCLUSION( 4.,  0.);

	OCCLUSION( 5.,  5.);
	OCCLUSION(-5.,  5.);
	OCCLUSION( 5., -5.);
	OCCLUSION(-5., -5.);
	
	ao /= k;
#endif
	//ao = 1. - clamp(ao, 0., 1.);
	
	return vec4(vec3(ao), 1.);
}
vec4 bright_pass()
{
	vec3 color = texture(color_map, tex_coord).rgb;
	vec3 brightness = vec3(pow(color.r, gamma), pow(color.g, gamma), pow(color.b, gamma));

	brightness = clamp(brightness, 0., white_cutoff);

	return vec4(brightness, 1.);
}

#define GAUSSIAN_5X5_ROW(x) \
do {\
	int y = x + 2;\
	g += textureOffset(color_map, tex_coord, ivec2(-2, x)) * gaussian_weights_5x5[(y * 5) + 0];\
	g += textureOffset(color_map, tex_coord, ivec2(-1, x)) * gaussian_weights_5x5[(y * 5) + 1];\
	g += textureOffset(color_map, tex_coord, ivec2( 0, x)) * gaussian_weights_5x5[(y * 5) + 2];\
	g += textureOffset(color_map, tex_coord, ivec2( 1, x)) * gaussian_weights_5x5[(y * 5) + 3];\
	g += textureOffset(color_map, tex_coord, ivec2( 2, x)) * gaussian_weights_5x5[(y * 5) + 4];\
} while (false)
#define GAUSSIAN_7X7_ROW(x) \
do {\
	int y = x + 3;\
	g += textureOffset(color_map, tex_coord, ivec2(-3, x)) * gaussian_weights_7x7[(y * 7) + 0];\
	g += textureOffset(color_map, tex_coord, ivec2(-2, x)) * gaussian_weights_7x7[(y * 7) + 1];\
	g += textureOffset(color_map, tex_coord, ivec2(-1, x)) * gaussian_weights_7x7[(y * 7) + 2];\
	g += textureOffset(color_map, tex_coord, ivec2( 0, x)) * gaussian_weights_7x7[(y * 7) + 3];\
	g += textureOffset(color_map, tex_coord, ivec2( 1, x)) * gaussian_weights_7x7[(y * 7) + 4];\
	g += textureOffset(color_map, tex_coord, ivec2( 2, x)) * gaussian_weights_7x7[(y * 7) + 5];\
	g += textureOffset(color_map, tex_coord, ivec2( 3, x)) * gaussian_weights_7x7[(y * 7) + 6];\
} while (false)
#define GAUSSIAN_11X11_ROW(x) \
do {\
	g += textureOffset(color_map, tex_coord, ivec2(-5, x));\
	g += textureOffset(color_map, tex_coord, ivec2(-4, x));\
	g += textureOffset(color_map, tex_coord, ivec2(-3, x));\
	g += textureOffset(color_map, tex_coord, ivec2(-2, x));\
	g += textureOffset(color_map, tex_coord, ivec2(-1, x));\
	g += textureOffset(color_map, tex_coord, ivec2( 0, x));\
	g += textureOffset(color_map, tex_coord, ivec2( 1, x));\
	g += textureOffset(color_map, tex_coord, ivec2( 2, x));\
	g += textureOffset(color_map, tex_coord, ivec2( 3, x));\
	g += textureOffset(color_map, tex_coord, ivec2( 4, x));\
	g += textureOffset(color_map, tex_coord, ivec2( 5, x));\
	k += 11.;\
} while (false)
#define BILATERAL_GAUSSIAN(x, y, w) \
do {\
	float v = average(textureOffset(depth_map, tex_coord, ivec2(x, y)).rgb);\
	float b = gaussian_weights_5x5[w] * gr(p, v);\
	k += b;\
	g += textureOffset(color_map, tex_coord, ivec2(x, y)) * b;\
} while (false)
vec4 gaussian_blur()
{
	vec4 g = vec4(0.);
	g += textureOffset(color_map, tex_coord, ivec2(-2, -2)) * gaussian_weights_5x5[ 0];
	g += textureOffset(color_map, tex_coord, ivec2(-1, -2)) * gaussian_weights_5x5[ 1];
	g += textureOffset(color_map, tex_coord, ivec2( 0, -2)) * gaussian_weights_5x5[ 2];
	g += textureOffset(color_map, tex_coord, ivec2( 1, -2)) * gaussian_weights_5x5[ 3];
	g += textureOffset(color_map, tex_coord, ivec2( 2, -2)) * gaussian_weights_5x5[ 4];
	g += textureOffset(color_map, tex_coord, ivec2(-2, -1)) * gaussian_weights_5x5[ 5];
	g += textureOffset(color_map, tex_coord, ivec2(-1, -1)) * gaussian_weights_5x5[ 6];
	g += textureOffset(color_map, tex_coord, ivec2( 0, -1)) * gaussian_weights_5x5[ 7];
	g += textureOffset(color_map, tex_coord, ivec2( 1, -1)) * gaussian_weights_5x5[ 8];
	g += textureOffset(color_map, tex_coord, ivec2( 2, -1)) * gaussian_weights_5x5[ 9];
	g += textureOffset(color_map, tex_coord, ivec2(-2, 0)) * gaussian_weights_5x5[10];
	g += textureOffset(color_map, tex_coord, ivec2(-1, 0)) * gaussian_weights_5x5[11];
	g += textureOffset(color_map, tex_coord, ivec2( 0, 0)) * gaussian_weights_5x5[12];
	g += textureOffset(color_map, tex_coord, ivec2( 1, 0)) * gaussian_weights_5x5[13];
	g += textureOffset(color_map, tex_coord, ivec2( 2, 0)) * gaussian_weights_5x5[14];
	g += textureOffset(color_map, tex_coord, ivec2(-2, 1)) * gaussian_weights_5x5[15];
	g += textureOffset(color_map, tex_coord, ivec2(-1, 1)) * gaussian_weights_5x5[16];
	g += textureOffset(color_map, tex_coord, ivec2( 0, 1)) * gaussian_weights_5x5[17];
	g += textureOffset(color_map, tex_coord, ivec2( 1, 1)) * gaussian_weights_5x5[18];
	g += textureOffset(color_map, tex_coord, ivec2( 2, 1)) * gaussian_weights_5x5[19];
	g += textureOffset(color_map, tex_coord, ivec2(-2, 2)) * gaussian_weights_5x5[20];
	g += textureOffset(color_map, tex_coord, ivec2(-1, 2)) * gaussian_weights_5x5[21];
	g += textureOffset(color_map, tex_coord, ivec2( 0, 2)) * gaussian_weights_5x5[22];
	g += textureOffset(color_map, tex_coord, ivec2( 1, 2)) * gaussian_weights_5x5[23];
	g += textureOffset(color_map, tex_coord, ivec2( 2, 2)) * gaussian_weights_5x5[24];
	return g;
}
vec4 gaussian_blur_large()
{
vec4 g = vec4(0.);
	g += textureOffset(color_map, tex_coord, ivec2(-3,  3)) * gaussian_weights_7x7[ 0];
	g += textureOffset(color_map, tex_coord, ivec2(-2,  3)) * gaussian_weights_7x7[ 1];
	g += textureOffset(color_map, tex_coord, ivec2(-1,  3)) * gaussian_weights_7x7[ 2];
	g += textureOffset(color_map, tex_coord, ivec2( 0,  3)) * gaussian_weights_7x7[ 3];
	g += textureOffset(color_map, tex_coord, ivec2( 1,  3)) * gaussian_weights_7x7[ 4];
	g += textureOffset(color_map, tex_coord, ivec2( 2,  3)) * gaussian_weights_7x7[ 5];
	g += textureOffset(color_map, tex_coord, ivec2( 3,  3)) * gaussian_weights_7x7[ 6];
	g += textureOffset(color_map, tex_coord, ivec2(-3,  2)) * gaussian_weights_7x7[ 7];
	g += textureOffset(color_map, tex_coord, ivec2(-2,  2)) * gaussian_weights_7x7[ 8];
	g += textureOffset(color_map, tex_coord, ivec2(-1,  2)) * gaussian_weights_7x7[ 9];
	g += textureOffset(color_map, tex_coord, ivec2( 0,  2)) * gaussian_weights_7x7[10];
	g += textureOffset(color_map, tex_coord, ivec2( 1,  2)) * gaussian_weights_7x7[11];
	g += textureOffset(color_map, tex_coord, ivec2( 2,  2)) * gaussian_weights_7x7[12];
	g += textureOffset(color_map, tex_coord, ivec2( 3,  2)) * gaussian_weights_7x7[13];
	g += textureOffset(color_map, tex_coord, ivec2(-3,  1)) * gaussian_weights_7x7[14];
	g += textureOffset(color_map, tex_coord, ivec2(-2,  1)) * gaussian_weights_7x7[15];
	g += textureOffset(color_map, tex_coord, ivec2(-1,  1)) * gaussian_weights_7x7[16];
	g += textureOffset(color_map, tex_coord, ivec2( 0,  1)) * gaussian_weights_7x7[17];
	g += textureOffset(color_map, tex_coord, ivec2( 1,  1)) * gaussian_weights_7x7[18];
	g += textureOffset(color_map, tex_coord, ivec2( 2,  1)) * gaussian_weights_7x7[19];
	g += textureOffset(color_map, tex_coord, ivec2( 3,  1)) * gaussian_weights_7x7[20];
	g += textureOffset(color_map, tex_coord, ivec2(-3,  0)) * gaussian_weights_7x7[21];
	g += textureOffset(color_map, tex_coord, ivec2(-2,  0)) * gaussian_weights_7x7[22];
	g += textureOffset(color_map, tex_coord, ivec2(-1,  0)) * gaussian_weights_7x7[23];
	g += textureOffset(color_map, tex_coord, ivec2( 0,  0)) * gaussian_weights_7x7[24];
	g += textureOffset(color_map, tex_coord, ivec2( 1,  0)) * gaussian_weights_7x7[25];
	g += textureOffset(color_map, tex_coord, ivec2( 2,  0)) * gaussian_weights_7x7[26];
	g += textureOffset(color_map, tex_coord, ivec2( 3,  0)) * gaussian_weights_7x7[27];
	g += textureOffset(color_map, tex_coord, ivec2(-3, -1)) * gaussian_weights_7x7[28];
	g += textureOffset(color_map, tex_coord, ivec2(-2, -1)) * gaussian_weights_7x7[29];
	g += textureOffset(color_map, tex_coord, ivec2(-1, -1)) * gaussian_weights_7x7[30];
	g += textureOffset(color_map, tex_coord, ivec2( 0, -1)) * gaussian_weights_7x7[31];
	g += textureOffset(color_map, tex_coord, ivec2( 1, -1)) * gaussian_weights_7x7[32];
	g += textureOffset(color_map, tex_coord, ivec2( 2, -1)) * gaussian_weights_7x7[33];
	g += textureOffset(color_map, tex_coord, ivec2( 3, -1)) * gaussian_weights_7x7[34];
	g += textureOffset(color_map, tex_coord, ivec2(-3, -2)) * gaussian_weights_7x7[35];
	g += textureOffset(color_map, tex_coord, ivec2(-2, -2)) * gaussian_weights_7x7[36];
	g += textureOffset(color_map, tex_coord, ivec2(-1, -2)) * gaussian_weights_7x7[37];
	g += textureOffset(color_map, tex_coord, ivec2( 0, -2)) * gaussian_weights_7x7[38];
	g += textureOffset(color_map, tex_coord, ivec2( 1, -2)) * gaussian_weights_7x7[39];
	g += textureOffset(color_map, tex_coord, ivec2( 2, -2)) * gaussian_weights_7x7[40];
	g += textureOffset(color_map, tex_coord, ivec2( 3, -2)) * gaussian_weights_7x7[41];
	g += textureOffset(color_map, tex_coord, ivec2(-3, -3)) * gaussian_weights_7x7[42];
	g += textureOffset(color_map, tex_coord, ivec2(-2, -3)) * gaussian_weights_7x7[43];
	g += textureOffset(color_map, tex_coord, ivec2(-1, -3)) * gaussian_weights_7x7[44];
	g += textureOffset(color_map, tex_coord, ivec2( 0, -3)) * gaussian_weights_7x7[45];
	g += textureOffset(color_map, tex_coord, ivec2( 1, -3)) * gaussian_weights_7x7[46];
	g += textureOffset(color_map, tex_coord, ivec2( 2, -3)) * gaussian_weights_7x7[47];
	g += textureOffset(color_map, tex_coord, ivec2( 3, -3)) * gaussian_weights_7x7[48];
	return g;
}
vec4 bilateral_gaussian_blur()
{
	float p = average(texture(depth_map, tex_coord).rgb);
	vec4 g = vec4(0.);
	float k = 0.;
	BILATERAL_GAUSSIAN(-2, -2,  0);
	BILATERAL_GAUSSIAN(-1, -2,  1);
	BILATERAL_GAUSSIAN( 0, -2,  2);
	BILATERAL_GAUSSIAN( 1, -2,  3);
	BILATERAL_GAUSSIAN( 2, -2,  4);
	BILATERAL_GAUSSIAN(-2, -1,  5);
	BILATERAL_GAUSSIAN(-1, -1,  6);
	BILATERAL_GAUSSIAN( 0, -1,  7);
	BILATERAL_GAUSSIAN( 1, -1,  8);
	BILATERAL_GAUSSIAN( 2, -1,  9);
	BILATERAL_GAUSSIAN(-2,  0, 10);
	BILATERAL_GAUSSIAN(-1,  0, 11);
	BILATERAL_GAUSSIAN( 0,  0, 12);
	BILATERAL_GAUSSIAN( 1,  0, 13);
	BILATERAL_GAUSSIAN( 2,  0, 14);
	BILATERAL_GAUSSIAN(-2,  1, 15);
	BILATERAL_GAUSSIAN(-1,  1, 16);
	BILATERAL_GAUSSIAN( 0,  1, 17);
	BILATERAL_GAUSSIAN( 1,  1, 18);
	BILATERAL_GAUSSIAN( 2,  1, 19);
	BILATERAL_GAUSSIAN(-2,  2, 20);
	BILATERAL_GAUSSIAN(-1,  2, 21);
	BILATERAL_GAUSSIAN( 0,  2, 22);
	BILATERAL_GAUSSIAN( 1,  2, 23);
	BILATERAL_GAUSSIAN( 2,  2, 24);
	return g / k;
}

float shadow_intensity()
{
	return textureProj(shadow_map, vertex_ls).r;
#if 0
	vec3 tex_shadow = vec3(vertex_ls.xyz / vertex_ls.w);
	tex_shadow.z -= 0.02;
	return texture(shadow_map, tex_shadow);
	return 0.;
#if 0
	float s = 1.0;
	vec2 filter = vec2(cos(gl_PointCoord.x * 1.33), sin(gl_PointCoord.y * 0.71));
	vec2 incr = vec2(r / shadow_size);
	float sum = 0.;
	for (int i = 0; i < random_filter.length(); i++)
	{
		vec2 sample_coord = incr;
#if 0
		sample_coord = vec2(
			(sample_coord.x * filter.x) - (sample_coord.y * filter.y), 
			(sample_coord.x * filter.y) + (sample_coord.y * filter.x)
		);
#endif
		sample_coord *= random_filter[i];
		sum += texture(shadow_map, tex_shadow + vec3(sample_coord, 0.));
	}
	float sample_shadow = sum / float(random_filter.length());
	return clamp(sample_shadow, 0., 1.);
#endif
#endif
}

#define ATTENUATION \
	float dist = distance(light_position, vertex_ss);\
	float atten = 1. / (light_falloff.x + (light_falloff.y * dist) + (light_falloff.z * dist * dist));
#define SPECULAR \
	float n_dot_h = dot(n, h);\
	float n_dot_v = dot(n, v);\
	float h_dot_v = dot(h, v);\
	float h_dot_l = dot(h, l);\
	float g1 = (2. * n_dot_h * n_dot_v) / h_dot_v;\
	float g2 = (2. * n_dot_h * n_dot_l) / h_dot_v;\
	float g = 1.;\
	if (g1 < g) g = g1;\
	if (g2 < g) g = g2;\
	float m = roughness * roughness;\
	float r = (1. / (m * pow(n_dot_h, 4.))) * exp((pow(n_dot_h, 2.) - 1.) / (m * pow(n_dot_h, 2.)));\
	float f = (ref_index + pow(1. - h_dot_v, 5.)) * (1. - ref_index);\
	float specular = max((abs(f * r * g) / n_dot_v), 0.) * specular_intensity;
#define LAMBERT \
	float n_dot_l = dot(n, l);\
	float lambert = max(n_dot_l, 0.);

#define POINTLIGHT_ALBEDO(x) \
do {\
	vec3 light_position = pointLight4_ss[x];\
	vec4 light_color = pointLight4_color[x];\
	vec3 light_falloff = pointLight4_falloff[x];\
	vec3 l = normalize(light_position - vertex_ss);\
	vec3 h = normalize(l + v);\
	ATTENUATION;\
	LAMBERT;\
	SPECULAR;\
	vec3 diffuse = (light_color.rgb * lambert) + vec3(specular * lambert);\
	albedo += (diffuse * atten * light_color.a);\
} while (false)
#define DIRECTIONAL_ALBEDO \
do {\
	vec3 l = normalize(directionalLight_ss);\
	LAMBERT;\
	vec3 diffuse = (directionalLight_color.rgb * lambert);\
	albedo += diffuse * directionalLight_color.a;\
} while (false)
void directionalLight_albedo(inout vec3 albedo, in vec3 n, in vec3 v)
{
	vec3 l = normalize(directionalLight_ss);
	vec3 h = normalize(l + v);

	float n_dot_l = dot(n, l);

	float lambert = max(n_dot_l, 0.);

	vec3 diffuse = (directionalLight_color.rgb * lambert);
	albedo += diffuse * directionalLight_color.a;
}
void pointLight_albedo(inout vec3 albedo, in vec3 n, in vec3 v, in float specular_intensity, in vec3 light_position, in vec4 light_color, in vec3 light_falloff)
{
	float dist = distance(light_position, vertex_ss);
	float atten = 1. / (light_falloff.x + (light_falloff.y * dist) + (light_falloff.z * dist * dist));

	vec3 l = normalize(light_position - vertex_ss);
	vec3 h = normalize(l + v);

	float n_dot_l = dot(n, l);
	float n_dot_h = dot(n, h);
	float n_dot_v = dot(n, v);
	float h_dot_v = dot(h, v);
	float h_dot_l = dot(h, l);

	float g1 = (2. * n_dot_h * n_dot_v) / h_dot_v;
	float g2 = (2. * n_dot_h * n_dot_l) / h_dot_v;
	float g = 1.;
	if (g1 < g) g = g1;
	if (g2 < g) g = g2;
	float m = roughness * roughness;
	float r = (1. / (m * pow(n_dot_h, 4.))) * exp((pow(n_dot_h, 2.) - 1.) / (m * pow(n_dot_h, 2.)));
	float f = (ref_index + pow(1. - h_dot_v, 5.)) * (1. - ref_index);
	float specular = max((abs(f * r * g) / n_dot_v), 0.) * specular_intensity;

	float lambert = max(n_dot_l, 0.);

	vec3 diffuse = (light_color.rgb * lambert * atten) + vec3(specular * lambert);
	albedo += (diffuse * light_color.a);
}

vec4 main_render()
{
	vec4 sample_color = texture(color_map, tex_coord);
	vec3 color = sample_color.rgb;

	vec4 sample_specular = texture(specular_map, tex_coord);
	float specular_intensity = average(sample_specular.rgb);

	vec3 n = unpack_normal(tex_coord);
	vec3 v = normalize(view_ss - vertex_ss);
	
	vec3 albedo = vec3(0.);

#if 0
	DIRECTIONAL_ALBEDO;

	if (numOfPointLights > 0) POINTLIGHT_ALBEDO(0);
	if (numOfPointLights > 1) POINTLIGHT_ALBEDO(1);
	if (numOfPointLights > 2) POINTLIGHT_ALBEDO(2);
	if (numOfPointLights > 3) POINTLIGHT_ALBEDO(3);
#else
	directionalLight_albedo(albedo, n, v);

#if 1
	if (numOfPointLights > 0) pointLight_albedo(albedo, n, v, specular_intensity, pointLight4_ss[0], pointLight4_color[0], pointLight4_falloff[0]);
	if (numOfPointLights > 1) pointLight_albedo(albedo, n, v, specular_intensity, pointLight4_ss[1], pointLight4_color[1], pointLight4_falloff[1]);
	if (numOfPointLights > 2) pointLight_albedo(albedo, n, v, specular_intensity, pointLight4_ss[2], pointLight4_color[2], pointLight4_falloff[2]);
	if (numOfPointLights > 3) pointLight_albedo(albedo, n, v, specular_intensity, pointLight4_ss[3], pointLight4_color[3], pointLight4_falloff[3]);
#endif
#endif

	//float shadow = shadow_intensity();
	
	return vec4(color * albedo, 1.);
}
vec4 final_render()
{
	vec2 filter = vec2(cos(gl_PointCoord.x * 1.33), sin(gl_PointCoord.x * 0.71));
	vec2 coord = vec2(0.5 / 128.);
	coord = vec2((coord.x * filter.x) - (coord.y * filter.y), (coord.x * filter.y) + (coord.y * filter.x));

	vec4 luminance = texture(luminance_map, tex_coord + coord);
	vec4 ao = texture(ao_map, tex_coord);
	vec4 base = texture(color_map, tex_coord);
	return (base + luminance) * ao;
}

void main()
{
	switch (flag)
	{
		case 1:// rendering shadow map
		outColor = vec4(0., 0., 0., 1.);
		return;
		case 2:
		case 41:
		outColor = texture(color_map, tex_coord);
		return;

		case 4:
		outColor = vec4(vertex_def.x, vertex_def.y, vertex_def.z, length(vertex_def) / (farZ - nearZ));
		return;
		case 5:
		outColor = vec4((normal_def.x * .5) + .5, (normal_def.y * .5) + .5, normal_def.z, 1.);
		return;

		case 11:
		outColor = gaussian_blur();
		return;
		case 12:
		outColor = gaussian_blur_large();
		return;
		case 13:
		outColor = bilateral_gaussian_blur();
		return;

		case 21:
		outColor = ambient_occlusion();
		return;
		case 22:
		outColor = bright_pass();
		return;

		case 31:
		outColor = anaglyphic_3d();
		return;

		case 51:
		outColor = final_render();
		return;

		default:
		outColor = main_render();
		return;
	}
}
