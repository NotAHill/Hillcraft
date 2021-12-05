#include "Player.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Player::Player()
{
	position = { 0, 0, -5 };
	velocity = { 0, 0, 0 };
}

void Player::handleInput(const sf::RenderWindow& window)
{
	keyboardInput();
	mouseInput(window);
}

void Player::update(float deltaTime)
{
	position += velocity * deltaTime;

	// Deceleration
	velocity *= 0.5;
}

const Vector3& Player::getVelocity()
{
	return velocity;
}

void Player::keyboardInput()
{
	Vector3 deltaV(0.0f, 0.0f, 0.0f);
	float angularSpeed = 0.5f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		deltaV.x = glm::cos(glm::radians(rotation.y + 90)) * angularSpeed;
		deltaV.z = glm::sin(glm::radians(rotation.y + 90)) * angularSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		deltaV.x = -glm::cos(glm::radians(rotation.y + 90)) * angularSpeed;
		deltaV.z = -glm::sin(glm::radians(rotation.y + 90)) * angularSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		deltaV.x = glm::cos(glm::radians(rotation.y)) * angularSpeed;
		deltaV.z = glm::sin(glm::radians(rotation.y)) * angularSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		deltaV.x = -glm::cos(glm::radians(rotation.y)) * angularSpeed;
		deltaV.z = -glm::sin(glm::radians(rotation.y)) * angularSpeed;
	}

	velocity += deltaV;
}

void Player::mouseInput(const sf::RenderWindow& window)
{
	static auto const MAX_ANGLE = 80;
	static auto lastMousePosition = sf::Mouse::getPosition(window);
	auto deltaPos = sf::Mouse::getPosition() - lastMousePosition;

	rotation.y += deltaPos.x * 0.05f;
	rotation.x += deltaPos.y * 0.05f;

	// Rotation along x-axis (yz plane)
	if (rotation.x > MAX_ANGLE)			rotation.x = MAX_ANGLE;
	else if (rotation.x < -MAX_ANGLE)	rotation.x = -MAX_ANGLE;

	// Rotation along y-axis (xz plane)
	if (rotation.y > 360)       rotation.y = 0;
	else if (rotation.y < 0)    rotation.y = 360;

	auto centerX = static_cast<int>(window.getSize().x / 2);
	auto centerY = static_cast<int>(window.getSize().y / 2);

	sf::Mouse::setPosition({ centerX, centerY }, window);

	lastMousePosition = sf::Mouse::getPosition();
}
