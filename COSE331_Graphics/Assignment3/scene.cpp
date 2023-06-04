#include "scene.h"
#include "binary/animation.h"
#include "binary/skeleton.h"
#include "binary/player.h"

Shader* Scene::vertexShader = nullptr;
Shader* Scene::fragmentShader = nullptr;
Program* Scene::program = nullptr;
Camera* Scene::camera = nullptr;
Object* Scene::player = nullptr;
Texture* Scene::diffuse = nullptr;
Material* Scene::material = nullptr;
Object* Scene::lineDraw = nullptr;
Texture* Scene::lineColor = nullptr;
Material* Scene::lineMaterial = nullptr;

bool Scene::upperFlag = true;
bool Scene::lowerFlag = true;



void Scene::setup(AAssetManager* aAssetManager) {
    Asset::setManager(aAssetManager);

    Scene::vertexShader = new Shader(GL_VERTEX_SHADER, "vertex.glsl");
    Scene::fragmentShader = new Shader(GL_FRAGMENT_SHADER, "fragment.glsl");

    Scene::program = new Program(Scene::vertexShader, Scene::fragmentShader);

    Scene::camera = new Camera(Scene::program);
    Scene::camera->eye = vec3(0.0f, 0.0f, 80.0f);

    Scene::diffuse = new Texture(Scene::program, 0, "textureDiff", playerTexels, playerSize);
    Scene::material = new Material(Scene::program, diffuse);
    Scene::player = new Object(program, material, playerVertices, playerIndices);
    player->worldMat = scale(vec3(1.0f / 3.0f));

    Scene::lineColor = new Texture(Scene::program, 0, "textureDiff", {{0xFF, 0x00, 0x00}}, 1);
    Scene::lineMaterial = new Material(Scene::program, lineColor);
    Scene::lineDraw = new Object(program, lineMaterial, {{}}, {{}}, GL_LINES);
}

void Scene::screen(int width, int height) {
    Scene::camera->aspect = (float) width/height;
}

void Scene::update(float deltaTime) {
    Scene::program->use();
    Scene::camera->update();

    /*
     *
     * Write your code.
     *
     */

    static float lowerTime = 0;
    static float upperTime = 0;

    // M_i_p 계산
    vector<mat4> M_ip;
    for (vec3 offset: jOffsets) {
        M_ip.push_back(glm::translate(offset));
    }

    //M_i_d 계산
    vector<mat4> M_id_inv;
    M_id_inv.push_back(inverse(M_ip[0]));
    for (int i = 1; i < jNames.size(); i++) {
        M_id_inv.push_back(glm::inverse(M_ip[i]) * M_id_inv[jParents[i]]);
    }

    //M_i_a 계산
    vector<mat4> M_ia;
    if (Scene::lowerFlag) {
        lowerTime += deltaTime;
        if (lowerTime >= 4) lowerTime -= 4.0f;
    }
    if (Scene::upperFlag) {
        upperTime += deltaTime;
        if (upperTime >= 4) upperTime -= 4.0f;
    }

    float interRate = lowerTime - (int)lowerTime;
    vector<float> curMot = motions[(int)lowerTime], nextMot = motions[((int)lowerTime + 1) % 4];

    mat4 trans = translate(mix(
            vec3(curMot[0], curMot[1], curMot[2]),
            vec3(nextMot[0], nextMot[1], nextMot[2]),
            interRate));

    quat curRot = quat_cast(
            rotate(radians(curMot[5]), vec3(0.0f, 0.0f, 1.0f))
            * rotate(radians(curMot[3]), vec3(1.0f, 0.0f, 0.0f))
            * rotate(radians(curMot[4]), vec3(0.0f, 1.0f, 0.0f)));
    quat nextRot = quat_cast(
            rotate(radians(nextMot[5]), vec3(0.0f, 0.0f, 1.0f))
            * rotate(radians(nextMot[3]), vec3(1.0f, 0.0f, 0.0f))
            * rotate(radians(nextMot[4]), vec3(0.0f, 1.0f, 0.0f)));
    mat4 rot = mat4_cast(slerp(curRot, nextRot, interRate));
    M_ia.push_back(M_ip[0] * trans * rot);

    for (int i = 1; i < jNames.size(); i++) {
        float time = i <= 11 ? lowerTime : upperTime;
        interRate = time - (int)time;
        curMot = motions[(int)time], nextMot = motions[((int)time + 1) % 4];

        curRot = quat_cast(
                rotate(radians(curMot[i * 3 + 5]), vec3(0.0f, 0.0f, 1.0f))
                * rotate(radians(curMot[i * 3 + 3]), vec3(1.0f, 0.0f, 0.0f))
                * rotate(radians(curMot[i * 3 + 4]), vec3(0.0f, 1.0f, 0.0f)));
        nextRot = quat_cast(
                rotate(radians(nextMot[i * 3 + 5]), vec3(0.0f, 0.0f, 1.0f))
                * rotate(radians(nextMot[i * 3 + 3]), vec3(1.0f, 0.0f, 0.0f))
                * rotate(radians(nextMot[i * 3 + 4]), vec3(0.0f, 1.0f, 0.0f)));

        rot = mat4_cast(slerp(curRot, nextRot, interRate));
        M_ia.push_back(M_ia[jParents[i]] * M_ip[i] * rot);
    }

    // matrix palette
    vector<mat4> mtxPalette;
    for (int i = 0; i < jNames.size(); i++) {
        mtxPalette.push_back(M_ia[i] * M_id_inv[i]);
    }

    static vector<Vertex> animated = playerVertices;
    for (int i = 0; i < animated.size(); i++) {
        mat4 M = mat4(0.0f);
        for (int j = 0; j < 4; j++) {
            int bone = animated[i].bone[j];
            if (bone == -1) continue;
            M += playerVertices[i].weight[j] * mtxPalette[bone];
        }
        animated[i].pos = vec3(M * vec4(playerVertices[i].pos, 1.0f));
    }
    Scene::player->load(animated, playerIndices);

    // Line Drawerq
    // glLineWidth(20);
    // Scene::lineDraw->load({{vec3(-20.0f, 0.0f, 0.0f)}, {vec3(20.0f, 0.0f, 0.0f)}}, {0, 1});
    // Scene::lineDraw->draw();

    Scene::player->draw();
}

void Scene::setUpperFlag(bool flag)
{
    Scene::upperFlag = flag;
}

void Scene::setLowerFlag(bool flag)
{
    Scene::lowerFlag = flag;
}