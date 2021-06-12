#pragma once
#include "CollisionComponent.h"

class TurretCollisionComponent : public CollisionComponent
{
private:
	//Rectangle Hitbox
	Rectangle2D collisionShape;
	//Used to set up the hitbox
	float OwnerXPos;
	float OwnerYPos;
public:
	//Constructor, takes in the Owner of the Component
	TurretCollisionComponent(GameObject* gameObject);
	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();
	//How the object will handle its collisions Parameters: other - the other object this collided with
	virtual void processCollision(GameObject& other);
	//called every frame Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};