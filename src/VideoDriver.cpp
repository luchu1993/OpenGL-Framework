#include "VideoDriver.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <functional>

namespace
{
	VideoDriver* activeDriver = nullptr;
}

static void onFramebufferResize(GLFWwindow* window, int width, int height)
{
    activeDriver->resize(width, height);
}

VideoDriver::VideoDriver(GLFWwindow* window, int width, int height)
    : m_window(window)
    , m_screenWidth(width)
    , m_screenHeight(height)
{
    activeDriver = this;
}

bool VideoDriver::initDeviceContext()
{
    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "[ERROR]: Init glad loader failed at " << __FILE__ << 
            ": line " << __LINE__ << std::endl;
        return false;
    }

	// output GL Version
	const unsigned char* glVersion = glGetString(GL_VERSION);
    std::cout << "[INFO]: OpenGL Version: " << glVersion << std::endl;
    
    // depth stencil test
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_STENCIL_TEST);

	glViewport(0, 0, m_screenWidth, m_screenHeight);

    glfwSetFramebufferSizeCallback(m_window, onFramebufferResize);
    
    return true;
}

bool initGui()
{
    return true;
}

bool VideoDriver::init()
{
    if (!initDeviceContext())
    {
        std::cerr << "[ERROR]: Init Device Context failed at " << __FILE__ << 
            ": line " << __LINE__ << std::endl;
        return false;
    }
	std::cout << "[INFO]: Init Device Context successed." << std::endl;

    // compile and bind shaders
    m_shader.reset(new Shader("../shader/shader.vs", "../shader/shader.ps"));
    if (!m_shader->init())
    {
        std::cerr << "[ERROR]: Create Shader Program failed at " << __FILE__ << 
            ": line " << __LINE__ << std::endl;
        return false;
    }
    std::cout << "[INFO]: Init Shader Program successed."  << std::endl;

	// create camera
	float aspect = static_cast<float>(m_screenWidth) / static_cast<float>(m_screenHeight);
	m_camera.reset(new Camera(m_shader->getProgram(), 45.0f, aspect, 0.1f, 100.0f));
	if (!m_camera->init())
	{
		std::cerr << "[ERROR]: Create Camera failed at " << __FILE__ <<
			": line " << __LINE__ << std::endl;
		return false;
	}
	std::cout << "[INFO]: Init Camera successed." << std::endl;

	// create cube mesh
	m_model.reset(new CubeModel());
	if (!m_model->init())
	{
		std::cerr << "[ERROR]: Init CubeModel failed at " << __FILE__ <<
			": line " << __LINE__ << std::endl;
		return false;
	}
	std::cout << "[INFO]: Init CudeModel successed." << std::endl;

    return true;
}

bool VideoDriver::render(float dt)
{
    bool running = false;
    begin();
    running = renderScene(dt);
    running = renderGui(dt) && running;
    end();
    return running;
}

void VideoDriver::begin()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    // glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void VideoDriver::end()
{
    glfwSwapBuffers(m_window);
}

void VideoDriver::cleanup()
{
	m_shader->cleanup();
	m_camera->cleanup();
	m_model->cleanup();
}

bool VideoDriver::resize(int width, int height)
{
    glViewport(0, 0, width, height);
	return true;
}

bool VideoDriver::renderScene(float dt)
{
	// setup camera
	m_camera->setPosition(0.0f, 0.0f, 10.0f);
	m_camera->render();
	
	// setup model
	m_model->setPosition(0.0f, 0.0f, 0.0f);
	m_model->setRotation(45.0f, 45.0f, 45.0f);
	
	m_shader->render
	(
		m_model->getWorldMatrix(),
		m_camera->getViewMatrix(),
		m_camera->getProjectionMatrix()
	);
	m_model->render();

    return true;
}

bool VideoDriver::renderGui(float dt)
{
    return true;
}