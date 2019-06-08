
// SDL_manipulate.cpp
// A class, that initialises SDL2 lbrary, creates window and renderer.
// It also uploads surfaces and converts them to textures,
// that are used as sprites in the game. In case of error,
// prints an error message to console and exits.
// Author: Hanna Kulaieva 

#include "SDL_manipulate.hpp"

SDL_manipulate::SDL_manipulate	() : done(SDL_FALSE), _renderer(NULL),
_winPtr(NULL), _tmpPlayerPaddle(NULL),
_tmpAIPaddle(NULL), _tmpTable(NULL), _tmpPuck(NULL),
_tmpBorder(NULL), _wWidth(584), _wHeight(720)
{
	int i;

	i = 0;
	_tmpNumbers = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 10);
	_tmpBlueNumbers = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 10);
	numbers = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10);
	blueNumbers = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10);
	while (i <= 9)
	{
		_tmpNumbers[i] = NULL;
		_tmpBlueNumbers[i] = NULL;
		numbers[i] = NULL;
		blueNumbers[i] = NULL;
		i++;
	}
}

SDL_manipulate::SDL_manipulate	(SDL_manipulate const & inst) : done(SDL_FALSE), _renderer(NULL),
_winPtr(NULL), _tmpPlayerPaddle(NULL),
_tmpAIPaddle(NULL), _tmpTable(NULL), _tmpPuck(NULL),
_tmpBorder(NULL), _wWidth(584), _wHeight(720)
{
	*this = inst;
}

SDL_manipulate::~SDL_manipulate	()
{
	if (_renderer)
		SDL_DestroyRenderer(_renderer);
	if (_winPtr)
		SDL_DestroyWindow(_winPtr);
	if (_tmpPlayerPaddle)
		SDL_FreeSurface(_tmpPlayerPaddle);
	if (_tmpAIPaddle)
		SDL_FreeSurface(_tmpAIPaddle);
	if (_tmpTable)
		SDL_FreeSurface(_tmpTable);
	if (_tmpPuck)
		SDL_FreeSurface(_tmpPuck);
	if (_tmpBorder)
		SDL_FreeSurface(_tmpBorder);
	if (_hockeyTable)
		SDL_DestroyTexture(_hockeyTable);
	if (startScreen)
		SDL_DestroyTexture(startScreen);
	if (AIWins)
		SDL_DestroyTexture(	AIWins);
	if (playerWins)
		SDL_DestroyTexture(	playerWins);
	if (_tmpStartScreen)
		SDL_FreeSurface(_tmpStartScreen);
	if (_tmpAIWins)
		SDL_FreeSurface(_tmpAIWins);
	if (_tmpPlayerWins)
		SDL_FreeSurface(_tmpPlayerWins);
	int i = 0;
	while (i <= 9)
	{
		if (_tmpNumbers[i])
			SDL_FreeSurface(_tmpNumbers[i]);
		if (_tmpBlueNumbers[i])
			SDL_FreeSurface(_tmpBlueNumbers[i]);
		if (numbers[i])
			SDL_DestroyTexture(numbers[i]);
		if (blueNumbers[i])
			SDL_DestroyTexture(blueNumbers[i]);
		i++;
	}
}

SDL_manipulate &			SDL_manipulate::operator=(SDL_manipulate const & inst)
{
	_renderer = inst._renderer;
	_winPtr = inst._winPtr;
	done = inst.done;
	_event = inst._event;
	_hockeyTable = inst._hockeyTable;
	_tmpPlayerPaddle = inst._tmpPlayerPaddle;
	_tmpAIPaddle = inst._tmpAIPaddle;
	_tmpTable = inst._tmpTable;
	_tmpPuck = inst._tmpPuck;
	_tmpBorder = inst._tmpBorder;
	_border = inst._border;
	return (*this);
}

int					SDL_manipulate::_convertTextures(Player_paddle *playerPaddle, AI_paddle *AIPaddle,
Puck *puck)
{
	int		i;

	if ((_hockeyTable = SDL_CreateTextureFromSurface(_renderer, _tmpTable)) == NULL ||
	(playerPaddle->objSurface = SDL_CreateTextureFromSurface(_renderer, _tmpPlayerPaddle)) == NULL ||
	(AIPaddle->objSurface = SDL_CreateTextureFromSurface(_renderer, _tmpAIPaddle)) == NULL ||
	(_border = SDL_CreateTextureFromSurface(_renderer, _tmpBorder)) == NULL ||
	(puck->objSurface = SDL_CreateTextureFromSurface(_renderer, _tmpPuck)) == NULL ||
	(startScreen = SDL_CreateTextureFromSurface(_renderer, _tmpStartScreen)) == NULL ||
	(AIWins = SDL_CreateTextureFromSurface(_renderer, _tmpAIWins)) == NULL ||
	(playerWins = SDL_CreateTextureFromSurface(_renderer, _tmpPlayerWins)) == NULL)
		return (0);
	i = 0;
	while (i <= 9)
	{
		if ((numbers[i] = SDL_CreateTextureFromSurface(_renderer, _tmpNumbers[i])) == NULL ||
		(blueNumbers[i] = SDL_CreateTextureFromSurface(_renderer, _tmpBlueNumbers[i])) == NULL)
			return (0);
		i++;
	}
	return (1);
}

