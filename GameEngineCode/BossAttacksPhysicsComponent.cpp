#include "BossAttacksPhysicsComponent.h"
#include "GameObject.h"

BossAttacksPhysicsComponent::BossAttacksPhysicsComponent(GameObject* gameObject, GameObject* player)
{
	pOwner = gameObject;
	pTarget = player;
	attackCooldown == 5.0f;
}

void BossAttacksPhysicsComponent::update(float frametime)
{
	if (attackCooldown == 0)
	{
		pOwner->setState(State::ACTIVE);

	}
}
