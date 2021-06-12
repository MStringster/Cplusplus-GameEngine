#pragma once
#include "PhysicsComponent.h"

class GameObject;
class ObjectManager;
//Boss bullets own physics component, these bullets will get bigger and split into enemy bullets
class BossBulletPhysicsComponent : public PhysicsComponent
{
private:
    float lifetime; //how long the boss bullet will stay alive
    GameObject* pTarget; //the target of the bullets
    float speed; 
    ObjectManager* pOM; //object manager for spawning the smaller bullets

public:
    //constructor, parmeters: gameObject - owner of this component
    //player - the target 
    //om - object manager
    BossBulletPhysicsComponent(GameObject* gameObject, GameObject* target, ObjectManager* om);
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;
    //spawns bullets, paramters: vel - direction of bullet
    //offset - spawn offset in relation to the owner
    void shoot(Vector2D vel, Vector2D offset);
};
