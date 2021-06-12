#pragma once
#include "CollisionComponent.h"

//Hitbox for bullets, specificly the players, enemy bullets file overrides processCollisions
class BulletCollisionComponent : public CollisionComponent
{
private:
	//Circle Hitbox
	Circle2D collisionShape;

public:
	//Default Constructor to be overridden by EnemyBullet
	BulletCollisionComponent();
	//Constructor, Parameters: gameObject - Owner of the Component
	BulletCollisionComponent(GameObject* gameObject);
	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();
	//How the object will handle its collisions, Parameters: other - other object this has collided with
	virtual void processCollision(GameObject& other);
	//called every frame, Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};