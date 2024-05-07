//
// Created by MFurmanczyk on 07/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_APPLICATION_H
#define EDURITHM_DIJKSTRA_APPLICATION_H

#include "SFML/Graphics/RenderWindow.hpp"

enum class State
{
    Idle,
    Initializing,
    Running,
    Ended
};


class Application {

public:

    void run();
    void initialize(unsigned _width, unsigned _height, const std::string& _name, unsigned _frameRate);

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
    void updateState();

private:
    State                       m_currentState;
    sf::RenderWindow            m_window;			// Application's window.
    //std::shared_ptr<GLevel>   m_level;		// Current level

};


#endif //EDURITHM_DIJKSTRA_APPLICATION_H
