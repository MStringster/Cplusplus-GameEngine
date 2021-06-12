#pragma once
#include "CollisionComponent.h"
//Item type used to determain what kind of pickup this is, will set the Object type appropriately in the constuctor
enum class itemType {HEALTH, WEAPON};

//Colision component for pickups in game
class PickupCollisionComponent : public CollisionComponent
{
private:
	//Circle Hitbox
	Circle2D collisionShape;

public:
	//Constructor, Parameters gameObject - the Owner of the Component,
	//it - the item type, Health or Weapon
	PickupCollisionComponent(GameObject* gameObject, itemType it);

	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();

	//How the object will handle its collisions Parameters: other - the other object this collided with
	virtual void processCollision(GameObject& other);

	//called every frame Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};