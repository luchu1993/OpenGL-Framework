#include "Application.h"

int main(void)
{
    Application app("OpenGL Framework", 800, 600);
    
    if (app.init())
        return app.run();

	return -1;
}