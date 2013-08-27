#version 130

in vec4 vertex;
in vec2 uv;
in vec3 normal;
in vec3 tangent;
in vec3 binormal;

out vec2 tex_coord;
out vec4 vertex_ls;
out vec3 vertex_ss;
out vec3 view_ss;

out vec4 vertex_def;
out vec3 normal_def;

out vec3 directionalLight_ss;
out vec3 pointLight4_ss[%MaxPointLights%];

uniform mat4 os_to_ws;
uniform mat4 ws_to_cs;
uniform mat4 ws_to_ls;
uniform mat4 billboard;
uniform mat4 projection;

uniform vec3 directionalLight_ws;
uniform vec4 pointLight4_ws[%MaxPointLights%];
uniform int numOfPointLights;

uniform vec2 uv_repeat;
uniform vec2 uv_offset;
uniform bool isBillboard;

uniform int flag;

void main()
{
	if (flag > 10)
	{
		tex_coord = (vertex.xy * uv_repeat) + uv_offset;
		gl_Position = vec4((tex_coord * 2.) - 1., 0., 1.);
		return;
	}
	
	tex_coord = (uv * uv_repeat) + uv_offset;

	vec4 vertex_ws = os_to_ws * vertex;
	vec4 vertex_cs = ws_to_cs * vertex_ws;

	gl_Position = projection * vertex_cs;
	
	vertex_def = vertex_cs;
	vertex_ls = ws_to_ls * vertex_ws;

	if (flag == 1 || flag == 2) return;
	if (flag == 4) return;
	
	mat4 os_to_cs = ws_to_cs * os_to_ws;
	
	vec3 normal_cs =   normalize((os_to_cs * vec4(normal,   0.)).xyz);
	vec3 tangent_cs =  normalize((os_to_cs * vec4(tangent,  0.)).xyz);
	vec3 binormal_cs = normalize((os_to_cs * vec4(binormal, 0.)).xyz);

	normal_def = normal_cs;
	if (flag == 5) return;

	mat3 cs_to_ss = mat3(tangent_cs, binormal_cs, normal_cs);

	vertex_ss = vertex_cs.xyz * cs_to_ss;
	view_ss = vec3(0., 0., 0.) * cs_to_ss;

	vec3 directionalLight_cs = normalize((ws_to_cs * vec4(directionalLight_ws, 0.)).xyz);
	directionalLight_ss = -directionalLight_cs * cs_to_ss;
	
	if (numOfPointLights > 0) pointLight4_ss[0] = (ws_to_cs * pointLight4_ws[0]).xyz * cs_to_ss;
	if (numOfPointLights > 1) pointLight4_ss[1] = (ws_to_cs * pointLight4_ws[1]).xyz * cs_to_ss;
	if (numOfPointLights > 2) pointLight4_ss[2] = (ws_to_cs * pointLight4_ws[2]).xyz * cs_to_ss;
	if (numOfPointLights > 3) pointLight4_ss[3] = (ws_to_cs * pointLight4_ws[3]).xyz * cs_to_ss;
}
