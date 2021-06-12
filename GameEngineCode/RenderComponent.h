#pragma once
#include "mydrawengine.h"

class RenderComponent
{
private:
	PictureIndex sprite; //image 
	Vector2D position; //position the image will be rendered in
	float direction; //direction the image is facing
	float size; //size of the image

public:
	//Constuctor, parameters: filename - image file
	//s - size of the image
	RenderComponent(const wchar_t* filename, float s);
	//load a new image for the sprite, parameters: filename - image file
	void loadImage(const wchar_t* filename);
	//renders the image to the screen, parameters: pos - position
	//direction - which way it is facing
	//transparency - how see though the image is
	void render(Vector2D pos, float direction, float transparancy);
	
	//getters
	float getSize();
	//setters
	void setSize(float s);
};