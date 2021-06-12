#include "FishCollisionComponent.h"
#include "GameObject.h"

FishCollisionComponent::FishCollisionComponent(GameObject* gameObject)
{
	type = ObjectType::ENEMY;
	pOwner = gameObject;
	
}

IShape2D& FishCollisionComponent::getShape()
{
	collisionShape.PlaceAt(pOwner->getPosition(), 120);
	
	if (visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), 120, MyDrawEngine::RED);
	}
	return collisionShape;
}

void FishCollisionComponent::processCollision(GameObject& other)
{
	if (other.getCollision()->getObjType() == ObjectType::WALL)
	{
		/*The Below if statements prevent a bug where the fish could travel though walls
		  while in aggro mode*/

		//if the fish is in patrol state, just bounce off wall and go the other way
		if (pOwner->getPhysicsComp()->getAIState() == AIState::PATROL)
		{
			pOwner->setVelocity(Vector2D(0,0) + -pOwner->getPhysicsComp()->getVelocity());
		}
		//if the fish is in aggro state, set the state back to Patrol
		if (pOwner->getPhysicsComp()->getAIState() == AIState::AGGRO)
		{
			pOwner->getPhysicsComp()->setAIState(AIState::PATROL);
		}
	}
	//if the other object is of bullet type then the owner of this component takes 1 damage and displays a red circle to indicate a hit
	if (other.getCollision()->getObjType() == ObjectType::BULLET)
	{
		pOwner->takeDamage(1);
		MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), 60, MyDrawEngine::RED);
	}

}

void FishCollisionComponent::update(float frametime)
{
}
