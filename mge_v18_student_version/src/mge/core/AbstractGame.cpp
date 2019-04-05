#include <iostream>

#include "AbstractGame.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

AbstractGame::AbstractGame():_window(NULL),_renderer(NULL),_world(NULL), _fps(0)
{
    //ctor
}

AbstractGame::~AbstractGame()
{
    //dtor
    delete _window;
    delete _renderer;
    delete _world;
}

void AbstractGame::initialize() {
    _initializeWindow();
    _printVersionInfo();
    _initializeGlew();
    _initializeRenderer();
    _initializeWorld();
    _initializeScene();
}

///SETUP

void AbstractGame::_initializeWindow() {
	lua_State *config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");
	int ScreenWidth = LuaWrapper::GetNumber<int>(config, "ScreenWidth");
	int ScreenHeight = LuaWrapper::GetNumber<int>(config, "ScreenHeight");
	std::string& windowTitle = LuaWrapper::GetString(config, "Title");


	//_window = new sf::RenderWindow( sf::VideoMode(ScreenWidth, ScreenHeight), windowTitle, sf::Style::Default, sf::ContextSettings(24,8,16,3,3));
	_window = new sf::RenderWindow(sf::VideoMode(ScreenWidth, ScreenHeight), windowTitle, sf::Style::Fullscreen, sf::ContextSettings(24, 8, 16, 3, 3));
	LuaWrapper::CloseLuaState(config);
	//_window->setVerticalSyncEnabled(true);
}

void AbstractGame::_printVersionInfo() {
    //print some debug stats for whoever cares
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
}

void AbstractGame::_initializeGlew() {
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
}

void AbstractGame::_initializeRenderer() {
    //setup our own renderer
	_renderer = new Renderer();
    _renderer->setClearColor(0,0,0);
}

void AbstractGame::_initializeWorld() {
    //setup the world
	_world = new World();
}

///MAIN GAME LOOP

void AbstractGame::run()
{
    //setting to calculate fps
	sf::Clock renderClock;
    int frameCount = 0;
    float timeSinceLastFPSCalculation = 0;

	//settings to make sure the update loop runs at 60 fps
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Clock updateClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (_window->isOpen()) {
		timeSinceLastUpdate += updateClock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		    while (timeSinceLastUpdate > timePerFrame) {
                timeSinceLastUpdate -= timePerFrame;
                _update(timePerFrame.asSeconds());
		    }

            _render();
            _window->display();

            //fps count is updated once every 1 second
            frameCount++;
            timeSinceLastFPSCalculation += renderClock.restart().asSeconds();
            if (timeSinceLastFPSCalculation > 1) {
                _fps = frameCount/timeSinceLastFPSCalculation;
                timeSinceLastFPSCalculation -= 1;
                frameCount = 0;
            }
		}

		//empty the event queue
		_processEvents();
    }
}

void AbstractGame::_update(float pStep) {
    _world->update(pStep);
	_world->lateUpdate(pStep);
}

void AbstractGame::_render () {
    _renderer->render(_world);
}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while( _window->pollEvent( event ) ) {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you for example you could implement a
        //SystemEventDispatcher / SystemEventListener pair which allows Listeners to
        //register with the dispatcher and then do something like:
        //SystemEventDispatcher::dispatchEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
                /*if (event.key.code == sf::Keyboard::Escape) {
                    exit = true;
                }*/
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
				//TODO add resizing for camera projection
                break;

            default:
                break;
        }
	}

	if (exit) {
        _window->close();
	}
}



