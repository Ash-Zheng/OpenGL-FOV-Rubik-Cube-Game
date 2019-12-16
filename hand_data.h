#define LEFT_HAND -1
#define RIGHT_HAND 1
#define EXTEND   true
#define SHRINK   false
const float oppo_size = 0.1f;
const float PI = 3.141592;
const float finger_res[2] = { -180.0f,180.0f };//最大下限--最大上限
const float max_ra[5] = { 50.0f,65.0f ,65.0f,65.0f,65.0f };      //移动角度上限
const float min_ra[5] = { 20.0f ,10.0f ,5.0f,10.0f,20.0f };      //移动角度下限
const float phi[5] = { 20.0f ,10.0f ,5.0f,10.0f,20.0f };//手指初始角度
const float wide[4] = { 0.821f * oppo_size,0.822f * oppo_size,0.823f * oppo_size,0.825f * oppo_size };
const float move_restrict[3] = { 30.0f,-65.5994f, -170.0f };//手掌竖向转动的目标角度，0逆时针，1标准位置，2顺时针
const float dial_restrict[2] = { 85.0f,10.1992f };//手掌横向转动的目标角度，0目标角度，1标准位置
const float hold_angle = 30.0f;

//手指长度单位          top                         middle                    root
const float finger_scale = 0.9* oppo_size;
const float len[15] = { 3.0f     *finger_scale,    4.09f  *finger_scale,     0.0f*finger_scale,//大拇指
					    2.5f*1.23f *finger_scale,    3.0f*1.23f*finger_scale,   3.0f*1.23f*finger_scale,//食指ָ
					    1.8f*1.354f  *finger_scale,  3.0f*1.354f*finger_scale,  3.0f*1.354f*finger_scale,//中指
					    1.8f*1.23f   *finger_scale,  3.0f*1.23f*finger_scale,    3.0f*1.23f*finger_scale,//无名指
					    1.8f   *finger_scale,       3.0f*finger_scale,        3.0f*finger_scale //小指
};

const float finger_relative_pos[15]{
	-1.0f* oppo_size,-3.5f* oppo_size, 5.0f* oppo_size,//大
	 0.0f* oppo_size, 0.0f* oppo_size, 3.0f* oppo_size,//食
	 0.0f* oppo_size, 0.0f* oppo_size, 0.0f* oppo_size,//中
	 0.0f* oppo_size, 0.0f* oppo_size,-3.0f* oppo_size,//无
	 0.0f* oppo_size, 0.0f* oppo_size,-5.0f* oppo_size //小
};

// 手指的顶点参数
// **大拇指** 
const float vertices_finger_dmz_top[] = {
	//位置                // 颜色
	  wide[0],  len[0],  wide[0],  1.0f, 0.0f, 0.0f,//正面--右上
	 -wide[0],  len[0],  wide[0],  0.0f, 1.0f, 0.0f,//正面--左上
	  wide[0], -len[0],  wide[0],  0.0f, 0.0f, 1.0f,//正面--右下
	  wide[0],  len[0], -wide[0],  1.0f, 1.0f, 0.0f,//反面--右上
	 -wide[0], -len[0],  wide[0],  1.0f, 0.0f, 1.0f,//正面--左下
	 -wide[0],  len[0], -wide[0],  0.0f, 1.0f, 1.0f,//反面--左上
	  wide[0], -len[0], -wide[0],  1.0f, 1.0f, 1.0f,//反面--右下
	 -wide[0], -len[0], -wide[0],  0.0f, 0.0f, 0.0f //反面--左下
};

const float vertices_finger_dmz_middle[] = {
	  wide[1],  len[1],  wide[1],  1.0f, 0.0f, 0.0f,
	 -wide[1],  len[1],  wide[1],  0.0f, 1.0f, 0.0f,
	  wide[1],   -0.08f,  wide[1],  0.0f, 0.0f, 1.0f,
	  wide[1],  len[1], -wide[1],  1.0f, 1.0f, 0.0f,
	 -wide[1],   -0.08f,  wide[1],  1.0f, 0.0f, 1.0f,
	 -wide[1],  len[1], -wide[1],  0.0f, 1.0f, 1.0f,
	  wide[1],   -0.08f, -wide[1],  1.0f, 1.0f, 1.0f,
	 -wide[1],   -0.08f, -wide[1],  0.0f, 0.0f, 0.0f
};

