#include "BubblePhysicsComponent.h"
#include "GameObject.h"

BubblePhysicsComponent::BubblePhysicsComponent(GameObject* gameObject)
{
	pOwner = gameObject;
	lifetime = 2.0f;
}

void BubblePhysicsComponent::update(float frametime)
{
	pOwner->setPosition(pOwner->getPosition() + Vector2D(0, -1.0f));
	pOwner->setTrans(pOwner->getTrans() + 0.02f);
	if (lifetime <= 0)
	{
		pOwner->setState(State::DELETEREADY);
	}

	lifetime = lifetime - frametime;
}
