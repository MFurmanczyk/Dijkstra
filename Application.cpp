//
// Created by MFurmanczyk on 07/05/2024.
//

#include "Application.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "Framework/Level/Points/DestinationPoint.h"
#include <iostream>

Application::Application() :
        m_currentState(State::Idle)
        {}

void Application::initialize(unsigned _size, const std::string& _name, unsigned _frameRate)
{
    if(m_currentState != State::Idle)
    {
        throw std::runtime_error("Cannot initialize object that is already initialized!");
    }

    m_currentState = State::Initializing;

    //setup window
    m_window.create(sf::VideoMode(_size, _size), _name);
    m_window.setFramerateLimit(_frameRate);

    //load level from file (map and graph)
    m_level.loadFromFile(
            "../../Resources/level1.lvl",
            "../../Resources/level1.graph",
            m_window.getSize());

}

void Application::run()
{
    if(m_currentState != State::Initializing) throw std::exception();
    m_currentState = State::Running;

    sf::Clock clock;
    float deltaTime = 1/30.f;
    while (m_currentState == State::Running)
    {
        float frameStart = clock.getElapsedTime().asSeconds();
        processEvents();
        m_window.clear();

        m_level.update(deltaTime);
        m_level.draw(m_window);

        m_window.display();
        deltaTime = clock.getElapsedTime().asSeconds() - frameStart;
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
            m_keyboardManager.invokeMapping(event.key);
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

void Application::leftClick(const sf::Vector2i& _position)
{
    m_level.setStartPoint(sf::Vector2f(_position));
}

void Application::rightClick(const sf::Vector2i& _position)
{
    m_level.setDestinationPoint(sf::Vector2f(_position));
}

void Application::closeApplication()
{
    m_currentState = State::Ended;
}

void Application::resetLevel()
{
    m_level.reset();
}
