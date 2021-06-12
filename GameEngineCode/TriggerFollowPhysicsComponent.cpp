#include "TriggerFollowPhysicsComponent.h"
#include "GameObject.h"

TriggerFollowPhysicsComponent::TriggerFollowPhysicsComponent(GameObject* gameObject, GameObject* ft)
{
	pOwner = gameObject;
	pTarget = ft;
}

void TriggerFollowPhysicsComponent::update(float frametime)
{
	pOwner->setPosition(pTarget->getPosition()); //position is the same as the target objects
}