const float vertices_finger_dmz_root[] = {
	  wide[2],  len[2],  wide[2],  1.0f, 0.0f, 0.0f,
	 -wide[2],  len[2],  wide[2],  0.0f, 1.0f, 0.0f,
	  wide[2],   -0.0f,  wide[2],  0.0f, 0.0f, 1.0f,
	  wide[2],  len[2], -wide[2],  1.0f, 1.0f, 0.0f,
	 -wide[2],   -0.0f,  wide[2],  1.0f, 0.0f, 1.0f,
	 -wide[2],  len[2], -wide[2],  0.0f, 1.0f, 1.0f,
	  wide[2],   -0.0f, -wide[2],  1.0f, 1.0f, 1.0f,
	 -wide[2],   -0.0f, -wide[2],  0.0f, 0.0f, 0.0f
};

// **食指** 
const float vertices_finger_sz_top[] = {
	//位置                // 颜色
	  wide[0],  len[3],  wide[0],  1.0f, 0.0f, 0.0f,//正面--右上
	 -wide[0],  len[3],  wide[0],  0.0f, 1.0f, 0.0f,//正面--左上
	  wide[0], -len[3],  wide[0],  0.0f, 0.0f, 1.0f,//正面--右下
	  wide[0],  len[3], -wide[0],  1.0f, 1.0f, 0.0f,//反面--右上
	 -wide[0], -len[3],  wide[0],  1.0f, 0.0f, 1.0f,//正面--左下
	 -wide[0],  len[3], -wide[0],  0.0f, 1.0f, 1.0f,//反面--左上
	  wide[0], -len[3], -wide[0],  1.0f, 1.0f, 1.0f,//反面--右下
	 -wide[0], -len[3], -wide[0],  0.0f, 0.0f, 0.0f //反面--左下
};

const float vertices_finger_sz_middle[] = {
	  wide[1],  len[4],  wide[1],  1.0f, 0.0f, 0.0f,
	 -wide[1],  len[4],  wide[1],  0.0f, 1.0f, 0.0f,
	  wide[1],   -0.0f,  wide[1],  0.0f, 0.0f, 1.0f,
	  wide[1],  len[4], -wide[1],  1.0f, 1.0f, 0.0f,
	 -wide[1],   -0.0f,  wide[1],  1.0f, 0.0f, 1.0f,
	 -wide[1],  len[4], -wide[1],  0.0f, 1.0f, 1.0f,
	  wide[1],   -0.0f, -wide[1],  1.0f, 1.0f, 1.0f,
	 -wide[1],   -0.0f, -wide[1],  0.0f, 0.0f, 0.0f
};

const float vertices_finger_sz_root[] = {
	  wide[2],  len[5],  wide[2],  1.0f, 0.0f, 0.0f,
	 -wide[2],  len[5],  wide[2],  0.0f, 1.0f, 0.0f,
	  wide[2],   -0.0f,  wide[2],  0.0f, 0.0f, 1.0f,
	  wide[2],  len[5], -wide[2],  1.0f, 1.0f, 0.0f,
	 -wide[2],   -0.0f,  wide[2],  1.0f, 0.0f, 1.0f,
	 -wide[2],  len[5], -wide[2],  0.0f, 1.0f, 1.0f,
	  wide[2],   -0.0f, -wide[2],  1.0f, 1.0f, 1.0f,
	 -wide[2],   -0.0f, -wide[2],  0.0f, 0.0f, 0.0f
};

// **中指** 
const float vertices_finger_zz_top[] = {
	//位置                // 颜色
	  wide[0],  len[6],  wide[0],  1.0f, 0.0f, 0.0f,//正面--右上
	 -wide[0],  len[6],  wide[0],  0.0f, 1.0f, 0.0f,//正面--左上
	  wide[0], -len[6],  wide[0],  0.0f, 0.0f, 1.0f,//正面--右下
	  wide[0],  len[6], -wide[0],  1.0f, 1.0f, 0.0f,//反面--右上
	 -wide[0], -len[6],  wide[0],  1.0f, 0.0f, 1.0f,//正面--左下
	 -wide[0],  len[6], -wide[0],  0.0f, 1.0f, 1.0f,//反面--左上
	  wide[0], -len[6], -wide[0],  1.0f, 1.0f, 1.0f,//反面--右下
	 -wide[0], -len[6], -wide[0],  0.0f, 0.0f, 0.0f //反面--左下
};

