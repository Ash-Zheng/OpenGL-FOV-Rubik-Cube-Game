#define ENABLE_CAMERA
#include "glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
//#include "my_shader.h"
#include "declaration.h"
#include "Camera.h"
#include "hand.h"
#include"magicCube.h" 

//°ó¶¨ÊÖµÄVAO
void bind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int& texture);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proInput(GLFWwindow* window);
//Êó±ê»Øµ÷
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
//¹öÂÖ»Øµ÷
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadCubemap(vector<std::string> faces);

//¸´Ô­Ïà¹Øº¯Êý
void cube_restore();
bool active_next_action();
bool check_end();


#ifdef ENABLE_CAMERA
float deltaTime = 0.0f;  //Á½Ö¡Ö®¼äµÄ¼ä¸ôÊ±¼ä
float lastFrame = 0.0f;  //ÉÏÒ»Ö¡»æÖÆµÄÊ±¼ä

float lastX = 400, lastY = 300;
bool firstMouse = true;
float yaw = 0.0f, pitch = 0.0f;


//ÉãÏñ»ú
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
#endif

//¶¨ÒåÊÖ
Hand left_hand(left_hand_init_pos, left_hand_init_angle, LEFT_HAND);
Hand right_hand(right_hand_init_pos, right_hand_init_angle, RIGHT_HAND);


int main()
{
	//³õÊ¼»¯glfw²¢ÇÒÉèÖÃ°æ±¾
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //Ö¸¶¨openglµÄÖ÷°æ±¾ºÅ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //Ö¸¶¨openglµÄ¸±°æ±¾ºÅ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//Ê¹ÓÃopenglµÄºËÐÄÄ£Ê½£¨¿É±à³ÌäÖÈ¾¹ÜµÀµÄÄ£Ê½£©

	//´´½¨glfw´°¿Ú
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, " rubiks cube ", NULL, NULL); //´´½¨´°¿Ú
	if (window == NULL)
	{
		std::cout << "´íÎó£ºGLFW´°¿Ú´´½¨Ê§°Ü\n" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);  //½«´°¿ÚµÄÉÏÏÂÎÄ»·¾³ÇÐ»»³Éµ±Ç°Ö÷Ïß³ÌµÄÉÏÏÂÎÄ»·¾³
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //×¢²á´°¿Ú»Øµ÷º¯Êý
#ifdef ENABLE_CAMERA
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //ÉèÖÃÊäÈëÄ£Ê½
	glfwSetCursorPosCallback(window, mouse_callback);  //×¢²áÊó±ê»Øµ÷º¯Êý
	glfwSetScrollCallback(window, scroll_callback);    //×¢²á¹öÂÖ»Øµ÷º¯Êý
