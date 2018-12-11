#include "VideoDriver.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
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

	glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "[ERROR]: Init glew loader failed at " << __FILE__ << 
            ": line " << __LINE__ << std::endl;
        return false;
    }

	// output GL Version
	const unsigned char* glVersion = glGetString(GL_VERSION);
    std::cout << "[INFO]: OpenGL Version: " << glVersion << std::endl;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


    return true;
}

bool VideoDriver::initGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 450 core");

	ImGui::StyleColorsDark();

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

	// create light
	m_directionalLight.reset(new DirectionalLight());
	if (!m_directionalLight->init())
	{
		std::cerr << "[ERROR]: Create Directional Light failed at " << __FILE__ <<
			": line " << __LINE__ << std::endl;
		return false;
	}

	m_pointLight.reset(new PointLight());
	if (!m_pointLight->init())
	{
		std::cerr << "[ERROR]: Create Point Light failed at " << __FILE__ <<
			": line " << __LINE__ << std::endl;
		return false;
	}

	// create cube mesh
	m_model.reset(new CubeModel());
	if (!m_model->init())
	{
		std::cerr << "[ERROR]: Init CubeModel failed at " << __FILE__ <<
			": line " << __LINE__ << std::endl;
		return false;
	}
	std::cout << "[INFO]: Init CudeModel successed." << std::endl;

	if (!initGui())
	{
		std::cerr << "[ERROR]: Init Gui failed at " << __FILE__ << ": line " << __LINE__ << std::endl;
		return false;
	}
	std::cout << "[INFO]: Init Gui successed." << std::endl;

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

	// setup directional light
	m_directionalLight->setDirection(1.0f * cosf(totalTime), 1.0f, 1.0f * sinf(totalTime));
	m_directionalLight->render();

	// setup point light
	m_pointLight->setPosition(15.0f * cosf(totalTime), -3.0f, 15.0f * sinf(totalTime));
	m_pointLight->render();
	
	Material material;
	material.ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	material.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	material.shineness = 64;
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
		m_model->render(material);
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
		material.shineness = 32.0f;
		m_model->render(material);
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
		material.shineness = 16.0f;
		m_model->render(material);
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
		material.shineness = 4.0f;
		m_model->render(material);
	}

    return true;
}

bool VideoDriver::renderGui(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Directional Light 
	static float dirLightAmbient[3] = { 0.1f, 0.1f, 0.1f };
	static float dirLightDiffuse[3] = { 0.4f, 0.4f, 0.4f };
	static float dirLightSpecular[3] = { 0.6f, 0.6f, 0.6f };

	ImGui::Begin("Directional Light");
	ImGui::Text("Directional Light");
	ImGui::DragFloat3("Ambient", dirLightAmbient, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat3("Diffuse", dirLightDiffuse, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat3("Specular", dirLightSpecular, 0.01f, 0.0f, 1.0f);
	m_directionalLight->setAmbient(dirLightAmbient[0], dirLightAmbient[1], dirLightAmbient[2]);
	m_directionalLight->setDiffuse(dirLightDiffuse[0], dirLightDiffuse[1], dirLightDiffuse[2]);
	m_directionalLight->setSpecular(dirLightSpecular[0], dirLightSpecular[1], dirLightSpecular[2]);
	ImGui::End();

	// Point Light
	static float pointLightAmbient[3] = { 0.05f, 0.05f, 0.05f };
	static float pointLightDiffuse[3] = { 0.3f, 0.3f, 0.3f };
	static float pointLightSpecular[3] = { 0.4f, 0.4f, 0.4f };
	static float range = 50.0f;
	static float attenuation[3] = { 1.0f, 0.09f, 0.032f };

	ImGui::Begin("Point Light");
	ImGui::Text("Point Light");
	ImGui::DragFloat3("Ambient", pointLightAmbient, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat3("Diffuse", pointLightDiffuse, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat3("Specular", pointLightSpecular, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat3("Attenuation", attenuation, 0.01f, -5.0f, 5.0f);
	ImGui::DragFloat("Range", &range, 1.0f, 0.0f, 200.0f);

	m_pointLight->setAmbient(pointLightAmbient[0], pointLightAmbient[1], pointLightAmbient[2]);
	m_pointLight->setDiffuse(pointLightDiffuse[0], pointLightDiffuse[1], pointLightDiffuse[2]);
	m_pointLight->setSpecular(pointLightSpecular[0], pointLightSpecular[1], pointLightSpecular[2]);
	m_pointLight->setAttenuation(attenuation[0], attenuation[1], attenuation[2]);
	m_pointLight->setRange(range);
	ImGui::End();

	// Assemble together draw data
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return true;
}
