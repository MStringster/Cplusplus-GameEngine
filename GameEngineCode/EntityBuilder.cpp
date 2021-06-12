#include "EntityBuilder.h"

EntityBuilder::EntityBuilder()
{
}

//Used to Build Rooms, Parameters: Position of room, 
GameObject* EntityBuilder::buildRoom(Vector2D pos)
{
	//Create Object
	GameObject* pRoom = new GameObject();
	pRoom->setPosition(pos);
	
	//Create and set Components
	RenderComponent* pRoomRenderComp = new RenderComponent(L"background_black_lighter.bmp", 1.2f);
	BoundriesCollisionComponent* pRoomCollisionComp = new BoundriesCollisionComponent(pRoom);
	pRoom->setCollision(pRoomCollisionComp);
	pRoom->setRenderer(pRoomRenderComp);

	pRoom->setState(State::ACTIVE);
	return pRoom;
}

//Used to Build Doors, Parameters: Position of Door,  Destination Room, Destination Position
GameObject* EntityBuilder::buildDoor(Vector2D pos, GameObject* outRoom, Vector2D outRoomPos)
{
	//Create Object
	GameObject* pDoor = new GameObject();
	pDoor->setPosition(pos);
	//Create and set Components
	RenderComponent* pDoorRenderComp = new RenderComponent(L"doorClosed.bmp", 1.0f);
	DoorCollisionComponent* pDoorCollisionComp = new DoorCollisionComponent(pDoor, outRoomPos, outRoom);
	pDoor->setRenderer(pDoorRenderComp);
	pDoor->setCollision(pDoorCollisionComp);

	pDoor->setState(State::ACTIVE);
	return pDoor;
}


/* Loads Goldfish Enemy. Parameters: Position, Velocity, Target for Aiming */
GameObject* EntityBuilder::buildGoldFish(Vector2D pos, Vector2D vel, GameObject* pTarget)
{
	//Create Object
	GameObject* pGoldFish = new GameObject(); //Create the Game Object

	//Create and set Components
	RenderComponent* pRenderComponent = new RenderComponent(L"fish_new.bmp", 0.6f); 
	FishPhysicsComponent* pPhysicsComponent = new FishPhysicsComponent(pGoldFish, pTarget); 
	pPhysicsComponent->setVelocity(vel); 
	FishCollisionComponent* pCollisionComponent = new FishCollisionComponent(pGoldFish);
	pGoldFish->setRenderer(pRenderComponent); 
	pGoldFish->setPhysics(pPhysicsComponent); 
	pGoldFish->setCollision(pCollisionComponent);

	pGoldFish->setPosition(pos); 
	pGoldFish->setHealth(5);
	pGoldFish->setState(State::ACTIVE);
	return pGoldFish;
}

/*Loads A trigger zone that is treated as another collision box altering enemy behaviors
	Parameters: Attached Enemy*/
GameObject* EntityBuilder::buildEnemyTriggerZone(GameObject* parent, int size)
{
	//Create Object
	GameObject* pGoldfishTrigger = new GameObject();
	//Create and set Components
	TriggerCollisionComponent* pTriggerCollisionComp = new TriggerCollisionComponent(pGoldfishTrigger, parent, size);
	TriggerFollowPhysicsComponent* pTriggerPhysicsComp = new TriggerFollowPhysicsComponent(pGoldfishTrigger, parent);
	pGoldfishTrigger->setPhysics(pTriggerPhysicsComp);
	pGoldfishTrigger->setCollision(pTriggerCollisionComp);

	pGoldfishTrigger->setState(State::ACTIVE);
	return pGoldfishTrigger;
}

GameObject* EntityBuilder::buildTurret(Vector2D pos, GameObject* pTarget, ObjectManager* om)
{
	//Create Object
	GameObject* pTurret = new GameObject();
	pTurret->setPosition(pos);
	//Create and set Components
	RenderComponent* pRenderComponent = new RenderComponent(L"Turret.bmp", 0.7f);
	TurretCollisionComponent* pCollisionComponent = new TurretCollisionComponent(pTurret);
	TurretPhysicsComponent* pPhysicsComponent = new TurretPhysicsComponent(pTurret, pTarget, om);
	pTurret->setPhysics(pPhysicsComponent);
	pTurret->setRenderer(pRenderComponent);
	pTurret->setCollision(pCollisionComponent);

	pTurret->setHealth(5);
	pTurret->setState(State::ACTIVE);
	return pTurret;
}

//Creates Rocks in a set either by row or column Parameters: Position, Color of rock (0 - Orange, 1 - Blue, 2 - Brown)
GameObject* EntityBuilder::buildRock(Vector2D pos, int color)
{
	//Create Object
	GameObject* pRock = new GameObject();
	//Create and set Components
	RenderComponent* pRockRender = new RenderComponent(L"Rocks_Orange.bmp", 1.0f);
	RockCollisionComponent* pRockCollision = new RockCollisionComponent(pRock);
	pRock->setPosition(pos);
	pRock->setRenderer(pRockRender);
	pRock->setCollision(pRockCollision);
	//set the picture according to desired colour
	switch (color)
	{
	case 0:
		pRockRender->loadImage(L"Rocks_Orange.bmp");
		break;
	case 1:
		pRockRender->loadImage(L"Rocks_Blue.bmp");
		break;
	case 2:
		pRockRender->loadImage(L"Rocks_Brown.bmp");
		break;
	default:
		pRockRender->loadImage(L"Rocks_Orange.bmp");
		break;
	}

	pRock->setState(State::ACTIVE);
	return pRock;
}