#endif


	//³õÊ¼»¯glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "´íÎó£ºGLADÖ¸Õë¼ÓÔØÊ§°Ü\n" << std::endl;
		return -1;
	}

	//¿ªÆôÉî¶È²âÊÔ
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
// ------------------------------------
	Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float skyboxVertices[] = {
		// positions
		-0.8f,  0.8f, -0.8f,
		-0.8f, -0.8f, -0.8f,
		 0.8f, -0.8f, -0.8f,
		 0.8f, -0.8f, -0.8f,
		 0.8f,  0.8f, -0.8f,
		-0.8f,  0.8f, -0.8f,

		-0.8f, -0.8f,  0.8f,
		-0.8f, -0.8f, -0.8f,
		-0.8f,  0.8f, -0.8f,
		-0.8f,  0.8f, -0.8f,
		-0.8f,  0.8f,  0.8f,
		-0.8f, -0.8f,  0.8f,

		 0.8f, -0.8f, -0.8f,
		 0.8f, -0.8f,  0.8f,
		 0.8f,  0.8f,  0.8f,
		 0.8f,  0.8f,  0.8f,
		 0.8f,  0.8f, -0.8f,
		 0.8f, -0.8f, -0.8f,

		-0.8f, -0.8f,  0.8f,
		-0.8f,  0.8f,  0.8f,
		 0.8f,  0.8f,  0.8f,
		 0.8f,  0.8f,  0.8f,
		 0.8f, -0.8f,  0.8f,
		-0.8f, -0.8f,  0.8f,

		-0.8f,  0.8f, -0.8f,
		 0.8f,  0.8f, -0.8f,
		 0.8f,  0.8f,  0.8f,
		 0.8f,  0.8f,  0.8f,
		-0.8f,  0.8f,  0.8f,
		-0.8f,  0.8f, -0.8f,

		-0.8f, -0.8f, -0.8f,
		-0.8f, -0.8f,  0.8f,
		 0.8f, -0.8f, -0.8f,
		 0.8f, -0.8f, -0.8f,
		-0.8f, -0.8f,  0.8f,
		 0.8f, -0.8f,  0.8f
	};


	// skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// load textures
	// -------------
	vector<std::string> faces
	{
		"resource/skybox1/front.jpg",
		"resource/skybox1/left.jpg",
		"resource/skybox1/top.jpg",
		"resource/skybox1/bottom.jpg",
		"resource/skybox1/back.jpg",
		"resource/skybox1/right.jpg"
	};
	unsigned int cubemapTexture = loadCubemap(faces);

	// ½¨Á¢²¢±àÒë×ÅÉ«³ÌÐò
	Shader shader("shaders/my_vertex_shader.vs", "shaders/my_fragment_shader.fs");

	/*          ³õÊ¼»¯vao¡¢vbo¡¢ebo          */
	//°ó¶¨VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);//Éú³ÉÎ¨Ò»id
	glBindVertexArray(VAO);

	//°ó¶¨VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);//Éú³ÉÎ¨Ò»id
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//Ö¸¶¨Îª¶¥µã»º´æ¶ÔÏó
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//½«¶¥µãÊý¾Ý¸´ÖÆµ½VBO

	// ×ø±êÊôÐÔ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//ÈÃ¶¥µãÊôÐÔÉúÐ§
	glEnableVertexAttribArray(0);
	// ÑÕÉ«ÊôÐÔ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//ÎÆÀíÊôÐÔ
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//°ó¶¨EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);//Éú³ÉÎ¨Ò»id
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//Ö¸¶¨ÎªÔªËØ»º´æ¶ÔÏó
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_d), index_d, GL_STATIC_DRAW);//¸´ÖÆË÷ÒýÊý¾Ýµ½EBOÖÐ


	//Éú³ÉÎÆÀí
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Îªµ±Ç°°ó¶¨µÄÎÆÀí¶ÔÏóÉèÖÃ»·ÈÆ¡¢¹ýÂË·½Ê½
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ¼ÓÔØ²¢Éú³ÉÎÆÀí
	int width, height, nrChannels;
	unsigned char* data = stbi_load("th.jpg", &width, &height, &nrChannels, 0);
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


	magicCube mc;
	// Ñ­»·äÖÈ¾
	while (!glfwWindowShouldClose(window))
	{
		// Çå³ý»º³å¡¢Çå³ýÉî¶È¼ì²â»º³å¡¢Çå³ý²¢ÇÒÉèÖÃµ×É«
		glClearColor(0.7f, 0.7f, 0.8f, 1.0f);   //ÉèÖÃÇåÆÁÑÕÉ«
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //ÇåÆÁ
#ifdef ENABLE_CAMERA
		//¼ÆËãÉÏÒ»Ö¡Ê±¼ä

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (in_a_restore)
			deltaTime = deltaTime * (1 + 1*action_stack.size()/10); //speed
#endif
		// ¼ì²éÊÇ·ñÍË³ö
		proInput(window);
		mc.MCProcessInput(window, deltaTime);
		// ¿ªÆô×ÅÉ«Æ÷
		shader.use();

		// ½¨Á¢×ø±ê±ä»»¾ØÕó

		//ÉèÖÃ¹Û²ì±ä»»¾ØÕó
		glm::mat4 projection; //¶¨Òå±ä»»¾ØÕó
		//ÉèÖÃÍ¶Ó°±ä»»¾ØÕó--Í¸ÊÓÍ¶Ó°£¨perspective£©
		//glm::radians¶¨ÒåÁËFOVµÄ½Ç¶È£»
		//µÚ¶þ¸ö²ÎÊý¶¨ÒåÁËÆÁÄ»¿í¸ß±È£¬Õâ¸öÖµ»áÓ°ÏìÏÔÊ¾µ½´°¿ÚÖÐµÄÎïÌåÊÇÔ­ÑùÏÔÊ¾»¹ÊÇ±»À­Éì£»
		//µÚÈý¸ö²ÎÊý½ü²Ã¼ôÃæ£¬µÚËÄ¸ö²ÎÊýÊÇÔ¶²Ã¼ôÃæ
		projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.8f, 100.0f);

		glm::mat4 view; //¹Û²ì±ä»»¾ØÕó
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -50.0f));
#ifdef ENABLE_CAMERA
		view = camera.GetViewMatrix();//glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
