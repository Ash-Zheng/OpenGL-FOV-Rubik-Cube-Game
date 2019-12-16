//vec3,vec4,表示有3个、4个float数据的向量
//包含布尔类型的向量bvec1234，包含整型数的向量ivec1234
//包含无符号整型数的向量uvec1234，包含双精度浮点型数的向量dvec1234
//上一个阶段(vs)的输出变量就会成为下一个阶段(fs)的输入变量，只要变量名相同
#version 330 core
out vec4 Fcolor;

in vec3 Tran_Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
   Fcolor = texture(ourTexture, TexCoord) *(0.5f*vec4(1.0f,1.0f,1.0f, 0.0f)+0.5f*vec4(Tran_Color, 0.0f));
}
