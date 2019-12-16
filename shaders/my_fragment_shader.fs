//vec3,vec4,±íÊ¾ÓÐ3¸ö¡¢4¸öfloatÊý¾ÝµÄÏòÁ¿
//°üº¬²¼¶ûÀàÐÍµÄÏòÁ¿bvec1234£¬°üº¬ÕûÐÍÊýµÄÏòÁ¿ivec1234
//°üº¬ÎÞ·ûºÅÕûÐÍÊýµÄÏòÁ¿uvec1234£¬°üº¬Ë«¾«¶È¸¡µãÐÍÊýµÄÏòÁ¿dvec1234
//ÉÏÒ»¸ö½×¶Î(vs)µÄÊä³ö±äÁ¿¾Í»á³ÉÎªÏÂÒ»¸ö½×¶Î(fs)µÄÊäÈë±äÁ¿£¬Ö»Òª±äÁ¿ÃûÏàÍ¬
#version 330 core
out vec4 Fcolor;

in vec3 Tran_Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
   Fcolor = texture(ourTexture, TexCoord) *(1.0f*vec4(1.0f,1.0f,1.0f, 0.0f)+0.0f*vec4(Tran_Color, 0.0f));
}
