#include "BossBulletPhysicsComponent.h"
#include "gameObject.h"
#include "BulletPhysicsComponent.h"
#include "EnemyBulletCollisionComponent.h"
#include "ObjectManager.h"

BossBulletPhysicsComponent::BossBulletPhysicsComponent(GameObject* gameObject, GameObject* target, ObjectManager* om)
{
	pOwner = gameObject;
	pTarget = target;
	lifetime = 5.0f;
	speed = 300.0f;
	pOM = om;

}

void BossBulletPhysicsComponent::update(float frametime)
{
	//Grow the sprite of the boss bullet over time and have it approch the target
	if (pOwner->getRenderComp()->getSize() < 5.0f)
	{
		pOwner->getRenderComp()->setSize(pOwner->getRenderComp()->getSize() + 0.2f * frametime);

		//get the targets x and y values and take away the owners x and y position,
		//then compute the angle and slowly approch the target
		float dy = pTarget->getPosition().YValue - pOwner->getPosition().YValue;
		float dx = pTarget->getPosition().XValue - pOwner->getPosition().XValue;
		float angle = atan2f(dy, dx);

		float vx = speed * cos(angle);
		float vy = speed * sin(angle);

		Vector2D v = Vector2D(vx, vy);
		Vector2D pos = pOwner->getPosition();
		pos = pos + v * frametime;

		pOwner->setPosition(pos);
	}
	//decrease the lifetime until it hits zero then spawn 6 enemy bullets that fly randomly out, then delete the boss bullet
	lifetime = lifetime - frametime;
	if (lifetime <= 0)
	{
		for (int i = 0; i < 6; i++)
		{
			Vector2D vel(float(rand() % 1000 - 600), float(rand() % 1000 - 600));
			shoot(vel, Vector2D(0, 0));
		}
		pOwner->setState(State::DELETEREADY);
	}
}

void BossBulletPhysicsComponent::shoot(Vector2D vel, Vector2D offset)
{
	//create object
	GameObject* pBullet = new GameObject;
	//create components
	RenderComponent* pBulletRenderComp = new RenderComponent(L"ink_bullets_enemy.bmp", .5f);
	BulletPhysicsComponent* pBulletPhysicsComp = new BulletPhysicsComponent(pBullet);
	EnemyBulletCollisionComponent* pBulletCollisionComp = new EnemyBulletCollisionComponent(pBullet);

	//set objects components
	pBullet->setRenderer(pBulletRenderComp);
	pBullet->setPhysics(pBulletPhysicsComp);
	pBullet->setCollision(pBulletCollisionComp);

	//spawn in using the owners position and velocity + the offset and extra velocity
	pBullet->setPosition(pOwner->getPosition() + offset); // 
	pBullet->setVelocity(pOwner->getPhysicsComp()->getVelocity() + vel); // 

	pBullet->setState(State::ACTIVE);
	//add to object manager
	pOM->addObject(pBullet);
}

