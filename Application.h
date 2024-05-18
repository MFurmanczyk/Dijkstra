//
// Created by MFurmanczyk on 07/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_APPLICATION_H
#define EDURITHM_DIJKSTRA_APPLICATION_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "Managers/MouseManager.h"

enum class State
{
    Idle,
    Initializing,
    Running,
    Ended
};


class Application final
{

public:

    void run();
    void initialize(unsigned _width, unsigned _height, const std::string& _name, unsigned _frameRate);
    //inline sf::RenderWindow& getWindow() { return m_window; } //bad idea

    void leftClick(sf::Vector2i& position);
    void rightClick(sf::Vector2i& position);

public:
    ~Application();
    Application(const Application&) = delete;
    void operator=(const Application &) = delete;
    inline static Application& instantiate()
    {
        static Application instance;
        return instance;
    };

private:
    Application();
    void processEvents();

private:
    State                       m_currentState;
    MouseManager                m_mouseManager;
    sf::RenderWindow            m_window;			// Application's window.

};


#endif //EDURITHM_DIJKSTRA_APPLICATION_H
