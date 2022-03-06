#pragma once
#include "Renderable.h"
/*
	This will be the class that holds all the functions for adding backgrounds, such as the ground
	To add obstacles for the player, derive another class from this class?
*/



class Background : public Renderable {

public:

	Background(Game* game, int rOrder, int w, int h, int c, std::string path);

	void render() ;

	void update(double dt) ;

private:


};