#endif

		// µÃµ½×ÅÉ«Æ÷ÖÐµÄÈ«¾Ö±äÁ¿
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		// ÉèÖÃäÖÈ¾µÄÊý¾Ý£¬²¢ÇÒ¿ªÊ¼äÖÈ¾
		bind(VAO, VBO, EBO, texture);
		// ¼ÓÔØ²¢Éú³ÉÎÆÀí
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
		/*glBindVertexArray(VAO);*/

		if (in_a_restore)
			cube_restore();

		right_hand.check_flag(deltaTime);
		right_hand.form_a_hand();
		right_hand.draw_a_hand(&shader);
		right_hand.h_clear();

		left_hand.check_flag(deltaTime);
		left_hand.form_a_hand();
		left_hand.draw_a_hand(&shader);
		left_hand.h_clear();

		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.use();
		glm::mat4 model = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		model = glm::scale(model, glm::vec3(5.0f));
		skyboxShader.setMat4("model", model);

		glm::mat3 newView = glm::mat3(camera.GetViewMatrix());
		view = glm::mat4(newView); //±£³ÖÉãÏñ»úÔÚboxÖÐÐÄ
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
		skyboxShader.setMat4("view", view);
		skyboxShader.setMat4("projection", projection);

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default


		mc.showMagicCube(camera, WINDOW_WIDTH, WINDOW_HEIGHT);

		// ¿ªÆôglfwµÄË«»º³åäÖÈ¾
		glfwSwapBuffers(window);  //½«ÏÔÊ¾»º´æºÍÀëÆÁ»º´æ½»»»
		glfwPollEvents();         //¼ì²éÊÇ·ñÓÐÊÂ¼þ´¥·¢£¨Êó±êÊÂ¼þ¡¢¼üÅÌÊÂ¼þ£©
	}

	// ½áÊøºóÉ¾³ýÊý¾Ý¼°»º³åÊý¾Ý
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// ½áÊø
	glfwTerminate();
	return 0;
}

// µ±ÊÓ¿Ú´óÐ¡±ä»¯£¬Ôò½øÐÐµ÷ÓÃ²¢ÖØÐÂÉèÖÃ£¬Ê×´Î´ò¿ª´°¿ÚÒ²»áµ÷ÓÃ
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);//µ÷ÕûopenglµÄÊÓ¿ÚÇøÓò
}

