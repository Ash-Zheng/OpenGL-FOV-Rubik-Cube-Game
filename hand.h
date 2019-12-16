#ifndef HAND_H
#define HAND_H
//#define TEST_HAND_MOVE

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "hand_data.h"
#include "my_shader.h"
using namespace std;

#include <stack>
stack<int> action_stack;//¸´Ô­µÄÕ»,ÊäÈë¾ÍÊÇ·´ÏòµÄ¶¯×÷

bool in_a_restore;
int action = 0;


float move_speed; //ÒÆ¶¯ËÙ¶È
glm::vec3 left_hand_init_pos = glm::vec3(-11.8401f * oppo_size, 0.8f * oppo_size, -3.0f * oppo_size);//×óÊÖÕÆ³õÊ¼Î»ÖÃ
glm::vec3 right_hand_init_pos = glm::vec3(11.8401f * oppo_size, 0.95f * oppo_size, -3.0f * oppo_size);//ÓÒÊÖÕÆ³õÊ¼Î»ÖÃ
glm::vec3 left_hand_init_angle = glm::vec3(-65.5994f, -10.1992f, -7.7f);//×óÊÖÕÆ³õÊ¼½Ç¶È
glm::vec3 right_hand_init_angle = glm::vec3(-65.5994f, 10.1992f, 7.7f);//ÓÒÊÖÕÆ³õÊ¼½Ç¶È
glm::vec3 x_anis = glm::vec3(1.0f, 0.0f, 0.0f);//xÖá
glm::vec3 y_anis = glm::vec3(0.0f, 1.0f, 0.0f);//yÖá
glm::vec3 z_anis = glm::vec3(0.0f, 0.0f, 1.0f);//zÖá

glm::vec3 jiaodu2hudu(glm::vec3 angle)
{
	return glm::vec3(glm::radians(angle[0]), glm::radians(angle[1]), glm::radians(angle[2]));
}

enum Finger_type {
	DA_MZ,
	SHI_Z,
	ZHONG_Z,
	WU_MZ,
	XIAO_MZ,
	FPLATE
};
enum Dactylus_type {
	TOP,
	MIDDLE,
	ROOT,
	DPLATE
};

/* ------------ Ö¸½Ú ------------ */
class Dactylus {
private:
	Finger_type f_type;
	Dactylus_type d_type;
	glm::vec3 d_position;
	glm::mat4 d_model;
	glm::vec3 rotate_hudu;//Ðý×ªµÄ»¡¶È
public:
	Dactylus(Finger_type t1, Dactylus_type t2) {
		f_type = t1;
		d_type = t2;
		d_model = glm::mat4(1.0f);//³õÊ¼»¯²»Òª´í
	};
	~Dactylus() {};
	bool draw_a_dactylus(Shader* s);
	bool trans_a_dactylus(glm::vec3 pos);
	bool rotate_a_dactylus(float angle, glm::vec3 axis);
	void d_clear();
	bool fixed_the_anis(glm::vec3 jiaodu);

};

/* ------------ ÊÖÖ¸ ------------ */
class Finger
{
private:
	Finger_type type;
	Dactylus part_root;
	Dactylus part_middle;
	Dactylus part_top;
	glm::vec3 f_position;//ÊÖÖ¸Ïà¶ÔÊÖÕÆµÄÎ»ÖÃ
	glm::vec3 hf_position;//ÊÖÕÆµÄÎ»ÖÃ
	float part_len[3];//0--top,1--middle,2--root
	float f_phi;
	float alpha;
	bool flag_up; //ÔÊÐíÊÖÖ¸ÉìÖ±
	bool flag_down;//ÔÊÐíÊÖÖ¸ÊÕËõ
	float speed_coe;//¼ÓËÙÏµÊý
	//glm::vec3 f_angle;//Ðý×ªµÄ½Ç¶È
public:
	Finger(Finger_type in_type, glm::vec3 p, float f_p, int h_type) :
		type(in_type),
		part_root(type, ROOT),
		part_middle(type, MIDDLE),
		part_top(type, TOP)
	{
		flag_up = false;
		flag_down = true;
		speed_coe = 3.0f;//ÎÞËùÎ½¶àÉÙºóÃæ»áÖØÖÃ

		f_phi = f_p;
		hf_position = p;
		alpha = glm::radians(f_phi);
		f_position = glm::vec3(0.0f, 0.0f, 0.0f);
		switch (type) {
		case DA_MZ:
			f_position[0] += h_type * finger_relative_pos[0];
			f_position[1] += finger_relative_pos[1];
			f_position[2] += finger_relative_pos[2];
			part_len[0] = len[0];//top
			part_len[1] = len[1];//middle
			part_len[2] = len[2];//root
			break;
		case SHI_Z:
			f_position[0] += h_type * finger_relative_pos[3];
			f_position[1] += finger_relative_pos[4];
			f_position[2] += finger_relative_pos[5];
			part_len[0] = len[3];//top
			part_len[1] = len[4];//middle
			part_len[2] = len[5];//root
			break;
		case ZHONG_Z:
			f_position[0] += h_type * finger_relative_pos[6];
			f_position[1] += finger_relative_pos[7];
			f_position[2] += finger_relative_pos[8];
			part_len[0] = len[6];//top
			part_len[1] = len[7];//middle
			part_len[2] = len[8];//root
			break;
		case WU_MZ:
			f_position[0] += h_type * finger_relative_pos[9];
			f_position[1] += finger_relative_pos[10];
			f_position[2] += finger_relative_pos[11];
			part_len[0] = len[9];//top
			part_len[1] = len[10];//middle
			part_len[2] = len[11];//root
			break;
		case XIAO_MZ:
			f_position[0] += h_type * finger_relative_pos[12];
			f_position[1] += finger_relative_pos[13];
			f_position[2] += finger_relative_pos[14];
			part_len[0] = len[12];//top
			part_len[1] = len[13];//middle
			part_len[2] = len[14];//root
			break;
		};
	}
	~Finger() {};
	bool draw_a_finger(Shader* s);
	bool form_a_finger(glm::vec3 rotate_jiaodu, int which_hand, glm::vec3 another_movement = glm::vec3(0));//¸ù¾ÝÒÑÓÐÐÅÏ¢ÔÚÖ¸¶¨Î»ÖÃÉú³ÉÒ»¸ö³õÊ¼»¯µÄÊÖÖ¸
	bool rotate_a_finger(glm::vec3 jiaodu, int i);
	bool update_pos(glm::vec3 p);
	void f_clear();
	bool move_a_finger();//Í¨¹ýÉÏ²ãµ÷ÓÃ¶à´Î½øÈëÒÔÍê³ÉÒ»¸ö¶¯×÷
	bool move_a_finger_with_an_angle(float h_angle, float l_angle);//×Ô¼ºÉèÖÃÒÆ¶¯½Ç¶È£¬hÊÇÍäÇú³Ì¶ÈÉÏÏÞ£¬lÊÇÏÂÏÞ
	void change_direction(bool dir);//ÕæÎªÉìÕ¹ÊÖÖ¸£¬¼ÙÎªÊÕËõÊÖÖ¸
};

