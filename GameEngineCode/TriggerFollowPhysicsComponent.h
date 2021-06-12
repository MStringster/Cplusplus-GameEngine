#pragma once
#include "PhysicsComponent.h"

class GameObject;
//allows Trigger to follow the enemy it is associtated with
class TriggerFollowPhysicsComponent : public PhysicsComponent
{
private:
	GameObject* pTarget; //follow target 
public:
	//consturctor, parameters: gameObject - owner of the component
	//ft - the following target this will stay with as it moves
	TriggerFollowPhysicsComponent(GameObject* gameObject, GameObject* ft);
	//called every frame, paremeters: frametime - time between frames
	void update(float frametime) override;
};