#include "Background.h"

Background::Background(Game* game, int rOrder, int w, int h, int c, std::string path)
	:Renderable(game, rOrder, w, h, c, path) //the constructor of renderable class will be called with these arguements!
{
	//setO2W(glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.0f)));
}


void Background::update(double dt) {

}


void Background::render() {

	

	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));
	

	//glUniform1i(glGetUniformLocation(getGame()->getRenderablesProgID(), "ourTexture"), 0);

	glBindTexture(GL_TEXTURE_2D, getTexture());


	glBindVertexArray(getGame()->getVAO());
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glBindTexture(GL_TEXTURE_2D, 0); //unbind the textures after use


}