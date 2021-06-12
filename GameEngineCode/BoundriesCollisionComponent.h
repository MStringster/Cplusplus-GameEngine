#pragma once
#include "CollisionComponent.h"

//Collision Components for the walls around the rooms, takes four rectangles and converts them into a compound shape
class BoundriesCollisionComponent : public CollisionComponent
{
private:
	//Four Rectangles to be used in the creation of the compound shape
	Rectangle2D northWall;
	Rectangle2D eastWall;
	Rectangle2D southWall;
	Rectangle2D westWall;

	//Hitbox, Made up of the four rectangles found above 
	CompoundShape2D collisionShape;
	
	//Used to set up the Rectangles
	float OwnerXPos;
	float OwnerYPos;

public:
	//Constructor, Parameters: gameObject - in owner of the object
	BoundriesCollisionComponent(GameObject* gameObject);
	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();
	//How the object will handle its collisions, Parameters: other - other object this has collided with
	virtual void processCollision(GameObject& other);
	//Called every frame, Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};