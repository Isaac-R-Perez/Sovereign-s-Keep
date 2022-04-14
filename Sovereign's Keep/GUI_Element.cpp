#include "GUI_Element.h"

GUI_Element::GUI_Element(Game* g, int rOrder, int defaultSpriteSheet, GUIType t)
	:Renderable(g, rOrder, defaultSpriteSheet)
{
	guiType = t;

	if (guiType == GUIType::HealthBar || guiType == GUIType::ManaBar) {
		resize(BAR_HEIGHT, BAR_HEIGHT);
	}
	else
	{
		resize(PLAYER_ICON_WIDTH, PLAYER_ICON_WIDTH);
	}

	
	IconData.clear();
}


void GUI_Element::update(double dt) {

	glm::mat4 move;
	float width = 0.0f;

	if (guiType == GUIType::HealthBar) {

		//change width of bar to math player's current Health
		width = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentHealth();

		width = (width / (SCREEN_WIDTH / 1.5f));

		resize(width, BAR_HEIGHT);

		setOrigin(glm::vec3(-0.99f, 0.95f, 0.0f));

		move = glm::translate(glm::mat4(1.0f), glm::vec3(getWidth() / 2.0f, 0.0f, 0.0f));

		updatePosition(move);


	}
	else if (guiType == GUIType::ManaBar) {
		
		//change width of bar to match player's current Mana
		width = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentMana();

		width = (width / (SCREEN_WIDTH / 1.5f));

		resize(width, BAR_HEIGHT);

		setOrigin(glm::vec3(-0.99f, 0.88f, 0.0f));

		move = glm::translate(glm::mat4(1.0f), glm::vec3(getWidth() / 2.0f, 0.0f, 0.0f));

		updatePosition(move);

	}
	



}


void GUI_Element::render() {

	


	/*
		render bars normally

		if icon, then loop through the vector, translate to location and change to set icon
		then render
	
	*/

	


	if (guiType == GUIType::HealthBar) {
		getGame()->setGUIFlag(1);

	}
	
	if (guiType == GUIType::ManaBar) {
		getGame()->setGUIFlag(2);
	}


	if (guiType == GUIType::HealthBar || guiType == GUIType::ManaBar) {
		
		GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
		if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
		glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

		glBindTexture(GL_TEXTURE_2D, getTexture());
		glBindVertexArray(getGame()->getVAO());

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	}
	else
	{
		
	}




	getGame()->setGUIFlag(0);
	//this clears the vector so that a fresh set of data can be sent.
	IconData.clear();
}