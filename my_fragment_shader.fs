//vec3,vec4,��ʾ��3����4��float���ݵ�����
//�����������͵�����bvec1234������������������ivec1234
//�����޷���������������uvec1234������˫���ȸ�������������dvec1234
//��һ���׶�(vs)����������ͻ��Ϊ��һ���׶�(fs)�����������ֻҪ��������ͬ
#version 330 core
out vec4 Fcolor;

in vec3 Tran_Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
   Fcolor = texture(ourTexture, TexCoord) *(0.5f*vec4(1.0f,1.0f,1.0f, 0.0f)+0.5f*vec4(Tran_Color, 0.0f));
}
