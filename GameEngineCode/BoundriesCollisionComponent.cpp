#include "BoundriesCollisionComponent.h"
#include "GameObject.h"

BoundriesCollisionComponent::BoundriesCollisionComponent(GameObject* gameObject)
{
	pOwner = gameObject;
	type = ObjectType::WALL;

	OwnerXPos = pOwner->getPosition().XValue;
	OwnerYPos = pOwner->getPosition().YValue;
}

IShape2D& BoundriesCollisionComponent::getShape()
{
	//place the four walls relative to the object x and y positions position
	southWall.PlaceAt(OwnerYPos + 800,OwnerXPos - 800,OwnerYPos + 900, OwnerXPos + 800);
	eastWall.PlaceAt(OwnerYPos + 880, OwnerXPos + 810, OwnerYPos - 880, OwnerXPos + 870);
	westWall.PlaceAt(OwnerYPos - 880, OwnerXPos - 810, OwnerYPos + 880, OwnerXPos - 870);
	northWall.PlaceAt(OwnerYPos - 800, OwnerXPos + 800, OwnerYPos - 840, OwnerXPos - 800);
	
	//for debug
	if (visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillRect(northWall, MyDrawEngine::RED);
		MyDrawEngine::GetInstance()->FillRect(eastWall, MyDrawEngine::RED);
		MyDrawEngine::GetInstance()->FillRect(southWall, MyDrawEngine::RED);
		MyDrawEngine::GetInstance()->FillRect(westWall, MyDrawEngine::RED);
	}

	//combind the four walls into a single hit box
	collisionShape.AddRectangle(northWall, eastWall, westWall, southWall);

	return collisionShape;
}

void BoundriesCollisionComponent::processCollision(GameObject& other)
{
}

void BoundriesCollisionComponent::update(float frametime)
{

}