/* ------------ ÊÖ ------------ */
class Hand
{
private:
	int hand_type; //1--×óÊÖ£¬-1ÓÒÊÖ
	Finger f_dmz;
	Finger f_sz;
	Finger f_zz;
	Finger f_wmz;
	Finger f_xmz;
	Dactylus plate;
	glm::vec3 h_position;
	glm::vec3 h_angle;//0--xÖáÄæÊ±ÕëÐý×ª×ª½Ç¶È£»1--yÖáÄæÊ±ÕëÐý×ª×ª½Ç¶È£»2--zÖáÄæÊ±ÕëÐý×ª×ª½Ç¶È£»
	bool in_a_action; //¶¯×÷»¥³â²»ÔÊÐí¶à¸öÍ¬Ê±Ö´ÐÐ
	int state;        //¶¯×÷×´Ì¬»úµÄ×´Ì¬
	bool signal_finger[5]; //ÓÃÀ´Í³Ò»ÊÖÖ¸ÔË¶¯µÄ±êÖ¾

public:
	bool flag_enable[5]; //ÔÊÐíÊÖÖ¸ÒÆ¶¯
	bool flag_part[12];  //Å¡Ä§·½µ¥ÃæµÄ²Ù×÷£¬ÉÏÏÂÇ°ºó×óÓÒ£¬Ë³Äæ
	bool flag_all[6];    //ÉÏÏÂ×óÓÒ,¿ªÊ¼½áÊø
	Hand(glm::vec3 pos, glm::vec3 angle, int which_hand) :
		h_position(pos),
		f_dmz(DA_MZ, pos, phi[0], which_hand),
		f_sz(SHI_Z, pos, phi[1], which_hand),
		f_zz(ZHONG_Z, pos, phi[2], which_hand),
		f_wmz(WU_MZ, pos, phi[3], which_hand),
		f_xmz(XIAO_MZ, pos, phi[4], which_hand),
		plate(FPLATE, DPLATE)
	{
		for (int i = 0; i < 5; i++) {
			flag_enable[i] = false;
		}
		hand_type = which_hand;
		h_angle = angle;
		in_a_action = false;
		in_a_restore = false;
		state = 0;
	};
	~Hand() {};
	bool draw_a_hand(Shader* s);
	bool form_a_hand();//¸ù¾ÝÒÑÓÐÐÅÏ¢ÔÚÖ¸¶¨Î»ÖÃÉú³ÉÒ»¸ö³õÊ¼»¯µÄÊÖ
	void h_clear();
	bool check_flag(float deltaTime);
	void update_pos();
	void update_angle();//¸üÐÂ½Ç¶È
	//¼ì²éÊÇ·ñÔÚ¶¯×÷ÖÐ
	bool check_in_action() {
		return in_a_action;
	}
	//·Ö½â¶¯×÷
	bool start_action();//½øÐÐ×¼±¸¶¯×÷
	bool end_action();  //½áÊø£¬Ò²¿ÉÒÔÊÇ½øÐÐÄ§·½¸´Ô­
	bool sz_play(); //Ê³Ö¸²¦¶¯Ä§·½
	bool wmz_play();//ÎÞÃûÖ¸²¦¶¯Ä£·Â
	bool hold_rubiks_cube();//×¥×¡Ä§·½
	bool release_rubiks_cube();//ËÉ¿ªÄ§·½
	bool hand_rotate_c(float down_res);//ÊÖÊúÏòË³Ê±Õë×ª¶¯
	bool hand_rotate_a(float up_res);//ÊÖÊúÏòÄæÊ±Õë×ª¶¯
	bool hand_dial_c(float down_res);//ÊÖºáÏòË³Ê±Õë×ª¶¯
	bool hand_dial_a(float up_res);//ÊÖºáÏòÄæÊ±Õë×ª¶¯
	//Å¡Ä§·½µÄ¶¯×÷
	bool action_move_uc();//ÉÏÃæ-Ë³Ê±Õë 
	bool action_move_ua();//ÉÏÃæ-ÄæÊ±Õë
	bool action_move_dc();//ÏÂÃæ-Ë³Ê±Õë 
	bool action_move_da();//ÏÂÃæ-ÄæÊ±Õë
	bool action_move_fc();//Ç°Ãæ-Ë³Ê±Õë 
	bool action_move_fa();//Ç°Ãæ-ÄæÊ±Õë
	bool action_move_bc();//ºóÃæ-Ë³Ê±Õë 
	bool action_move_ba();//ºóÃæ-ÄæÊ±Õë
	bool action_move_lc();//×óÃæ-Ë³Ê±Õë 
	bool action_move_la();//×óÃæ-ÄæÊ±Õë
	bool action_move_rc();//ÓÒÃæ-Ë³Ê±Õë 
	bool action_move_ra();//ÓÒÃæ-ÄæÊ±Õë
	//Ä§·½ÕûÌåµÄ²Ù×÷¶¯×÷
	bool action_all_up();   //ÏòÉÏ×ª
	bool action_all_down(); //ÏòÏÂ×ª
	bool action_all_left(); //Ïò×ó×ª
	bool action_all_right();//ÏòÓÒ×ª


};