int					SDL_manipulate::_uploadTextures()
{
	int		i;

	if ((_tmpTable = SDL_LoadBMP("./textures/hockey_table.bmp")) == NULL ||
	(_tmpAIPaddle = SDL_LoadBMP("./textures/blue_paddle.bmp")) == NULL ||
	(_tmpPlayerPaddle = SDL_LoadBMP("./textures/red_paddle.bmp")) == NULL ||
	(_tmpBorder = SDL_LoadBMP("./textures/table_border.bmp")) == NULL ||
	(_tmpPuck = SDL_LoadBMP("./textures/puck.bmp")) == NULL ||
	(_tmpStartScreen = SDL_LoadBMP("./textures/start_screen.bmp")) == NULL ||
	(_tmpAIWins = SDL_LoadBMP("./textures/AI_wins.bmp")) == NULL ||
	(_tmpPlayerWins = SDL_LoadBMP("./textures/player_wins.bmp")) == NULL)
		return (0);
	i = 0;
	while (i <= 9)
	{
		std::string name = "./textures/numbers/";
		name += static_cast <char> (i + 48);
		name += ".bmp";
		char cName[55];
		strcpy(cName, name.c_str());
		std::string blueName = "./textures/numbers/Blue";
		blueName += static_cast <char> (i + 48);
		blueName += ".bmp";
		char cBlueName[55];
		strcpy(cBlueName, blueName.c_str());
		if ((_tmpNumbers[i] = SDL_LoadBMP(cName)) == NULL ||
		(_tmpBlueNumbers[i] = SDL_LoadBMP(cBlueName)) == NULL)
			return (0);
		i++;
	}
	return (1);
}

void			my_audio_callback(void *userdata, Uint8 *stream, int len)
{
	t_audio		*sound;

	sound = reinterpret_cast <t_audio*> (userdata);
	if (!sound->audioLen)
		return ;
	len = (len > sound->audioLen ? sound->audioLen : len);
	SDL_MixAudio(stream, sound->audioPos, len, SDL_MIX_MAXVOLUME);
	sound->audioPos += len;
	sound->audioLen -= len;
}

void			SDL_manipulate::sdlInit (Player_paddle *playerPaddle, AI_paddle *AIPaddle,
Puck *puck)
{
	std::vector<std::string> errors;
	errors.push_back("Problem with SDL init");
	errors.push_back("Couldn't create window");
	errors.push_back("Couldn't load background texture");
	errors.push_back("Couldn't convert surface");
	errors.push_back("Couldn't copy renderer");
	errors.push_back("Couldn't load audio");
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw 0;
		if	((_winPtr = SDL_CreateWindow("Air_hockey", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, _wWidth, _wHeight, 0)) == NULL)
			throw 1;
		if ((_renderer = SDL_CreateRenderer(_winPtr, -1, 0)) == NULL)
			throw 2;
		if (!_uploadTextures())
			throw 3;
		if (!_convertTextures(playerPaddle, AIPaddle, puck))
			throw 4;
		if (SDL_LoadWAV("./sounds/victory.wav", &_victorySound.wavSpec,
		&_victorySound.wavBuffer, &_victorySound.wavLength) == NULL ||
		SDL_LoadWAV("./sounds/lost.wav", &_lostSound.wavSpec,
		&_lostSound.wavBuffer, &_lostSound.wavLength) == NULL)
		{
			std::cout << SDL_GetError() << std::endl;
			throw 5;
		}
		_victorySound.audioLen = _victorySound.wavLength;
		_victorySound.audioPos = _victorySound.wavBuffer;
		_victorySound.wavSpec.callback = my_audio_callback;
		_victorySound.wavSpec.userdata = &_victorySound;
		_lostSound.audioLen = _lostSound.wavLength;
		_lostSound.audioPos = _lostSound.wavBuffer;
		_lostSound.wavSpec.callback = my_audio_callback;
		_lostSound.wavSpec.userdata = &_lostSound;
	}
	catch (int ex)
	{
		std::cout << errors[ex] << std::endl;
		exit (ex);
	}
}

SDL_Texture			*SDL_manipulate::getTableTex()
{
	return (_hockeyTable);
}

SDL_Texture			*SDL_manipulate::getBorderTex()
{
	return (_border);
}

SDL_Renderer		*SDL_manipulate::getRenderer()
{
	return (_renderer);
}

SDL_Event		*SDL_manipulate::getEvent()
{
	return (&_event);
}

t_audio				SDL_manipulate::getVictorySound()
{
	return (_victorySound);
}

t_audio				SDL_manipulate::getLostSound()
{
	return (_lostSound);
}
