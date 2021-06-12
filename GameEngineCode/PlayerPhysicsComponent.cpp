#include "PlayerPhysicsComponent.h"
#include "GameObject.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameObject* GameObject)
{
	velocity.set(DEFAULT_VELOCITY);
	pOwner = GameObject;
}

void PlayerPhysicsComponent::update(float frametime)
{
	//movement calculations
	Vector2D pos = pOwner->getPosition();
	//Friction that will slow the player
	Vector2D friction = -1 * velocity;
	velocity = velocity + friction * frametime;
	pos = pos + velocity * frametime;
	pOwner->setPosition(pos);

	//MyDrawEngine::GetInstance()->theCamera.PlaceAt(position); //Used for moving camera around squid for debugging
}
