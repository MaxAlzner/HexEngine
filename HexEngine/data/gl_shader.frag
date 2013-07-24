#version 130

in vec2 tex_coord;
in vec4 vertex_ls;
in vec3 vertex_ss;
in vec3 view_ss;

in vec3 directionalLight_ss;
in vec3 pointLight4_ss[4];

out vec4 outColor;

uniform sampler2D color_map;
uniform sampler2D normal_map;
uniform sampler2D specular_map;
uniform sampler2D luminance_map;

uniform sampler2D depth_map;
uniform sampler2D shadow_map;

uniform sampler2D leftEye_map;
uniform sampler2D rightEye_map;

uniform vec4 directionalLight_color;
uniform vec4 pointLight4_color[4];
uniform vec3 pointLight4_falloff[4];
uniform int numOfPointLights;

uniform float shadow_size;
uniform float luminance_size;
uniform vec2[36] random_filter;
uniform float gamma;
uniform vec4 leftEye_color;
uniform vec4 rightEye_color;

uniform int flag;

uniform float gaussian_weights[25] = 
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

vec4 ambient_occlusion()
{
	return vec4(0.);
}
vec4 bright_pass()
{
	vec3 color = texture(color_map, tex_coord).rgb;
	float depth = 1.;// - average(texture(depth_map, tex_coord).rgb);
	vec3 brightness = vec3(pow(color.r, gamma), pow(color.g, gamma), pow(color.b, gamma));
	brightness = clamp(brightness, 0., 1.);
	return vec4(brightness * depth, 1.);
}

