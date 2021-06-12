#pragma once
#include "Shapes.h"

class GameObject;

//Enum class that holds the object type, will be used when determaining what objects have collided with each other and how to handle it
enum class ObjectType {DEFAULT, SQUID, ENEMY, BULLET, ENEMYBULLET, BOSSBULLET, WALL, DOORCLOSED, DOOROPEN, TRIGGER, HEALTH, WEAPON, EMPTY};

//SuperClass of the collider components
class CollisionComponent
{
protected:
	//Objects Type for details see Enum above 
	ObjectType type;
	//Owner of the collision component
	GameObject* pOwner;
	//Whether the hitboxes can be seen or not
	bool visibleHitboxes;

public:
	//Constructor
	CollisionComponent();
	//get the type of object to be used in collision
	const ObjectType getObjType();
	//Set the type of object to be used in collision, Parameters: objType - (ENUM) What object this is
	void setObjType(ObjectType objType);
	//Abstract method, Update called every frame, Parameters: frametime - takes in time between frames
	virtual void update(float frametime) = 0;
	//Abstract method, Create and returns the collision shape associated with this object used for collision detection
	virtual IShape2D& getShape() =0;
	//Tell the objects how to interact with one and other when colliding, Parameters: other - other object this has collided with
	virtual void processCollision(GameObject& other);
};