GameObject* EntityBuilder::buildShark(Vector2D pos)
{
	//Create Object
	GameObject* pShark = new GameObject();
	//Create and set Components
	RenderComponent* pSharkRenderComp = new RenderComponent(L"shark.bmp", 0.5f);
	SharkPhysicsComponent* pSharkPhysicsComp = new SharkPhysicsComponent(pShark);
	SharkCollisionComponent* pSharkCollisionComp = new SharkCollisionComponent(pShark);
	pShark->setPosition(pos);
	pShark->setRenderer(pSharkRenderComp);
	pShark->setPhysics(pSharkPhysicsComp);
	pShark->setCollision(pSharkCollisionComp);

	pShark->setHealth(8);
	pShark->setState(State::ACTIVE);
	return pShark;
}

GameObject* EntityBuilder::buildSquidPlayer(Vector2D pos, ObjectManager* om)
{
	//Create Object
	GameObject* pSquid = new GameObject();
	//Create and set Components
	RenderComponent* pSquidRenderComp = new RenderComponent(L"squid.bmp", 2.0f);
	PlayerPhysicsComponent* pSquidPhysicsComp = new PlayerPhysicsComponent(pSquid);
	SquidCollisionComponent* pSquidCollision = new SquidCollisionComponent(pSquid);
	InputComponent* pSquidInputComp = new InputComponent(pSquid, om);
	pSquid->setRenderer(pSquidRenderComp);
	pSquid->setPhysics(pSquidPhysicsComp);
	pSquid->setCollision(pSquidCollision);
	pSquid->setInput(pSquidInputComp);

	pSquid->setPosition(pos);
	pSquid->setState(State::ACTIVE);

	return pSquid;
}

GameObject* EntityBuilder::buildBossHead()
{
	//Create Object
	GameObject* pBoss = new GameObject();
	//Create and set Components
	RenderComponent* pBossRender = new RenderComponent(L"Boss_Head.bmp", 1.0f);
	BossCollisionComponent* pBossCollision = new BossCollisionComponent(pBoss);
	pBoss->setRenderer(pBossRender);
	pBoss->setCollision(pBossCollision);
	pBoss->setPosition(Vector2D(0, -7000));

	pBoss->setHealth(30);
	pBoss->setState(State::ACTIVE);
	return pBoss;
}

GameObject* EntityBuilder::buildBossArm(Vector2D pos, int arm, GameObject* target, ObjectManager* om)
{
	//Create Object
	GameObject* pBossLeftArm = new GameObject();
	//Create and set Components
	RenderComponent* pBossLeftRender = new RenderComponent(L"Boss_Hand_Left.bmp", 1.0f);
	if (arm == 0)
	{
		pBossLeftRender->loadImage(L"Boss_Hand_Right.bmp");
	}
	BossArmPhysicsComponent* pBossLeftPhysicsComp = new BossArmPhysicsComponent(pBossLeftArm, target, om);
	pBossLeftArm->setRenderer(pBossLeftRender);
	pBossLeftArm->setPhysics(pBossLeftPhysicsComp);

	pBossLeftArm->setPosition(pos);
	pBossLeftArm->setState(State::ACTIVE);
	return pBossLeftArm;
}

GameObject* EntityBuilder::buildHeartPickup(Vector2D pos)
{
	//Create Object
	GameObject* pHeartPickup = new GameObject();
	//Create and set Components
	RenderComponent* pHeart = new RenderComponent(L"full_heart.bmp", 0.3);
	PickupCollisionComponent* pHeartCollision = new PickupCollisionComponent(pHeartPickup, itemType::HEALTH);
	pHeartPickup->setRenderer(pHeart);
	pHeartPickup->setCollision(pHeartCollision);

	pHeartPickup->setPosition(pos);
	pHeartPickup->setState(State::ACTIVE);
	return pHeartPickup;
}

GameObject* EntityBuilder::buildShotSpeedPowerUp(Vector2D pos)
{
	//Create Object
	GameObject* pShotSpeedPickup = new GameObject();
	//Create and set Components
	RenderComponent* pShotSpeedRenderComp = new RenderComponent(L"powerup.bmp", 0.3);
	PickupCollisionComponent* pShotSpeedPickupCollComp = new PickupCollisionComponent(pShotSpeedPickup, itemType::WEAPON);
	pShotSpeedPickup->setRenderer(pShotSpeedRenderComp);
	pShotSpeedPickup->setCollision(pShotSpeedPickupCollComp);

	pShotSpeedPickup->setPosition(pos);
	pShotSpeedPickup->setState(State::ACTIVE);
	return pShotSpeedPickup;
}

GameObject* EntityBuilder::buildBubbles(Vector2D pos, ObjectManager* om)
{
	GameObject* pBubblesCrack = new GameObject();
	RenderComponent* bubblesRenderComp = new RenderComponent(L"bubbles_source.bmp", 1.0f);
	BubbleCrackPhysicsComponent* bubblesPhysics = new BubbleCrackPhysicsComponent(pBubblesCrack, om);
	pBubblesCrack->setRenderer(bubblesRenderComp);
	pBubblesCrack->setPhysics(bubblesPhysics);
	pBubblesCrack->setPosition(pos);
	pBubblesCrack->setState(State::ACTIVE);
	return pBubblesCrack;
}
