#include "RoomManager.h"

void RoomManager::addDoor(GameObject* door)
{
	pDoorsList.push_back(door); //Add door to list
}

void RoomManager::ClearLists()
{
	pDoorsList.clear(); //clear the list
}

void RoomManager::updateRoom(int noEnemies)
{
	//Rudementry system, doors in each room open corrisponding to how many enemies are left

	//Kill the one enemy in the first room, open first room doors
	if (noEnemies == 8)
	{
		std::list<GameObject*>::iterator it1 = pDoorsList.begin();
		std::advance(it1, 0);
		(**it1).getCollision()->setObjType(ObjectType::DOOROPEN);
		(**it1).getRenderComp()->loadImage(L"doorOpen.bmp");
	}
	//kill the three enemies in second room, open the second room doors
	if (noEnemies == 5)
	{
		std::list<GameObject*>::iterator it1 = pDoorsList.begin();
		std::advance(it1, 1);
		(**it1).getCollision()->setObjType(ObjectType::DOOROPEN);
		(**it1).getRenderComp()->loadImage(L"doorOpen.bmp");
		std::advance(it1, 1);
		(**it1).getCollision()->setObjType(ObjectType::DOOROPEN);
		(**it1).getRenderComp()->loadImage(L"doorOpen.bmp");
	}
	//kill the four enemies in the third room, opens the third room doors
	if (noEnemies == 1)
	{
		std::list<GameObject*>::iterator it1 = pDoorsList.begin();
		std::advance(it1, 3);
		(**it1).getCollision()->setObjType(ObjectType::DOOROPEN);
		(**it1).getRenderComp()->loadImage(L"doorOpen.bmp");
		std::advance(it1, 1);
		(**it1).getCollision()->setObjType(ObjectType::DOOROPEN);
		(**it1).getRenderComp()->loadImage(L"doorOpen.bmp");
	}
}
