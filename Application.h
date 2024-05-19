//
// Created by MFurmanczyk on 07/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_APPLICATION_H
#define EDURITHM_DIJKSTRA_APPLICATION_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "Framework/Managers/MouseManager.h"
#include "Framework/Managers/KeyboardManager.h"
#include "Framework/Level/Level.h"

enum class State
{
    Idle,
    Initializing,
    Running,
    Ended
};

/**
 * Top application class. Receives and dispatches all requests. Works as a singleton.
 */
class Application final
{

public:

    void run();
    void initialize(unsigned _size, const std::string& _name, unsigned _frameRate);
    inline Level& getLevel() { return m_level; };

    //inline sf::RenderWindow& getWindow() { return m_window; } //bad idea

public:
    //inputs
    ///Called once LMB is clicked.
    void leftClick(sf::Vector2i& _position);
    ///Called once RMB is clicked.
    void rightClick(sf::Vector2i& _position);
    ///Called once Escape is pressed.
    void closeApplication();

    //BEGIN: Singleton
public:
    ~Application();
    Application(const Application&) = delete;
    void operator=(const Application&) = delete;
    ///Singleton's instance getter.
    inline static Application& instantiate()
    {
        static Application instance;
        return instance;
    };

private:
    Application();
    //END: Singleton

private:
    void processEvents();

private:
    State                       m_currentState;
    MouseManager                m_mouseManager;
    KeyboardManager             m_keyboardManager;
    Level                       m_level;
    sf::RenderWindow            m_window;			// Application's window.

};

#endif //EDURITHM_DIJKSTRA_APPLICATION_H
