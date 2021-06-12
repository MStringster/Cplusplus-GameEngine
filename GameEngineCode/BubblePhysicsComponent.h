#pragma once
#include "PhysicsComponent.h"

class GameObject;
class ObjectManager;
//Spawns Bubbles particle that travel up
class BubblePhysicsComponent : public PhysicsComponent
{
private:
    float lifetime; //how long till it pops
    
public:
    //constructor, parameters: gameObject - owner of this component
    BubblePhysicsComponent(GameObject* gameObject);
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;

};