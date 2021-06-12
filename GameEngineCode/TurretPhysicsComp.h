#pragma once
#include "PhysicsComponent.h"

class GameObject;
class ObjectManager;
//turret physics and ai behaviours
class TurretPhysicsComponent : public PhysicsComponent
{
private:
    GameObject* pTarget; //target the turret will shoot towards
    float Speed; //speed of shots
    ObjectManager* pOM; //object manager for spawning bullets
    float shotDelay;

public:
    //constructor, parameters: gameObject - owner of this component
    //player - the target the turret will shoot towards
    //om - object manager
    TurretPhysicsComponent(GameObject* gameObject, GameObject* player, ObjectManager* om);
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;
    //spawns bullets, paramters: vel - direction of bullet
    //offset - spawn offset in relation to the owner
    void shoot(Vector2D vel, Vector2D offset);

};