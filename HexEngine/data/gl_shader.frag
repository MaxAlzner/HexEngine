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
uniform sampler2D depth_map;
uniform sampler2DShadow shadow_map;

uniform vec4 directionalLight_color;
uniform vec4 pointLight4_color[4];
uniform vec3 pointLight4_falloff[4];
uniform int numOfPointLights;

uniform float shadow_size;
uniform vec2[36] random_filter;

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

float average(vec3 color)
{
	return (color.r + color.g + color.b) / 3.;
}
float gr(float a, float b)
{
	return exp(1. - abs(a - b));
}

#define S(x, y, w) \
do {\
	float v = average(textureOffset(depth_map, tex_coord, ivec2(x, y)).rgb);\
	float b = gaussian_weights[w] * gr(p, v);\
	k += b;\
	g += textureOffset(color_map, tex_coord, ivec2(x, y)) * b;\
} while (false)
vec4 gaussian_blur()
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
	vec3 tex_shadow = vec3(vertex_ls.xyz / vertex_ls.w);
	tex_shadow.z -= 0.02;
	return texture(shadow_map, tex_shadow);
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

	if (flag == 2) return vec4(color, 1.);
	
	vec4 sample_normal = texture(normal_map, tex_coord);
	vec3 n = normalize((sample_normal.rgb * 2.) - 1.);
	vec3 v = normalize(view_ss);
	//n = vec3(0., 0., 1.);
	
	vec3 albedo = vec3(0.);

	directionalLight_albedo(albedo, n, v);
	
	if (numOfPointLights > 0) pointLight_albedo(albedo, n, v, pointLight4_ss[0], pointLight4_color[0].rgb, pointLight4_falloff[0]);
	if (numOfPointLights > 1) pointLight_albedo(albedo, n, v, pointLight4_ss[1], pointLight4_color[1].rgb, pointLight4_falloff[1]);
	if (numOfPointLights > 2) pointLight_albedo(albedo, n, v, pointLight4_ss[2], pointLight4_color[2].rgb, pointLight4_falloff[2]);
	if (numOfPointLights > 3) pointLight_albedo(albedo, n, v, pointLight4_ss[3], pointLight4_color[3].rgb, pointLight4_falloff[3]);

	//return vec4(shadow_intensity());
	//return vec4(abs(directionalLight_ss), 1.);
	return vec4(color * albedo, 1.);
}

void main()
{
	if (flag == 1) return;
	else if (flag > 2)
	{
		//outColor = vec4(tex_coord, 0., 1.);
		outColor = gaussian_blur();
		return;
	}
	else outColor = main_render();
}