#pragma once
#include "PhysicsComponent.h"

class GameObject;

//Shark movement and ai behaviours
class SharkPhysicsComponent : public PhysicsComponent
{
private:
    GameObject* pTarget; 
    float speed; //speed of the object
    float aggroTime; //how long the shark stays in aggro mode
    int previousXLocation; //previous x location used to determain which way the shark is facing
public:
    //constuctor, parameters: gameObject - owner of this component
    SharkPhysicsComponent(GameObject* gameObject);
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;
};