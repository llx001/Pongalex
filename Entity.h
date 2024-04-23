#pragma once
#include "raylib.h"
#include <iostream>

class Entity
{
public:
	Entity();
	Entity(std::string Name);
	Entity(std::string Name, Vector2 Position);
	Entity(std::string Name, Vector2 Position, float Rotation);

	Vector2 GetPosition();
	std::string GetName();
	void Move(Vector2 Movement);
private:
	std::string objectName;
	Vector2 position;
	float yRotation;
};