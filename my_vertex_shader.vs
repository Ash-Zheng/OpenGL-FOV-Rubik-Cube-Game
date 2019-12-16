#version 330 core //ָ�������а汾��ģʽ
//in��ʾ����һ���׶��������
//out��ʾ����׶���Ҫ���������
//uniform��ʾȫ�ֵ����ݣ�Ӧ����Ҳ�ܶ�ȡ��д������������������ɫ����Ӧ��֮�以ͨ���ݵķ�����
//uniform������Ӧ���з�����ҪһЩ����ķ��ʷ�ʽ:
//1����ȡ�ñ�������ɫ�������е�λ�á�
//2��ͨ��glUniform4fv����������и�ֵ��
//������main�а����˴�����̣�����������ֵ���������

//ָ������Ҫ����һ�������л�ȡһ��vec3���͵�λ�����ݣ�����λ�����������ݵ�0ƫ��λ�ã�һ�����ݵ�ͷ����
layout (location = 0) in vec3 Vposition;

//ָ������Ҫ����һ�������л�ȡһ��vec3���͵�λ�����ݣ�����λ�����������ݵ�1ƫ��λ�ã�һ�����ݵ�ͷ����
layout (location = 1) in vec3 Vcolor;

//ָ������Ҫ����һ�������л�ȡһ��vec3���͵�λ�����ݣ�����λ�����������ݵ�2ƫ��λ�ã�һ�����ݵ�ͷ����
layout (location = 2) in vec2 aTexCoord;

out vec3 Tran_Color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
// �������λ��ֱ�Ӹ�ֵ�������λ�ã�gl_Position��һ�����õı�����������ʾ����λ�õġ�
	gl_Position = projection * view * model * vec4(Vposition, 1.0f);
    Tran_Color = Vcolor;
	TexCoord = aTexCoord;
}