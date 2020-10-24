#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in ivec3 aJointIds;
layout (location = 4) in vec3 aJointWeights;

out vec2 texCoord;
out vec3 fragPosition;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform bool hasJoints;
uniform mat4 jointTransforms[64];

void main()
{
	vec4 totalLocalPosition = vec4(0.0);
	vec4 totalNormal = vec4(0.0);

	if (hasJoints)
	{
		for (int i=0;i<3;++i)
		{
			vec4 localPosition = jointTransforms[aJointIds[i]] * vec4(aPosition, 1.0) ;
			totalLocalPosition += localPosition * aJointWeights[i];

			vec4 worldNormal = jointTransforms[aJointIds[i]] * vec4(aNormal, 0.0);
			totalNormal += worldNormal * aJointWeights[i];
		}
	}
	else
	{
		totalLocalPosition = vec4(aPosition, 1.0);
		totalNormal = vec4(aNormal, 0.0);
	}

	//gl_Position = projection * view * model * vec4(aPosition, 1.0);
	//texCoord = aTexCoord;
	//fragPosition = vec3(model * vec4(aPosition, 1.0));
	//normal = mat3(transpose(inverse(model))) * aNormal;  

	gl_Position = projection * view * model * totalLocalPosition;
	texCoord = aTexCoord;
	fragPosition = vec3(model * totalLocalPosition);
	normal = mat3(transpose(inverse(model))) * totalNormal.xyz;
}