#include "PickupCollisionComponent.h"
#include "GameObject.h"

PickupCollisionComponent::PickupCollisionComponent(GameObject* gameObject, itemType it)
{
    pOwner = gameObject;
    //if this item is a health pickup then set the object type to health
    if (it == itemType::HEALTH)
    {
        type = ObjectType::HEALTH;
    }
    //if this item is a weapon pickup then set the object type to health
    //note: this could be expanded to allow for multiple weapons rahter than just a shot speed upgrade
    if (it == itemType::WEAPON)
    {
        type = ObjectType::WEAPON;
    }

}

IShape2D& PickupCollisionComponent::getShape()
{
    collisionShape.PlaceAt(pOwner->getPosition(), 50);
    if (visibleHitboxes == true)
    {
        MyDrawEngine::GetInstance()->FillCircle(pOwner->getPosition(), 50, MyDrawEngine::RED);
    }
    return collisionShape;
}

void PickupCollisionComponent::processCollision(GameObject& other)
{
}

void PickupCollisionComponent::update(float frametime)
{
}
