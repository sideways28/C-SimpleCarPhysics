#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 matRotations;

out vec3 fragPosition;
out vec3 outNormal;
out vec2 texCoord;

void main()
{
	mat4 VM = view*model;
	mat4 PVM = projection * VM; 
	vec4 vertexPos = vec4(position, 1);

	gl_Position = PVM * vertexPos;
	gl_PointSize = gl_Position.z;
	
	fragPosition = vec3(model * vertexPos);
	outNormal = mat3(transpose(inverse(model))) * normal; //Rotation of normals when model rotates
	texCoord = uv;  
}