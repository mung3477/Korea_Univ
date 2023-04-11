#include "scene.h"

#include "obj_teapot.h"
#include "tex_flower.h"

Shader* Scene::vertexShader = nullptr;
Shader* Scene::fragmentShader = nullptr;
Program* Scene::program = nullptr;
Camera* Scene::camera = nullptr;
Light* Scene::light = nullptr;
Object* Scene::teapot = nullptr;
Material* Scene::flower = nullptr;
float Scene::time = 0.0f;

void Scene::setup(AAssetManager* aAssetManager) {

    // set asset manager
    Asset::setManager(aAssetManager);

    // create shaders
    vertexShader = new Shader(GL_VERTEX_SHADER, "vertex.glsl");
    fragmentShader = new Shader(GL_FRAGMENT_SHADER, "fragment.glsl");

    // create program
    program = new Program(vertexShader, fragmentShader);

    // create camera
    camera = new Camera(program);
    camera->eye = vec3(60.0f, 60.0f, 60.0f);
    camera->cameraN = glm::normalize(camera->eye - camera->at);
    camera->cameraU = glm::normalize(glm::cross(camera->up, camera->cameraN));
    camera->cameraV = glm::normalize(glm::cross(camera->cameraN, camera->cameraU));

    // create light
    light = new Light(program);
    light->position = vec3(100.0f, 0.0f, 0.0f);

    // create floral texture
    flower = new Material(program, texFlowerData, texFlowerSize);

    // create teapot object
    teapot = new Object(program, flower, objTeapotVertices, objTeapotIndices,
                        objTeapotVerticesSize, objTeapotIndicesSize);
}

void Scene::screen(int width, int height) {

    // set camera aspect ratio
    camera->aspect = (float) width / height;
}

void Scene::update(float deltaTime) {
    static float radius = 15.0f;

    // use program
    program->use();

    // scale teapot
    float scale = 0.5;
    mat4 scaleM;
    scaleM = transpose(mat4(scale, 0.0f, 0.0f, 0.0f,
                            0.0f, scale, 0.0f, 0.0f,
                            0.0f, 0.0f, scale, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f));
    teapot->worldMatrix = scaleM;

    //////////////////////////////
    /* TODO: Problem 2.
    *  Fill in the lines below.
    */
    // TODO : Make the teapot orbit on YZ plane
    float orbitAngle = time / 60.0f;
    vec3 orbitCenter = vec3(0.0f, 0.0f, 0.0f);
    vec3 teapotPosition(orbitCenter.x + radius * cos(orbitAngle),
                        orbitCenter.y + radius * sin(orbitAngle),
                        orbitCenter.z);
    mat4 translateM = glm::translate(mat4(1.0f), teapotPosition);

    // TODO : Rotate the teapot around its own y-axis
    float rotateAngle = time / 30.0f;
    vec3 yAxis = vec3(0.f, 1.f, 0.f);
    mat4 rotateM = glm::rotate(mat4(1.0f), rotateAngle, yAxis);
    teapot->worldMatrix = translateM * rotateM * teapot->worldMatrix;

    //////////////////////////////

    camera->updateViewMatrix();
    camera->updateProjectionMatrix();

    teapot->viewMatrix = camera->viewMatrix;
    teapot->projMatrix = camera->projMatrix;

    light->setup();

    // increase time
    time = time + deltaTime * 100;

    // draw teapot
    teapot->draw();
}

void Scene::dragScreen(float dx,float dy)
{
    float Sensitivity = 0.1;

    float thetaYaw=glm::radians(Sensitivity*dx);

    moveCamera(thetaYaw);
}
void Scene::moveCamera(float theta)
{
    //////////////////////////////
    /* TODO: Problem 3.
     *  Note that u,v,n should always be orthonormal.
     *  The u vector can be accessed via camera->cameraU.
     *  The v vector can be accessed via camera->cameraV.
     *  The n vector can be accessed via camera->cameraN.
     *  === HINT ===
     *  Initial camera position is (60.0f, 60.0f, 60.0f)
     *  Argument theta is amount of camera rotation in radians
     */

    camera->eye = mat3(glm::rotate(theta, vec3(0.f, 1.f, 0.f))) * camera->eye;

     mat4 translateM = glm::translate(mat4(1.0f),
                                     vec3(-1 * camera->eye.x, -1 * camera->eye.y, -1 * camera->eye.z));

    camera->cameraN = normalize(camera->eye - camera->at);
    camera->cameraU = normalize(glm::cross(camera->up, camera->cameraN));
    camera->cameraV = normalize(glm::cross(camera->cameraN, camera->cameraU));

    mat4 rotateM  = transpose(mat4(camera->cameraU.x, camera->cameraU.y, camera->cameraU.z, 0.f,
                               camera->cameraV.x, camera->cameraV.y, camera->cameraV.z, 0.f,
                               camera->cameraN.x, camera->cameraN.y, camera->cameraN.z, 0.f,
                               0.f, 0.f, 0.f, 1.f));
    camera->viewMatrix = rotateM * translateM * camera->viewMatrix;
    //////////////////////////////
}






































