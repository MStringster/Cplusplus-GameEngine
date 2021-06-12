#include "BulletPhysicsComponent.h"
#include "GameObject.h"

BulletPhysicsComponent::BulletPhysicsComponent(GameObject* gameObject)
{
	velocity.set(DEFAULT_VELOCITY);
	lifetime = 2.0f;
	pOwner = gameObject;
}

void BulletPhysicsComponent::update(float frametime)
{
	//shoot bullet in a stright line from its spawn
	pOwner->setPosition(position = position + velocity * frametime);
	//delete object once lifetime hits zero or less
	lifetime = lifetime - frametime;
	if (lifetime <= 0)
	{
		pOwner->setState(State::DELETEREADY);
	}
}

