#pragma once
#include "CollisionComponent.h"
//Colision component used by the goldfish enemy
class FishCollisionComponent : public CollisionComponent
{
private:
	//Circle Hitbox
	Circle2D collisionShape;

public:
	//Constructor, takes in the Owner of the Component
	FishCollisionComponent(GameObject* gameObject);

	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();

	//How the object will handle its collisions Parameters: other - the other object this collided with
	virtual void processCollision(GameObject& other);

	//called every frame Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};