/* -----------------------Ö¸½ÚÊµÏÖº¯Êý----------------------- */
bool Dactylus::draw_a_dactylus(Shader* s)
{
	switch (f_type) {
	case DA_MZ:
		if (d_type == TOP)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_dmz_top), vertices_finger_dmz_top, GL_STATIC_DRAW);
		else if (d_type == MIDDLE)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_dmz_middle), vertices_finger_dmz_middle, GL_STATIC_DRAW);
		else if (d_type == ROOT)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_dmz_root), vertices_finger_dmz_root, GL_STATIC_DRAW);
		break;
	case SHI_Z:
		if (d_type == TOP)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_sz_top), vertices_finger_sz_top, GL_STATIC_DRAW);
		else if (d_type == MIDDLE)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_sz_middle), vertices_finger_sz_middle, GL_STATIC_DRAW);
		else if (d_type == ROOT)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_sz_root), vertices_finger_sz_root, GL_STATIC_DRAW);
		break;
	case ZHONG_Z:
		if (d_type == TOP)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_zz_top), vertices_finger_zz_top, GL_STATIC_DRAW);
		else if (d_type == MIDDLE)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_zz_middle), vertices_finger_zz_middle, GL_STATIC_DRAW);
		else if (d_type == ROOT)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_zz_root), vertices_finger_zz_root, GL_STATIC_DRAW);
		break;
	case WU_MZ:
		if (d_type == TOP)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_wmz_top), vertices_finger_wmz_top, GL_STATIC_DRAW);
		else if (d_type == MIDDLE)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_wmz_middle), vertices_finger_wmz_middle, GL_STATIC_DRAW);
		else if (d_type == ROOT)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_wmz_root), vertices_finger_wmz_root, GL_STATIC_DRAW);
		break;
	case XIAO_MZ:
		if (d_type == TOP)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_xmz_top), vertices_finger_xmz_top, GL_STATIC_DRAW);
		else if (d_type == MIDDLE)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_xmz_middle), vertices_finger_xmz_middle, GL_STATIC_DRAW);
		else if (d_type == ROOT)
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_finger_xmz_root), vertices_finger_xmz_root, GL_STATIC_DRAW);
		break;
	case FPLATE:
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_plate), vertices_plate, GL_STATIC_DRAW);
		break;
	}
	//cout << "ÕâÊÇ²»Õý³£µÄ£ºÊÖÖ¸=" << f_type << "Ö¸½ÚÊÇ="<<d_type<<"d_modelÊÇ£º" <<d_model[3][0] << "," <<d_model[3][1] << "," <<d_model[3][2] << "," <<d_model[3][3] << endl;
	s->setMat4("model", d_model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	return true;
}

inline bool Dactylus::trans_a_dactylus(glm::vec3 pos)
{
	d_model = glm::translate(d_model, pos);
	d_position = pos;
	return true;
}

inline bool Dactylus::rotate_a_dactylus(float angle, glm::vec3 axis)
{
	d_model = glm::rotate(d_model, angle, axis);
	return true;
}

inline void Dactylus::d_clear()
{
	d_model = glm::mat4(1.0f);
}
inline bool Dactylus::fixed_the_anis(glm::vec3 jiaodu)
{
	rotate_hudu = jiaodu2hudu(jiaodu);
	rotate_a_dactylus(rotate_hudu[1], y_anis);
	rotate_a_dactylus(rotate_hudu[2], z_anis);
	rotate_a_dactylus(rotate_hudu[0], x_anis);
	return true;
}
/* -----------------------ÊÖÖ¸ÊµÏÖº¯Êý----------------------- */
bool Finger::draw_a_finger(Shader* s) {
	part_top.draw_a_dactylus(s);
	part_middle.draw_a_dactylus(s);
	part_root.draw_a_dactylus(s);
	return true;
}

inline bool Finger::form_a_finger(glm::vec3 rotate_jiaodu, int which_hand, glm::vec3 another_movement)
{
	alpha = glm::radians(f_phi);
	//f_angle = rotate_jiaodu;
	//Ö¸½Ú1
	part_root.trans_a_dactylus(hf_position);
	//part_root.fixed_the_anis(f_angle);
	part_root.fixed_the_anis(rotate_jiaodu);
	part_root.trans_a_dactylus(f_position);
	part_root.rotate_a_dactylus(glm::radians(another_movement[1]), y_anis);
	part_root.rotate_a_dactylus(glm::radians(another_movement[0]), x_anis);
	part_root.rotate_a_dactylus(glm::radians(another_movement[2]), z_anis);
	//part_root.fixed_the_anis(another_movement);
	part_root.rotate_a_dactylus(which_hand * alpha, z_anis);

	//Ö¸½Ú2
	part_middle.trans_a_dactylus(hf_position);
	//part_middle.fixed_the_anis(f_angle);
	part_middle.fixed_the_anis(rotate_jiaodu);
	part_middle.trans_a_dactylus(f_position);
	part_middle.rotate_a_dactylus(glm::radians(another_movement[1]), y_anis);
	part_middle.rotate_a_dactylus(glm::radians(another_movement[0]), x_anis);
	part_middle.rotate_a_dactylus(glm::radians(another_movement[2]), z_anis);
	part_middle.rotate_a_dactylus(which_hand * alpha, z_anis);
	part_middle.trans_a_dactylus(glm::vec3(0, part_len[2], 0));
	part_middle.rotate_a_dactylus(which_hand * alpha, z_anis);

	//Ö¸½Ú3
	part_top.trans_a_dactylus(hf_position);
	//part_top.fixed_the_anis(f_angle);
	part_top.fixed_the_anis(rotate_jiaodu);
	part_top.trans_a_dactylus(f_position);
	part_top.rotate_a_dactylus(glm::radians(another_movement[1]), y_anis);
	part_top.rotate_a_dactylus(glm::radians(another_movement[0]), x_anis);
	part_top.rotate_a_dactylus(glm::radians(another_movement[2]), z_anis);
	part_top.rotate_a_dactylus(which_hand * alpha, z_anis);
	part_top.trans_a_dactylus(glm::vec3(0, part_len[2], 0));
	part_top.rotate_a_dactylus(which_hand * alpha, z_anis);
	part_top.trans_a_dactylus(glm::vec3(0, part_len[1], 0));
	part_top.rotate_a_dactylus(which_hand * alpha, z_anis);
	part_top.trans_a_dactylus(glm::vec3(0, part_len[0], 0));

	/*-----¾É·½·¨£¨ÌÔÌ­£©-----*/
	/*
	glm::vec3 tem_pos;
	tem_pos[0] = f_position[0] - part_len[1] * sin(2 * alpha);
	tem_pos[1] = f_position[1] + part_len[1] * cos(2 * alpha);
	tem_pos[2] = f_position[2];
	part_middle.trans_a_dactylus(tem_pos);
	part_middle.rotate_a_dactylus(-0.5f, glm::vec3(1, 0, 0));

	tem_pos[0] = tem_pos[0] - part_len[2] * sin(3 * alpha);
	tem_pos[1] = tem_pos[1] + part_len[2] * cos(3 * alpha);
	tem_pos[2] = tem_pos[2];
	part_top.trans_a_dactylus(tem_pos);
	part_top.rotate_a_dactylus(-0.5f, glm::vec3(1, 0, 0));

	//¿ØÖÆÖ¸½ÚÇãÐ±³Ì¶È
	part_root.rotate_a_dactylus(1 * alpha, glm::vec3(0, 0, 1));
	part_middle.rotate_a_dactylus(2 * alpha, glm::vec3(0, 0, 1));
	part_top.rotate_a_dactylus(3 * alpha, glm::vec3(0, 0, 1));
	*/
	return true;
}