// ¼ì²éÊÇ·ñÍË³ö£¬¼üÅÌ°´¼ü´óÐ´Q¼´¿ÉÍË³ö
void proInput(GLFWwindow* window)
{
	static bool flag_start = false;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //¼ì²éÊÇ·ñ°´ÏÂQ¼ü
		glfwSetWindowShouldClose(window, true);        //ÉèÖÃÍË³ö´°¿Ú

#ifdef ENABLE_CAMERA
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(Q, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(E, deltaTime);
	else
		camera.ProcessKeyboard(NONE, deltaTime);
#endif

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !flag_start) {//¿ªÊ¼¾ÍÐ÷¶¯×÷
		left_hand.flag_all[4] = true;
		right_hand.flag_all[4] = true;
		flag_start = true;
	}
	if (!left_hand.check_in_action() && !right_hand.check_in_action() && flag_start) {

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {//¿ªÊ¼¾ÍÐ÷¶¯×÷
			left_hand.flag_all[5] = true;
			right_hand.flag_all[5] = true;
			flag_start = false;
		}
		//Ã¿Ò»Ãæµ¥¶À¶¯×÷
		//ÉÏÃæ
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {//Ë³Ê±Õë²¦¶¯ 
			right_hand.flag_part[0] = true;
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {//ÄæÊ±Õë²¦¶¯ 
			left_hand.flag_part[1] = true;
		}
		//ÏÂÃæ
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {//Ë³Ê±Õë²¦¶¯ 
			right_hand.flag_part[2] = true;
		}
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {//ÄæÊ±Õë²¦¶¯ 
			left_hand.flag_part[3] = true;
		}
		//Ç°Ãæ
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {//Ë³Ê±Õë²¦¶¯ 
			left_hand.flag_part[4] = true;
			right_hand.flag_part[4] = true;
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {//ÄæÊ±Õë²¦¶¯ 
			left_hand.flag_part[5] = true;
			right_hand.flag_part[5] = true;
		}
		//ºóÃæ
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {//Ë³Ê±Õë²¦¶¯ 
			left_hand.flag_part[6] = true;
			right_hand.flag_part[6] = true;
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {//ÄæÊ±Õë²¦¶¯ 
			left_hand.flag_part[7] = true;
			right_hand.flag_part[7] = true;
		}
		//×óÃæ
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {//Ë³Ê±Õë²¦¶¯ 
			left_hand.flag_part[8] = true;
			right_hand.flag_part[8] = true;
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {//ÄæÊ±Õë²¦¶¯ 
			left_hand.flag_part[9] = true;
			right_hand.flag_part[9] = true;
		}
		//ÓÒÃæ
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {//Ë³Ê±Õë²¦¶¯ 
			left_hand.flag_part[10] = true;
			right_hand.flag_part[10] = true;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {//ÄæÊ±Õë²¦¶¯ 
			left_hand.flag_part[11] = true;
			right_hand.flag_part[11] = true;
		}

		//Õë¶ÔÄ§·½ÕûÌå¶¯×÷
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {//ÕûÌåÏò×ó
			left_hand.flag_all[2] = true;
			right_hand.flag_all[2] = true;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {//ÕûÌåÏòÓÒ
			left_hand.flag_all[3] = true;
			right_hand.flag_all[3] = true;
		}

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {//ÕûÌåÏòÉÏ
			left_hand.flag_all[0] = true;
			right_hand.flag_all[0] = true;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {//ÕûÌåÏòÏÂ
			left_hand.flag_all[1] = true;
			right_hand.flag_all[1] = true;
		}
	}
#ifdef TEST_HAND_MOVE
	//Ðý×ª
	if (!flag_start) {
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)//ÈÆÊÖxÖáÄæÊ±Õë
			right_hand_init_angle[0] += 0.1f;

		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)//ÈÆÊÖxÖáË³Ê±Õë
			right_hand_init_angle[0] -= 0.1f;

		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)//ÈÆÊÖyÖáÄæÊ±Õë
			right_hand_init_angle[1] += 0.1f;

		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)//ÈÆÊÖyÖáË³Ê±Õë
			right_hand_init_angle[1] -= 0.1f;

		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)//ÈÆÊÖzÖáÄæÊ±Õë
			right_hand_init_angle[2] += 0.1f;

		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)//ÈÆÊÖzÖáË³Ê±Õë
			right_hand_init_angle[2] -= 0.1f;

		//Æ½ÒÆ
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)//ÊÖÏòÉÏÒÆ¶¯
			right_hand_init_pos[1] += 0.02f;

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)//ÊÖÏòÏÂÒÆ¶¯
			right_hand_init_pos[1] -= 0.02f;

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)//ÊÖÏò×óÒÆ¶¯
			right_hand_init_pos[0] -= 0.02f;

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)//ÊÖÏòÓÒÒÆ¶¯
			right_hand_init_pos[0] += 0.02f;

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)//ÊÖÏò½ü´¦ÒÆ¶¯
			right_hand_init_pos[2] += 0.02f;

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)//ÊÖÏòÔ¶´¦ÒÆ¶¯
			right_hand_init_pos[2] -= 0.02f;

		right_hand.update_pos();
		right_hand.update_angle();
	}


#endif // TEST_HAND_MOVE

}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
#ifdef ENABLE_CAMERA
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = lastX - xPos;	//ÔÚ´°¿ÚÖÐ£¬×ó±ßµÄ×ø±êÐ¡ÓÚÓÒ±ßµÄ×ø±ê£¬¶øÎÒÃÇÐèÒªÒ»¸öÕýµÄ½Ç¶È
	float yoffset = lastY - yPos;	//ÔÚ´°¿ÚÖÐ£¬ÏÂÃæµÄ×ø±ê´óÓÚÉÏÃæµÄ×ø±ê£¬¶øÎÒÃÇÍùÉÏÌ§Í·µÄÊ±ºòÐèÒªÒ»¸öÕýµÄ½Ç¶È
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);
#endif
}

//Êó±ê¹öÂÖÏûÏ¢»Øµ÷
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
#ifdef ENABLE_CAMERA
	camera.ProcessMouseScroll(yoffset);
#endif
}


unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

//°ó¶¨ÊÖµÄVAO
void bind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int& texture)
{
	/*          ³õÊ¼»¯vao¡¢vbo¡¢ebo          */
	//°ó¶¨VAO
	glBindVertexArray(VAO);

	//°ó¶¨VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//Ö¸¶¨Îª¶¥µã»º´æ¶ÔÏó
	//Éú³ÉÎÆÀí
	glActiveTexture(GL_TEXTURE0); // ÔÚ°ó¶¨ÎÆÀíÖ®Ç°ÏÈ¼¤»îÎÆÀíµ¥Ôª
	glBindTexture(GL_TEXTURE_2D, texture);
}

void cube_restore()
{
	static int state_tem = 0;
	bool is_empty = false;
	bool is_end = false;
	switch (state_tem) {
	case 0:
		is_empty = active_next_action();
		if (is_empty)
			state_tem = 2;
		else
			state_tem = 1;
		break;
	case 1:
		is_end = check_end();
		if (is_end)
			state_tem = 0;
		break;
	case 2:
		state_tem = 0;
		in_a_restore = false;
		break;
	}
	return;
}

bool active_next_action() {
	if (action_stack.empty())
		return true;
	int signal = action_stack.top();
	action_stack.pop();
	if (!action_stack.empty()) 
		action_stack.pop();
	switch (signal) {
	case 0:
		right_hand.flag_part[0] = true;
		break;
	case 1:
		left_hand.flag_part[1] = true;
		break;
	case 2:
		right_hand.flag_part[2] = true;
		break;
	case 3:
		left_hand.flag_part[3] = true;
		break;
	case 4:
		left_hand.flag_part[4] = true;
		right_hand.flag_part[4] = true;
		break;
	case 5:
		left_hand.flag_part[5] = true;
		right_hand.flag_part[5] = true;
		break;
	case 6:
		left_hand.flag_part[6] = true;
		right_hand.flag_part[6] = true;
		break;
	case 7:
		left_hand.flag_part[7] = true;
		right_hand.flag_part[7] = true;
		break;
	case 8:
		left_hand.flag_part[8] = true;
		right_hand.flag_part[8] = true;
		break;
	case 9:
		left_hand.flag_part[9] = true;
		right_hand.flag_part[9] = true;
		break;
	case 10:
		left_hand.flag_part[10] = true;
		right_hand.flag_part[10] = true;
		break;
	case 11:
		left_hand.flag_part[11] = true;
		right_hand.flag_part[11] = true;
		break;
	case 100:
		left_hand.flag_all[0] = true;
		right_hand.flag_all[0] = true;
		break;
	case 101:
		left_hand.flag_all[1] = true;
		right_hand.flag_all[1] = true;
		break;
	case 102:
		left_hand.flag_all[2] = true;
		right_hand.flag_all[2] = true;
		break;
	case 103:
		left_hand.flag_all[3] = true;
		right_hand.flag_all[3] = true;
		break;
	default:
		return true;
		break;
	}

	return false;
}

bool check_end()
{
	if (!left_hand.flag_part[0] && !right_hand.flag_part[0] &&
		!left_hand.flag_part[1] && !right_hand.flag_part[1] &&
		!left_hand.flag_part[2] && !right_hand.flag_part[2] &&
		!left_hand.flag_part[3] && !right_hand.flag_part[3] &&
		!left_hand.flag_part[4] && !right_hand.flag_part[4] &&
		!left_hand.flag_part[5] && !right_hand.flag_part[5] &&
		!left_hand.flag_part[6] && !right_hand.flag_part[6] &&
		!left_hand.flag_part[7] && !right_hand.flag_part[7] &&
		!left_hand.flag_part[8] && !right_hand.flag_part[8] &&
		!left_hand.flag_part[9] && !right_hand.flag_part[9] &&
		!left_hand.flag_part[10] && !right_hand.flag_part[10] &&
		!left_hand.flag_part[11] && !right_hand.flag_part[11] &&
		!left_hand.flag_all[0] && !right_hand.flag_all[0] &&
		!left_hand.flag_all[1] && !right_hand.flag_all[1] &&
		!left_hand.flag_all[2] && !right_hand.flag_all[2] &&
		!left_hand.flag_all[3] && !right_hand.flag_all[3] &&
		!left_hand.flag_all[4] && !right_hand.flag_all[4])
	{
		return true;
	}
	return false;
}