const float vertices_finger_zz_middle[] = {
	  wide[1],  len[7],  wide[1],  1.0f, 0.0f, 0.0f,
	 -wide[1],  len[7],  wide[1],  0.0f, 1.0f, 0.0f,
	  wide[1],   -0.0f,  wide[1],  0.0f, 0.0f, 1.0f,
	  wide[1],  len[7], -wide[1],  1.0f, 1.0f, 0.0f,
	 -wide[1],   -0.0f,  wide[1],  1.0f, 0.0f, 1.0f,
	 -wide[1],  len[7], -wide[1],  0.0f, 1.0f, 1.0f,
	  wide[1],   -0.0f, -wide[1],  1.0f, 1.0f, 1.0f,
	 -wide[1],   -0.0f, -wide[1],  0.0f, 0.0f, 0.0f
};

const float vertices_finger_zz_root[] = {
	  wide[2],  len[8],  wide[2],  1.0f, 0.0f, 0.0f,
	 -wide[2],  len[8],  wide[2],  0.0f, 1.0f, 0.0f,
	  wide[2],   -0.0f,  wide[2],  0.0f, 0.0f, 1.0f,
	  wide[2],  len[8], -wide[2],  1.0f, 1.0f, 0.0f,
	 -wide[2],   -0.0f,  wide[2],  1.0f, 0.0f, 1.0f,
	 -wide[2],  len[8], -wide[2],  0.0f, 1.0f, 1.0f,
	  wide[2],   -0.0f, -wide[2],  1.0f, 1.0f, 1.0f,
	 -wide[2],   -0.0f, -wide[2],  0.0f, 0.0f, 0.0f
};

// **无名指** 
const float vertices_finger_wmz_top[] = {
	//位置                // 颜色
	  wide[0],  len[9],  wide[0],  1.0f, 0.0f, 0.0f,//正面--右上
	 -wide[0],  len[9],  wide[0],  0.0f, 1.0f, 0.0f,//正面--左上
	  wide[0], -len[9],  wide[0],  0.0f, 0.0f, 1.0f,//正面--右下
	  wide[0],  len[9], -wide[0],  1.0f, 1.0f, 0.0f,//反面--右上
	 -wide[0], -len[9],  wide[0],  1.0f, 0.0f, 1.0f,//正面--左下
	 -wide[0],  len[9], -wide[0],  0.0f, 1.0f, 1.0f,//反面--左上
	  wide[0], -len[9], -wide[0],  1.0f, 1.0f, 1.0f,//反面--右下
	 -wide[0], -len[9], -wide[0],  0.0f, 0.0f, 0.0f //反面--左下
};

const float vertices_finger_wmz_middle[] = {
	  wide[1],  len[10],  wide[1],  1.0f, 0.0f, 0.0f,
	 -wide[1],  len[10],  wide[1],  0.0f, 1.0f, 0.0f,
	  wide[1],   -0.0f,  wide[1],  0.0f, 0.0f, 1.0f,
	  wide[1],  len[10], -wide[1],  1.0f, 1.0f, 0.0f,
	 -wide[1],   -0.0f,  wide[1],  1.0f, 0.0f, 1.0f,
	 -wide[1],  len[10], -wide[1],  0.0f, 1.0f, 1.0f,
	  wide[1],   -0.0f, -wide[1],  1.0f, 1.0f, 1.0f,
	 -wide[1],   -0.0f, -wide[1],  0.0f, 0.0f, 0.0f
};

