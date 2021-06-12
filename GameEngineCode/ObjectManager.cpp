#include "ObjectManager.h" 

//Add pointer to an object to the object list 
void ObjectManager::addObject(GameObject* pNewObject)
{
	pObjectList.push_back(pNewObject);
}

//Render all objects inside the object list 
void ObjectManager::renderAll()
{
	for (GameObject* pNextObject : pObjectList)
	{
		if (pNextObject->isActive() == State::ACTIVE)
		{
			
		}
	}
}

//Update all objects inside the object list 
void ObjectManager::updateAll(float frameTime)
{
	for (GameObject* pNextObject : pObjectList)
	{
		pNextObject->update(frameTime);
	}
}

void ObjectManager::checkAllCollisions()
{
	//Iterators to go though the list
	std::list<GameObject*>::iterator it1; 
	std::list<GameObject*>::iterator it2;

	//Check every object with every object that proceeds it.
	//If they intersect then preform collition code
	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++) //Compare The first object
	{
		for (it2 = std::next(it1); it2 != pObjectList.end(); it2++) //With the first object + 1
		{
			if ((*it1)->isActive() == State::ACTIVE) //Compare if Active
			{
				if ((*it1)->hasCollider() && (*it2)->hasCollider()) //And has a collider
				{
					if ((*it1)->getCollision()->getShape().Intersects((*it2)->getCollision()->getShape())) //get shape
					{
						(*it1)->getCollision()->processCollision((**it2)); //Double *, Dereference the iterator to get a pointer, Dereference the pointer to get the object
						(*it2)->getCollision()->processCollision((**it1));
					}
				}
			}
		}
	}
}

//loop though every object in the object list, delete it, set to null pointer and then clear the list at the end
void ObjectManager::deleteAll()
{
	for (GameObject* pNextObject : pObjectList)
	{
		delete pNextObject;
		pNextObject = nullptr;
	}
	pObjectList.clear();
}

//loop though all game objects check for active flag, if not active delete and set pointer to null. 
//Then move objects to end of list and clear the list
void ObjectManager::deleteInactive()
{
	for (GameObject*& pNext : pObjectList)
	{
		if (pNext->isActive() == State::DELETEREADY)
		{
			delete pNext;
			pNext = nullptr;
		}
	}
	auto it = std::remove(pObjectList.begin(), pObjectList.end(), nullptr);

	pObjectList.erase(it, pObjectList.end());
}

int ObjectManager::getNumberofType(ObjectType OT)
{
	int number = 0;
	std::list<GameObject*>::iterator it1;

	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++)
	{
		if((*it1)->getCollision()->getObjType() == OT)
		{
			number++; //if the object type is the same as the parameter type increase the number
		}
	}
	return number;

}

//Used for Debugging to see the size of the list
int ObjectManager::getSize()
{
	return pObjectList.size();
}

