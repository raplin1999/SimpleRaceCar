#include "Level1.h"

#define L1ENEMY_COUNT 4
#define L1Object_COUNT 150


void Level1::Initialize() {



    state.nextScene = -1;
    //state.enemyCount = L1ENEMY_COUNT; 


    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(0, 1.0f, 0);
    state.player->rotation = glm::vec3(0, 0, 0);
    state.player->acceleration = glm::vec3(0, 0, 0);
    state.player->speed = 1;


    GLuint enemyTextureID = Util::LoadTexture("mushroom.png");
    state.enemies = new Entity[L1ENEMY_COUNT];
    for (int i = 0; i < L1ENEMY_COUNT; i++) {
        state.enemies[i].billboard = true;
        state.enemies[i].textureID = enemyTextureID;
        state.enemies[i].entityType = ENEMY;
        state.enemies[i].position = glm::vec3(-3+i*2, 0.5, -9);
        state.enemies[i].rotation = glm::vec3(0, 0, 0);
        state.enemies[i].acceleration = glm::vec3(0, 0, 0);
    }

    GLuint endTextureID = Util::LoadTexture("finishLine.jpg");
    state.enemies[3].billboard = true;
    state.enemies[3].entityType = FinishLine;
    state.enemies[3].textureID = endTextureID;
    state.enemies[3].position = glm::vec3(100, 0.5, 100);
    state.enemies[3].rotation = glm::vec3(0, 0, 0);
    state.enemies[3].acceleration = glm::vec3(0, 0, 0);


    state.objects = new Entity[L1Object_COUNT];

    GLuint floorTexutreID = Util::LoadTexture("floor.jpg");
    Mesh* cubeMesh = new Mesh();
    cubeMesh->LoadOBJ("cube.obj", 200);

    state.objects[0].textureID = floorTexutreID;
    state.objects[0].position = glm::vec3(0, -0.25, 0);
    state.objects[0].entityType = FLOOR;
    state.objects[0].mesh = cubeMesh;
    state.objects[0].rotation = glm::vec3(0, 0, 0);
    state.objects[0].acceleration = glm::vec3(0, 0, 0);
    state.objects[0].scale = glm::vec3(200, 0.5f, 200);


    GLuint carTexutreID = Util::LoadTexture("crate1_bump.png");
    Mesh* CarMesh = new Mesh();
    CarMesh->LoadOBJ("raceCar.obj", 1);

    state.objects[1].textureID = carTexutreID;
    state.objects[1].position = state.player->position + glm::vec3(0.0f,-0.5f,-2.0f);
    state.objects[1].entityType = Car;
    state.objects[1].mesh = CarMesh;
    state.objects[1].scale = glm::vec3(0.06,0.06,0.06);
    state.objects[1].rotation = glm::vec3(0,180,0);
    GLuint crateTexutreID = Util::LoadTexture("crate1_diffuse.png");
    Mesh* crateMesh = new Mesh();
    crateMesh->LoadOBJ("cube.obj", 1);

    for (int i = 2; i < 12; i++) {
        state.objects[i].textureID = crateTexutreID;
        state.objects[i].position = glm::vec3(4, 0.5, -(i-2)*1.0f);
        state.objects[i].entityType = CUBE;
        state.objects[i].mesh = crateMesh;
    
    }
    for (int i = 12; i < 22; i++) {
        state.objects[i].textureID = crateTexutreID;
        state.objects[i].position = glm::vec3(-4, 0.5, -(i-12) * 1.0f);
        state.objects[i].entityType = CUBE;
        state.objects[i].mesh = crateMesh;

    }
    for (int i = 22; i < 32; i++) {
        state.objects[i].textureID = crateTexutreID;
        state.objects[i].position = glm::vec3(4+0.8*(i-22), 0.5, -(i - 12) * 1.0f);
        state.objects[i].entityType = CUBE;
        state.objects[i].mesh = crateMesh;

    }
    for (int i = 32; i < 52; i++) {
        state.objects[i].textureID = crateTexutreID;
        state.objects[i].position = glm::vec3(-4 + 0.5 * (i - 32), 0.5, -(i - 22) * 1.0f);
        state.objects[i].entityType = CUBE;
        state.objects[i].mesh = crateMesh;
    }

    for (int i = 52; i < 100; i++) {
        state.objects[i].textureID = crateTexutreID;
        state.objects[i].position = glm::vec3(12 + 1 * (i - 52), 0.5, -20);
        state.objects[i].entityType = CUBE;
        state.objects[i].mesh = crateMesh;

    }
    for (int i = 100; i < 150; i++) {
        state.objects[i].textureID = crateTexutreID;
        state.objects[i].position = glm::vec3(22 + 1 * (i - 100), 0.5, -30);
        state.objects[i].entityType = CUBE;
        state.objects[i].mesh = crateMesh;

    }

}

void Level1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.objects, L1Object_COUNT);


    state.objects[1].position = state.player->position + glm::vec3(0.0f, -1.0f, -2.0f);
    state.objects[1].rotation = glm::vec3(0, 180, 0) + state.player->rotation;

    for (int i = 0; i < L1Object_COUNT; i++) {
        state.objects[i].Update(deltaTime, state.player, state.objects, L1Object_COUNT);
    }


    for (int i = 0; i < L1ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.objects, L1Object_COUNT);
    }

}

void Level1::Render(ShaderProgram* program) {

    for (int i = 0; i < L1Object_COUNT; i++) {
        state.objects[i].Render(program);
    };

    for (int i = 0; i < L1ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    };
}