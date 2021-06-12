#pragma once
#include "GameObject.h"

//walls
class Wall : public GameObject
{
private:
	Rectangle2D collisionShape;


public:
	Wall();
	void initialise(Vector2D pos);
	void update(float frametime); //Abstract

	virtual IShape2D& getShape();
	virtual void processCollision(GameObject& other);

};