vec4 gaussian_blur()
{
	vec4 g = vec4(0.);
	g += textureOffset(color_map, tex_coord, ivec2(-2, -2)) * gaussian_weights[ 0];
	g += textureOffset(color_map, tex_coord, ivec2(-1, -2)) * gaussian_weights[ 1];
	g += textureOffset(color_map, tex_coord, ivec2( 0, -2)) * gaussian_weights[ 2];
	g += textureOffset(color_map, tex_coord, ivec2( 1, -2)) * gaussian_weights[ 3];
	g += textureOffset(color_map, tex_coord, ivec2( 2, -2)) * gaussian_weights[ 4];
	g += textureOffset(color_map, tex_coord, ivec2(-2, -1)) * gaussian_weights[ 5];
	g += textureOffset(color_map, tex_coord, ivec2(-1, -1)) * gaussian_weights[ 6];
	g += textureOffset(color_map, tex_coord, ivec2( 0, -1)) * gaussian_weights[ 7];
	g += textureOffset(color_map, tex_coord, ivec2( 1, -1)) * gaussian_weights[ 8];
	g += textureOffset(color_map, tex_coord, ivec2( 2, -1)) * gaussian_weights[ 9];
	g += textureOffset(color_map, tex_coord, ivec2(-2,  0)) * gaussian_weights[10];
	g += textureOffset(color_map, tex_coord, ivec2(-1,  0)) * gaussian_weights[11];
	g += textureOffset(color_map, tex_coord, ivec2( 0,  0)) * gaussian_weights[12];
	g += textureOffset(color_map, tex_coord, ivec2( 1,  0)) * gaussian_weights[13];
	g += textureOffset(color_map, tex_coord, ivec2( 2,  0)) * gaussian_weights[14];
	g += textureOffset(color_map, tex_coord, ivec2(-2,  1)) * gaussian_weights[15];
	g += textureOffset(color_map, tex_coord, ivec2(-1,  1)) * gaussian_weights[16];
	g += textureOffset(color_map, tex_coord, ivec2( 0,  1)) * gaussian_weights[17];
	g += textureOffset(color_map, tex_coord, ivec2( 1,  1)) * gaussian_weights[18];
	g += textureOffset(color_map, tex_coord, ivec2( 2,  1)) * gaussian_weights[19];
	g += textureOffset(color_map, tex_coord, ivec2(-2,  2)) * gaussian_weights[20];
	g += textureOffset(color_map, tex_coord, ivec2(-1,  2)) * gaussian_weights[21];
	g += textureOffset(color_map, tex_coord, ivec2( 0,  2)) * gaussian_weights[22];
	g += textureOffset(color_map, tex_coord, ivec2( 1,  2)) * gaussian_weights[23];
	g += textureOffset(color_map, tex_coord, ivec2( 2,  2)) * gaussian_weights[24];
	return g;
}
vec4 gaussian_blur_large()
{
	vec4 g = vec4(0.);
	g += textureOffset(color_map, tex_coord, ivec2(-5,  5));
	g += textureOffset(color_map, tex_coord, ivec2(-4,  5));
	g += textureOffset(color_map, tex_coord, ivec2(-3,  5));
	g += textureOffset(color_map, tex_coord, ivec2(-2,  5));
	g += textureOffset(color_map, tex_coord, ivec2(-1,  5));
	g += textureOffset(color_map, tex_coord, ivec2( 0,  5));
	g += textureOffset(color_map, tex_coord, ivec2( 1,  5));
	g += textureOffset(color_map, tex_coord, ivec2( 2,  5));
	g += textureOffset(color_map, tex_coord, ivec2( 3,  5));
	g += textureOffset(color_map, tex_coord, ivec2( 4,  5));
	g += textureOffset(color_map, tex_coord, ivec2( 5,  5));
	g += textureOffset(color_map, tex_coord, ivec2(-5,  4));
	g += textureOffset(color_map, tex_coord, ivec2(-4,  4));
	g += textureOffset(color_map, tex_coord, ivec2(-3,  4));
	g += textureOffset(color_map, tex_coord, ivec2(-2,  4));
	g += textureOffset(color_map, tex_coord, ivec2(-1,  4));
	g += textureOffset(color_map, tex_coord, ivec2( 0,  4));
	g += textureOffset(color_map, tex_coord, ivec2( 1,  4));
	g += textureOffset(color_map, tex_coord, ivec2( 2,  4));
	g += textureOffset(color_map, tex_coord, ivec2( 3,  4));
	g += textureOffset(color_map, tex_coord, ivec2( 4,  4));
	g += textureOffset(color_map, tex_coord, ivec2( 5,  4));
	g += textureOffset(color_map, tex_coord, ivec2(-5,  3));
	g += textureOffset(color_map, tex_coord, ivec2(-4,  3));
	g += textureOffset(color_map, tex_coord, ivec2(-3,  3));
	g += textureOffset(color_map, tex_coord, ivec2(-2,  3));
	g += textureOffset(color_map, tex_coord, ivec2(-1,  3));
	g += textureOffset(color_map, tex_coord, ivec2( 0,  3));
	g += textureOffset(color_map, tex_coord, ivec2( 1,  3));
	g += textureOffset(color_map, tex_coord, ivec2( 2,  3));
	g += textureOffset(color_map, tex_coord, ivec2( 3,  3));
	g += textureOffset(color_map, tex_coord, ivec2( 4,  3));
	g += textureOffset(color_map, tex_coord, ivec2( 5,  3));
	g += textureOffset(color_map, tex_coord, ivec2(-5,  2));
	g += textureOffset(color_map, tex_coord, ivec2(-4,  2));
	g += textureOffset(color_map, tex_coord, ivec2(-3,  2));
	g += textureOffset(color_map, tex_coord, ivec2(-2,  2));
	g += textureOffset(color_map, tex_coord, ivec2(-1,  2));
	g += textureOffset(color_map, tex_coord, ivec2( 0,  2));
	g += textureOffset(color_map, tex_coord, ivec2( 1,  2));
	g += textureOffset(color_map, tex_coord, ivec2( 2,  2));
	g += textureOffset(color_map, tex_coord, ivec2( 3,  2));
	g += textureOffset(color_map, tex_coord, ivec2( 4,  2));
	g += textureOffset(color_map, tex_coord, ivec2( 5,  2));
	g += textureOffset(color_map, tex_coord, ivec2(-5,  1));
	g += textureOffset(color_map, tex_coord, ivec2(-4,  1));
	g += textureOffset(color_map, tex_coord, ivec2(-3,  1));
	g += textureOffset(color_map, tex_coord, ivec2(-2,  1));
	g += textureOffset(color_map, tex_coord, ivec2(-1,  1));
	g += textureOffset(color_map, tex_coord, ivec2( 0,  1));
	g += textureOffset(color_map, tex_coord, ivec2( 1,  1));
	g += textureOffset(color_map, tex_coord, ivec2( 2,  1));
	g += textureOffset(color_map, tex_coord, ivec2( 3,  1));
	g += textureOffset(color_map, tex_coord, ivec2( 4,  1));
	g += textureOffset(color_map, tex_coord, ivec2( 5,  1));
	g += textureOffset(color_map, tex_coord, ivec2(-5,  0));
	g += textureOffset(color_map, tex_coord, ivec2(-4,  0));
	g += textureOffset(color_map, tex_coord, ivec2(-3,  0));
	g += textureOffset(color_map, tex_coord, ivec2(-2,  0));
	g += textureOffset(color_map, tex_coord, ivec2(-1,  0));
	g += textureOffset(color_map, tex_coord, ivec2( 0,  0));
	g += textureOffset(color_map, tex_coord, ivec2( 1,  0));
	g += textureOffset(color_map, tex_coord, ivec2( 2,  0));
	g += textureOffset(color_map, tex_coord, ivec2( 3,  0));
	g += textureOffset(color_map, tex_coord, ivec2( 4,  0));
	g += textureOffset(color_map, tex_coord, ivec2( 5,  0));
	g += textureOffset(color_map, tex_coord, ivec2(-5, -1));
	g += textureOffset(color_map, tex_coord, ivec2(-4, -1));
	g += textureOffset(color_map, tex_coord, ivec2(-3, -1));
	g += textureOffset(color_map, tex_coord, ivec2(-2, -1));
	g += textureOffset(color_map, tex_coord, ivec2(-1, -1));
	g += textureOffset(color_map, tex_coord, ivec2( 0, -1));
	g += textureOffset(color_map, tex_coord, ivec2( 1, -1));
	g += textureOffset(color_map, tex_coord, ivec2( 2, -1));
	g += textureOffset(color_map, tex_coord, ivec2( 3, -1));
	g += textureOffset(color_map, tex_coord, ivec2( 4, -1));
	g += textureOffset(color_map, tex_coord, ivec2( 5, -1));
	g += textureOffset(color_map, tex_coord, ivec2(-5, -2));
	g += textureOffset(color_map, tex_coord, ivec2(-4, -2));
	g += textureOffset(color_map, tex_coord, ivec2(-3, -2));
	g += textureOffset(color_map, tex_coord, ivec2(-2, -2));
	g += textureOffset(color_map, tex_coord, ivec2(-1, -2));
	g += textureOffset(color_map, tex_coord, ivec2( 0, -2));
	g += textureOffset(color_map, tex_coord, ivec2( 1, -2));
	g += textureOffset(color_map, tex_coord, ivec2( 2, -2));
	g += textureOffset(color_map, tex_coord, ivec2( 3, -2));
	g += textureOffset(color_map, tex_coord, ivec2( 4, -2));
	g += textureOffset(color_map, tex_coord, ivec2( 5, -2));
	g += textureOffset(color_map, tex_coord, ivec2(-5, -3));
	g += textureOffset(color_map, tex_coord, ivec2(-4, -3));
	g += textureOffset(color_map, tex_coord, ivec2(-3, -3));
	g += textureOffset(color_map, tex_coord, ivec2(-2, -3));
	g += textureOffset(color_map, tex_coord, ivec2(-1, -3));
	g += textureOffset(color_map, tex_coord, ivec2( 0, -3));
	g += textureOffset(color_map, tex_coord, ivec2( 1, -3));
	g += textureOffset(color_map, tex_coord, ivec2( 2, -3));
	g += textureOffset(color_map, tex_coord, ivec2( 3, -3));
	g += textureOffset(color_map, tex_coord, ivec2( 4, -3));
	g += textureOffset(color_map, tex_coord, ivec2( 5, -3));
	g += textureOffset(color_map, tex_coord, ivec2(-5, -4));
	g += textureOffset(color_map, tex_coord, ivec2(-4, -4));
	g += textureOffset(color_map, tex_coord, ivec2(-3, -4));
	g += textureOffset(color_map, tex_coord, ivec2(-2, -4));
	g += textureOffset(color_map, tex_coord, ivec2(-1, -4));
	g += textureOffset(color_map, tex_coord, ivec2( 0, -4));
	g += textureOffset(color_map, tex_coord, ivec2( 1, -4));
	g += textureOffset(color_map, tex_coord, ivec2( 2, -4));
	g += textureOffset(color_map, tex_coord, ivec2( 3, -4));
	g += textureOffset(color_map, tex_coord, ivec2( 4, -4));
	g += textureOffset(color_map, tex_coord, ivec2( 5, -4));
	g += textureOffset(color_map, tex_coord, ivec2(-5, -5));
	g += textureOffset(color_map, tex_coord, ivec2(-4, -5));
	g += textureOffset(color_map, tex_coord, ivec2(-3, -5));
	g += textureOffset(color_map, tex_coord, ivec2(-2, -5));
	g += textureOffset(color_map, tex_coord, ivec2(-1, -5));
	g += textureOffset(color_map, tex_coord, ivec2( 0, -5));
	g += textureOffset(color_map, tex_coord, ivec2( 1, -5));
	g += textureOffset(color_map, tex_coord, ivec2( 2, -5));
	g += textureOffset(color_map, tex_coord, ivec2( 3, -5));
	g += textureOffset(color_map, tex_coord, ivec2( 4, -5));
	g += textureOffset(color_map, tex_coord, ivec2( 5, -5));
	return g / 121.;
}
#define S(x, y, w) \
do {\
	float v = average(textureOffset(depth_map, tex_coord, ivec2(x, y)).rgb);\
	float b = gaussian_weights[w] * gr(p, v);\
	k += b;\
	g += textureOffset(color_map, tex_coord, ivec2(x, y)) * b;\
} while (false)
vec4 bilateral_gaussian_blur()
{
	float p = average(texture(depth_map, tex_coord).rgb);
	vec4 g = vec4(0.);
	float k = 0.;
	S(-2, -2,  0);
	S(-1, -2,  1);
	S( 0, -2,  2);
	S( 1, -2,  3);
	S( 2, -2,  4);
	S(-2, -1,  5);
	S(-1, -1,  6);
	S( 0, -1,  7);
	S( 1, -1,  8);
	S( 2, -1,  9);
	S(-2,  0, 10);
	S(-1,  0, 11);
	S( 0,  0, 12);
	S( 1,  0, 13);
	S( 2,  0, 14);
	S(-2,  1, 15);
	S(-1,  1, 16);
	S( 0,  1, 17);
	S( 1,  1, 18);
	S( 2,  1, 19);
	S(-2,  2, 20);
	S(-1,  2, 21);
	S( 0,  2, 22);
	S( 1,  2, 23);
	S( 2,  2, 24);
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

void pointLight_albedo(inout vec3 albedo, in vec3 n, in vec3 v, in vec3 light_position, in vec3 light_color, in vec3 light_falloff)
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
	
	/*float g1 = (2. * n_dot_h * n_dot_v) / h_dot_v;
	float g2 = (2. * n_dot_h * n_dot_l) / h_dot_v;
	float g = 1.;
	if (g1 < g) g = g1;
	if (g2 < g) g = g2;
	float m = roughness * roughness;
	float r = (1. / (m * pow(n_dot_h, 4.))) * exp((pow(n_dot_h, 2.) - 1.) / (m * pow(n_dot_h, 2.)));
	float f = (ref_index + pow(1. - h_dot_v, 5.)) * (1. - ref_index);
	float specular = max((abs(f * r * g) / n_dot_v), 0.);*/

	float lambert = clamp(n_dot_l, ambient_intensity, 1.);

	vec3 diffuse = (light_color * lambert);// + vec3(specular);
	albedo += (diffuse * atten);
}
void directionalLight_albedo(inout vec3 albedo, in vec3 n, in vec3 v)
{
	vec3 l = normalize(directionalLight_ss);

	float n_dot_l = dot(n, l);

	//float shadow = shadow_intensity();
	float lambert = max(n_dot_l, ambient_intensity);
	
	vec3 diffuse = (directionalLight_color.rgb * lambert);
	albedo += diffuse;
}

