#include "PhysicsComponent.h"
#include "GameObject.h"
void PhysicsComponent::setVelocity(Vector2D vel)
{
	velocity = vel;
}

void PhysicsComponent::setPosition(Vector2D pos)
{
	position = pos;
}

Vector2D PhysicsComponent::getVelocity()
{
	return velocity;
}
Vector2D PhysicsComponent::getPosition()
{
	return position;
}

void PhysicsComponent::setAIState(AIState ai)
{
	AI = ai;
}

AIState PhysicsComponent::getAIState()
{
	return AI;
}
