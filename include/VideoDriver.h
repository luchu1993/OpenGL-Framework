#ifndef __VIDEO_DRIVER_H__
#define __VIDEO_DRIVER_H__

#include "Shader.h"
#include "Camera.h"
#include "CubeModel.h"
#include "Light.h"
#include "Texture.h"
#include <memory>

class VideoDriver
{
public:
    VideoDriver(GLFWwindow* window, int width, int height);
    bool init();
    void cleanup();
    bool render(float dt);
    bool resize(int width, int height);
	
protected:
    bool initDeviceContext();
    bool initGui();

    void begin();
    void end();

    bool renderScene(float dt);
    bool renderGui(float dt);

private:
    GLFWwindow* m_window;
    int m_screenWidth;
    int m_screenHeight;

	std::unique_ptr<Shader> m_shader;
	std::unique_ptr<Texture> m_texture;
	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<DirectionalLight> m_directionalLight;
	std::unique_ptr<PointLight> m_pointLight;
	std::unique_ptr<CubeModel> m_model;
};

#endif
