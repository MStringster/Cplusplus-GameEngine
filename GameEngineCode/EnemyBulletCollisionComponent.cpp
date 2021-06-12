#include "EnemyBulletCollisionComponent.h"
#include "GameObject.h"

EnemyBulletCollisionComponent::EnemyBulletCollisionComponent(GameObject* gameObject)
{
	type = ObjectType::ENEMYBULLET;
	pOwner = gameObject;

}

void EnemyBulletCollisionComponent::processCollision(GameObject& other)
{
	//if the other object is the squid or wall then destory the bullet
	if (other.getCollision()->getObjType() == ObjectType::SQUID || other.getCollision()->getObjType() == ObjectType::WALL)
	{
		pOwner->setState(State::DELETEREADY);
	}
}
