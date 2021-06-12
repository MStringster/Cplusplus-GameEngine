#include "myinputs.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "BulletPhysicsComponent.h"
#include "BulletCollisionComponent.h"
#include "ObjectManager.h"

InputComponent::InputComponent(GameObject* gameobject, ObjectManager* om)
{
	pOwner = gameobject;
	pOM = om;
	shotDelay = 0.0f;
	shotCooldown = 0.5f;
	speed = 700;
}


void InputComponent::update(float frametime)
{
	
	//Character Controller
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	
	//Movement. W - Up, S - Down, D - Right, A - Left, Spacebar - Reset
	//Acceleration used to create a natrual speed up, speed down effect
	if (pInputs->KeyboardIsAvailable())
	{
		if (pInputs->KeyPressed(DIK_S))
		{
			Vector2D acceleration(0, speed);
			pOwner->setVelocity(pOwner->getPhysicsComp()->getVelocity() + acceleration * frametime);
			
		}
		if (pInputs->KeyPressed(DIK_W))
		{
			Vector2D acceleration(0, -speed);
			pOwner->setVelocity(pOwner->getPhysicsComp()->getVelocity() + acceleration * frametime);
		}
		if (pInputs->KeyPressed(DIK_A))
		{
			Vector2D acceleration(-speed, 0);
			pOwner->setVelocity(pOwner->getPhysicsComp()->getVelocity() + acceleration * frametime);
		}
		if (pInputs->KeyPressed(DIK_D))
		{
			Vector2D acceleration(speed, 0);
			pOwner->setVelocity(pOwner->getPhysicsComp()->getVelocity() + acceleration * frametime);
		}

		//Shooting code, if the player presses one of the shooting keys and the shotdelay is less than or equal to zero they will shoot in the corrisponding direction
		//Controls, UPARROW - Shoot up, DOWNARROW - shoot down, LEFTARROW - shoot left, RIGHTARROW - shoot right
		if (pInputs->KeyPressed(DIK_DOWNARROW) && shotDelay <= 0.0f)
		{
			shoot(Vector2D(0, 400.00f), Vector2D(0, 100.0f));
			shotDelay = shotCooldown;
		}
		if (pInputs->KeyPressed(DIK_UPARROW) && shotDelay <= 0.0f)
		{
			shoot(Vector2D(0, -400.00f), Vector2D(0, -100.0f));
			shotDelay = shotCooldown;
		}
		if (pInputs->KeyPressed(DIK_LEFTARROW) && shotDelay <= 0.0f)
		{
			shoot(Vector2D(-400.00f, 0), Vector2D(-100.0f, 0));
			shotDelay = shotCooldown;
		}
		if (pInputs->KeyPressed(DIK_RIGHTARROW) && shotDelay <= 0.0f)
		{
			shoot(Vector2D(400.00f, 0), Vector2D(100.0f, 0));
			shotDelay = shotCooldown;
		}
		
	}
	//decrease shot delay by the frame time
	shotDelay = shotDelay - frametime;

	//Display the owner of this components health in heart images in the top left corner of the screen
	for (int i = 0; i != pOwner->getHealth(); i++)
	{
		PictureIndex heart;
		heart = MyDrawEngine::GetInstance()->LoadPicture(L"full_heart.bmp");
		MyDrawEngine::GetInstance()->DrawAt(MyDrawEngine::GetInstance()->theCamera.getPosition() + Vector2D(-1600, -800) + Vector2D(i * 50, 0), heart, 0.5f, 0.0f, 0.0f);
	}

}

void InputComponent::setShotCooldown(float s)
{
	shotCooldown = s;
}

void InputComponent::shoot(Vector2D vel, Vector2D offset)
{
	//Create bullet object
	GameObject* pBullet = new GameObject;
	//Component creation
	RenderComponent* pBulletRenderComp = new RenderComponent(L"ink_bullets_new.bmp", .5f);
	BulletPhysicsComponent* pBulletPhysicsComp = new BulletPhysicsComponent(pBullet);
	BulletCollisionComponent* pBulletCollisionComp = new BulletCollisionComponent(pBullet);
	//Set the objects components
	pBullet->setRenderer(pBulletRenderComp);
	pBullet->setPhysics(pBulletPhysicsComp);
	pBullet->setCollision(pBulletCollisionComp);
	
	//Spawn the bullet at the owners position + the offset at the speed of the player with the velocity
	pBullet->setPosition(pOwner->getPosition() + offset); 
	pBullet->setVelocity(vel); 

	pBullet->setState(State::ACTIVE);
	//add to the object manager
	pOM->addObject(pBullet);
}