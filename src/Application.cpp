#include "Application.h"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
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
        glfwPollEvents();
        m_isRunning = oneFrame();
    }
    cleanup();

    return 0;
}

bool Application::oneFrame()
{
    float dt = 0.0f;
    bool running = false;

    running = m_videoDriver->render(dt);

    return running;
}
