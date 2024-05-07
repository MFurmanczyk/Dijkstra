#include "Application.h"

int main()
{
    Application& application = Application::instantiate();
    application.initialize(960u, 960u, "Edurithm: Dijkstra", 30u);
    application.run();
    return 0;
}
