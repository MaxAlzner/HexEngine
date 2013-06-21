#version 130

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 binormal;

out vec2 tex_coord;
out vec3 vertex_ss;
out vec3 light_ss;
out vec3 view_ss;
out vec3 n;

uniform mat4 os_to_ws;
uniform mat4 ws_to_cs;
uniform mat4 ws_to_ls;
uniform mat4 projection;

uniform vec3 directionalLight_ws;

void main()
{
	mat4 os_to_cs = ws_to_cs * os_to_ws;
	mat3 os_to_cs_normal = mat3(os_to_cs);
	mat3 ws_to_cs_normal = mat3(ws_to_cs);

	vec3 normal_cs = normalize(os_to_cs_normal * normal);
	/*vec3 tangent_cs;

	vec3 c1 = cross(normal_cs, vec3(0., 0., 1.));
	vec3 c2 = cross(normal_cs, vec3(0., 1., 0.));
	if (length(c1) > length(c2)) 
		tangent_cs = c1;
	else 
		tangent_cs = c2;
	vec3 binormal_cs = normalize(cross(normal_cs, tangent_cs));*/

	vec3 tangent_cs = normalize(os_to_cs_normal * tangent);
	vec3 binormal_cs = normalize(os_to_cs_normal * binormal);

	mat3 cs_to_ss = mat3(
		tangent_cs, binormal_cs, normal_cs
	);

	vec4 vertex_cs = os_to_cs * vertex;

	tex_coord = uv;
	vertex_ss = vertex_cs.xyz * cs_to_ss;
	light_ss = -(ws_to_cs_normal * directionalLight_ws) * cs_to_ss;
	view_ss = vec3(0., 0., 1.) * cs_to_ss;

	gl_Position = projection * vertex_cs;
}