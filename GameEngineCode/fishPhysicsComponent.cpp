#include "fishPhysicsComponent.h"
#include "GameObject.h"

FishPhysicsComponent::FishPhysicsComponent(GameObject* gameObject, GameObject* player)
{
	velocity.set(DEFAULT_VELOCITY);
	pOwner = gameObject;
	pTarget = player;
	AI = AIState::PATROL;
	Speed = 300.0f;
	previousXLocation = pOwner->getPosition().XValue;

}

void FishPhysicsComponent::update(float frametime)
{
	//if the previous location of the fish is less than the current position then it is travelling right so load right facing image, vice versa for left
	if (previousXLocation < pOwner->getPosition().XValue)
	{
		pOwner->getRenderComp()->loadImage(L"fish_new_right.bmp");
	}
	else if (previousXLocation > pOwner->getPosition().XValue)
	{
		pOwner->getRenderComp()->loadImage(L"fish_new.bmp");
	}
	previousXLocation = pOwner->getPosition().XValue; //store previous x location

	//if AI state is agrro then approch the target consistantly
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

		pOwner->setPosition(pos);
	}
	//if patrol state, move in a line (fish collision will invert velocity)
	if (AI == AIState::PATROL)
	{
		Vector2D pos = pOwner->getPosition();
		pos = pos + velocity * frametime;
		pOwner->setPosition(pos);
	}
	if (AI == AIState::ASLEEP)
	{
		//empty
	}
} 

