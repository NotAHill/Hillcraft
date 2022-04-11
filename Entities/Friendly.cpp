#include "Friendly.h"

#include "../States/GameState.h"
#include "../Command/DialogueCommand.h"
#include "../Command/ScriptEngine.h"

Friendly::Friendly(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale) :
	Object(_model, _position, _rotation, _scale)
{
}

void Friendly::update(float deltaTime, Player& player)
{
}

void Friendly::interact(GameState& state, Player& player)
{
	state.script.addCommand(std::make_unique<DialogueCommand>(state, std::vector<std::string>
	{ "Shopkeeper:", "Hi there!", "Unfortunately we are closed right now", "You have visited us " + std::to_string(++counter) + " times", "Come again soon!"}));
	player.currentHealth += 5;
	if (player.currentHealth >= player.maxHealth) player.currentHealth = player.maxHealth;
	state.script.addCommand(std::make_unique<DialogueCommand>(state, std::vector<std::string>
	{ "System:", "For your kind actions,", "you have been awarded:", "5 health"}));
}
