
// Game_logic.hpp
// A header for the class, that runs the main game loop. It also has a method,
// that renders copies every texture to the SDL render and redraws every frame according to the chosen FPS rate.
// Author: Hanna Kulaieva 

#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include "Air_hockey.hpp"

class Game_logic
{
public:
	Game_logic		();
	Game_logic		(Game_logic const & inst);
	~Game_logic		();
	Game_logic &	operator=(Game_logic const & inst);

	int				getWinWidth() const;
	int				getWinHeight() const;
	void			newGame();

private:

	SDL_manipulate	_SDLData;
	CP_manipulate	_CPData;
	const int		_window_width;
	const int		_window_height;
	const int		_FPS;
	const cpFloat	_timeStep;
	const int		_frameDelay;
	Uint32			_frameStart;
	int				_frameTime;
	Player_paddle	_playerPaddle;
	AI_paddle		_AIPaddle;
	Puck			_puck;
	int				_mouseX;
	int				_mouseY;
	SDL_Rect		_borderTop;
	SDL_Rect		_borderBottom;
	SDL_Rect		_blueRect;
	SDL_Rect		_redRect;

	void			_cpInit();
	void			_gameLoop();
	void			_setGameObjects();
	void			_showStartScreen();
	void			_redraw();
};

#endif