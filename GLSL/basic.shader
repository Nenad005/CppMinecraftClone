#FRAGMENT SHADER

#version 460 core

in vec2 vTexCoords;
uniform sampler2D u_Texture;
out vec4 outputColor;

void main()
{
	//outputColor = vec4(vTexCoords.y, vTexCoords.x, 0, 1);
	outputColor = texture(u_Texture, vTexCoords);
}

#VERTEX SHADER

#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aTexInfo;

uniform mat4 proj;
out vec2 vTexCoords;

void main()
{
	vTexCoords = vec2(mod(aTexInfo.z, 2), floor(aTexInfo.z / 2));
	//vTexCoords = vec2((mod(aTexInfo.x, 16) + mod(aTexInfo.y, 2)) / 16.0, (floor(aTexInfo.x / 16) + floor(aTexInfo.y / 2)) / 16.0);
	vTexCoords = vec2((aTexInfo.x/16.0 + mod(aTexInfo.z, 2) / 16.0 ), (aTexInfo.y / 16.0 + floor(aTexInfo.z / 2) / 16.0));
	gl_Position = proj * vec4(aPosition, 1);
}
