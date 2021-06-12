#include "TurretCollisionComp.h"
#include "GameObject.h"

TurretCollisionComponent::TurretCollisionComponent(GameObject* gameObject)
{
    pOwner = gameObject;
    type = ObjectType::ENEMY;
    OwnerXPos = pOwner->getPosition().XValue;
    OwnerYPos = pOwner->getPosition().YValue;
}

IShape2D& TurretCollisionComponent::getShape()
{
    //position the hitbox in relation to the owners x and y position
    collisionShape.PlaceAt(OwnerYPos + 70, OwnerXPos - 70, OwnerYPos - 70, OwnerXPos + 70);

    if (visibleHitboxes == true)
    {
        MyDrawEngine::GetInstance()->FillRect(collisionShape, MyDrawEngine::RED);
    }
    return collisionShape;
}

void TurretCollisionComponent::processCollision(GameObject& other)
{
    //if other object type is a bullet then the owner of this component takes 1 damage and displayed a red circle to indicate a hit
	if (other.getCollision()->getObjType() == ObjectType::BULLET)
	{
		pOwner->takeDamage(1); 
        MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), 20, MyDrawEngine::RED);
	}

}
//called every frame
void TurretCollisionComponent::update(float frametime)
{
}
