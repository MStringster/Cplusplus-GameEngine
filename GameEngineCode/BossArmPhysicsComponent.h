#pragma once
#include "PhysicsComponent.h"

class GameObject;
class ObjectManager; 
//Boss arms that will move up and down and spawn boss bullets
class BossArmPhysicsComponent : public PhysicsComponent
{
private:
    GameObject* pTarget; //Target the bullets will head towards
    ObjectManager* pOM; //Object mananger for spawning bullets
    float speed; 
    float shootDelay; //shot delay 

public:
    //constructor, parmeters: gameObject - owner of this component
    //player - the target 
    //om - object manager
    BossArmPhysicsComponent(GameObject* gameObject, GameObject* player, ObjectManager* om);
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;
    //spawns bullets, paramters: vel - direction of bullet
    //offset - spawn offset in relation to the owner
    void shoot(Vector2D vel, Vector2D offset);

};