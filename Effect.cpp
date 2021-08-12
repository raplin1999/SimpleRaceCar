#include "Effect.h"

Effects::Effects(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	// Non textured Shader
	program.Load("shaders/vertex.glsl", "shaders/fragment.glsl");
	program.SetProjectionMatrix(projectionMatrix);
	program.SetViewMatrix(viewMatrix);
	currentEffect = NONE;
	alpha = 0;
	viewOffset = glm::vec3(0, 0, 0);
}
void Effects::DrawOverlay()
{
	glUseProgram(program.programID);
	float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program.positionAttribute);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(program.positionAttribute);
}


void Effects::Start(EffectType effectType)
{
	currentEffect = effectType;
	switch (currentEffect) {
	case NONE:
		break;
	case FADEIN:
		alpha = 1.0f;

		break;
	case FADEOUT:
		alpha = 0.0f;
		break;
	case GROW:
		size = 0.0f;
		break;
	case SHAKE:
		timeLeft = 1.0f;
		break;
	}
}
void Effects::Update(float deltaTime)
{
	switch (currentEffect) {
	case NONE:
		break;
	case FADEIN:
		alpha -= deltaTime*0.1;
		if (alpha <= 0) currentEffect = NONE;
		break;
	case FADEOUT:
		alpha += deltaTime * 0.1;
		break;
	case GROW:
		size += deltaTime * speed;
		break;
	case SHAKE:
		timeLeft -= deltaTime*1;
		if (timeLeft >= 0) {
			viewOffset = glm::vec3(0, 0, 0);
			currentEffect = NONE;
		}
		else {
			float max = 0.1f;
			float min = -0.1f;
			float r = ((float)rand() / RAND_MAX) * (max - min) + min;
			viewOffset = glm::vec3(r, r, 0);
		}
	}
}
void Effects::Render()
{

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	switch (currentEffect) {
	case NONE:
		return;
		break;
	case FADEOUT:

	case FADEIN:
		modelMatrix = glm::scale(modelMatrix, glm::vec3(10, 10, 1));
		program.SetModelMatrix(modelMatrix);
		program.SetColor(0, 0, 0, alpha);
		DrawOverlay();
		break;
	case GROW:
		modelMatrix = glm::scale(modelMatrix, glm::vec3(size, size, 1));
		program.SetModelMatrix(modelMatrix);
		program.SetColor(0, 0, 0, 1);
		DrawOverlay();
		break;
	case SHAKE:
		break;
	}
}
