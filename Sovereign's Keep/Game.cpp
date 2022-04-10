#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "DataManager.h"
#include "Enemy.h"

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
	View = glm::mat4(1.0f);
	ShowHitBoxes = false;
}






void Game::loadAllTextures() {

	//background
	generateTexture(generatedTexture, 1920, 1080, 3, "images/background/demo_background.png");
	allSpriteSheets.insert(std::pair<int, GLuint>(static_cast<int>(SPRITE_SHEETS::background), generatedTexture));
	
	//player default
	generateTexture(generatedTexture, 17, 29, 3, "images/player/player_default.png");
	allSpriteSheets.insert(std::pair<int, GLuint>(static_cast<int>(SPRITE_SHEETS::player_default), generatedTexture));

	//player idle
	generateTexture(generatedTexture, 68, 30, 3, "images/player/player_idle_animation.png");
	allSpriteSheets.insert(std::pair<int, GLuint>(static_cast<int>(SPRITE_SHEETS::player_idle), generatedTexture));

	//player walking
	generateTexture(generatedTexture, 312, 56, 3, "images/player/player_walking_animation_X2.png");
	allSpriteSheets.insert(std::pair<int, GLuint>(static_cast<int>(SPRITE_SHEETS::player_walking), generatedTexture));

	//player attacking
	generateTexture(generatedTexture, 450, 35, 3, "images/player/player_attack_animation.png");
	allSpriteSheets.insert(std::pair<int, GLuint>(static_cast<int>(SPRITE_SHEETS::player_attacking), generatedTexture));

	//player casting
	generateTexture(generatedTexture, 224, 29, 3, "images/player/player_casting_animation.png");
	allSpriteSheets.insert(std::pair<int, GLuint>(static_cast<int>(SPRITE_SHEETS::player_casting), generatedTexture));

	//basic attack
	generateTexture(generatedTexture, 224, 29, 3, "images/player/basic_attack.png");
	allSpriteSheets.insert(std::pair<int, GLuint>(static_cast<int>(SPRITE_SHEETS::basic_attack), generatedTexture));

	// slime enemy
	generateTexture(generatedTexture, 96, 20, 3, "images/enemy/slime/Slime_Run.png");
	allSpriteSheets.insert(std::pair<int, GLuint>(static_cast<int>(SPRITE_SHEETS::slime), generatedTexture));


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


	//casting logic should be checked first?

	//move up
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {

		/*
			Check if the player can cast current spell
			If they cant, ignore this.
			If they can, start casting animation, and make the casting time specific to the spell being cast.
		*/
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setCasting(true);
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->resetCastingVariables();

	}
	if (key == GLFW_KEY_Q && action == GLFW_REPEAT) {

	}

	if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {

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


		if (dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getFacingRight() && !dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getAttackingRight()) {

			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->flip();

			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingLeft(true);
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(true);
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(false);
		}
		else if (dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getAttackingRight()) {
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingLeft(true);
		}
		else {
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingLeft(true);
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(true);
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(false);
		}


	}
	if (key == GLFW_KEY_A && action == GLFW_REPEAT) {

	}
	//move left
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingLeft(false);


	}

	//move right
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		

		if(dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getFacingLeft() && !dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getAttackingLeft()){
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->flip();

			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingRight(true);
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(false);
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(true);

		}
		else if (dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getAttackingLeft()) {
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingRight(true);
		}
		else {
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setMovingRight(true);
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(false);
			dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(true);
		}


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
			//printf("basic attack left\n");
			if (dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getFacingRight()) {

				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->flip();
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setStartAttacking(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackLeft(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(false);
			}
			else
			{
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setStartAttacking(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackLeft(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(false);
			}

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

			if (dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getMovingRight()) {
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->flip();
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(false);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(true);
			}

		}
	}



	//basic attack up
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//this means that the player is trying to input their element 2.

		}

	}
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {

	}

	if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//DO NOTHING, the element was already added when it was initally pressed

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

			if (dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getFacingLeft()) {

				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->flip();
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setStartAttacking(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackRight(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(false);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(true);
			}
			else
			{
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setStartAttacking(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setAttackRight(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(false);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(true);
			}

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

			if (dynamic_cast<Player*>(gameREFERENCE->getPlayer())->getMovingLeft()) {
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->flip();
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingLeft(true);
				dynamic_cast<Player*>(gameREFERENCE->getPlayer())->setFacingRight(false);
			}

		}
	}




	//basic attack down
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//this means that the player is trying to input their element 3.

		}

	}
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {

	}

	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {

		if (gameREFERENCE->getSpellComboMode() == true) {
			//DO NOTHING, the element was already added when it was initally pressed

		}
	}


	if (key == GLFW_KEY_H && action == GLFW_PRESS) {

		if (gameREFERENCE->getShowHitBoxes()) {
			gameREFERENCE->setShowHitBoxes(false);
		}
		else
		{
			gameREFERENCE->setShowHitBoxes(true);
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

	//create hitbox render variables
	glGenVertexArrays(1, &HITBOX_VAO);
	glBindVertexArray(HITBOX_VAO);

	glGenBuffers(1, &HITBOX_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, HITBOX_VBO);

	hitbox_programID = LoadShaders("HITBOX_vshader.txt", "HITBOX_fshader.txt");

	setupHitBoxBuffers();


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
	View = glm::lookAt(cameraPosition, glm::vec3(cameraPosition.x, cameraPosition.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	//load shaders
	renderables_programID = LoadShaders("vertex_shader.txt", "fragment_shader.txt");
	

	glUseProgram(renderables_programID);


	setupBuffers();

	loadAllTextures();


	
	

	//update
	//Renderable* b = new Background(this, 1, 1920, 1080, 3, "images/background/demo_background.png");
	
	//renderQueue.insert(pair<int, Renderable*>(b->renderOrder, b));
	
	Renderable* b = new Background(this, 1, static_cast<int>(SPRITE_SHEETS::background));
	renderQueue.insert(pair<int, Renderable*>(b->renderOrder, b));
	

	player = new Player(this, 2, static_cast<int>(SPRITE_SHEETS::player_default));
	
	renderQueue.insert(pair<int, Renderable*>(player->renderOrder, player));

	b = new Enemy(this, 3, static_cast<int>(SPRITE_SHEETS::slime), EnemyType::slime);
	renderableToPendingAdd(b);

	return true;

}

void Game::setupHitBoxBuffers() {
	hitboxVertices.clear();


	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);



	GLint vPosition = glGetAttribLocation(hitbox_programID, "vPosition");
	if (vPosition < 0) printf("Couldn't find vPosition in hitbox shader! SETUP\n");
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);

	GLint viewLoc = glGetUniformLocation(hitbox_programID, "view");
	if (viewLoc < 0) printf("Couldn't find view in hitbox shader! SETUP\n");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(View));

}

