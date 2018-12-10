#include "Application.h"
#include <sstream>

Application* gApplication = nullptr;

Application::Application(const char* appName, int width, int height)
	: m_appName(appName)
	, m_screenWidth(width)
	, m_screenHeight(height)
	, m_isRunning(false)
{
    gApplication = this;
}

bool Application::init()
{
    if (!initWindow())
    {
        std::cerr << "[ERROR]: Init Window failed at "
             << __FILE__ << ": line " << __LINE__ << std::endl;
        return false;
    }
    std::cout << "[INFO]: " << "Init Window successed." << std::endl;

    m_videoDriver.reset(new VideoDriver(m_window, m_screenWidth, m_screenHeight));
    if (!m_videoDriver->init())
    {
        std::cerr << "[ERROR]: Init Video Driver failed at "
             << __FILE__ << ": line " << __LINE__ << std::endl;
        return false;
    }
    std::cout << "[INFO]: " << "Init Video Driver successed." << std::endl;

    return true;
}

bool Application::initWindow()
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, m_appName, nullptr, nullptr);
    if (m_window == nullptr)
    {
        std::cerr << "[ERROR]: Init Window failed at " << __FILE__ << 
            ": line " << __LINE__ << std::endl;
        return false;
    }
    return true;
}

void Application::cleanup()
{
    m_videoDriver->cleanup();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

int Application::run()
{
    std::cout << "[INFO]: Application is running ..." << std::endl;
    m_isRunning = true;
    while (!glfwWindowShouldClose(m_window) && m_isRunning)
    {
        m_isRunning = oneFrame();
		glfwPollEvents();
    }
    cleanup();

    return 0;
}

bool Application::oneFrame()
{
	bool running = false;

	double currentTime;
	static double lastTime;
	static bool isFirstFrame = true;
	static float totalTime = 0.0f;
	static int frameCount = 0;

	if (isFirstFrame)
	{
		lastTime = glfwGetTime();
		isFirstFrame = false;
	}

	currentTime = glfwGetTime();
	float dt = static_cast<float>(currentTime - lastTime);
	lastTime = currentTime;

    running = m_videoDriver->render(dt);
	totalTime += dt;
	++frameCount;

	if (totalTime >= 1.0f)
	{
		std::stringstream title;
		title << m_appName << "  fps: " << frameCount <<
			" frame time: " << totalTime / frameCount * 1000.0f << " ms";
		glfwSetWindowTitle(m_window, title.str().c_str());

		totalTime = 0.0f;
		frameCount = 0;
	}

    return running;
}