inline bool Finger::update_pos(glm::vec3 p)
{
	hf_position = p;
	return true;
}

inline void Finger::f_clear()
{
	part_root.d_clear();
	part_middle.d_clear();
	part_top.d_clear();
}

inline bool Finger::move_a_finger()
{
	if (flag_up) {
		speed_coe = (max_ra[type] - f_phi) * 5 + 40.0f;
		f_phi -= move_speed * speed_coe;
	}
	else if (flag_down) {
		speed_coe = (max_ra[type] - f_phi) * 4 + 30.0f;
		f_phi += move_speed * speed_coe;
	}

	if (f_phi >= max_ra[type]) {
		flag_up = true;
		flag_down = false;
		return true;
	}
	if (f_phi <= min_ra[type]) {
		flag_up = false;
		flag_down = true;
		return true;
	}

	return false;
}

inline bool Finger::move_a_finger_with_an_angle(float h_angle, float l_angle)
{
	if (flag_up) {
		speed_coe = (h_angle - f_phi) * 5 + 40.0f;
		f_phi -= move_speed * speed_coe;
	}
	else if (flag_down) {
		speed_coe = (h_angle - f_phi) * 4 + 30.0f;
		f_phi += move_speed * speed_coe;
	}

	if (f_phi >= h_angle) {
		f_phi = h_angle;
		flag_up = true;
		flag_down = false;
		return true;
	}
	if (f_phi <= l_angle) {
		f_phi = l_angle;
		flag_up = false;
		flag_down = true;
		return true;
	}
	return false;
}

inline void Finger::change_direction(bool dir)
{
	if (dir) {
		flag_up = true;
		flag_down = false;
	}
	else {
		flag_up = false;
		flag_down = true;
	}
}

/* -----------------------ÊÖÕÆÊµÏÖº¯Êý----------------------- */
bool Hand::draw_a_hand(Shader* s) {
	f_dmz.draw_a_finger(s);
	f_sz.draw_a_finger(s);
	f_zz.draw_a_finger(s);
	f_wmz.draw_a_finger(s);
	f_xmz.draw_a_finger(s);
	plate.draw_a_dactylus(s);
	return true;
}

inline bool Hand::form_a_hand()
{
	update_angle();
	//cout << "ÊÖÀàÐÍ£º" << hand_type << ",½Ç¶È£º" << h_angle[0] << "--" << h_angle[1] << "--" << h_angle[2] << endl;
	//cout << "ÊÖÀàÐÍ£º" << hand_type << ",Î»ÖÃ£º" << h_position[0] << "--" << h_position[1] << "--" << h_position[2] << endl;
	f_dmz.form_a_finger(h_angle, hand_type, glm::vec3(90.0f, -hand_type * 90.0f, -hand_type * 90.0f));
	f_sz.form_a_finger(h_angle, hand_type);
	f_zz.form_a_finger(h_angle, hand_type);
	f_wmz.form_a_finger(h_angle, hand_type);
	f_xmz.form_a_finger(h_angle, hand_type);

	plate.trans_a_dactylus(h_position);
	plate.fixed_the_anis(h_angle);

	//plate.rotate_a_dactylus(1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
	return true;
}

inline void Hand::h_clear()
{
	f_dmz.f_clear();
	f_sz.f_clear();
	f_zz.f_clear();
	f_wmz.f_clear();
	f_xmz.f_clear();
	plate.d_clear();
}

inline bool Hand::check_flag(float deltaTime)
{
	move_speed = deltaTime;
	//ÊÖÖ¸ÒÆ¶¯
	if (0) {
		if (flag_enable[0]) {
			bool check = false;
			check = f_dmz.move_a_finger();
			if (check) {
				flag_enable[0] = false;
			}
		}
		if (flag_enable[1]) {
			bool check = false;
			check = f_sz.move_a_finger();
			if (check) {
				flag_enable[1] = false;
			}
		}
		if (flag_enable[2]) {
			bool check = false;
			check = f_zz.move_a_finger();
			if (check) {
				flag_enable[2] = false;
			}
		}
		if (flag_enable[3]) {
			bool check = false;
			check = f_wmz.move_a_finger();
			if (check) {
				flag_enable[3] = false;
			}
		}
		if (flag_enable[4]) {
			bool check = false;
			check = f_xmz.move_a_finger();
			if (check) {
				flag_enable[4] = false;
			}
		}
	}
	//Å¡Ä§·½µ¥ÃæµÄ¶¯×÷
	if (flag_part[0]) {
		bool check = false;
		check = action_move_uc();
		if (check) {
			flag_part[0] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(1);
		}
	}
	else if (flag_part[1]) {//ÉÏÄæ
		bool check = false;
		check = action_move_ua();
		if (check) {
			flag_part[1] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(0);
		}
	}
	else if (flag_part[2]) {//ÏÂË³
		bool check = false;
		check = action_move_dc();
		if (check) {
			flag_part[2] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(3);
		}
	}
	else if (flag_part[3]) {//ÏÂÄæ
		bool check = false;
		check = action_move_da();
		if (check) {
			flag_part[3] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(2);
		}
	}
	else if (flag_part[4]) {//Ç°Ë³
		bool check = false;
		check = action_move_fc();
		if (check) {
			flag_part[4] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(5);
		}
	}
	else if (flag_part[5]) {//Ç°Äæ
		bool check = false;
		check = action_move_fa();
		if (check) {
			flag_part[5] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(4);
		}
	}
	else if (flag_part[6]) {//ºóË³
		bool check = false;
		check = action_move_bc();
		if (check) {
			flag_part[6] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(7);
		}
	}
	else if (flag_part[7]) {//ºóÄæ
		bool check = false;
		check = action_move_ba();
		if (check) {
			flag_part[7] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(6);
		}
	}
	else if (flag_part[8]) {//×óË³
		bool check = false;
		check = action_move_lc();
		if (check) {
			flag_part[8] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(9);
		}
	}
	else if (flag_part[9]) {//×óÄæ
		bool check = false;
		check = action_move_la();
		if (check) {
			flag_part[9] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(8);
		}
	}
	else if (flag_part[10]) {//ÓÒË³
		bool check = false;
		check = action_move_rc();
		if (check) {
			flag_part[10] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(11);
		}
	}
	else if (flag_part[11]) {//ÓÒÄæ
		bool check = false;
		check = action_move_ra();
		if (check) {
			flag_part[11] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(10);
		}
	}
	//Å¡Ä§·½ÕûÌåµÄ¶¯×÷
	else if (flag_all[0]) {  //ÏòÉÏ×ª
		bool check = false;
		check = action_all_up();
		if (check) {
			flag_all[0] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(101);
		}
	}
	else if (flag_all[1]) {  //ÏòÏÂ×ª
		bool check = false;
		check = action_all_down();
		if (check) {
			flag_all[1] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(100);
		}
	}
	else if (flag_all[2]) {  //Ïò×ó×ª
		bool check = false;
		check = action_all_left();
		if (check) {
			flag_all[2] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(103);
		}
	}
	else if (flag_all[3]) {  //ÏòÓÒ×ª
		bool check = false;
		check = action_all_right();
		if (check) {
			flag_all[3] = false;
			in_a_action = false;
			if (!in_a_restore)
				action_stack.push(102);
		}
	}
	else if (flag_all[4]) {  //×¼±¸¶¯×÷£¬½øÈëÓÎÏ·
		bool check = false;
		check = start_action();
		if (check) {
			flag_all[4] = false;
			in_a_action = false;
		}
	}
	else if (flag_all[5]) {  //½áÊøÓÎÏ·£¬×Ô¶¯¸´Ô­
		bool check = false;
		check = end_action();
		if (check) {
			flag_all[5] = false;
			in_a_restore = false;
		}
	}

	return true;
}

