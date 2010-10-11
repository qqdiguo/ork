#include "ork/resource/XMLResourceLoader.h"
#include "ork/resource/ResourceManager.h"
#include "ork/render/FrameBuffer.h"
#include "ork/ui/GlutWindow.h"

using namespace ork::resource;
using namespace ork::render;
using namespace ork::ui;

class SimpleExample : public GlutWindow
{
public:
    Ptr<ResourceManager> resManager;
    Ptr<MeshBuffers> m;
    Ptr<Program> p;

    SimpleExample() : GlutWindow(Window::Parameters())
    {
        Ptr<XMLResourceLoader> resLoader = new XMLResourceLoader();
        resLoader->addPath("resources/textures");
        resLoader->addPath("resources/shaders");
        resLoader->addPath("resources/meshes");

        resManager = new ResourceManager(resLoader);
        m = resManager->loadResource("quad.mesh").cast<MeshBuffers>();
        p = resManager->loadResource("basic;").cast<Program>();
    }

    // rest of the code unchanged
};
