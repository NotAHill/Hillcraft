#include "Player.h"

#include "../Config.h"
#include "../Util/Statistics.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Player::Player() :
	flyMode(false),
	inAir(true)
{
	position = { 10.0f, 10.0f, 10.0f };
	rotation = { 0, 180, 0 };
	velocity = { 0, 0, 0 };
}

void Player::handleInput(const sf::RenderWindow& window)
{
	keyboardInput();
	mouseInput(window);
}

void Player::toggleFlight()
{
	flyMode = !flyMode;
}

void Player::update(float deltaTime, Terrain& terrain)
{
	Statistics::get().addText("Current chunk: (" + std::to_string((int)terrain.offset.x) + ", " + std::to_string((int)terrain.offset.y) + ")");

	// Do gravity calculation
	if (!flyMode) velocity.y += Config::GRAVITY;

	// Update position based on velocity
	position += velocity * deltaTime;

	// If the player is not flying then the y-level must be checked
	if (!flyMode)
	{
		float terrainHeight = terrain.getHeightOfTerrain(position.x, position.z);
		
		// Happens when not jumping
		if (position.y <= terrainHeight)
		{
			// Reset y speed when on ground
			velocity.y = 0.0f;
			inAir = false;
			position.y = terrainHeight;
		}
		// Deceleration on x and z axes
		velocity.x *= 0.95f;
		velocity.z *= 0.95f;
	}
	else
	{
		velocity *= 0.95f;
	}
	Statistics::get().addText("Flight Mode: " + std::string(flyMode ? "ON" : "OFF"));
}

const glm::vec3& Player::getVelocity()
{
	return velocity;
}

void Player::keyboardInput()
{
	glm::vec3 change(0,0,0);
	float speed = 0.5f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		speed *= 5;

	if (flyMode)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			change.x += -glm::cos(glm::radians(rotation.y + 90)) * speed;
			// Comment out for xz rotation only
			change.y += -glm::sin(glm::radians(rotation.x)) * speed;
			change.z += -glm::sin(glm::radians(rotation.y + 90)) * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			change.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
			// Comment out for xz rotation only
			change.y += glm::sin(glm::radians(rotation.x)) * speed;
			change.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			change.x += -glm::cos(glm::radians(rotation.y)) * speed;
			change.z += -glm::sin(glm::radians(rotation.y)) * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			change.x += glm::cos(glm::radians(rotation.y)) * speed;
			change.z += glm::sin(glm::radians(rotation.y)) * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			change.y += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			change.y -= speed;
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			change.x += -glm::cos(glm::radians(rotation.y + 90)) * speed;
			change.z += -glm::sin(glm::radians(rotation.y + 90)) * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			change.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
			change.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			change.x += -glm::cos(glm::radians(rotation.y)) * speed;
			change.z += -glm::sin(glm::radians(rotation.y)) * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			change.x += glm::cos(glm::radians(rotation.y)) * speed;
			change.z += glm::sin(glm::radians(rotation.y)) * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			// Jump
			if (!inAir)
			{
				change.y += Config::JUMP_STRENGTH;
				inAir = !inAir;
			}
		}
	}

	velocity += change;
}

void Player::mouseInput(const sf::RenderWindow& window)
{
	static auto lastMousePosition = sf::Mouse::getPosition(window);
	static auto lastDeltaPos = sf::Vector2i{ 0, 0 };

	auto deltaPos = sf::Mouse::getPosition() - lastMousePosition;

	if (lastDeltaPos != sf::Vector2i(0, 0))
	{
		rotation.y += deltaPos.x * Config::MOUSE_SENSITIVITY;
		rotation.x += deltaPos.y * Config::MOUSE_SENSITIVITY;
	}

	// Rotation along x-axis (yz plane)
	if (rotation.x > Config::MAX_PITCH_ANGLE)			rotation.x = Config::MAX_PITCH_ANGLE;
	else if (rotation.x < -Config::MAX_PITCH_ANGLE)	rotation.x = -Config::MAX_PITCH_ANGLE;

	// Rotation along y-axis (xz plane)
	if (rotation.y > 360.0f)       rotation.y = 0.0f;
	else if (rotation.y < 0.0f)    rotation.y = 360.0f;

	auto centerX = static_cast<int>(window.getSize().x / 2);
	auto centerY = static_cast<int>(window.getSize().y / 2);

	sf::Mouse::setPosition({ centerX, centerY }, window);

	lastMousePosition = sf::Mouse::getPosition();
	lastDeltaPos = deltaPos;
}
