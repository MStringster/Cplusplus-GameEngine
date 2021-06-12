#include "BossCollisionComponent.h"
#include "GameObject.h"

BossCollisionComponent::BossCollisionComponent(GameObject* gameObject)
{
	pOwner = gameObject;
	type = ObjectType::ENEMY;
}

IShape2D& BossCollisionComponent::getShape()
{
	collisionShape.PlaceAt(pOwner->getPosition(), 300);
	if (visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), 300, MyDrawEngine::RED);
	}
	return collisionShape;
}

void BossCollisionComponent::processCollision(GameObject& other)
{
	ObjectType otherObjectType = other.getCollision()->getObjType();
	//if the boss is hit with a bullet, do one damage and show a red circle to indicate the hit
	if (otherObjectType == ObjectType::BULLET)
	{
		pOwner->takeDamage(1);
		MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), 200, MyDrawEngine::RED);
	}
}

void BossCollisionComponent::update(float frametime)
{
}
