#include "SquidCollisionComponent.h"
#include "GameObject.h"

SquidCollisionComponent::SquidCollisionComponent(GameObject* gameObject)
{
	type = ObjectType::SQUID;
	pOwner = gameObject;
	cooldown = 0.0f;
}

IShape2D& SquidCollisionComponent::getShape()
{
	//Get the x and y values of the owners position and use them to position the hitbox 
	float SquidsXPosition = pOwner->getPosition().XValue;
	float SquidsYPosition = pOwner->getPosition().YValue;
	collisionShape.PlaceAt(SquidsYPosition + 50, SquidsXPosition + 30, SquidsYPosition - 70, SquidsXPosition - 30);

	if (visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillRect(collisionShape, MyDrawEngine::RED);
	}

	 return collisionShape;
}

void SquidCollisionComponent::processCollision(GameObject& other)
{
	ObjectType otherObjectType = other.getCollision()->getObjType();
	//if the other object colided with is a wall then reverse the velocity
	if ((otherObjectType == ObjectType::WALL))
	{
		pOwner->setVelocity(-pOwner->getPhysicsComp()->getVelocity());
	}
	//if the other object collided with is an enemy and the cooldown for being hit is less than or equal to zero then take damage and set cooldown time
	if ((otherObjectType == ObjectType::ENEMY) && (cooldown <= 0.0f))
	{
		pOwner->takeDamage(1);
		cooldown = 2.6f;
	}
	//Set the players velocity to 0 when they walk though an open door
	if ((otherObjectType == ObjectType::DOOROPEN))
	{
		pOwner->setVelocity(Vector2D(0, 0));
	}
	//if the other object collided with is an enemy bullet and the cooldown for being hit is less than or equal to zero then take damage and set cooldown time
	if ((otherObjectType == ObjectType::ENEMYBULLET) && (cooldown <= 0.0f))
	{
		pOwner->takeDamage(1);
		cooldown = 2.6f;
	}
	//if the other object collided with is an Boss bullet and the cooldown for being hit is less than or equal to zero then take damage and set cooldown time
	if ((otherObjectType == ObjectType::BOSSBULLET) && (cooldown <= 0.0f))
	{
		pOwner->takeDamage(2);
		cooldown = 2.6f;
	}
	//if the other object collided with is a health object, and the owners health is less than 10 heal the owner and destory the pickup
	if (otherObjectType == ObjectType::HEALTH && pOwner->getHealth() < 10)
	{
			pOwner->heal(1);
			other.setState(State::DELETEREADY);
	}
	//if the other object collided with is a weapon then set the shot speed cooldown to make the shots faster, also delete the pickup
	if (otherObjectType == ObjectType::WEAPON)
	{
		pOwner->getInput()->setShotCooldown(0.2f);
		other.setState(State::DELETEREADY);
	}
}

void SquidCollisionComponent::update(float frametime)
{
	//if cooldown for being hit is higher than zero then lower it by the frametime also set the transparency back and forth to show the invicibility frames
	if (cooldown > 0.0f)
	{
		cooldown = cooldown - frametime;

		if (pOwner->getTrans() == 0.0f)
		{
			pOwner->setTrans(1.0f);
		}
		else
		{
			pOwner->setTrans(0.0f);
		}
	}
	else
	{
		pOwner->setTrans(0.0f); //makes sure the squid is visible after the invivicibility frames
	}
}
