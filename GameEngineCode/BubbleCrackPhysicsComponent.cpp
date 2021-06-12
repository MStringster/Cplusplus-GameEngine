#include "BubbleCrackPhysicsComponent.h"
#include "GameObject.h"
#include "ObjectManager.h"

BubbleCrackPhysicsComponent::BubbleCrackPhysicsComponent(GameObject* gameObject, ObjectManager* pOM)
{
	pOwner = gameObject;
	om = pOM;
	cooldown = 1.0f;
}

void BubbleCrackPhysicsComponent::update(float frametime)
{
	if (cooldown <= 0)
	{
		SpawnBubbles();
		cooldown = 1.0f;
	}
	cooldown = cooldown - frametime;
}

void BubbleCrackPhysicsComponent::SpawnBubbles()
{
	GameObject* bubble = new GameObject();
	RenderComponent* bubbleRender = new RenderComponent(L"bubble.bmp", 0.4f);
	BubblePhysicsComponent* bubblePhysics = new BubblePhysicsComponent(bubble);
	bubble->setPosition(pOwner->getPosition());
	bubble->setPhysics(bubblePhysics);
	bubble->setRenderer(bubbleRender);
	bubble->setState(State::ACTIVE);
	om->addObject(bubble);
}