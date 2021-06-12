#pragma once
#include "GameObject.h"

//Builder to return game object pointers for different objects in the game
class EntityBuilder
{
private:

public:
	//constructor
	EntityBuilder();
	//Room Parameters: pos - position
	GameObject* buildRoom(Vector2D pos);
	//Door Parameters: pos - position
	//outRoom - the room the camara will be looking at
	//outRoomPos - the position the player will be in when they touch the door
	GameObject* buildDoor(Vector2D pos, GameObject* outRoom, Vector2D outRoomPos);
	//Goldfish Parameters: pos - position
	//vel - velocity of the object
	//pTarget - the target of the goldfish it will approch when in aggro mode
	GameObject* buildGoldFish(Vector2D pos, Vector2D vel, GameObject* pTarget);
	//Trigger zone Parameters: parent - Enemy object releated to trigger
	//size - size of the trigger zone
	GameObject* buildEnemyTriggerZone(GameObject* parent, int size);
	//Turret Parameters: pos - position
	//pTarget - target of the turret that it shoots towards
	//om - object manager to spawn bullets
	GameObject* buildTurret(Vector2D pos, GameObject* pTarget, ObjectManager* om);
	//Rock Parameters: pos - position
	//color - which rock color out of three, 0 - orange, 1 - blue, 2 - brown, default - orange
	GameObject* buildRock(Vector2D pos, int color);
	//Shark Parameters: pos - position
	GameObject* buildShark(Vector2D pos);
	//Squid Parameters: pos - position
	//om - object manager for spawning bullets
	GameObject* buildSquidPlayer(Vector2D pos, ObjectManager* om);
	//Boss head
	GameObject* buildBossHead();
	//Boss arms Parameters: Pos - position
	//arm - which arm 1 for left, 2 for right, default left
	//om - object manager for spawning boss bullets
	GameObject* buildBossArm(Vector2D pos, int arm, GameObject* target, ObjectManager* om);
	//heart pickup Parameters: pos - position
	GameObject* buildHeartPickup(Vector2D pos);
	//ShotSpeed pickup Parameters: pos - position
	GameObject* buildShotSpeedPowerUp(Vector2D pos);
	//Particle effect, bubbles coming out of crack
	GameObject* buildBubbles(Vector2D pos, ObjectManager* om);
};