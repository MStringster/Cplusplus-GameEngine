#include "TriggerCollisionComponent.h"
#include "fishPhysicsComponent.h"
#include "GameObject.h"

TriggerCollisionComponent::TriggerCollisionComponent(GameObject* gameObject, GameObject* fish, int s)
{
	pOwner = gameObject;
	fishPhysics = fish;
	size = s;
}

IShape2D& TriggerCollisionComponent::getShape()
{
	collisionShape.PlaceAt(pOwner->getPosition(), size);
	if (visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), size, MyDrawEngine::RED);
	}
	return collisionShape;

}

void TriggerCollisionComponent::processCollision(GameObject& other)
{
	//if the other object inside the trigger zone is a squid set the AI state to aggro
	if (other.getCollision()->getObjType() == ObjectType::SQUID)
	{
		fishPhysics->getPhysicsComp()->setAIState(AIState::AGGRO);
	}
}

void TriggerCollisionComponent::update(float frametime)
{

}
