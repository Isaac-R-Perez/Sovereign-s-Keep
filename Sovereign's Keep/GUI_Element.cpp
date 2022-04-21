#include "GUI_Element.h"

GUI_Element::GUI_Element(Game* g, int rOrder, int defaultSpriteSheet, GUIType t)
	:Renderable(g, rOrder, defaultSpriteSheet)
{
	guiType = t;

	if (guiType == GUIType::HealthBar || guiType == GUIType::ManaBar) {
		resize(BAR_HEIGHT, BAR_HEIGHT);
	}
	else if(guiType == GUIType::AirIcon)
	{
		resize(SHIFT_ICON_WIDTH, SHIFT_ICON_HEIGHT);
	}
	else if (guiType == GUIType::Start) {
		resize(BUTTON_WIDTH, BUTTON_HEIGHT);

	}
	else if (guiType == GUIType::HowToPlay) {
		resize(BUTTON_WIDTH, BUTTON_HEIGHT);

	}
	else if (guiType == GUIType::Exit) {
		resize(BUTTON_WIDTH, BUTTON_HEIGHT);
		

	}
	else
	{
		resize(PLAYER_ICON_WIDTH, PLAYER_ICON_HEIGHT);
	}

	firstRender = true;
	HOVERED = false;
	
}


void GUI_Element::update(double dt) {

	glm::mat4 move;
	float width = 0.0f;

	if (guiType == GUIType::HealthBar) {

		//change width of bar to math player's current Health
		width = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentHealth();

		width = (width / (SCREEN_WIDTH ));

		resize(width, BAR_HEIGHT);

		setOrigin(glm::vec3(-0.99f, 0.95f, 0.0f));

		move = glm::translate(glm::mat4(1.0f), glm::vec3(getWidth() / 2.0f, 0.0f, 0.0f));

		updatePosition(move);


	}
	else if (guiType == GUIType::ManaBar) {
		
		//change width of bar to match player's current Mana
		width = dynamic_cast<Player*>(getGame()->getPlayer())->getCurrentMana();

		width = (width / (SCREEN_WIDTH ));

		resize(width, BAR_HEIGHT);

		setOrigin(glm::vec3(-0.99f, 0.88f, 0.0f));

		move = glm::translate(glm::mat4(1.0f), glm::vec3(getWidth() / 2.0f, 0.0f, 0.0f));

		updatePosition(move);

	}
	else if (guiType == GUIType::Start || guiType == GUIType::HowToPlay || guiType == GUIType::Exit) {
		//check if player has clicked hovered over this button, if they have, make it larger, if not reset size
		
		

	}
	else
	{

	}
	

	

}


void GUI_Element::render() {

	glm::mat4 move;
	
	if (firstRender) {
		firstRender = false;
	}
	else
	{



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
		else if (guiType == GUIType::Start || guiType == GUIType::HowToPlay || guiType == GUIType::Exit) {
			
			const float HOVER = 1.075f;

			if (HOVERED) {
				resize(BUTTON_WIDTH * HOVER, BUTTON_HEIGHT * HOVER);
			}
			else
			{
				resize(BUTTON_WIDTH, BUTTON_HEIGHT);
			}
			
			GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
			if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
			glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

			glBindTexture(GL_TEXTURE_2D, getTexture());
			glBindVertexArray(getGame()->getVAO());

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		else
		{

			//this tells the shader that the renderable is a GUI element, but has a texture
			getGame()->setGUIFlag(3);
			//loop through the vector, change to the appropriate icon texture, and move to the correct position.

			if (IconData.type == GUIType::HealthBar) {

			}
			else
			{

				if (IconData.type == GUIType::FireIcon) {
					setTexture(static_cast<int>(SPRITE_SHEETS::fire_icon));
				}
				if (IconData.type == GUIType::WaterIcon) {
					setTexture(static_cast<int>(SPRITE_SHEETS::water_icon));
				}
				if (IconData.type == GUIType::EarthIcon) {
					setTexture(static_cast<int>(SPRITE_SHEETS::earth_icon));
				}
				if (IconData.type == GUIType::AirIcon) {
					setTexture(static_cast<int>(SPRITE_SHEETS::air_icon));
				}


				setOrigin(glm::vec3(0.0f, 0.0f, 0.0f));

				move = glm::translate(glm::mat4(1.0f), IconData.location);

				updatePosition(move);

				GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
				if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
				glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

				glBindTexture(GL_TEXTURE_2D, getTexture());
				glBindVertexArray(getGame()->getVAO());

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}


			kill();
		}




		getGame()->setGUIFlag(0);
	}

	/*
		render bars normally

		if icon, then loop through the vector, translate to location and change to set icon
		then render
	
	*/

	
	//this clears the vector so that a fresh set of data can be sent.
	
}