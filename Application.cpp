//
// Created by MFurmanczyk on 07/05/2024.
//

#include "Application.h"
#include "SFML/Window/Event.hpp"

Application::Application() :
        m_currentState(State::Idle)
        {}

void Application::initialize(unsigned _width, unsigned _height, const std::string& _name, unsigned _frameRate)
{
    m_currentState = State::Initializing;

    m_window.create(sf::VideoMode(_width, _height), _name);
    m_window.setFramerateLimit(_frameRate);


}

void Application::run()
{
    m_currentState = State::Running;

    while (m_currentState == State::Running)
    {
        m_window.clear();

        //update here

        m_window.display();
        updateState();
    }
}

void Application::updateState()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
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


