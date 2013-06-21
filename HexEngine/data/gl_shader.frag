#version 130

in vec2 tex_coord;
in vec3 vertex_ss;
in vec3 light_ss;
in vec3 view_ss;
in vec3 n;

out vec4 outColor;

void main()
{
	vec3 l = normalize(light_ss);
	
	float n_dot_l = dot(l, vec3(0., 0., 1.));

	outColor = vec4(vec3(n_dot_l), 1.);
	//outColor = vec4(tex_coord, 0., 1.);
	//outColor = vec4(abs(l), 1.);
}