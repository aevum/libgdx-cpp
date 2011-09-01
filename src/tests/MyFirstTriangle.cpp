#include <backends/linux/init.hpp>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <linux/LinuxApplication.hpp>

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;
class MyFirstTriangleApplication : public gdx_cpp::ApplicationListener {
public:
    MyFirstTriangleApplication() : mesh(0) , renderCount(0) {
        std::vector< VertexAttribute > attributes;
        attributes.push_back(VertexAttribute(VertexAttributes::Usage::Position, 3, "a_position"));

        mesh = new Mesh(true, 3, 3, attributes);

        std::vector<float> vertices;
        vertices.push_back(-0.5f);
        vertices.push_back(-0.5f);
        vertices.push_back(0);
        vertices.push_back(0.5f);
        vertices.push_back(-0.5f);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(0.5f);
        vertices.push_back(0);
        
        mesh->setVertices(vertices);
        
        std::vector<short int> vi;

        vi.push_back(0);
        vi.push_back(1);
        vi.push_back(2);
        
        mesh->setIndices(vi);
    }
    
    void create() {

    }
    
    void dispose() {
    }
    
    void pause() {
    }
    void render() {
        renderCount++;
        Gdx::app->log("RenderCountTest") << renderCount << std::flush;
        Gdx::gl10->glClearColor(1, 1, 0.5, 1);
        Gdx::gl10->glClear(GL10::GL_COLOR_BUFFER_BIT);
        mesh->render(GL10::GL_TRIANGLES, 0, 3);
        
    }

    void resize(int width, int height) {

    }
    
    void resume() {
    }
private:
    gdx_cpp::graphics::Mesh* mesh;
    int renderCount;
};

int main() {
    gdx_cpp::backends::nix::initializeSystem();
    gdx_cpp::backends::nix::LinuxApplication app(new MyFirstTriangleApplication, "My first Triangle", 640, 480, false);
    
    return 0;
}