inline void Hand::update_pos()
{
	h_position = (hand_type == RIGHT_HAND) ? right_hand_init_pos : left_hand_init_pos;
	f_dmz.update_pos(h_position);
	f_sz.update_pos(h_position);
	f_zz.update_pos(h_position);
	f_wmz.update_pos(h_position);
	f_xmz.update_pos(h_position);
}

inline void Hand::update_angle()
{
	h_angle = (hand_type == RIGHT_HAND) ? right_hand_init_angle : left_hand_init_angle;
}

inline bool Hand::start_action()
{
	bool flag_tem = hold_rubiks_cube();
	if (flag_tem) {
		return true;
	}
	return false;
}

inline bool Hand::end_action()
{
	static int state_tem_r = 0;
	static int state_tem_l = 0;
	bool flag_tem = false;
	if (hand_type == RIGHT_HAND) {
		switch (state_tem_r) {
		case 0:
			flag_tem = release_rubiks_cube();
			if (flag_tem)
				state_tem_r = 1;
			break;
		case 1:
			flag_tem = hold_rubiks_cube();
			if (flag_tem) {
				in_a_restore = true;
				state_tem_r = 2;
			}
			break;
		case 2:
			if (!in_a_restore)
				state_tem_r = 3;;
			break;
		case 3:
			flag_tem = release_rubiks_cube();
			if (flag_tem) {
				state_tem_r = 0;
				return true;
			}
			break;
		}
	}
	else {
		switch (state_tem_l) {
		case 0:
			flag_tem = release_rubiks_cube();
			if (flag_tem)
				state_tem_l = 1;
			break;
		case 1:
			flag_tem = hold_rubiks_cube();
			if (flag_tem)
				state_tem_l = 2;
			break;
		case 2:
			if (!in_a_restore)
				state_tem_l = 3;
			break;
		case 3:
			flag_tem = release_rubiks_cube();
			if (flag_tem) {
				state_tem_l = 0;
				return true;
			}
			break;
		}
	}
	return false;
}

