#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "VideoDriver.h"
#include <iostream>
#include <memory>

class Application
{
public:
    Application(const char* appName, int width, int height);
    virtual ~Application() { }

    virtual bool init();
    virtual int run();

protected:
    void cleanup();
    bool initWindow();
    bool oneFrame();

private:
    const char* m_appName;
    int m_screenWidth;
    int m_screenHeight;
    GLFWwindow* m_window;
    bool m_isRunning;

    std::unique_ptr<VideoDriver> m_videoDriver;
};

#endif
