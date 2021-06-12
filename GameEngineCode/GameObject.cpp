#include "GameObject.h";

GameObject::GameObject()
{
	pRender = nullptr;
	pPhysics = nullptr;
	pCollision = nullptr;
	pInput = nullptr;
	health = 10;
	active = State::INACTIVE;
	transparancy = 0.0f;

}

GameObject::~GameObject()
{
	if (pRender)
	{
		delete pRender;
		pRender = nullptr;
	}
	if (pPhysics)
	{
		delete pPhysics;
		pPhysics = nullptr;
	}
	if (pCollision)
	{
		delete pCollision;
		pCollision = nullptr;
	}
	if (pInput)
	{
		delete pInput;
		pInput = nullptr;
	}
}

const State GameObject::isActive()
{
	return active;
}

void GameObject::setState(State objectState)
{
	active = objectState;
}

void GameObject::setHealth(int h)
{
	health = h;
}

void GameObject::setTrans(float trans)
{
	transparancy = trans;
}

void GameObject::takeDamage(int damage)
{
	health = health - damage;
}

void GameObject::heal(int healing)
{
	health = health + healing;
}

boolean GameObject::hasCollider()
{
	if (pCollision)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameObject::update(float frametime)
{
	if (pPhysics)
	{
		pPhysics->setPosition(position);
	}

	//if the game object is active start updating the components
	if (active == State::ACTIVE)
	{
		//check the gameobject has a renderer component
		if (pRender)
		{
			pRender->render(position, direction, transparancy);
		}
		//check the gameobject has a physics component
		if (pPhysics)
		{
			pPhysics->update(frametime);
		}
		//check the gameobject has a input component
		if (pInput)
		{
			pInput->update(frametime);
		}
		if (pCollision)
		{
			pCollision->update(frametime);
		}
	}

	if (health <= 0)
	{
		active = State::DELETEREADY;
	}
}


const Vector2D GameObject::getPosition()
{
	return position;
}

const int GameObject::getHealth()
{
	return health;
}

const float GameObject::getTrans()
{
	return transparancy;
}

const ObjectType GameObject::getObjectType()
{
	if (pCollision)
	{
		return pCollision->getObjType();
	}
	else
	{
		return ObjectType::EMPTY;
	}
}

const float GameObject::getDirection()
{
	return direction;
}

void GameObject::setDirection(float dir)
{
	direction = dir;
}



void GameObject::setRenderer(RenderComponent* RC)
{
	pRender = RC;
}

void GameObject::setPhysics(PhysicsComponent* PC)
{
	pPhysics = PC;
}

void GameObject::setCollision(CollisionComponent* CC)
{
	pCollision = CC;
}

void GameObject::setInput(InputComponent* IC)
{
	pInput = IC;
}

CollisionComponent* GameObject::getCollision()
{
	if (pCollision)
	{
		return pCollision;
	}
}

InputComponent* GameObject::getInput()
{
	return pInput;
}


void GameObject::setVelocity(Vector2D vel)
{
	pPhysics->setVelocity(vel);
}

PhysicsComponent* GameObject::getPhysicsComp()
{
	return pPhysics;
}

RenderComponent* GameObject::getRenderComp()
{
	if (pRender)
	{
		return pRender;
	}
	else
	{
		return nullptr;
	}
}

void GameObject::setPosition(Vector2D pos)
{
	position.set(pos);
}

