// SDL_manipulate.ppp
// A header file for the class, that initialises SDL2 lbrary, creates window and renderer.
// It also uploads surfaces and converts them to textures,
// that are used as sprites in the game. In case of error,
// prints an error message to console and exits.
// Author: Hanna Kulaieva 

#ifndef SDL_MANIPULATE_HPP
#define SDL_MANIPULATE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Player_paddle.hpp"
#include "AI_paddle.hpp"
#include "Puck.hpp"

typedef struct			s_audio
{
	Uint32				wavLength;
	Uint8				*wavBuffer;
	SDL_AudioSpec		wavSpec;
	Uint8				*audioPos;
	Uint32				audioLen;
}						t_audio;

class SDL_manipulate
{
public:
	SDL_manipulate		();
	SDL_manipulate		(SDL_manipulate const & inst);
	~SDL_manipulate		();
	SDL_manipulate &	operator=(SDL_manipulate const & inst);

	SDL_bool			done;
	SDL_Texture			**numbers;
	SDL_Texture			**blueNumbers;
	SDL_Texture			*startScreen;
	SDL_Texture			*playerWins;
	SDL_Texture			*AIWins;

	SDL_Texture			*getTableTex();
	SDL_Texture			*getBorderTex();
	SDL_Renderer		*getRenderer();
	SDL_Event			*getEvent();
	t_audio				getVictorySound();
	t_audio				getLostSound();

	void				sdlInit(Player_paddle *playerPaddle, AI_paddle *AIPaddle,
						Puck *puck);

private:
	SDL_Renderer 		*_renderer;
	SDL_Window			*_winPtr;
	SDL_Event			_event;
	SDL_Texture			*_border;
	SDL_Texture			*_hockeyTable;
	SDL_Surface			*_tmpStartScreen;
	SDL_Surface			*_tmpPlayerWins;
	SDL_Surface			*_tmpAIWins;
	SDL_Surface			*_tmpPlayerPaddle;
	SDL_Surface			*_tmpAIPaddle;
	SDL_Surface			*_tmpTable;
	SDL_Surface			*_tmpPuck;
	SDL_Surface			*_tmpBorder;
	SDL_Surface			**_tmpNumbers;
	SDL_Surface			**_tmpBlueNumbers;
	const int			_wWidth;
	const int			_wHeight;
	t_audio				_victorySound;
	t_audio				_lostSound;

	int					_uploadTextures();
	int					_convertTextures(Player_paddle *playerPaddle, AI_paddle *AIPaddle,
						Puck *puck);
};

#endif