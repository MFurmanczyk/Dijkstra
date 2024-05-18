//
// Created by MFurmanczyk on 07/05/2024.
//

#include "Application.h"
#include <iostream>
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/VertexArray.hpp"

Application::Application() :
        m_currentState(State::Idle)
        {}

void Application::initialize(unsigned _width, unsigned _height, const std::string& _name, unsigned _frameRate)
{
    if(m_currentState != State::Idle)
    {
        throw std::runtime_error("Cannot initialize object that is already initialized!");
    }

    m_currentState = State::Initializing;
    m_window.create(sf::VideoMode(_width, _height), _name);
    m_window.setFramerateLimit(_frameRate);

}

void Application::run()
{
    if(m_currentState != State::Initializing) throw std::exception();
    m_currentState = State::Running;

    while (m_currentState == State::Running)
    {
        processEvents();

        m_window.clear();



        m_window.display();
    }
}

void Application::processEvents()
{
    sf::Event event{};
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::KeyPressed)
        {
            //process keyboard event
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            //process mouse event
            m_mouseManager.invokeMapping(event.mouseButton);
        }
        else if (event.type == sf::Event::Closed)
        {
            m_currentState = State::Ended;
            return;
        }
    }
}

Application::~Application()
{
    if(m_window.isOpen())
    {
        m_window.close();
    }
}

void Application::leftClick(sf::Vector2i &position)
{
    std::cout << "mouse x: " << position.x << ", mouse y:" << position.y << std::endl;
}

void Application::rightClick(sf::Vector2i &position)
{
    std::cout << "mouse x: " << position.x << ", mouse y:" << position.y << std::endl;
}
