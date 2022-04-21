#pragma once
#include "Renderable.h"
/*
	This class will handle all logic related to the GUI elements (HPbar, ManaBar, Element icons)
*/

const float SHIFT_ICON_WIDTH = 0.075f;
const float SHIFT_ICON_HEIGHT = 0.1f;

const float PLAYER_ICON_WIDTH = 0.09375f;
const float PLAYER_ICON_HEIGHT = 0.125f;

const float BAR_HEIGHT = 0.025f;

const float BUTTON_WIDTH = 956.0f / 1920.0f;
const float BUTTON_HEIGHT = 98.0f / 1080.0f;



enum class GUIType {
	HealthBar, ManaBar, FireIcon, WaterIcon, EarthIcon, AirIcon,
	Start, HowToPlay, Exit,
};


struct DisplayElementData {
	//holds what type of icon to display
	GUIType type;

	//determines where to render this GUI element
	glm::vec3 location;


	//this package is sent to the GUI_Element in game class to tell it where to render itself
	DisplayElementData(GUIType t, glm::vec3 loc) {
		type = t;
		location = loc;
	}

	DisplayElementData() {
		type = GUIType::HealthBar;
		location = glm::vec3(1.0f);
	}
};



class GUI_Element : public Renderable {

public:

	GUI_Element(Game* g, int rOrder, int defaultSpriteSheet, GUIType t);

	void render();
	void update(double dt);

	void addToIconData(DisplayElementData d) { IconData = d; }

	void setHovered(bool b) { HOVERED = b; }
	bool getHovered() { return HOVERED; }

private:

	//determines how this element behaves
	GUIType guiType;
	
	//clear this vector each frame, send the icon and location data each frame
	//render them based on this vector
	DisplayElementData IconData;

	bool firstRender;

	bool HOVERED;

	
};