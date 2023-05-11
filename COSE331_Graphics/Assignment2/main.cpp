#include "main.h"

void surfaceCreated(AAssetManager* aAssetManager) {
    //////////////////////////////
    /* TODO: Problem 1 : Implement Z-buffering
     *  Fill in the lines below.
     *  === HINT ===
     *  Use gl Functions
     */
    glClearDepthf(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //////////////////////////////

    //////////////////////////////
    /* TODO: Problem 4 : Implement alpha blending
     *  Fill in the lines below.
     *  === HINT ===
     *  Use gl Functions
     */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //////////////////////////////

    Scene::setup(aAssetManager);
}

void surfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    Scene::screen(width, height);
}

void drawFrame(float deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::update(deltaTime);
}
void mouseDownEvents(float x, float y) {
    Scene::mouseDownEvents(x, y);
}

void mouseMoveEvents(float x, float y) {
    Scene::mouseMoveEvents(x, y);
}

