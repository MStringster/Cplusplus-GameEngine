#pragma once
#include "mydrawengine.h"
#include "PhysicsComponent.h";
#include "RenderComponent.h";
#include "CollisionComponent.h"
#include "fishPhysicsComponent.h"
#include "FishCollisionComponent.h"
#include "PlayerPhysicsComponent.h"
#include "SquidCollisionComponent.h"
#include "InputComponent.h"
#include "BoundriesCollisionComponent.h"
#include "DoorCollisionComponent.h"
#include "TriggerCollisionComponent.h"
#include "TriggerFollowPhysicsComponent.h"
#include "TurretCollisionComp.h"
#include "TurretPhysicsComp.h"
#include "BossArmPhysicsComponent.h"
#include "RockCollisionComponent.h"
#include "BossCollisionComponent.h"
#include "SharkPhysicsComponent.h"
#include "SharkCollisionComponent.h"
#include "PickupCollisionComponent.h"
#include "BubbleCrackPhysicsComponent.h"
#include "BubblePhysicsComponent.h"

//State of the object, INACTIVE is not deleted, DELETEREADY is deleted by object manager
enum class State{ACTIVE, INACTIVE, DELETEREADY};

//Game object
class GameObject
{
protected:
	Vector2D position;
	float direction;
	float size;
	float transparancy;
	int health;

	//Enums
	State active; 

private:
	//Components
	RenderComponent* pRender;
	PhysicsComponent* pPhysics;
	CollisionComponent* pCollision;
	InputComponent* pInput;

public:
	//consturctors
	GameObject();
	virtual ~GameObject();
	
	//Setter
	void setVelocity(Vector2D vel);
	void setPosition(Vector2D pos);
	void setState(State objectState);
	void setDirection(float dir);
	void setHealth(int health);
	void setTrans(float trans);
	
	//Take damage, heal behaves as setters
	void takeDamage(int damage);
	void heal(int healing);

	//Component
	void setRenderer(RenderComponent* RC);
	void setPhysics(PhysicsComponent* PC);
	void setCollision(CollisionComponent* CC);
	void setInput(InputComponent* IC);

	//Getters
	const State isActive();

	const Vector2D getPosition();
	const float getDirection();
	const int getHealth();
	const float getTrans();
	const ObjectType getObjectType();

	//Components
	PhysicsComponent* getPhysicsComp();
	RenderComponent* getRenderComp();
	CollisionComponent* getCollision();
	InputComponent* getInput();
	
	//Collition
	boolean hasCollider();

	//update called every frame
	virtual void update(float frametime); 
};