void Game::setupBuffers() {
	
	//top right
	vertices.emplace_back(1.0f);
	vertices.emplace_back(1.0f); //positions
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //colors
	vertices.emplace_back(0.0f);

	vertices.emplace_back(1.0f);
	vertices.emplace_back(1.0f); //texture coords


	//bottom right
	vertices.emplace_back(1.0f);
	vertices.emplace_back(-1.0f); //positions
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //colors
	vertices.emplace_back(0.0f);

	vertices.emplace_back(1.0f);
	vertices.emplace_back(0.0f); //texture coords

	//bottom left
	vertices.emplace_back(-1.0f);
	vertices.emplace_back(-1.0f); //positions
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //colors
	vertices.emplace_back(0.0f);

	vertices.emplace_back(0.0f);
	vertices.emplace_back(0.0f); //texture coords

	//top left
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

	GLint viewLoc = glGetUniformLocation(renderables_programID, "view");
	if (viewLoc < 0) printf("Couldn't find view in shader! SETUP\n");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(View));



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

void Game::generateTexture(GLuint &tex, int w, int h, int nrC, std::string path) {
	

	stbi_set_flip_vertically_on_load(true);

	data = stbi_load(path.c_str(), &w, &h, &nrC, 0);

	if (!data) {
		printf("Failed to load texture!\n");
	}

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

}


