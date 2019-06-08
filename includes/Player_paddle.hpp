
// Player_paddle.hpp
// A header for the child class of Game_object.cpp.
// Initialises specific values for paddle, controlled by player.
// Author: Hanna Kulaieva 

#ifndef PLAYER_PADDLE_HPP
#define PLAYER_PADDLE_HPP

#include "Game_object.hpp"
#include <cmath>

class Player_paddle : public Game_object
{
public:
	Player_paddle	();
	Player_paddle	(Player_paddle const & inst);
	~Player_paddle	();
	Player_paddle &	operator=(Player_paddle const & inst);

private:

};

#endif