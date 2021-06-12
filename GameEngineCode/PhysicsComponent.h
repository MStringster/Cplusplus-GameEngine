#pragma once
#include "mydrawengine.h"
CONST Vector2D DEFAULT_VELOCITY(0, 0); //default velocity
enum class AIState { ASLEEP, PATROL, AGGRO, PLAYER }; //enum class for handling NPC behaviors
class GameObject;
//Physics compoennt abstract class
class PhysicsComponent
{
protected:
	GameObject* pOwner; //owner of the component
	Vector2D position; //position
	Vector2D velocity; //direction the object is heading in
	AIState AI; // the state of the object, used for multiple behaviors

public:
	//called every frame, paremeters: frametime - time between frames
	virtual void update(float frametime) = 0;
	//setters
	virtual void setVelocity(Vector2D vel);
	virtual void setPosition(Vector2D pos);
	void setAIState(AIState ai);

	//getters
	virtual Vector2D getVelocity();
	virtual Vector2D getPosition();
	AIState getAIState();
};