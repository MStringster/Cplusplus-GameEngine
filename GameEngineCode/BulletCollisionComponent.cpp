#include "BulletCollisionComponent.h"
#include "GameObject.h"

BulletCollisionComponent::BulletCollisionComponent()
{
}

BulletCollisionComponent::BulletCollisionComponent(GameObject* gameObject)
{
	type = ObjectType::BULLET;
	pOwner = gameObject;

}

IShape2D& BulletCollisionComponent::getShape()
{
	collisionShape.PlaceAt(pOwner->getPosition(), pOwner->getRenderComp()->getSize() * 50);
	
	if (visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), pOwner->getRenderComp()->getSize(), MyDrawEngine::RED);
	}

	return collisionShape;
}

void BulletCollisionComponent::processCollision(GameObject& other)
{
	ObjectType otherObjectType = other.getCollision()->getObjType();
	//Destory Bullet if it hits a wall
	if (otherObjectType == ObjectType::ENEMY || otherObjectType == ObjectType::WALL)
	{
		pOwner->setState(State::DELETEREADY); 
	}

}

void BulletCollisionComponent::update(float frametime)
{
}
