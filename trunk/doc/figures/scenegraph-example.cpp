#include "ork/resource/XMLResourceLoader.h"
#include "ork/render/FrameBuffer.h"
#include "ork/ui/GlutWindow.h"
#include "ork/taskgraph/MultithreadScheduler.h"
#include "ork/scenegraph/SceneManager.h"

using namespace ork::resource;
using namespace ork::render;
using namespace ork::taskgraph;
using namespace ork::scenegraph;
using namespace ork::ui;

class SimpleExample : public GlutWindow
{
public:
    Ptr<SceneManager> manager;

    SimpleExample() : GlutWindow(Window::Parameters())
    {
        Ptr<XMLResourceLoader> l = new XMLResourceLoader();
        l->addPath("resources/textures");
        l->addPath("resources/shaders");
        l->addPath("resources/meshes");
        l->addPath("resources/methods");
        l->addPath("resources/scenes");

        Ptr<ResourceManager> r = new ResourceManager(l, 8);

        manager = new SceneManager();
        manager->setResourceManager(r);
        manager->setScheduler(new MultithreadScheduler());
        manager->setRoot(r->loadResource("scene").cast<SceneNode>());
        manager->setCameraNode("camera");
        manager->setCameraMethod("draw");
    }

    virtual void redisplay(double t, double dt)
    {
        Ptr<FrameBuffer> fb = FrameBuffer::getDefault();
        fb->clear(true, false, true);
        manager->update(t, dt);
        manager->draw();
        Window::redisplay(t, dt);
    }

    // rest of the code unchanged
};
