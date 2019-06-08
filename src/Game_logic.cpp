
// Game_logic.cpp
// A class, that runs the main game loop. It also has a method, that renders copies everu texture
// to the SDL render and redraws every frame according to the chosen FPS rate.
// Author: Hanna Kulaieva 

#include "Game_logic.hpp"

Game_logic::Game_logic	() : _window_width(584), _window_height(720),
_FPS(60), _timeStep(0.017), _frameDelay(9)
{
	_borderTop.x = 122;
	_borderTop.y = 0;
	_borderTop.w = 343;
	_borderTop.h = 38;
	_borderBottom.x = 122;
	_borderBottom.y = 680;
	_borderBottom.w = 343;
	_borderBottom.h = 40;
	_blueRect.x = 10;
	_blueRect.y = _window_height / 2 - 20;
	_blueRect.w = 0;
	_blueRect.h = 0;
	_redRect.x = 547;
	_redRect.y = _window_height / 2 - 20;
	_redRect.w = 0;
	_redRect.h = 0;
}

Game_logic::Game_logic	(Game_logic const & inst) : _window_width(584), _window_height(720),
_FPS(60), _timeStep(0.017), _frameDelay(10)
{
	*this = inst;
}

Game_logic::~Game_logic	() {}

void				Game_logic::newGame()
{
	_gameLoop();
}

Game_logic &			Game_logic::operator=(Game_logic const & inst)
{
	_SDLData = inst._SDLData;
	_CPData = inst._CPData;
	_frameStart = inst._frameStart;
	_frameTime = inst._frameTime;
	_playerPaddle = inst._playerPaddle;
	_AIPaddle = inst._AIPaddle;
	_puck = inst._puck;
	_mouseX = inst._mouseX;
	_mouseY = inst._mouseY;
	_borderTop = inst._borderTop;
	_borderBottom = inst._borderBottom;
	_blueRect = inst._blueRect;
	return (*this);
}

void			Game_logic::_setGameObjects()
{
	SDL_Renderer	*renderer;

	renderer = _SDLData.getRenderer();
	_playerPaddle.setRenderer(renderer);
	_AIPaddle.setRenderer(renderer);
	_puck.setRenderer(renderer);
	_redraw();
}

void			Game_logic::_redraw()
{
	SDL_Texture		*hockeyTable;
	SDL_Texture		*border;
	SDL_Renderer	*renderer;
	int				w;
	int				h;

	renderer = _SDLData.getRenderer();
	hockeyTable = _SDLData.getTableTex();
	border = _SDLData.getBorderTex();
	SDL_RenderClear(renderer);
	SDL_QueryTexture(_SDLData.blueNumbers[_CPData.getBlueScore()], NULL, NULL, &w, &h);
	_blueRect.w = w;
	_blueRect.h = h;
	SDL_QueryTexture(_SDLData.numbers[_CPData.getRedScore()], NULL, NULL, &w, &h);
	_redRect.w = w;
	_redRect.h = h;
	if (_CPData.getRedScore() == 10 || _CPData.getBlueScore() == 10)
	{
		SDL_AudioSpec audio;
		int delay = 0;
		bool audioOpen = false;
		if (_CPData.getBlueScore() == 10)
		{
			audio = _SDLData.getVictorySound().wavSpec;
			delay = 3900;
			SDL_RenderCopy(renderer, _SDLData.playerWins, NULL, NULL);
		}
		else
		{
			audio = _SDLData.getLostSound().wavSpec;
			delay = 2300;
			SDL_RenderCopy(renderer, _SDLData.AIWins, NULL, NULL);
		}
		if (SDL_OpenAudio(&audio, NULL) >= 0)
		{
			audioOpen = true;
			SDL_PauseAudio(0);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(delay);
		if (audioOpen)
			SDL_CloseAudio();
		exit(0);
	}
	if (SDL_RenderCopy(renderer, hockeyTable, NULL, NULL) ||
	SDL_RenderCopy(renderer, _SDLData.blueNumbers[_CPData.getBlueScore()], NULL, &_blueRect) ||
	SDL_RenderCopy(renderer, _SDLData.numbers[_CPData.getRedScore()], NULL, &_redRect))
	{
		std::cout << "Couldn't copy renderer" << std::endl;
		exit(5);
	}
	_playerPaddle.placeObject();
	_AIPaddle.placeObject();
	_puck.placeObject();
	if (SDL_RenderCopy(renderer, border, NULL, &_borderTop) ||
	SDL_RenderCopy(renderer, border, NULL, &_borderBottom))
	{
		std::cout << "Couldn't copy renderer" << std::endl;
		exit(5);
	}
	SDL_RenderPresent(renderer);
}

void			Game_logic::_showStartScreen()
{
	int			start;
	SDL_Event	event;

	start = 0;
	while (!start)
	{
		if (SDL_RenderCopy(_SDLData.getRenderer(), _SDLData.startScreen, NULL, NULL))
		{
			std::cout << "Couldn't copy renderer" << std::endl;
			exit(5);
		}
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT || (
			event.key.keysym.scancode == SDL_SCANCODE_ESCAPE &&
			event.type == SDL_KEYDOWN)))
			{
				SDL_Quit();
				exit(0);
			}
			if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
				start = 1;
		}
		SDL_RenderPresent(_SDLData.getRenderer());
		SDL_Delay(10);
	}
}

void			Game_logic::_gameLoop()
{
	cpVect		point;
	SDL_Event	event;
	cpSpace		*gameSpace;
	cpMouse		*mouse;

	_SDLData.sdlInit(&_playerPaddle, &_AIPaddle, &_puck);
	_CPData.cpInit(&_playerPaddle, &_AIPaddle, &_puck);
	_setGameObjects();
	event = *(_SDLData.getEvent());
	gameSpace = _CPData.getSpace();
	mouse = _CPData.getMouse();
	_showStartScreen();
	srand(time(NULL));
	TouchBegan(cpv(405, 582), mouse, 0);
	while (!_SDLData.done)
	{
		_frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&event) && !_SDLData.done)
		{
			if (event.type == SDL_QUIT || (
			event.key.keysym.scancode == SDL_SCANCODE_ESCAPE &&
			event.type == SDL_KEYDOWN))
				_SDLData.done = SDL_TRUE;
			else
			{
				SDL_GetMouseState(&_mouseX, &_mouseY);
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					cpBodySetPosition(_puck.objBody, cpv(275, 341));
					cpBodySetVelocity(_puck.objBody, cpvzero);
				}
				if (event.type == SDL_MOUSEMOTION)
				{
					point = cpv(_mouseX, _mouseY);
					TouchMoved(point, mouse);
					_playerPaddle.placeObject();
				}
			}
		}
		_AIPaddle.checkProcess(&_puck);
		_redraw();
		_frameTime = SDL_GetTicks() - _frameStart;
		if (_frameTime < _frameDelay)
			SDL_Delay(_frameDelay - _frameTime);
		cpSpaceStep(gameSpace, _timeStep);
	}
	SDL_Quit();
}

int				Game_logic::getWinWidth() const
{
	return (_window_width);
}

int				Game_logic::getWinHeight() const
{
	return (_window_height);
}
