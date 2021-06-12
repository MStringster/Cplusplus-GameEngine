#pragma once
#include "PhysicsComponent.h"

class GameObject;
//controls the physics and AI of the fish
class FishPhysicsComponent : public PhysicsComponent
{
private:

    GameObject* pTarget; //Target the fish will go towards when in aggro mode
    float Speed; //speed of movement
    int previousXLocation; //previous X location, used to determain which picture is loaded (left or right facing)
public:
    //consturctor, parameters: gameObject - owner of this component
    //player - the target the fish will follow when aggroed
    FishPhysicsComponent(GameObject* gameObject, GameObject* player); 
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;

};