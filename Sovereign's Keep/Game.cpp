#include "Game.h"
#include "Background.h"
#include "Player.h"

//globals
int SCREEN_HEIGHT;
int SCREEN_WIDTH;

//the last known position of the mouse, in screen coordinates
double Last_Mouse_X;
double Last_Mouse_Y;

//use this to call game functions in the callback functions
Game* gameREFERENCE;




/*

	SHADER FUNCTION

*/

GLuint LoadShaders(const char* vertFilePath, const char* fragFilePath)
{
	//create the shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//read vertex shader code from file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertFilePath, std::ios::in);

	if (vertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else
	{
		printf("could not open %s. Make sure the file path is correct!", vertFilePath);
		getchar();
		return 0;
	}

	//read fragment shader code from file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragFilePath, std::ios::in);

	if (fragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}


	GLint Result = GL_FALSE;
	int InfoLogLength;

	//compile vertex shader
	//printf("compiling shader : %s\n", vertFilePath);
	char const* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShader);

	//check vertex shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}


	//compile fragment shader
	//printf("compiling shader : %s\n", fragFilePath);
	char const* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShader);

	//check fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}


	//link the program
	//printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	//check program
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(programID, vertexShader);
	glDetachShader(programID, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return programID;

}




Game::Game() {
	paused = false;
	gameREFERENCE = this;
	spellComboMode = false;
	pendingAdd = std::vector<Renderable*>();
	pendingDestroy = std::vector<Renderable*>();
}



/*
	GAME CONTROLS and CONTROLS LOGIC
*/


void mouse_position_callback(GLFWwindow* window, double x, double y)
{

	

	//this function tracks the position of the mouse, it does not track the mouse buttons!

	//screen coordinates
	Last_Mouse_X = x;
	Last_Mouse_Y = y;


}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		
		//need to check where mouse is, and what clicking will do


	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_REPEAT) {
		//do nothing
	}
	

}



void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		//FOR NOW, ESC closes the game, but later a pause menu will be added! Use pause bool for this.
		glfwSetWindowShouldClose(window, GL_TRUE);

	}

	//player's movement states are dependent on if a key is currently held down
	//if w is held, they will move up until it is released.

	//move up
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {

		//printf("w key pressed\n");
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingUp(true);

	}
	if (key == GLFW_KEY_W && action == GLFW_REPEAT) {

	}

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {

		
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingUp(false);
	}


	//move down
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingDown(true);
	}
	if (key == GLFW_KEY_S && action == GLFW_REPEAT) {

	}
	//move backward
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingDown(false);
	}


	//move left
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {

		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingLeft(true);
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(true);
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(false);


	}
	if (key == GLFW_KEY_A && action == GLFW_REPEAT) {

	}
	//move left
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {

		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingLeft(false);


	}

	//move right
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {

		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingRight(true);
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(false);
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(true);
	}
	if (key == GLFW_KEY_D && action == GLFW_REPEAT) {

	}
	//move right
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingRight(false);
	}



	//if SHIFT is pressed/held, then the arrow keys will add their corresponding elements into a vector?
	//else they will just try to shoot a basic attack

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		gameREFERENCE->setSpellComboMode(true);
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_REPEAT) {
		
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		gameREFERENCE->setSpellComboMode(false);

		//this is where you tell the player to combine their current elements into a spell
	}


	

	/*
		ELEMENT 1 = LEFT_ARROW
		ELEMENT 2 = UP_ARROW
		ELEMENT 3 = RIGHT_ARROW
		ELEMENT 4 = DOWN_ARROW
	*/

	//basic attack left
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		
		if (gameREFERENCE->getSpellComboMode() == true) {
			//this means that the player is trying to input their element 1.
			//printf("input element 1\n");



		}
		else
		{
			//SHIFT IS NOT HELD, so fire a basic attack in the left direction
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackLeft(true);
			//printf("basic attack left\n");
		}

	}
	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {

	}
	
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		
		if (gameREFERENCE->getSpellComboMode() == true) {
			//DO NOTHING, the element was already added when it was initally pressed

		}
		else
		{
			//SHIFT IS NOT HELD, tell the player class to stop attack with left arrow
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackLeft(false);
		}
	}



	//basic attack up
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//this means that the player is trying to input their element 2.

		}
		else
		{
			//SHIFT IS NOT HELD, so fire a basic attack in the left direction
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackUp(true);
		}

	}
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {

	}

	if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//DO NOTHING, the element was already added when it was initally pressed

		}
		else
		{
			//SHIFT IS NOT HELD, tell the player class to stop attack with left arrow
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackUp(false);
		}
	}


	//basic attack right
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//this means that the player is trying to input their element 3.

		}
		else
		{
			//SHIFT IS NOT HELD, so fire a basic attack in the left direction
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackRight(true);
		}

	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {

	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//DO NOTHING, the element was already added when it was initally pressed

		}
		else
		{
			//SHIFT IS NOT HELD, tell the player class to stop attack with left arrow
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackRight(false);
		}
	}




	//basic attack down
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//this means that the player is trying to input their element 3.

		}
		else
		{
			//SHIFT IS NOT HELD, so fire a basic attack in the left direction
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackDown(true);
		}

	}
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {

	}

	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//DO NOTHING, the element was already added when it was initally pressed

		}
		else
		{
			//SHIFT IS NOT HELD, tell the player class to stop attack with left arrow
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackDown(false);
		}
	}




	/*
	tester
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {

		if (!gameREFERENCE->getEnemies().empty()) {
			gameREFERENCE->getEnemies().at(0)->setAlive(false);
		}


	}

	*/



}






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

	//const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	
	//SCREEN_HEIGHT = mode->height;
	//SCREEN_WIDTH = mode->width;

	//create a window, not fullscreen
	window = glfwCreateWindow(1920, 1080, "Sovereign's Keep", NULL, NULL);

	//create a fullscreen window
	//window = glfwCreateWindow(1920, 1080, "Sovereign's Keep", monitor, NULL);

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

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	


	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	//set callback functions,      THESE ARE FOR IMPLEMENTING THE CONTROLS FOR THE GAME
	
	glfwSetCursorPosCallback(window, mouse_position_callback);
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	
	
	glClearColor(0.1, 0.1, 0.1, 1.0);

	glfwSwapInterval(1); //Sets VSync for enforced 60 fps

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //enables transparency in textures!



	cameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);

	
	//load shaders
	renderables_programID = LoadShaders("vertex_shader.txt", "fragment_shader.txt");
	

	glUseProgram(renderables_programID);


	setupBuffers();




	
	


	Renderable* b = new Background(this, 1, 1920, 1080, 3, "images/background/demo_background.png");
	
	renderQueue.insert(pair<int, Renderable*>(b->renderOrder, b));
	
	

	player = new Player(this, 2, 19, 29, 3, "images/player/player_idle.png");
	
	renderQueue.insert(pair<int, Renderable*>(player->renderOrder, player));


	return true;

}



