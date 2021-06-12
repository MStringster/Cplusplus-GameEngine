#include "SharkCollisionComponent.h"
#include "GameObject.h"

SharkCollisionComponent::SharkCollisionComponent(GameObject* gameObject)
{
	type = ObjectType::ENEMY;
	pOwner = gameObject;

}

IShape2D& SharkCollisionComponent::getShape()
{
	collisionShape.PlaceAt(pOwner->getPosition(), 120);
	if(visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), 120, MyDrawEngine::RED);
	}
	return collisionShape;
}

void SharkCollisionComponent::processCollision(GameObject& other)
{
	//if the object collided with is a wall reverse the velocity of the owner of this component
	if (other.getCollision()->getObjType() == ObjectType::WALL)
	{
			pOwner->setVelocity(Vector2D(0,0) + -pOwner->getPhysicsComp()->getVelocity());
		
	}
	//if the other object collided with is a bullet, owner object take one damage and display a red circle as a hit indicator
	if (other.getCollision()->getObjType() == ObjectType::BULLET)
	{
		pOwner->takeDamage(1);
		MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), 60, MyDrawEngine::RED);
	}
}

void SharkCollisionComponent::update(float frametime)
{
}
