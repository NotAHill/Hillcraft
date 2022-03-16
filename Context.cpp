#include "Context.h"
#include "Util/ResourceManager.h"

#include "Config.h"
#include <iostream>

Context::Context(sf::VideoMode size, sf::String title, bool fullscreen)
{
	// Configure OpenGL context settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	// Create our window with specified context settings
	if (fullscreen)
		window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen, settings);
	else
		window.create(size, title, sf::Style::Close | sf::Style::Titlebar, settings);

	// Load OpenGL function pointers
	//gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction))
	if (!gladLoadGL())
	{
		std::cerr << "Unable to load OpenGL functions\n";
		exit(-1);
	}

	// Create the OpenGL viewport
	glViewport(0, 0, window.getSize().x, window.getSize().y);
	window.setFramerateLimit(60);

	//Config::ASPECT_RATIO = (float)window.getSize().x / (float)window.getSize().y;

	// 2D fonts and textures
	ResourceManager::get().fonts.load("Fixedsys.ttf");
	ResourceManager::get().fonts.load("Sansation.ttf");
	ResourceManager::get().textures.load("vector.jpg", "background");
	ResourceManager::get().textures.load("heightmap.png");
	
	// Shaders
	ResourceManager::get().shaders.loadShader("basic_vertex.glsl", "basic_fragment.glsl", "basic_shader");
	ResourceManager::get().shaders.loadShader("terrain_vertex.glsl", "terrain_fragment.glsl", "terrain_shader");
	ResourceManager::get().shaders.loadShader("object_vertex.glsl", "object_fragment.glsl", "object_shader");
	
	// 3D Objects and textures
	ResourceManager::get().meshes.load("toonRocks.obj");
	ResourceManager::get().images.load("rock.png");
}
