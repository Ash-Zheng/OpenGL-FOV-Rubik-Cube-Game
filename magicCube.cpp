#include"magicCube.h"

magicCube::magicCube()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//float cubeVertices[] = {
	//	// positions
	//	-0.5f, -0.5f, -0.5f,
	//	-0.5f, -0.5f, 0.5f,
	//	-0.5f, 0.5f, -0.5f,
	//	-0.5f,  0.5f, 0.5f,
	//	0.5f, -0.5f, -0.5f,
	//	0.5f, -0.5f, 0.5f,
	//	0.5f, 0.5f, -0.5f,
	//	0.5f,  0.5f, 0.5f,

	//};
	//unsigned int cubeIndices[6][6] = {  // note that we start from 0!
	//	0, 1, 2,  // ×ó
	//	1, 2, 3,   // 

	//	0, 1, 4,  // Ç°
	//	1, 4, 5,   // 

	//	4, 5, 6,  // ÓÒ
	//	5, 6, 7,   // 

	//	2, 3, 6,  // ºó
	//	3, 6, 7,   // 

	//	1, 3, 5,  // ÉÏ
	//	3, 5, 7,   // 

	//	0, 2, 4,  // ÏÂ
	//	2, 4, 6   // 
	//};
	float cubeVertices[] = {
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f
	};

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	/*for (int i = 0; i < 6; i++)
		glGenBuffers(1, &cubeEBO[i]);*/
	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*for (int i = 0; i < 6; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices[i]), cubeIndices[i], GL_STATIC_DRAW);
	}*/
	for (int i = 0; i < 27; i++)//³õÊ¼»¯Î»ÖÃ¾ØÕó
	{
		cubePosChanged[i] = glm::translate(glm::mat4(1.0f), cubePos[i]);

	}
	//////////////////////////////////////////////////////////////////////////////////////////////ÌùÍ¼

	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE0); // ÔÚ°ó¶¨ÎÆÀíÖ®Ç°ÏÈ¼¤»îÎÆÀíµ¥Ôª
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Îªµ±Ç°°ó¶¨µÄÎÆÀí¶ÔÏóÉèÖÃ»·ÈÆ¡¢¹ýÂË·½Ê½
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ¼ÓÔØ²¢Éú³ÉÎÆÀí
	int width, height, nrChannels;
	unsigned char* data = stbi_load("resource/surface.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1); // ÔÚ°ó¶¨ÎÆÀíÖ®Ç°ÏÈ¼¤»îÎÆÀíµ¥Ôª
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Îªµ±Ç°°ó¶¨µÄÎÆÀí¶ÔÏóÉèÖÃ»·ÈÆ¡¢¹ýÂË·½Ê½
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ¼ÓÔØ²¢Éú³ÉÎÆÀí
	//int width, height, nrChannels;
	data = stbi_load("resource/test.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void magicCube::showMagicCube(Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
{
	cubeShader.use();

	cubeShader.setInt("ourTexture1", 0);
	cubeShader.setInt("ourTexture2", 1);


	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.8f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	cubeShader.setMat4("projection", projection);
	cubeShader.setMat4("view", view);

	// ÉèÖÃÉãÏñ»úÎ»ÖÃ
	cubeShader.setVec3("viewPos", camera.Position);

	// light properties
	// Ò»¹²4ÕµµÆ£¬×óÓÒÉÏ¸÷Ò»Õµ£¬Ô¶´¦ÉÏ·½Ò²ÓÐÒ»Õµ¡£µÆ¹âÎª°×É«¡£
	cubeShader.setVec3("light1.position", lightPos1);
	cubeShader.setVec3("light1.ambient", glm::vec3(1.0f));
	cubeShader.setVec3("light1.diffuse", glm::vec3(1.0f));
	cubeShader.setVec3("light1.specular", glm::vec3(1.0f));

	cubeShader.setVec3("light2.position", lightPos2);
	cubeShader.setVec3("light2.ambient", glm::vec3(1.0f));
	cubeShader.setVec3("light2.diffuse", glm::vec3(1.0f));
	cubeShader.setVec3("light2.specular", glm::vec3(1.0f));

	cubeShader.setVec3("light3.position", lightPos3);
	cubeShader.setVec3("light3.ambient", glm::vec3(1.0f));
	cubeShader.setVec3("light3.diffuse", glm::vec3(1.0f));
	cubeShader.setVec3("light3.specular", glm::vec3(1.0f));

	cubeShader.setVec3("light4.position", lightPos4);
	cubeShader.setVec3("light4.ambient", glm::vec3(1.0f));
	cubeShader.setVec3("light4.diffuse", glm::vec3(1.0f));
	cubeShader.setVec3("light4.specular", glm::vec3(1.0f));

	glActiveTexture(GL_TEXTURE0); // ÔÚ°ó¶¨ÎÆÀíÖ®Ç°ÏÈ¼¤»îÎÆÀíµ¥Ôª
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1); // ÔÚ°ó¶¨ÎÆÀíÖ®Ç°ÏÈ¼¤»îÎÆÀíµ¥Ôª
	glBindTexture(GL_TEXTURE_2D, texture2);
	glBindVertexArray(cubeVAO);

	// Ä§·½ÓÉ27¸öÐ¡·½¿é×é³É£¬Ã¿´Î»æÖÆ1¸ö£¬ÖØ¸´»æÖÆ27´Î¡£
	for (int i = 0; i < 27; i++)
	{
		/*
		²Î¿¼´úÂë
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0, 0, 0));
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		*/
		glm::mat4 model = cubePosChanged[i];
		/*model = glm::translate(glm::mat4(1.0f), glm::vec3(-4.5f, 0.0f, -3.0f))*model;

		model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * model;
		model = glm::rotate(glm::mat4(1.0f), glm::radians(-10.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * model;*/
		model = glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * model;

		//model = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * model;
		model = glm::scale(glm::mat4(1.0f), glm::vec3(0.3, 0.3, 0.3)) * model;
		cubeShader.setMat4("model", model);

		// Ã¿¸öÐ¡·½¿éÓÐ6¸öÃæ£¬Ã¿´Î»æÖÆ1Ãæ£¬ÖØ¸´»æÖÆ6´Î¡£
		for (int j = 0; j < 6; j++)
		{
			// ÉèÖÃÃ¿¸öÃæµÄÑÕÉ«ºÍ·¨ÏßÏòÁ¿
			glm::vec3 rgb;
			glm::vec3 aNormal;
			if (cubePos[i][0] == -1 && j == 0)
				rgb = { 0.0,0.0,1.0 };
			else if (cubePos[i][1] == -1 && j == 1)
				rgb = { 1.0,0.0,0.0 };
			else if (cubePos[i][0] == 1 && j == 2)
				rgb = { 0.0,1.0,0.0 };
			else if (cubePos[i][1] == 1 && j == 3)
				rgb = { 1.0,0.5,0.0 };
			else if (cubePos[i][2] == 1 && j == 4)
				rgb = { 1.0,1.0,0.0 };
			else if (cubePos[i][2] == -1 && j == 5)
				rgb = { 1.0,1.0,1.0 };
			else
				rgb = { 0.0,0.0,0.0 };

			switch (j)
			{
			case 0:aNormal = { -1.0,0.0,0.0 }; break;
			case 1:aNormal = { 0.0,-1.0,0.0 }; break;
			case 2:aNormal = { 1.0,0.0,0.0 }; break;
			case 3:aNormal = { 0.0,1.0,0.0 }; break;
			case 4:aNormal = { 0.0,0.0,1.0 }; break;
			case 5:aNormal = { 0.0,0.0,-1.0 }; break;
			default:
				break;
			}
			cubeShader.setVec3("aNormal", aNormal);

			// material properties
			// ²é±íµÃ£¬Ä§·½ÎªËÜÁÏ²ÄÖÊ¡£
			cubeShader.setVec3("material.ambient", rgb * glm::vec3(0.1f));
			cubeShader.setVec3("material.diffuse", rgb * glm::vec3(0.5f));
			cubeShader.setVec3("material.specular", 0.55f, 0.55f, 0.55f);
			cubeShader.setFloat("material.shininess", 16.0f);

			// »­³ö27¸öÐ¡·½¿éµÄÆäÖÐ1¸öµÄ1¸öÃæ¡£ÖØ¸´6´Î¿ÉÒÔ»­³öÒ»¸öÐ¡·½¿é£¬ÔÙÕûÌåÖØ¸´27´Î¿ÉÒÔ»­ÍêÕû¸öÄ§·½¡£
			glDrawArrays(GL_TRIANGLES, 6 * j, 6);
		}
	}
}

magicCube::~magicCube()
{
	glDeleteVertexArrays(1, &cubeVAO);
}

//·ÀÖ¹·½¿éÎ»ÖÃ·É³ö¡£ÓÉÓÚ¸¡µãÊý¼ÆËãÎó²î£¬¶à´ÎÐý×ªºó¿ÉÄÜ³öÏÖ´íÎ»Çé¿ö¡£´Ëº¯Êý½«ÐÞ¸´´íÎ»Çé¿ö¡£
void magicCube::repair()
{
	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
			{
				if (abs(cubePosChanged[i][j][k] - 1.0) < 0.5)
					cubePosChanged[i][j][k] = 1;
				else if (abs(cubePosChanged[i][j][k]) < 0.5)
					cubePosChanged[i][j][k] = 0;
				else if (abs(cubePosChanged[i][j][k] + 1.0) < 0.5)
					cubePosChanged[i][j][k] = -1;
			}
	return;
}

// ´Ëº¯ÊýÓÃÀ´²Ù×÷Ä§·½¡£·Ç³£³óÂªµ«ÊÇÄÜÓÃ¡£
void magicCube::MCProcessInput(GLFWwindow* window, float deltaTime)
{

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	// Ã¿ÃëÏÞÖÆ60Ö¡£¬ÆäÊµÎÞËùÎ½À²
	//if (deltaTime < 0.016)
	//	return;
	lastFrame = currentFrame;

	//ÊÇ·ñ·´ÏòÐý×ª¡£°´×¡Tab¼ü¼´¿É·´ÏòÐý×ª
	static int anti = 0;

	// ËÙ¶È
	static float rSpeed = 0;

	// ¼ÆÊ±Æ÷
	static float timer = 0;

	// ×Ô¶¯¸´Ô­Ä§·½
	static int autoRecover = 0;

	static int busy = 0;

	deltaTime *= 2;
	if (autoRecover == 1)
		deltaTime *= 2;
	timer += deltaTime;
	if (timer < 0.5)
		rSpeed = deltaTime * (timer * timer) * 1080;
	else
		rSpeed = deltaTime * ((1 - timer) * (1 - timer)) * 1080;



	switch (busy)
	{
	case 0:
		anti = 1;
		rSpeed = 0;
		timer = 0;
		if (action == 1)
			busy = 1;
		else if (action == 10)
			busy = 10;
		else if (action == 2)
			busy = 2;
		else if (action == 3)
			busy = 3;
		else if (action == 4)
			busy = 4;
		else if (action == 5)
			busy = 5;
		else if (action == 6)
			busy = 6;
		else if (action == 7)
			busy = 7;
		else if (action == 8)
			busy = 8;
		else if (action == 9)
			busy = 9;
		else if (action == 11)
			busy = 11;
		else if (action == 12)
			busy = 12;
		else if (action == 13)
			busy = 13;
		else if (action == 14)
			busy = 14;
		else if (action == 15)
			busy = 15;
		else if (action == 16)
			busy = 16;
		else if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
			autoRecover = 1;
		if (busy != 0 && autoRecover == 0)
			stk.push(anti * busy);
		break;

	case 1:if (UpTurn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 2:if (leftTurn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 3:if (rightTurn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 4:if (z1Turn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 5:if (z_1Turn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 6:if (x_1Turn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 7:if (x1Turn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 8:if (y_1Turn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 9:if (y1Turn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
		   break;
	case 10:if (DownTurn(window, rSpeed * anti) == 1)
	{
		busy = 0;
		action = 0;
	}
			break;
	case 11:if (z1Turn(window, rSpeed * anti * (-1)) == 1)
	{
		busy = 0;
		action = 0;
	}
			break;
	case 12:if (z_1Turn(window, rSpeed * anti * (-1)) == 1)
	{
		busy = 0;
		action = 0;
	}
			break;
	case 13:if (x_1Turn(window, rSpeed * anti * (-1)) == 1)
	{
		busy = 0;
		action = 0;
	}
			break;
	case 14:if (x1Turn(window, rSpeed * anti * (-1)) == 1)
	{
		busy = 0;
		action = 0;
	}
			break;
	case 15:if (y_1Turn(window, rSpeed * anti * (-1)) == 1)
	{
		busy = 0;
		action = 0;
	}
			break;
	case 16:if (y1Turn(window, rSpeed * anti * (-1)) == 1)
	{
		busy = 0;
		action = 0;
	}
			break;
	default:
		break;
	}

//	if (autoRecover == 1 && busy == 0)
//	{
//		busy = -stk.top();
//		stk.pop();
//		anti = busy > 1 ? 1 : -1;
//		busy = abs(busy);
//
//		rSpeed = 0;
//		timer = 0;
//		if (stk.empty())
//			autoRecover = 0;
//	}


	return;
}
