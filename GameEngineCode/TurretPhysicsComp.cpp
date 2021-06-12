#include "TurretPhysicsComp.h"
#include "ObjectManager.h"
#include "BulletPhysicsComponent.h"
#include "EnemyBulletCollisionComponent.h"

TurretPhysicsComponent::TurretPhysicsComponent(GameObject* gameObject, GameObject* player, ObjectManager* om)
{
	velocity.set(DEFAULT_VELOCITY);
	pOwner = gameObject;
	pTarget = player;
	AI = AIState::PATROL;
	Speed = 300.0f;
	pOM = om;
	shotDelay = 1.0f;
}

void TurretPhysicsComponent::update(float frametime)
{
	//Aim at the objects target and shoot towards them
	if (AI == AIState::AGGRO)
	{
	float dy = pTarget->getPosition().YValue - pOwner->getPosition().YValue;
	float dx = pTarget->getPosition().XValue - pOwner->getPosition().XValue;
	float angle = atan2f(dy, dx);

	float vx = Speed * cos(angle);
	float vy = Speed * sin(angle);

	Vector2D v = Vector2D(vx, vy);
	Vector2D pos = pOwner->getPosition();
	pos = pos + v * frametime;

	pOwner->setDirection(angle); //set direction to be looking at the player

		//if shot delay is less than or equal to zero then shoot towards the player
		if (shotDelay <= 0.0f)
		{
			shoot(v, Vector2D(0,0));
			shotDelay = 1.0f;
		}
	}
	shotDelay = shotDelay - frametime;

	//Patrol only aim at the target
	if (AI == AIState::PATROL)
	{
		float dy = pTarget->getPosition().YValue - pOwner->getPosition().YValue;
		float dx = pTarget->getPosition().XValue - pOwner->getPosition().XValue;
		float angle = atan2f(dy, dx);

		float vx = Speed * cos(angle);
		float vy = Speed * sin(angle);

		Vector2D v = Vector2D(vx, vy);

		Vector2D pos = pOwner->getPosition();
		pos = pos + v * frametime;

		pOwner->setDirection(angle);
	}
}

void TurretPhysicsComponent::shoot(Vector2D vel, Vector2D offset)
{
	//create object
	GameObject* pBullet = new GameObject;
	//create components
	RenderComponent* pBulletRenderComp = new RenderComponent(L"ink_bullets_enemy.bmp", .5f);
	BulletPhysicsComponent* pBulletPhysicsComp = new BulletPhysicsComponent(pBullet);
	EnemyBulletCollisionComponent* pBulletCollisionComp = new EnemyBulletCollisionComponent(pBullet);
	//set components
	pBullet->setRenderer(pBulletRenderComp);
	pBullet->setPhysics(pBulletPhysicsComp);
	pBullet->setCollision(pBulletCollisionComp);

	//spawn in position and velocity with offset and extra velocity
	pBullet->setPosition(pOwner->getPosition() + offset); // 
	pBullet->setVelocity(pOwner->getPhysicsComp()->getVelocity() + vel); // 

	pBullet->setState(State::ACTIVE);
	//add to object manager
	pOM->addObject(pBullet);
}