vec4 main_render()
{
	vec4 sample_color = texture(color_map, tex_coord);
	vec3 color = sample_color.rgb;

	vec4 sample_normal = texture(normal_map, tex_coord);
	vec3 n = normalize((sample_normal.rgb * 2.) - 1.);
	vec3 v = normalize(view_ss);
	//n = vec3(0., 0., 1.);
	
	vec3 albedo = vec3(0.);

	directionalLight_albedo(albedo, n, v);
	
	//if (numOfPointLights > 0) pointLight_albedo(albedo, n, v, pointLight4_ss[0], pointLight4_color[0].rgb, pointLight4_falloff[0]);
	//if (numOfPointLights > 1) pointLight_albedo(albedo, n, v, pointLight4_ss[1], pointLight4_color[1].rgb, pointLight4_falloff[1]);
	//if (numOfPointLights > 2) pointLight_albedo(albedo, n, v, pointLight4_ss[2], pointLight4_color[2].rgb, pointLight4_falloff[2]);
	//if (numOfPointLights > 3) pointLight_albedo(albedo, n, v, pointLight4_ss[3], pointLight4_color[3].rgb, pointLight4_falloff[3]);

	//return vec4(shadow_intensity());
	//return vec4(abs(directionalLight_ss), 1.);
	return vec4(color * albedo, 1.);
}
vec4 final_render()
{
	vec2 incr = vec2(1. / luminance_size);
#if 0
	vec4 sum = vec4(0.);
	for (int i = 0; i < random_filter.length(); i++)
	{
		vec2 sample_coord = incr;
		sample_coord *= random_filter[i];
		sum += texture(luminance_map, tex_coord + sample_coord);
	}
	vec4 luminance = sum / float(random_filter.length());
#elif 0
	vec2 filter = vec2(cos(tex_coord.x), sin(tex_coord.x));
	vec2 sample_coord = vec2(
		(incr.x * filter.x) - (incr.y * filter.y), 
		(incr.x * filter.y) + (incr.y * filter.x)
	);
	vec4 luminance = vec4(tex_coord + sample_coord, 0., 1.);//texture(luminance_map, sample_coord);
#endif
	vec4 luminance = texture(luminance_map, tex_coord);
	vec4 base = texture(color_map, tex_coord);
	return base + luminance;
}

void main()
{
	switch (flag)
	{
		case 1:// rendering shadow map
		outColor = vec4(0., 0., 0., 1.);
		return;
		case 2:
		case 3:
		outColor = texture(color_map, tex_coord);
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
		case 32:
		outColor = final_render();
		return;

		default:
		outColor = main_render();
		return;
	}
}
