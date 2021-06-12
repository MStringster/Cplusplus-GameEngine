#pragma once
#include "CollisionComponent.h"

//Collision Component for the doors, handles the teleporting of the player to the next room and movement of the camera
class DoorCollisionComponent : public CollisionComponent
{
private:
	//Rectangle hitbox
	Rectangle2D collisionShape;
	//Position the player will be teleported too when they touch the door
	Vector2D teleportPos;
	//What room the camera needs to focus on when the player goes though the door
	GameObject* CameraRoomFocus;

public:
	//Constuctor Parameters: 
	//gameObject - Owner of the component, 
	//outDoor - Location the player will be teleported too when they touch the door, 
	//outRoom - The room the camera needs to foucs on once the player has been teleported
	DoorCollisionComponent(GameObject* gameObject, Vector2D outDoor, GameObject* outRoom);

	//Create and returns the collision shape associated with this object
	virtual IShape2D& getShape();

	//How the object will handle its collisions, Parameters: other - other object this has collided with
	virtual void processCollision(GameObject& other);

	//called every frame Parameters: frametime - takes in time between frames
	void update(float frametime) override;
};