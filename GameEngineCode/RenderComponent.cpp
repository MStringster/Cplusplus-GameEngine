#include "RenderComponent.h"

RenderComponent::RenderComponent(const wchar_t* filename, float s)
{
	sprite = MyDrawEngine::GetInstance()->LoadPicture(filename);
	size = s;
}

void RenderComponent::loadImage(const wchar_t* filename)
{
	sprite = MyDrawEngine::GetInstance()->LoadPicture(filename);
}

void RenderComponent::render(Vector2D pos, float direction, float transparancy = 0.0f)
{
	MyDrawEngine::GetInstance()->DrawAt(pos , sprite, size, direction, transparancy);
}

float RenderComponent::getSize()
{
	return size;
}

void RenderComponent::setSize(float s)
{
	size = s;
}
