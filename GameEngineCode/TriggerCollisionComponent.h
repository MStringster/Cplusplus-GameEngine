#pragma once
#include "CollisionComponent.h"
//Uses the fish physics component to set the AI state of the enemy associated with the trigger
class FishPhysicsComponent; 

//Trigger collision component that acts as a Zone that changes the state of the AI (passive to aggressive) when the player enters it
class TriggerCollisionComponent : public CollisionComponent
{
private:
	//Circle hitbox/trigger zone
	Circle2D collisionShape;
	//Enemy who is associated with the trigger
	GameObject* fishPhysics;
	//Size of trigger area
	int size;
public:
	//Constructor, Parameters: gameObject - in owner of the object
	//Enemy - Enemy who the trigger will be associated with
	//s - Size of the trigger area
	TriggerCollisionComponent(GameObject* gameObject, GameObject* Enemy, int s);

	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();

	//How the object will handle its collisions Parameters: other - the other object this collided with
	virtual void processCollision(GameObject& other);

	//called every frame Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};