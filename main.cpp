#include "Application.h"

int main()
{
    Application& application = Application::instantiate();
    application.initialize(800u, 800u, "Edurithm: Dijkstra", 30u);
    application.run();
    return 0;
}
