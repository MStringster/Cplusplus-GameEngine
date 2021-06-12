#pragma once
#include "CollisionComponent.h"
//Collision component for the squid/player
class SquidCollisionComponent : public CollisionComponent
{
private:
	//Rectangle hitbox
	Rectangle2D collisionShape;
	//cooldown associated with invincible frames, see update(float frametime) function in .cpp file
	float cooldown;

public:
	//Constructor, Parameters: gameObject - in owner of the object
	SquidCollisionComponent(GameObject* gameObject);
	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();
	//How the object will handle its collisions Parameters: other - the other object this collided with
	virtual void processCollision(GameObject& other);
	//called every frame Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};