#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) centroid in vec4 vaColor;
layout(location = 1) centroid in vec4 vaTexCoord;

layout(set = 1, binding = 1) uniform sampler2D uTexture0;

layout(location = 0) out vec4 o_Color;

void main()
{
	o_Color = vaColor * texture(uTexture0, vaTexCoord.xy);

	if(o_Color.w <= 0.0)
		discard;
}
