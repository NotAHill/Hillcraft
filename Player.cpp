#include "Player.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Player::Player()
{
	position = { 0, 0, -5.0f };
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
	velocity *= 0.95f;
}

const glm::vec3& Player::getVelocity()
{
	return velocity;
}

void Player::keyboardInput()
{
	glm::vec3 change(0,0,0);
	float speed = 0.5f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{		
		change.x = glm::cos(glm::radians(rotation.y + 90)) * speed;
		// Comment out for xz rotation only
		change.y = glm::sin(glm::radians(rotation.x)) * speed;
		change.z = glm::sin(glm::radians(rotation.y + 90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		change.x = -glm::cos(glm::radians(rotation.y + 90)) * speed;
		// Comment out for xz rotation only
		change.y = -glm::sin(glm::radians(rotation.x)) * speed;
		change.z = -glm::sin(glm::radians(rotation.y + 90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		change.x = glm::cos(glm::radians(rotation.y)) * speed;
		change.z = glm::sin(glm::radians(rotation.y)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		change.x = -glm::cos(glm::radians(rotation.y)) * speed;
		change.z = -glm::sin(glm::radians(rotation.y)) * speed;
	}

	velocity += change;
}

void Player::mouseInput(const sf::RenderWindow& window)
{
	static auto const MAX_ANGLE = 80;
	static auto lastMousePosition = sf::Mouse::getPosition(window);
	static auto lastDeltaPos = sf::Vector2i{ 0, 0 };

	auto deltaPos = sf::Mouse::getPosition() - lastMousePosition;

	if (lastDeltaPos != sf::Vector2i(0, 0))
	{
		rotation.y += deltaPos.x * 0.05f;
		rotation.x += deltaPos.y * 0.05f;
	}

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
	lastDeltaPos = deltaPos;
}