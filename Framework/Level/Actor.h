//
// Created by MFurmanczyk on 18/05/2024.
//

#ifndef EDURITHM_DIJKSTRA_ACTOR_H
#define EDURITHM_DIJKSTRA_ACTOR_H


#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include <memory>

class Actor;

template <typename T>
concept ActorBase =  std::is_base_of<Actor, T>::value;


/**
 * Base class for all the object to be present in the level.
 */
class Actor
{

public:

    virtual ~Actor() = default;

    ///Draws actor on the render target.
    virtual void draw(sf::RenderTarget& _target);

    ///Getter for actor position.
    /// @return position of main Drawable component
    virtual sf::Vector2f getPosition() const = 0;

    ///Setter by reference.
    virtual void setPositionByRef(sf::Vector2f& _position) = 0;
    ///Setter by value.
    virtual void setPosition(sf::Vector2f _position) = 0;

    ///Runs every frame and updates state of the object.
    virtual void update(float _deltaTime) = 0;

    ///Getter for main drawable.
    ///@return main Drawable component
    virtual sf::Drawable& getDrawable() = 0;

    ///Creates instance of Actor of given derived type.
    ///Note that at this moment Acton isn't present in the level yet.
    template<ActorBase T>
    static std::shared_ptr<T> createActor()
    {
        return std::make_shared<T>();
    };
};

#endif //EDURITHM_DIJKSTRA_ACTOR_H
