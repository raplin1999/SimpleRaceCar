#include "Menu.h"


GLuint fontTextureID;

void Menu::Initialize() {
    state.nextScene = -1;
    state.player = state.player = new Entity();
    state.objects = new Entity();
    glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
    fontTextureID = Util::LoadTexture("font1.png");

}
void Menu::Update(float deltaTime) {

}
void Menu::Render(ShaderProgram* program) {

    Util::DrawText(program, fontTextureID, "Simple Race Car", 0.5, -0.3f,
        glm::vec3(-4, 3, 0));


    Util::DrawText(program, fontTextureID, "Press Enter To Start", 0.5, -0.3f,
        glm::vec3(-4, 2, 0));

    Util::DrawText(program, fontTextureID, "Press A to speed, Press Space to brake", 0.5, -0.3f,
        glm::vec3(-4, 1, 0));

    Util::DrawText(program, fontTextureID, "Find the Finish Line", 0.5, -0.3f,
        glm::vec3(-4, 0, 0));

}