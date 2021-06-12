#include "DoorCollisionComponent.h"
#include "GameObject.h"

DoorCollisionComponent::DoorCollisionComponent(GameObject* gameObject, Vector2D outDoor, GameObject* outRoom)
{
	pOwner = gameObject;
	type = ObjectType::DOORCLOSED;
	teleportPos = outDoor; 
	CameraRoomFocus = outRoom;

}

IShape2D& DoorCollisionComponent::getShape()
{
	//if the door is set to open then the player will be able to access it
	if (type == ObjectType::DOOROPEN)
	{
		collisionShape.PlaceAt(pOwner->getPosition().YValue + 150, pOwner->getPosition().XValue - 200, pOwner->getPosition().YValue - 50, pOwner->getPosition().XValue + 150);
	}
	else
	{
	//else dont place a collision shape

	}
	//debug code
	if (visibleHitboxes == true)
	{
		MyDrawEngine::GetInstance()->FillRect(collisionShape, MyDrawEngine::RED);
	}

	return collisionShape;
}

void DoorCollisionComponent::processCollision(GameObject& other)
{
		//if the squid collides with the door and the THIS door type is not closed then teleport player to the teleport position and move the camera
		if ((other.getCollision()->getObjType() == ObjectType::SQUID) && !(pOwner->getObjectType() == ObjectType::DOORCLOSED))
		{
			other.setPosition(teleportPos);
			MyDrawEngine::GetInstance()->theCamera.PlaceAt(CameraRoomFocus->getPosition());
		}
}

void DoorCollisionComponent::update(float frametime)
{

}
