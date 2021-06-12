#pragma once
#include "list"
#include "GameObject.h"

//Object Manager, A list used to manage all objects within the game. Stores pointers to objects within the list
class ObjectManager
{
private:
	std::list<GameObject*> pObjectList;

public:
	//parameters: pNewObject - object to be added to the manager
	void addObject(GameObject* pNewObject);
	//Render all the object in the object manager providing they are active
	void renderAll();
	//Update, parameters: frameTime - time between frames
	void updateAll(float frameTime);
	//Collision Checking
	void checkAllCollisions();
	//Delete all the objects used when game ends
	void deleteAll();
	//Delete all inactive objects
	void deleteInactive();
	//Get number of a specific type found in the manager, Parameters: OT - (Enum) object type
	int getNumberofType(ObjectType OT);
	
	//getter
	int getSize(); //for debugging

};
