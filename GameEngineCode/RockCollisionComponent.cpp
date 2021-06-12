#include "RockCollisionComponent.h"
#include "GameObject.h"

RockCollisionComponent::RockCollisionComponent(GameObject* gameObject)
{
	pOwner = gameObject;
	type = ObjectType::WALL;
}

IShape2D& RockCollisionComponent::getShape()
{

	float OwnerXPos = pOwner->getPosition().XValue;
	float OwnerYPos = pOwner->getPosition().YValue;

	//place hitbox in relation to the owner x and y values
	collisionShape.PlaceAt(OwnerYPos + 65, OwnerXPos - 65, OwnerYPos - 65, OwnerXPos + 65);

	if (visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillRect(collisionShape, MyDrawEngine::RED);
	}	

	return collisionShape;
}

void RockCollisionComponent::processCollision(GameObject& other)
{
}

void RockCollisionComponent::update(float frametime)
{
}
