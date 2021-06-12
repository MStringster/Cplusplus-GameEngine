#pragma once
#include "DoorCollisionComponent.h"
#include "ObjectManager.h"

//handles the obpening of doors when the enemies are defeated
class RoomManager
{
protected:
	std::list<GameObject*> pDoorsList; //List of doors 

public:
	//Add door whenever they are created parameters: door - the door
	void addDoor(GameObject* door);
	//clear lists
	void ClearLists();
	//update the room Parameters: noenemies - number of enemies in game
	void updateRoom(int noenemies);
};
