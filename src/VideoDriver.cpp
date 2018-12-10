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
	glfwSetFramebufferSizeCallback(m_window, onFramebufferResize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "[ERROR]: Init glad loader failed at " << __FILE__ << 
            ": line " << __LINE__ << std::endl;
        return false;
    }

	// output GL Version
	const unsigned char* glVersion = glGetString(GL_VERSION);
    std::cout << "[INFO]: OpenGL Version: " << glVersion << std::endl;

	glEnable(GL_DEPTH_TEST);

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
    m_shader.reset(new Shader("../shader/shader.vs", "../shader/shader.fs"));
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
    running = running && renderGui(dt);
    end();
    return running;
}

void VideoDriver::begin()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	if (m_camera) m_camera->resize(width, height);
	return true;
}

bool VideoDriver::renderScene(float dt)
{
	static float totalTime = 0.0f;
	totalTime += dt;

	float rotateSpeed = 180.0f;
	
	float cameraSpeed = 5.0f;
	static float cameraPosX = 0.0f;
	static float cameraPosY = 0.0f;
	static float cameraPosZ = 15.0f;

	// keyboard input
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosZ -= cameraSpeed * dt;
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosZ += cameraSpeed * dt;
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosX -= cameraSpeed * dt;
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosX += cameraSpeed * dt;
	if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPosY += cameraSpeed * dt;
	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
		cameraPosY -= cameraSpeed * dt;

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		return false;

	// setup camera
	m_camera->setPosition(cameraPosX, cameraPosY, cameraPosZ);
	m_camera->render();
	
	// setup model
	// cube0 (original)
	{
		// 创建Model
		m_model->resetGeometry();
		m_model->setPosition(0.0f, 3.0f, 0.0f);
		m_model->setRotation(0.0f, 0.0f, 0.0f);

		// 设置shader cbuffer参数
		m_shader->render
		(
			m_model->getWorldMatrix(),
			m_camera->getViewMatrix(),
			m_camera->getProjMatrix()
		);
		// 绘制模型
		m_model->render();
	}

	// cube1 (rotate by X axis)
	{
		m_model->resetGeometry();
		m_model->setPosition(-5.0f, -3.0f, 0.0f);
		m_model->setRotation(rotateSpeed * totalTime, 0.0f, 0.0f);

		m_shader->render
		(
			m_model->getWorldMatrix(),
			m_camera->getViewMatrix(),
			m_camera->getProjMatrix()
		);
		m_model->render();
	}

	// cube2 (rotate by Y axis)
	{
		m_model->resetGeometry();
		m_model->setPosition(0.0f, -3.0f, 0.0f);
		m_model->setRotation(0.0f, rotateSpeed * totalTime, 0.0f);

		m_shader->render
		(
			m_model->getWorldMatrix(),
			m_camera->getViewMatrix(),
			m_camera->getProjMatrix()
		);
		m_model->render();
	}

	// cube3 (rotate by Z axis)
	{
		m_model->resetGeometry();
		m_model->setPosition(5.0f, -3.0f, 0.0f);
		m_model->setRotation(0.0f, 0.0f, rotateSpeed * totalTime);

		m_shader->render
		(
			m_model->getWorldMatrix(),
			m_camera->getViewMatrix(),
			m_camera->getProjMatrix()
		);
		m_model->render();
	}

    return true;
}

bool VideoDriver::renderGui(float dt)
{
    return true;
}
