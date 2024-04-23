#include "Entity.h"

Entity::Entity() : Entity("GameObject", Vector2{ 0.0f,0.0f }, 0.0f) {}

Entity::Entity(std::string Name) : Entity(Name, Vector2{0.0f,0.0f}, 0.0f) {}

Entity::Entity(std::string Name, Vector2 Position) : Entity(Name, Position, 0.0f) {}

Entity::Entity(std::string Name, Vector2 Position, float Rotation) : objectName(Name), position(Position), yRotation(Rotation) {

	std::cout<< "Entity: (" << Name << ") created at (" << Position.x << "," << Position.y << ") with " << yRotation << " rotation" << std::endl;
}

Vector2 Entity::GetPosition()
{
	return Vector2();
}

std::string Entity::GetName()
{
	return std::string();
}

void Entity::Move(Vector2 Movement)
{
}