void Game::resetTextureCoordinates() {
	

	//top right
	vertices.at(6) = 1.0f;
	vertices.at(7) = 1.0f;

	//bottom right
	vertices.at(14) = 1.0f;
	vertices.at(15) = 0.0f;

	//bottom left
	vertices.at(22) = 0.0f;
	vertices.at(23) = 0.0f;

	//top left
	vertices.at(30) = 0.0f;
	vertices.at(31) = 1.0f;

	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
}

void Game::setTextureCoordinates(float TRx, float TRy, float BRx, float BRy, float BLx, float BLy, float TLx, float TLy)
{
	//top right
	vertices.at(6) = TRx;
	vertices.at(7) = TRy;

	//bottom right
	vertices.at(14) = BRx;
	vertices.at(15) = BRy;

	//bottom left
	vertices.at(22) = BLx;
	vertices.at(23) = BLy;

	//top left
	vertices.at(30) = TLx;
	vertices.at(31) = TLy;

	

	

	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
}


GLuint& Game::getTextureFromMap(int a)
{
	return allSpriteSheets.find(a)->second;
}

//getters and setters
GLFWwindow* Game::getWindow() { return window; }

void Game::updateCamera(glm::vec3& playerOrigin) {
	
	glm::vec3 cameraCenter = playerOrigin;


	const float BACKGROUND_SCALE = 2.0f;
	const float CAMERA_SIZE = 1.0f; //camera is always a square centered at origin with top right corner being (1.0,1.0)

	if (playerOrigin.x + CAMERA_SIZE > BACKGROUND_SCALE)
	{
		cameraCenter.x = BACKGROUND_SCALE - CAMERA_SIZE;
	}
	if (playerOrigin.x - CAMERA_SIZE < -BACKGROUND_SCALE)
	{
		cameraCenter.x = -BACKGROUND_SCALE + CAMERA_SIZE;
	}
	if (playerOrigin.y + CAMERA_SIZE > BACKGROUND_SCALE)
	{
		cameraCenter.y = BACKGROUND_SCALE - CAMERA_SIZE;
	}
	if (playerOrigin.y - CAMERA_SIZE < -BACKGROUND_SCALE)
	{
		cameraCenter.y = -BACKGROUND_SCALE + CAMERA_SIZE;
	}
	
	View = glm::lookAt(glm::vec3(cameraCenter.x, cameraCenter.y,1.0f), glm::vec3(cameraCenter.x, cameraCenter.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	
	
	GLint viewLoc = glGetUniformLocation(renderables_programID, "view");
	if (viewLoc < 0) printf("Couldn't find view in shader! CAMERA UPDATE\n");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(View));
}


//change the vertices in the hitbox vector to be able to render the hitbox correctly. CALL bindHitBoxVariables FIRST
void Game::changeHitBoxVertices(HitBox box) {
	hitboxVertices.clear();
	
	hitboxVertices.emplace_back(glm::vec3(box.topRight));
	hitboxVertices.emplace_back(glm::vec3(box.topLeft));
	hitboxVertices.emplace_back(glm::vec3(box.bottomRight));

	hitboxVertices.emplace_back(glm::vec3(box.topRight));
	hitboxVertices.emplace_back(glm::vec3(box.bottomLeft));
	hitboxVertices.emplace_back(glm::vec3(box.bottomRight));

	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), hitboxVertices.data(), GL_STATIC_DRAW);
}

void Game::bindHitBoxVariables() {
	glBindVertexArray(HITBOX_VAO);
	glBindVertexArray(HITBOX_VBO);

	glUseProgram(hitbox_programID);

}

void Game::bindNormalRenderVariables() {
	glBindVertexArray(VAO);
	glBindVertexArray(VBO);

	glUseProgram(renderables_programID);
}