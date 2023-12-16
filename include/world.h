#ifndef WORLD_H
#define WORLD_H

#include "helper.h"
#include <vector>
#include <memory>
#include "camera.h"
#include "model/model.h"

class World {
public:
    using ModelPtr = std::shared_ptr<Model>;
    using CameraPtr = std::shared_ptr<Camera>;

    World();

    void addModel(ModelPtr model);
    void addModel(std::vector<ModelPtr> model);
    void setCamera(CameraPtr camera);
    //void addLight(Light light);

    void render();

private:
    std::vector<ModelPtr> modelCollection;
    CameraPtr camera;
};

#endif