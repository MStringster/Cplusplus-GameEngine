#pragma once
#include "mydrawengine.h"

class GameObject;
//object manager used during shooting 
class ObjectManager;

//Handles input, only used by the player avatar in this case a squid
class InputComponent
{

private:
	GameObject* pOwner; //Owner of the component
	ObjectManager* pOM; //object manager

	float shotDelay; //bullet shot delay
	float shotCooldown; //bullet shot cooldown that delay is set too after every shot

	int speed; //speed of the player
public:
	//Constructor, Parameters gameobject - owner of this component
	//om - Game object manager
	InputComponent(GameObject* gameobject, ObjectManager* om);
	//Called every time, Parameters frametime - the time between frames
	void update(float frametime);
	//set the shot cooldown speed, lower number = faster shots, Parameters s = new shot cooldown
	void setShotCooldown(float s);
	//Spawns bullet and shoots it in a direction, parameters: vel - direction of shot
	//offset - where the bullet spawns in relation to the owner
	void shoot(Vector2D vel, Vector2D offset);
};