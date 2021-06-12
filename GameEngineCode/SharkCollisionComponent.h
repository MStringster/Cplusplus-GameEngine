#pragma once
#include "CollisionComponent.h"

class SharkCollisionComponent : public CollisionComponent
{
private:
	Circle2D collisionShape;

public:
	//Constructor, Parameters: gameObject - in owner of the object
	SharkCollisionComponent(GameObject* gameObject);
	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();
	//How the object will handle its collisions Parameters: other - the other object this collided with
	virtual void processCollision(GameObject& other);
	//called every frame Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};