const float vertices_finger_wmz_root[] = {
	  wide[2],  len[11],  wide[2],  1.0f, 0.0f, 0.0f,
	 -wide[2],  len[11],  wide[2],  0.0f, 1.0f, 0.0f,
	  wide[2],   -0.0f,  wide[2],  0.0f, 0.0f, 1.0f,
	  wide[2],  len[11], -wide[2],  1.0f, 1.0f, 0.0f,
	 -wide[2],   -0.0f,  wide[2],  1.0f, 0.0f, 1.0f,
	 -wide[2],  len[11], -wide[2],  0.0f, 1.0f, 1.0f,
	  wide[2],   -0.0f, -wide[2],  1.0f, 1.0f, 1.0f,
	 -wide[2],   -0.0f, -wide[2],  0.0f, 0.0f, 0.0f
};

// **小拇指** 
const float vertices_finger_xmz_top[] = {
	//位置                // 颜色
	  wide[0],  len[12],  wide[0],  1.0f, 0.0f, 0.0f,//正面--右上
	 -wide[0],  len[12],  wide[0],  0.0f, 1.0f, 0.0f,//正面--左上
	  wide[0], -len[12],  wide[0],  0.0f, 0.0f, 1.0f,//正面--右下
	  wide[0],  len[12], -wide[0],  1.0f, 1.0f, 0.0f,//反面--右上
	 -wide[0], -len[12],  wide[0],  1.0f, 0.0f, 1.0f,//正面--左下
	 -wide[0],  len[12], -wide[0],  0.0f, 1.0f, 1.0f,//反面--左上
	  wide[0], -len[12], -wide[0],  1.0f, 1.0f, 1.0f,//反面--右下
	 -wide[0], -len[12], -wide[0],  0.0f, 0.0f, 0.0f //反面--左下
};

const float vertices_finger_xmz_middle[] = {
	  wide[1],  len[13],  wide[1],  1.0f, 0.0f, 0.0f,
	 -wide[1],  len[13],  wide[1],  0.0f, 1.0f, 0.0f,
	  wide[1],   -0.0f,  wide[1],  0.0f, 0.0f, 1.0f,
	  wide[1],  len[13], -wide[1],  1.0f, 1.0f, 0.0f,
	 -wide[1],   -0.0f,  wide[1],  1.0f, 0.0f, 1.0f,
	 -wide[1],  len[13], -wide[1],  0.0f, 1.0f, 1.0f,
	  wide[1],   -0.0f, -wide[1],  1.0f, 1.0f, 1.0f,
	 -wide[1],   -0.0f, -wide[1],  0.0f, 0.0f, 0.0f
};

const float vertices_finger_xmz_root[] = {
	  wide[2],  len[14],  wide[2],  1.0f, 0.0f, 0.0f,
	 -wide[2],  len[14],  wide[2],  0.0f, 1.0f, 0.0f,
	  wide[2],   -0.0f,  wide[2],  0.0f, 0.0f, 1.0f,
	  wide[2],  len[14], -wide[2],  1.0f, 1.0f, 0.0f,
	 -wide[2],   -0.0f,  wide[2],  1.0f, 0.0f, 1.0f,
	 -wide[2],  len[14], -wide[2],  0.0f, 1.0f, 1.0f,
	  wide[2],   -0.0f, -wide[2],  1.0f, 1.0f, 1.0f,
	 -wide[2],   -0.0f, -wide[2],  0.0f, 0.0f, 0.0f
};

//手掌
const float vertices_plate[] = {
	  wide[3],  0.0f* oppo_size,  4.5f* oppo_size,  1.0f, 0.0f, 0.0f,
	 -wide[3],  0.0f* oppo_size,  4.5f* oppo_size,  0.0f, 1.0f, 0.0f,
	  wide[3], -8.0f* oppo_size,  4.5f* oppo_size,  0.0f, 0.0f, 1.0f,
	  wide[3],  0.0f* oppo_size, -5.5f* oppo_size,  1.0f, 1.0f, 0.0f,
	 -wide[3], -8.0f* oppo_size,  4.5f* oppo_size,  1.0f, 0.0f, 1.0f,
	 -wide[3],  0.0f* oppo_size, -5.5f* oppo_size,  0.0f, 1.0f, 1.0f,
	  wide[3], -8.0f* oppo_size, -5.5f* oppo_size,  1.0f, 1.0f, 1.0f,
	 -wide[3], -8.0f* oppo_size, -5.5f* oppo_size,  0.0f, 0.0f, 0.0f
};
