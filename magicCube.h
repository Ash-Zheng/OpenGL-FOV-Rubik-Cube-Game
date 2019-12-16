#pragma once
#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "my_shader.h"
#include "camera.h"

#include <iostream>
#include "stb_image.h"

#include <stack>
extern int action;
class magicCube
{
private:
	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// 四盏灯的位置
	glm::vec3 lightPos1 = glm::vec3(0.0f, 5.0f, 0.0f);
	glm::vec3 lightPos2 = glm::vec3(5.0f, 0.0f, 0.0f);
	glm::vec3 lightPos3 = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 lightPos4 = glm::vec3(-5.0f, 3.0f, -5.0f);

	//方块位置变换矩阵。储存魔方的27个小方块的位置和朝向。
	glm::mat4 cubePosChanged[27]{
		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),
		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),
		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),

		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),
		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),
		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),

		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),
		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f),
		glm::mat4(1.0f),glm::mat4(1.0f),glm::mat4(1.0f)
	};

	// 着色器
	Shader cubeShader = Shader("shaders/cubeShader.vs", "shaders/cubeShader.fs");

	// VBO和VAO
	unsigned int cubeVBO, cubeVAO;

	// 工具数组。把魔方初始化为 3 x 3 x 3。可以不用管.
	glm::vec3 cubePos[27] = {
		glm::vec3(-1.0f,-1.0f,-1.0f),
		glm::vec3(0.0f,-1.0f,-1.0f),
		glm::vec3(1.0f,-1.0f,-1.0f),
		glm::vec3(-1.0f,0.0f,-1.0f),
		glm::vec3(0.0f,0.0f,-1.0f),
		glm::vec3(1.0f,0.0f,-1.0f),
		glm::vec3(-1.0f,1.0f,-1.0f),
		glm::vec3(0.0f,1.0f,-1.0f),
		glm::vec3(1.0f,1.0f,-1.0f),

		glm::vec3(-1.0f,-1.0f,0.0f),
		glm::vec3(0.0f,-1.0f,0.0f),
		glm::vec3(1.0f,-1.0f,0.0f),
		glm::vec3(-1.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),
		glm::vec3(-1.0f,1.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(1.0f,1.0f,0.0f),

		glm::vec3(-1.0f,-1.0f,1.0f),
		glm::vec3(0.0f,-1.0f,1.0f),
		glm::vec3(1.0f,-1.0f,1.0f),
		glm::vec3(-1.0f,0.0f,1.0f),
		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(1.0f,0.0f,1.0f),
		glm::vec3(-1.0f,1.0f,1.0f),
		glm::vec3(0.0f,1.0f,1.0f),
		glm::vec3(1.0f,1.0f,1.0f)
	};

	//防止方块位置飞出。由于浮点数计算误差，多次旋转后可能出现错位情况。此函数将修复错位情况。
	void repair();

	//贴图
	unsigned int texture1;
	unsigned int texture2;

	// 还原魔方的栈
	std::stack<int> stk;
public:
	// 初始化
	magicCube();

	// 绘制魔方
	void showMagicCube(Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);

	// 释放空间
	~magicCube();

	// 控制魔方
	void MCProcessInput(GLFWwindow* window, float deltaTime);

	// 翻转魔方
	bool overTurn(GLFWwindow* window, float angle)
	{
		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1, 1, 0));
		for (int i = 0; i < 27; i++)
		{
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 180.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

	bool UpTurn(GLFWwindow* window, float angle)
	{

		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(1, 0, 0));
		for (int i = 0; i < 27; i++)
		{
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}


	bool DownTurn(GLFWwindow* window, float angle)
	{
		
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1, 0, 0));
		for (int i = 0; i < 27; i++)
		{
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

	// 魔方整体右转 
	bool rightTurn(GLFWwindow* window, float angle)
	{

		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(0, 1, 0));
		for (int i = 0; i < 27; i++)
		{
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

	// 魔方整体左转 
	bool leftTurn(GLFWwindow* window, float angle)
	{
		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));
		for (int i = 0; i < 27; i++)
		{
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}
	//旋转顶层,z==1
	bool z1Turn(GLFWwindow* window, float angle)
	{
		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));
		for (int i = 0; i < 27; i++)
		{
			if (abs(cubePosChanged[i][3].z - 1) > 0.1)
				continue;
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

	//旋转底层,z==-1
	bool z_1Turn(GLFWwindow* window, float angle)
	{
		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));
		for (int i = 0; i < 27; i++)
		{
			if (abs(cubePosChanged[i][3].z + 1) > 0.1)
				continue;
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

	//旋转x轴靠近玩家的侧面，x==-1,"左面"。
	bool x_1Turn(GLFWwindow* window, float angle)
	{
		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1, 0, 0));
		for (int i = 0; i < 27; i++)
		{
			if (abs(cubePosChanged[i][3].x + 1) > 0.1)
				continue;
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

	//旋转x轴远离玩家的侧面，x==1,"左面的对面"。
	bool x1Turn(GLFWwindow* window, float angle)
	{
		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1, 0, 0));
		for (int i = 0; i < 27; i++)
		{
			if (abs(cubePosChanged[i][3].x - 1) > 0.1)
				continue;
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

	//旋转y轴靠近玩家的侧面，y==-1,"右面"。
	bool y_1Turn(GLFWwindow* window, float angle)
	{
		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));
		for (int i = 0; i < 27; i++)
		{
			if (abs(cubePosChanged[i][3].y + 1) > 0.1)
				continue;
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

	//旋转y轴远离玩家的侧面，y==1,"右面的对面"。
	bool y1Turn(GLFWwindow* window, float angle)
	{
		// 已经转过的角度
		static float cnt = 0;

		glm::mat4 tmp = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));
		for (int i = 0; i < 27; i++)
		{
			if (abs(cubePosChanged[i][3].y - 1) > 0.1)
				continue;
			cubePosChanged[i] = tmp * cubePosChanged[i];
		}
		cnt += abs(angle);
		if (cnt >= 90.0)
		{
			cnt = 0;
			repair();
			return 1;
		}
		else
			return 0;
	}

};
