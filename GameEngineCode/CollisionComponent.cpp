#include "CollisionComponent.h"
//Constructor, takes in the Owner of the Component
CollisionComponent::CollisionComponent()
{
	type = ObjectType::DEFAULT; //Default type, needs to be set by sub classes
	pOwner = nullptr; //Given to the class in subclass
	visibleHitboxes = false; //Change this to see hitboxes
}
//get the type of object to be used in collision
const ObjectType CollisionComponent::getObjType()
{
	return type;
}

//Set the type of object to be used in collision
void CollisionComponent::setObjType(ObjectType objType)
{
	type = objType;
}

//Tell the objects how to interact with one and other when colliding
void CollisionComponent::processCollision(GameObject& other)
{
	//Empty
}