inline bool Hand::sz_play()
{
	bool flag_tem = false;
	switch (state) {
	case 0:
		in_a_action = true;
		state = 1;
		f_sz.change_direction(SHRINK);
		break;
	case 1:
		flag_tem = f_sz.move_a_finger_with_an_angle(max_ra[SHI_Z], finger_res[0]);
		if (flag_tem) {
			state = 2;
		}
		break;
	case 2:
		f_sz.change_direction(EXTEND);
		state = 3;
		break;
	case 3:
		flag_tem = f_sz.move_a_finger_with_an_angle(finger_res[1], hold_angle);
		if (flag_tem) {
			state = 0;

			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::wmz_play()
{
	bool flag_tem = false;
	switch (state) {
	case 0:
		in_a_action = true;
		state = 1;
		f_wmz.change_direction(SHRINK);
		break;
	case 1:
		flag_tem = f_wmz.move_a_finger_with_an_angle(max_ra[WU_MZ], finger_res[0]);
		if (flag_tem) {
			state = 2;
		}
		break;
	case 2:
		f_wmz.change_direction(EXTEND);
		state = 3;
		break;
	case 3:
		flag_tem = f_wmz.move_a_finger_with_an_angle(finger_res[1], hold_angle);
		if (flag_tem) {
			state = 0;

			return true;
		}
		break;
	}
	return false;
	return false;
}

inline bool Hand::hold_rubiks_cube()
{
	static bool flag_tem_r[5] = { false };
	static bool flag_tem_l[5] = { false };
	switch (state) {
	case 0:
		in_a_action = true;
		state = 1;
		for (int i = 0; i < 5; i++) {
			if (hand_type == RIGHT_HAND)
				flag_tem_r[i] = false;
			else
				flag_tem_l[i] = false;
		}
		f_dmz.change_direction(SHRINK);
		f_sz.change_direction(SHRINK);
		f_zz.change_direction(SHRINK);
		f_wmz.change_direction(SHRINK);
		f_xmz.change_direction(SHRINK);
		break;
	case 1:
		if (hand_type == RIGHT_HAND) {
			if (!flag_tem_r[0])
				flag_tem_r[0] = f_dmz.move_a_finger_with_an_angle(hold_angle + 0.8f, finger_res[0]);
			if (!flag_tem_r[1])
				flag_tem_r[1] = f_sz.move_a_finger_with_an_angle(hold_angle - 5.0f, finger_res[0]);
			if (!flag_tem_r[2])
				flag_tem_r[2] = f_zz.move_a_finger_with_an_angle(hold_angle, finger_res[0]);
			if (!flag_tem_r[3])
				flag_tem_r[3] = f_wmz.move_a_finger_with_an_angle(hold_angle, finger_res[0]);
			if (!flag_tem_r[4])
				flag_tem_r[4] = f_xmz.move_a_finger_with_an_angle(hold_angle, finger_res[0]);
			if (flag_tem_r[0] && flag_tem_r[1] && flag_tem_r[2] && flag_tem_r[3] && flag_tem_r[4]) {
				state = 0;
				return true;
			}
		}
		else {
			if (!flag_tem_l[0])
				flag_tem_l[0] = f_dmz.move_a_finger_with_an_angle(hold_angle + 0.8f, finger_res[0]);
			if (!flag_tem_l[1])
				flag_tem_l[1] = f_sz.move_a_finger_with_an_angle(hold_angle, finger_res[0]);
			if (!flag_tem_l[2])
				flag_tem_l[2] = f_zz.move_a_finger_with_an_angle(hold_angle, finger_res[0]);
			if (!flag_tem_l[3])
				flag_tem_l[3] = f_wmz.move_a_finger_with_an_angle(hold_angle, finger_res[0]);
			if (!flag_tem_l[4])
				flag_tem_l[4] = f_xmz.move_a_finger_with_an_angle(hold_angle, finger_res[0]);
			if (flag_tem_l[0] && flag_tem_l[1] && flag_tem_l[2] && flag_tem_l[3] && flag_tem_l[4]) {
				state = 0;
				return true;
			}
		}
		break;
	}
	return false;
}

inline bool Hand::release_rubiks_cube()
{
	static bool flag_tem_r[5] = { false };
	static bool flag_tem_l[5] = { false };
	switch (state) {
	case 0:
		in_a_action = true;
		state = 1;
		for (int i = 0; i < 5; i++) {
			if (hand_type == RIGHT_HAND)
				flag_tem_r[i] = false;
			else
				flag_tem_l[i] = false;
		}
		f_dmz.change_direction(EXTEND);
		f_sz.change_direction(EXTEND);
		f_zz.change_direction(EXTEND);
		f_wmz.change_direction(EXTEND);
		f_xmz.change_direction(EXTEND);
		break;
	case 1:
		if (hand_type == RIGHT_HAND) {
			if (!flag_tem_r[0])
				flag_tem_r[0] = f_dmz.move_a_finger_with_an_angle(finger_res[1], min_ra[DA_MZ]);
			if (!flag_tem_r[1])
				flag_tem_r[1] = f_sz.move_a_finger_with_an_angle(finger_res[1], min_ra[SHI_Z]);
			if (!flag_tem_r[2])
				flag_tem_r[2] = f_zz.move_a_finger_with_an_angle(finger_res[1], min_ra[ZHONG_Z]);
			if (!flag_tem_r[3])
				flag_tem_r[3] = f_wmz.move_a_finger_with_an_angle(finger_res[1], min_ra[WU_MZ]);
			if (!flag_tem_r[4])
				flag_tem_r[4] = f_xmz.move_a_finger_with_an_angle(finger_res[1], min_ra[XIAO_MZ]);
			if (flag_tem_r[0] && flag_tem_r[1] && flag_tem_r[2] && flag_tem_r[3] && flag_tem_r[4]) {
				state = 0;
				return true;
			}
		}
		else {
			if (!flag_tem_l[0])
				flag_tem_l[0] = f_dmz.move_a_finger_with_an_angle(finger_res[1], min_ra[DA_MZ]);
			if (!flag_tem_l[1])
				flag_tem_l[1] = f_sz.move_a_finger_with_an_angle(finger_res[1], min_ra[SHI_Z]);
			if (!flag_tem_l[2])
				flag_tem_l[2] = f_zz.move_a_finger_with_an_angle(finger_res[1], min_ra[ZHONG_Z]);
			if (!flag_tem_l[3])
				flag_tem_l[3] = f_wmz.move_a_finger_with_an_angle(finger_res[1], min_ra[WU_MZ]);
			if (!flag_tem_l[4])
				flag_tem_l[4] = f_xmz.move_a_finger_with_an_angle(finger_res[1], min_ra[XIAO_MZ]);
			if (flag_tem_l[0] && flag_tem_l[1] && flag_tem_l[2] && flag_tem_l[3] && flag_tem_l[4]) {
				state = 0;
				return true;
			}
		}
		break;
	}
	return false;
}

inline bool Hand::hand_rotate_c(float down_res)
{
	if (hand_type == RIGHT_HAND) {
		float speed_coe = (right_hand_init_angle[0] - down_res) * 5 + 40.0f;
		right_hand_init_angle[0] -= move_speed * speed_coe;
		if (right_hand_init_angle[0] <= down_res)
			return true;
	}
	else {
		float speed_coe = (left_hand_init_angle[0] - down_res) * 5 + 40.0f;
		left_hand_init_angle[0] -= move_speed * speed_coe;
		if (left_hand_init_angle[0] <= down_res)
			return true;
	}
	return false;
}

inline bool Hand::hand_rotate_a(float up_res)
{
	if (hand_type == RIGHT_HAND) {
		float speed_coe = (up_res - right_hand_init_angle[0]) * 5 + 40.0f;
		right_hand_init_angle[0] += move_speed * speed_coe;
		if (right_hand_init_angle[0] >= up_res)
			return true;
	}
	else {
		float speed_coe = (up_res - left_hand_init_angle[0]) * 5 + 40.0f;
		left_hand_init_angle[0] += move_speed * speed_coe;
		if (left_hand_init_angle[0] >= up_res)
			return true;
	}
	return false;
}

inline bool Hand::hand_dial_c(float down_res)
{
	if (hand_type == RIGHT_HAND) {
		float speed_coe = (right_hand_init_angle[1] - down_res) * 5 + 40.0f;
		right_hand_init_angle[1] -= move_speed * speed_coe;
		if (right_hand_init_angle[1] <= down_res)
			return true;
	}
	else {
		float speed_coe = (left_hand_init_angle[1] - down_res) * 5 + 40.0f;
		left_hand_init_angle[1] -= move_speed * speed_coe;
		if (left_hand_init_angle[1] <= down_res)
			return true;
	}
	return false;
}

inline bool Hand::hand_dial_a(float up_res)
{
	if (hand_type == RIGHT_HAND) {
		float speed_coe = (up_res - right_hand_init_angle[1]) * 5 + 40.0f;
		right_hand_init_angle[1] += move_speed * speed_coe;
		if (right_hand_init_angle[1] >= up_res)
			return true;
	}
	else {
		float speed_coe = (up_res - left_hand_init_angle[1]) * 5 + 40.0f;
		left_hand_init_angle[1] += move_speed * speed_coe;
		if (left_hand_init_angle[1] >= up_res)
			return true;
	}
	return false;
}

inline bool Hand::action_move_uc()
{
	bool flag_tem = false;
	static int tem_state = 0;
	switch (tem_state) {
	case 0:
		state = 0;
		tem_state = 1;
		break;
	case 1:
		if (hand_type == LEFT_HAND)
			return true;
		if (!action) {
			action = 16;
			tem_state = 2;
		}
		break;
	case 2:
		flag_tem = sz_play();
		if (flag_tem)
		{
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_ua()
{
	bool flag_tem = false;
	static int tem_state = 0;
	switch (tem_state) {
	case 0:
		state = 0;
		tem_state = 1;
		break;
	case 1:
		if (hand_type == RIGHT_HAND) 
			return true;
		if (!action) {
			action = 9;
			tem_state = 2;
		}
		break;
	case 2:
		flag_tem = sz_play();
		if (flag_tem)
		{
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_dc()
{
	bool flag_tem = false;
	static int tem_state = 0;
	switch (tem_state) {
	case 0:
		if (hand_type == RIGHT_HAND) {
			return true;
		}
		else if (!action) {
			state = 0;
			action = 15;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == RIGHT_HAND)
			return true;
		flag_tem = wmz_play();
		if (flag_tem)
		{
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_da()
{
	bool flag_tem = false;
	static int tem_state = 0;
	switch (tem_state) {
	case 0:
		if (hand_type == LEFT_HAND) {
			return true;
		}
		else if (!action) {
			state = 0;
			action = 8;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == RIGHT_HAND)
			return true;
		flag_tem = wmz_play();
		if (flag_tem)
		{
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_fc()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		if (hand_type == LEFT_HAND)
			return true;
		if (hand_type == RIGHT_HAND) {
			in_a_action = true;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == LEFT_HAND)
			return true;
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 2;

		break;
	case 2:
		flag_tem = hand_rotate_a(move_restrict[0]);
		if (flag_tem)
			tem_state = 3;
		break;
	case 3:
		flag_tem = hold_rubiks_cube();
		if (flag_tem && !action) {
			action = 11;
			tem_state = 4;
		}
		break;
	case 4:
		flag_tem = sz_play();
		if (flag_tem)
			tem_state = 5;
		break;
	case 5:
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 6;
		break;
	case 6:
		flag_tem = hand_rotate_c(move_restrict[1]);
		if (flag_tem)
			tem_state = 7;
		break;
	case 7:
		flag_tem = hold_rubiks_cube();
		if (flag_tem) {
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_fa()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		if (hand_type == RIGHT_HAND)
			return true;
		if (hand_type == LEFT_HAND) {
			in_a_action = true;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == RIGHT_HAND)
			return true;
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 2;
		break;
	case 2:
		flag_tem = hand_rotate_a(move_restrict[0]);
		if (flag_tem)
			tem_state = 3;
		break;
	case 3:
		flag_tem = hold_rubiks_cube();
		if (flag_tem && !action)
		{
			tem_state = 4;
			action = 4;
		}
		break;
	case 4:
		flag_tem = sz_play();
		if (flag_tem)
			tem_state = 5;
		break;
	case 5:
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 6;
		break;
	case 6:
		flag_tem = hand_rotate_c(move_restrict[1]);
		if (flag_tem)
			tem_state = 7;
		break;
	case 7:
		flag_tem = hold_rubiks_cube();
		if (flag_tem) {
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_bc()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		if (hand_type == LEFT_HAND)
			return true;
		if (hand_type == RIGHT_HAND) {
			in_a_action = true;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == LEFT_HAND)
			return true;
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 2;

		break;
	case 2:
		flag_tem = hand_rotate_c(move_restrict[2]);
		if (flag_tem)
			tem_state = 3;
		break;
	case 3:
		flag_tem = hold_rubiks_cube();
		if (flag_tem && !action)
		{
			tem_state = 4;
			action = 5;
		}
		break;
	case 4:
		flag_tem = sz_play();
		if (flag_tem)
			tem_state = 5;
		break;
	case 5:
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 6;
		break;
	case 6:
		flag_tem = hand_rotate_a(move_restrict[1]);
		if (flag_tem)
			tem_state = 7;
		break;
	case 7:
		flag_tem = hold_rubiks_cube();
		if (flag_tem) {
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_ba()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		if (hand_type == RIGHT_HAND)
			return true;
		if (hand_type == LEFT_HAND) {
			in_a_action = true;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == RIGHT_HAND)
			return true;
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 2;

		break;
	case 2:
		flag_tem = hand_rotate_c(move_restrict[2]);
		if (flag_tem)
			tem_state = 3;
		break;
	case 3:
		flag_tem = hold_rubiks_cube();
		if (flag_tem && !action) {
			action = 12;
			tem_state = 4;
		}
		break;
	case 4:
		flag_tem = sz_play();
		if (flag_tem)
			tem_state = 5;
		break;
	case 5:
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 6;
		break;
	case 6:
		flag_tem = hand_rotate_a(move_restrict[1]);
		if (flag_tem)
			tem_state = 7;
		break;
	case 7:
		flag_tem = hold_rubiks_cube();
		if (flag_tem) {
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_lc()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		if (hand_type == RIGHT_HAND)
			return true;
		if (hand_type == LEFT_HAND && !action) {
			in_a_action = true;
			action = 6;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == RIGHT_HAND)
			return true;
		flag_tem = hand_rotate_a(move_restrict[0]);
		if (flag_tem)
			tem_state = 2;

		break;
	case 2:
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 3;
		break;
	case 3:
		flag_tem = hand_rotate_c(move_restrict[1]);
		if (flag_tem)
			tem_state = 4;
		break;
	case 4:
		flag_tem = hold_rubiks_cube();
		if (flag_tem) {
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_la()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		if (hand_type == RIGHT_HAND)
			return true;
		if (hand_type == LEFT_HAND && !action) {
			in_a_action = true;
			action = 13;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == RIGHT_HAND)
			return true;
		flag_tem = hand_rotate_c(move_restrict[2]);
		if (flag_tem)
			tem_state = 2;

		break;
	case 2:
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 3;
		break;
	case 3:
		flag_tem = hand_rotate_a(move_restrict[1]);
		if (flag_tem)
			tem_state = 4;
		break;
	case 4:
		flag_tem = hold_rubiks_cube();
		if (flag_tem) {
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_rc()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		if (hand_type == LEFT_HAND)
			return true;
		if (hand_type == RIGHT_HAND && !action) {
			in_a_action = true;
			action = 14;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == LEFT_HAND)
			return true;
		flag_tem = hand_rotate_c(move_restrict[2]);
		if (flag_tem)
			tem_state = 2;

		break;
	case 2:
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 3;
		break;
	case 3:
		flag_tem = hand_rotate_a(move_restrict[1]);
		if (flag_tem)
			tem_state = 4;
		break;
	case 4:
		flag_tem = hold_rubiks_cube();
		if (flag_tem) {
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_move_ra()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		if (hand_type == LEFT_HAND)
			return true;
		if (hand_type == RIGHT_HAND && !action) {
			in_a_action = true;
			action = 7;
			tem_state = 1;
		}
		break;
	case 1:
		if (hand_type == LEFT_HAND)
			return true;
		flag_tem = hand_rotate_a(move_restrict[0]);
		if (flag_tem)
			tem_state = 2;

		break;
	case 2:
		flag_tem = release_rubiks_cube();
		if (flag_tem)
			tem_state = 3;
		break;
	case 3:
		flag_tem = hand_rotate_c(move_restrict[1]);
		if (flag_tem)
			tem_state = 4;
		break;
	case 4:
		flag_tem = hold_rubiks_cube();
		if (flag_tem) {
			tem_state = 0;
			return true;
		}
		break;
	}
	return false;
}

inline bool Hand::action_all_up()
{
	static int tem_state_l = 0;
	static int tem_state_r = 0;
	bool flag_tem = false;
	if (hand_type == RIGHT_HAND) {
		switch (tem_state_r) {
		case 0:
			in_a_action = true;
			tem_state_r = 1;
			break;
		case 1:
			flag_tem = hand_rotate_c(move_restrict[2]);
			if (flag_tem)
				tem_state_r = 2;
			break;
		case 2:
			flag_tem = release_rubiks_cube();
			if (flag_tem)
				tem_state_r = 3;
			break;
		case 3:
			flag_tem = hand_rotate_a(move_restrict[1]);
			if (flag_tem)
				tem_state_r = 4;
			break;
		case 4:
			flag_tem = hold_rubiks_cube();
			if (flag_tem) {
				tem_state_r = 0;
				return true;
			}
			break;
		}
	}
	else {
		switch (tem_state_l) {
		case 0:
			in_a_action = true;
			tem_state_l = 1;
			break;
		case 1:
			flag_tem = hand_rotate_c(move_restrict[2]);
			if (flag_tem)
				tem_state_l = 2;
			break;
		case 2:
			flag_tem = release_rubiks_cube();
			if (flag_tem)
				tem_state_l = 3;
			break;
		case 3:
			flag_tem = hand_rotate_a(move_restrict[1]);
			if (flag_tem)
				tem_state_l = 4;
			break;
		case 4:
			flag_tem = hold_rubiks_cube();
			if (flag_tem) {
				tem_state_l = 0;
				return true;
			}
			break;
		}
	}
	return false;
}

inline bool Hand::action_all_down()
{
	static int tem_state_l = 0;
	static int tem_state_r = 0;
	bool flag_tem = false;
	if (hand_type == RIGHT_HAND) {
		switch (tem_state_r) {
		case 0:
			in_a_action = true;
			tem_state_r = 1;
			break;
		case 1:
			flag_tem = hand_rotate_a(move_restrict[0]);
			if (flag_tem)
				tem_state_r = 2;
			break;
		case 2:
			flag_tem = release_rubiks_cube();
			if (flag_tem)
				tem_state_r = 3;
			break;
		case 3:
			flag_tem = hand_rotate_c(move_restrict[1]);
			if (flag_tem)
				tem_state_r = 4;
			break;
		case 4:
			flag_tem = hold_rubiks_cube();
			if (flag_tem) {
				tem_state_r = 0;
				return true;
			}
			break;
		}
	}
	else {
		switch (tem_state_l) {
		case 0:
			in_a_action = true;
			tem_state_l = 1;
			break;
		case 1:
			flag_tem = hand_rotate_a(move_restrict[0]);
			if (flag_tem)
				tem_state_l = 2;
			break;
		case 2:
			flag_tem = release_rubiks_cube();
			if (flag_tem)
				tem_state_l = 3;
			break;
		case 3:
			flag_tem = hand_rotate_c(move_restrict[1]);
			if (flag_tem)
				tem_state_l = 4;
			break;
		case 4:
			flag_tem = hold_rubiks_cube();
			if (flag_tem) {
				tem_state_l = 0;
				return true;
			}
			break;
		}
	}
	return false;
}

inline bool Hand::action_all_left()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		in_a_action = true;
		tem_state = 1;
		break;
	case 1:
		if (hand_type == LEFT_HAND) {
			flag_tem = release_rubiks_cube();
			if (flag_tem)
				tem_state = 2;
		}
		break;
	case 2:
		if (hand_type == RIGHT_HAND) {
			flag_tem = hand_dial_a(hand_type * dial_restrict[0]);
			if (flag_tem)
				tem_state = 3;
		}
		break;
	case 3:
		if (hand_type == RIGHT_HAND) {
			flag_tem = hand_dial_c(hand_type * dial_restrict[1]);
			if (flag_tem)
				tem_state = 4;
		}
		break;
	case 4:
		if (hand_type == LEFT_HAND) {
			flag_tem = hold_rubiks_cube();
			if (flag_tem) {
				tem_state = 5;
				return true;
			}
		}
		break;
	case 5:
		tem_state = 0;
		return true;
		break;
	}
	return false;
}

inline bool Hand::action_all_right()
{
	static int tem_state = 0;
	bool flag_tem = false;
	switch (tem_state) {
	case 0:
		in_a_action = true;
		tem_state = 1;
		break;
	case 1:
		if (hand_type == RIGHT_HAND) {
			flag_tem = release_rubiks_cube();
			if (flag_tem)
				tem_state = 2;
		}
		break;
	case 2:
		if (hand_type == LEFT_HAND) {
			flag_tem = hand_dial_c(hand_type * dial_restrict[0]);
			if (flag_tem)
				tem_state = 3;
		}
		break;
	case 3:
		if (hand_type == LEFT_HAND) {
			flag_tem = hand_dial_a(hand_type * dial_restrict[1]);
			if (flag_tem)
				tem_state = 4;
		}
		break;
	case 4:
		if (hand_type == RIGHT_HAND) {
			flag_tem = hold_rubiks_cube();
			if (flag_tem) {
				tem_state = 5;
				return true;
			}
		}
		break;
	case 5://¾²Ì¬º¯Êý´¦ÀíÁ½Ö»ÊÖ£¬ÒªÍË³öÁ½´Î£¬·ÀÖ¹ËÀÑ­»·
		tem_state = 0;
		return true;
		break;
	}
	return false;
}




#endif
