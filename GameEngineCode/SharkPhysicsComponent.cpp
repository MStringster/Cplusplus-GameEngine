#include "SharkPhysicsComponent.h"
#include "GameObject.h"

SharkPhysicsComponent::SharkPhysicsComponent(GameObject* gameObject)
{
	pOwner = gameObject;
	pTarget = nullptr;
	AI = AIState::PATROL;
	speed = -600.0f;
	float aggroTime = 0.4f;
	velocity.set(speed, 0);
	previousXLocation = pOwner->getPosition().XValue;
}

void SharkPhysicsComponent::update(float frametime)
{
	//if the previous location of the fish is less than the current position then it is travelling right so load right facing image, vice versa for left
	if (previousXLocation < pOwner->getPosition().XValue)
	{
		pOwner->getRenderComp()->loadImage(L"shark_right.bmp");
	}
	else if (previousXLocation > pOwner->getPosition().XValue)
	{
		pOwner->getRenderComp()->loadImage(L"shark.bmp");
	}
	previousXLocation = pOwner->getPosition().XValue; 

	//if patroling just move in a line (collision component will invert velocity when a wall is hit)
	if (AI == AIState::PATROL)
	{
		Vector2D pos = pOwner->getPosition();
		pos = pos + velocity * frametime;
		pOwner->setPosition(pos);
		aggroTime = 0.4f;
	}
	//same as above but the speed of the movement is raised
	if (AI == AIState::AGGRO)
	{
		Vector2D pos = pOwner->getPosition();
		pos = pos + (velocity * 2) * frametime;
		pOwner->setPosition(pos);
		if (aggroTime <= 0.0f)
		{
			AI = AIState::PATROL;
		}
		aggroTime = aggroTime - frametime;

	}
	if (AI == AIState::ASLEEP)
	{
		//empty
	}
}