void Game::setupBuffers() {
	
	
	vertices.emplace_back(1.0f);
	vertices.emplace_back(1.0f); //positions
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //colors
	vertices.emplace_back(0.0f);

	vertices.emplace_back(1.0f);
	vertices.emplace_back(1.0f); //texture coords


	vertices.emplace_back(1.0f);
	vertices.emplace_back(-1.0f); //positions
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //colors
	vertices.emplace_back(0.0f);

	vertices.emplace_back(1.0f);
	vertices.emplace_back(0.0f); //texture coords


	vertices.emplace_back(-1.0f);
	vertices.emplace_back(-1.0f); //positions
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //colors
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //texture coords

	vertices.emplace_back(-1.0f);
	vertices.emplace_back(1.0f); //positions
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //colors
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(1.0f); //texture coords

	indices[0] = 0; indices[1] = 1; indices[2] = 3; indices[3] = 1; indices[4] = 2; indices[5] = 3;


	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	GLint vPosition = glGetAttribLocation(renderables_programID, "vPosition");
	if (vPosition < 0) printf("Couldn't find vPosition in shader! SETUP\n");
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(vPosition);
	
	GLint vColor = glGetAttribLocation(renderables_programID, "vColor");
	if (vColor < 0) printf("Couldn't find vColor in shader! SETUP\n");
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(vColor);
	
	
	
	GLint vTexCoord = glGetAttribLocation(renderables_programID, "vTexCoord");
	if (vTexCoord < 0) printf("Couldn't find vTexCoord in shader! SETUP\n");
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(vTexCoord);



}






//this function updates ALL renderable entities
void Game::update(double dt) {

	//destroy all renderables in the pending destroy vector
	std::multimap<int, Renderable*>::iterator itr;
	
	
	if (!renderQueue.empty())
	{
		//remove any renderables that should be destroyed
		for (itr = renderQueue.begin(); itr != renderQueue.end(); ) {

			if (itr->second->shouldDestroy()) {
				itr = renderQueue.erase(itr);
			}
			else
			{
				++itr;
			}

		}
	}

	



	if (!paused) {
		//this means that the game is not paused, so update all renderables here

		
		if (!renderQueue.empty())
		{
			for (itr = renderQueue.begin(); itr != renderQueue.end(); ++itr) {
				itr->second->update(dt);
			}
		}
		

	}



	//add any new renderables in the pending add vector
	while (!pendingAdd.empty())
	{
		for (Renderable* r : pendingAdd) {
			renderQueue.insert(std::pair<int, Renderable*>(r->renderOrder, r));
		}
		
		pendingAdd.clear();
	}

}


//this functions renders Renderables, in the correct order
void Game::render() {

	//current solution is to create a total copy of the priority queue, MAY AFFECT PERFORMANCE WITH TONS OF ENTITIES!!!

	std::multimap<int, Renderable*>::iterator itr;

	for (itr = renderQueue.begin(); itr != renderQueue.end(); ++itr) {
		itr->second->render();
	}
	
}


void Game::cleanup() {

}


void Game::renderableToPendingAdd(Renderable* r) {
	pendingAdd.push_back(r);
}



//getters and setters
GLFWwindow* Game::getWindow() { return window; }