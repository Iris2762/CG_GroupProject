#include "world.h"

std::function<void(GLFWwindow*, int, int)> frameSizeCallback;

World::World() {

}

void World::addModel(ModelPtr model) {
    modelCollection.push_back(model);
}

void World::addModel(std::vector<ModelPtr> model) {
    modelCollection.insert(modelCollection.end(),model.begin(),model.end());
}


void World::setCamera(CameraPtr camera) {
    this->camera = camera;
    frameSizeCallback = [camera](GLFWwindow *window, int width, int height) {
        if(width == 0 || height == 0) {
            return;
        }
        camera->resize(width, height);
        glViewport(0, 0, width, height);
    };
}

void World::render() {
    auto viewMat = camera->getView();
    auto projMat = camera->getProj();
    for(auto &model: modelCollection) {
        model->render(viewMat, projMat);
    }
}