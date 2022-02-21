#include "Game.h"


//globals
int SCREEN_HEIGHT;
int SCREEN_WIDTH;


bool Game::initialize() {
	glewExperimental = GL_TRUE;

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	
	SCREEN_HEIGHT = mode->height;
	SCREEN_WIDTH = mode->width;

	//create a window, not fullscreen
	window = glfwCreateWindow(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Sovereign's Keep", NULL, NULL);

	//create a fullscreen window
	//window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sovereign's Keep", monitor, NULL);

	if (window == nullptr) {
		fprintf(stderr, "Failed to create a window!\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW!\n");
		return false;
	}


	//create VAO and VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);



	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	//set callback functions,      THESE ARE FOR IMPLEMENTING THE CONTROLS FOR THE GAME
	/*
	glfwSetCursorPosCallback(window, mouse_position_callback);
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	*/
	
	glClearColor(0.1, 0.1, 0.1, 1.0);

	glfwSwapInterval(1); //Sets VSync for enforced 60 fps

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);



	cameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);

	
	//load all shaders here
	


	return true;

}



//this function updates ALL renderable entities
void Game::update() {


}


//this functions renders Renderables, in the correct order
void Game::render() {


}


void Game::cleanup() {

}

//getters and setters
GLFWwindow* Game::getWindow() { return window; }