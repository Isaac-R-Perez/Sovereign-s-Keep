#include "Basic_Attack.h"

Basic_Attack::Basic_Attack(Game* g, int rOrder, int defaultSpriteSheet)
	:Renderable(g, rOrder, defaultSpriteSheet) {

	glm::mat4 resize = glm::mat4(1.0f);

	resize = glm::scale(glm::mat4(1.0f), glm::vec3(0.025f, 0.02f, 0.0f));
	this->setO2W(resize);


	damage = BASE_DAMAGE;
	speed = BULLET_BASE_SPEED;
	angle = 0.0f;
	direction = glm::vec3(1.0f, 0.0f, 0.0f); //points down x axis
}


void Basic_Attack::update(double dt) {

	glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(direction.x * dt * BULLET_BASE_SPEED, direction.y * dt * BULLET_BASE_SPEED, 0.0f));

	updatePosition(move);

}

void Basic_Attack::render() {

	GLint objectToWorld = glGetUniformLocation(getGame()->getRenderablesProgID(), "objectToWorld");
	if (objectToWorld < 0) printf("couldn't find objectToWorld in shader\n");
	glUniformMatrix4fv(objectToWorld, 1, GL_FALSE, glm::value_ptr(getO2W()));

	glBindTexture(GL_TEXTURE_2D, getTexture());
	glBindVertexArray(getGame()->getVAO());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}