#version 330 core //指明了运行版本及模式
//in表示从上一个阶段输入的数
//out表示这个阶段需要输出的数据
//uniform表示全局的数据（应用里也能读取和写入这个变量，这就是着色器和应用之间互通数据的方法）
//uniform变量在应用中访问需要一些特殊的访问方式:
//1、获取该变量在着色器程序中的位置。
//2、通过glUniform4fv函数对其进行赋值。
//主函数main中包含了处理过程，将处理结果赋值给输出变量

//指明了需要从上一个步骤中获取一个vec3类型的位置数据，数据位置在输入数据的0偏移位置（一块数据的头部）
layout (location = 0) in vec3 Vposition;

//指明了需要从上一个步骤中获取一个vec3类型的位置数据，数据位置在输入数据的1偏移位置（一块数据的头部）
layout (location = 1) in vec3 Vcolor;

//指明了需要从上一个步骤中获取一个vec3类型的位置数据，数据位置在输入数据的2偏移位置（一块数据的头部）
layout (location = 2) in vec2 aTexCoord;

out vec3 Tran_Color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
// 将顶点的位置直接赋值成输入的位置，gl_Position是一个内置的变量，用来表示顶点位置的。
	gl_Position = projection * view * model * vec4(Vposition, 1.0f);
    Tran_Color = Vcolor;
	TexCoord = aTexCoord;
}