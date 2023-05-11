#include "scene.h"
#include "binary/teapot.h"
#include "binary/rgb.h"
#include "binary/cloud.h"
#include "binary/tex_flower.h"
#include "checker.h"

Shader* Scene::vertexShader = nullptr;
Shader* Scene::fragmentShader = nullptr;
Program* Scene::program = nullptr;
Camera* Scene::camera = nullptr;
Object* Scene::teapot = nullptr;
Texture* Scene::diffuse = nullptr;
Texture* Scene::dissolve = nullptr;
Material* Scene::material = nullptr;
Light* Scene::light = nullptr;

int Scene::width = 0;
int Scene::height = 0;

// Arcball variables
float lastMouseX = 0, lastMouseY = 0;
float currentMouseX = 0, currentMouseY = 0;

void Scene::setup(AAssetManager* aAssetManager) {
    Asset::setManager(aAssetManager);

    Scene::vertexShader = new Shader(GL_VERTEX_SHADER, "vertex.glsl");
    Scene::fragmentShader = new Shader(GL_FRAGMENT_SHADER, "fragment.glsl");

    Scene::program = new Program(Scene::vertexShader, Scene::fragmentShader);

    Scene::camera = new Camera(Scene::program);
    Scene::camera->eye = vec3(20.0f, 30.0f, 20.0f);

    Scene::light = new Light(program);
    Scene::light->position = vec3(15.0f, 15.0f, 0.0f);

    //////////////////////////////
    /* TODO: Problem 2 : Change the texture of the teapot
     *  Modify and fill in the lines below.
     */

    vector<Texel> modifiedRGB = rgbTexels;
    for (Texel& tex : modifiedRGB) {
        GLubyte orig_green = tex.green;

        tex.green = tex.blue;
        tex.blue = tex.red;
        tex.red = orig_green;
    }
    Scene::diffuse = new Texture(Scene::program, 0, "textureDiff", modifiedRGB, rgbSize);
    //////////////////////////////

    Scene::material = new Material(Scene::program, diffuse, dissolve);
    Scene::teapot = new Object(program, material, teapotVertices, teapotIndices);
}

void Scene::screen(int width, int height) {
    Scene::camera->aspect = (float) width/height;
    Scene::width = width;
    Scene::height = height;
}

void Scene::update(float deltaTime) {
    static float time = 0.0f;

    Scene::program->use();

    Scene::camera->update();
    Scene::light->update();

    Scene::teapot->draw();

    time += deltaTime;
}

void Scene::mouseDownEvents(float x, float y) {
    lastMouseX = currentMouseX = x;
    lastMouseY = currentMouseY = y;
}

void Scene::mouseMoveEvents(float x, float y) {
    //////////////////////////////
    /* TODO: Problem 3 : Implement Phong lighting
     *  Fill in the lines below.
     */
    float lastPosX = 2.0 * lastMouseX / Scene::width - 1.0;
    float lastPosY = 2.0 * lastMouseY / Scene::height - 1.0;
    float curPosX = 2.0 * x / Scene::width - 1.0;
    float curPosY = 2.0 * y / Scene::height - 1.0;
    lastMouseX = x;
    lastMouseY = y;

    mat4 viewMat = lookAt(Scene::camera->eye, Scene::camera->at, Scene::camera->up);
    mat4 projMat = perspective(radians(Scene::camera->fovy), Scene::camera->aspect, Scene::camera->zNear, Scene::camera->zFar);
    mat4 axis_inv = mat4({-1.0f, 0.0f, 0.0f, 0.0f},
                         {0.0f, 1.0f, 0.0f, 0.0f},
                         {0.0f, 0.0f, 1.0f, 0.0f},
                         {0.0f, 0.0f, 0.0f, 1.0f});
    projMat = axis_inv * projMat;

    vec3 v_last = glm::normalize(vec3(lastPosX, lastPosY, \
        sqrt(glm::max(1 - pow(lastPosX, 2) - pow(lastPosY, 2), 0.0))));
    vec3 v_cur = glm::normalize(vec3(curPosX, curPosY, \
        sqrt(glm::max(1 - pow(curPosX, 2) - pow(curPosY, 2), 0.0))));
    vec3 rot_axis = vec4(cross(v_last, v_cur), 1.0f);

    float angle = glm::acos(dot(v_last, v_cur));
    mat4 rotate = glm::rotate(angle, rot_axis);

    Scene::light->position = vec3(glm::inverse(viewMat) * glm::inverse(projMat) * rotate * projMat * viewMat * vec4(Scene::light->position, 1.0f));
    //////////////////////////////
}