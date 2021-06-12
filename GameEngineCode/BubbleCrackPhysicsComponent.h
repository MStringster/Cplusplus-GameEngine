#pragma once
#include "PhysicsComponent.h"

class GameObject;
class ObjectManager;
//Spawns Bubbles that travel up
class BubbleCrackPhysicsComponent : public PhysicsComponent
{
private:
    ObjectManager* om; //Objectmanager for spawning bubbles
    float cooldown; //cooldown for spawning bubbles
public:
    //constructor, parameters: gameObject - owner of this component
    BubbleCrackPhysicsComponent(GameObject* gameObject, ObjectManager* pOM);
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;

    void SpawnBubbles();

};