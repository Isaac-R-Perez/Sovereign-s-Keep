#include "Renderable.h"

/*
	a defalt renderable has 6 total points, it is essentailly a square from (-0.1, -0.1) to (0.1, 0.1)
	with an origin at 0.0, 0.0
*/


/*
	This function takes in the width, height, color channels, and the path of the image to generate and bind a texture to this renderable.
	These must be given every time a new renderable is created!
*/
void Renderable::setTexture(int w, int h, int nrC, std::string path) {
	textureWidth = w;
	textureHeight = h;
	nrChannels = nrC;

	data = stbi_load(path.c_str(), &textureWidth, &textureHeight, &nrChannels, 0);

	if (!data) {
		printf("Failed to load texture!\n");
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

}


Renderable::Renderable(Game* g, int rOrder, int w, int h, int c, std::string path) {
	game = g;
	renderOrder = rOrder;

	objectToWorld = glm::mat4(1.0f);
	origin = glm::vec3(0.0f, 0.0f, 0.0f);

	setTexture(w, h, c, path); //generate the texture for this renderable

}


void Renderable::render() {

}

void Renderable::update(double dt)  {

}
