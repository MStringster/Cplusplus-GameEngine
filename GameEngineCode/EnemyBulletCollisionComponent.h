#pragma once
#include "BulletCollisionComponent.h"
//Inherits from the bullet collision component, These bullets hurt the player and dont effect the enemies
class EnemyBulletCollisionComponent : public BulletCollisionComponent
{
public:
	//Constructor. Parameters: gameObject - the Owner of the Component
	EnemyBulletCollisionComponent(GameObject* gameObject);
	//How the object will handle its collisions, Parameters: other - other object this has collided with
	virtual void processCollision(GameObject& other);
};