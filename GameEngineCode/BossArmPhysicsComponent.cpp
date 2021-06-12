#include "BossArmPhysicsComponent.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "BossBulletPhysicsComponent.h"
#include "EnemyBulletCollisionComponent.h"

BossArmPhysicsComponent::BossArmPhysicsComponent(GameObject* gameObject, GameObject* player, ObjectManager* om)
{
	pOwner = gameObject;
	pTarget = player;
	velocity = Vector2D(0, 2.0f);
	speed = 0.0f;
	pOM = om;
	shootDelay = 3.0f;
	AI = AIState::ASLEEP;
}

void BossArmPhysicsComponent::update(float frametime)
{
	//if the boss arm is in aggro state then move them up and down
	if (AI == AIState::AGGRO)
	{
		if (pOwner->getPosition() == Vector2D(pOwner->getPosition().XValue, -6900))
		{
			velocity = -velocity;
		}
		if (pOwner->getPosition() == Vector2D(pOwner->getPosition().XValue, -6800))
		{
			velocity = -velocity;
		}
		pOwner->setPosition(pOwner->getPosition() + -velocity);


		//if shoot delay is less than or equal to 0 then shoot and set the shot delay
		if (shootDelay <= 0.0f)
		{
			//Handled by the boss bullet physics Component when the bullet shoots
			shoot(Vector2D(0,0), Vector2D(0, 0));
			shootDelay = 5.0f;
		}
		//decrease shoot delay
		shootDelay = shootDelay - frametime;
	}
	if (AI == AIState::ASLEEP)
	{
		//Purposely empty
	}

}

void BossArmPhysicsComponent::shoot(Vector2D vel, Vector2D offset)
{
	//Create object
	GameObject* pBullet = new GameObject;
	//Create components
	RenderComponent* pBulletRenderComp = new RenderComponent(L"ink_bullets_enemy.bmp", 0.5f);
	EnemyBulletCollisionComponent* pBulletCollisionComp = new EnemyBulletCollisionComponent(pBullet);
	BossBulletPhysicsComponent* pBulletPhysicsComp = new BossBulletPhysicsComponent(pBullet, pTarget, pOM);
	//set object type
	pBulletCollisionComp->setObjType(ObjectType::BOSSBULLET);
	//set components to game object
	pBullet->setRenderer(pBulletRenderComp);
	pBullet->setPhysics(pBulletPhysicsComp);
	pBullet->setCollision(pBulletCollisionComp);

	//spawn bullet in positon with the velocity of the player + the offset and vel
	pBullet->setPosition(pOwner->getPosition() + offset); // 
	pBullet->setVelocity(pOwner->getPhysicsComp()->getVelocity() + vel); // 

	pBullet->setState(State::ACTIVE);
	//add to object manager
	pOM->addObject(pBullet);
}