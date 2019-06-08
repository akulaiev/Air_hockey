
// AI_paddle.hpp
// A header for the child class of Game_object.cpp.
// Initialises specific values for paddle, controlled by player and implements
// the methods for moving the opposite paddle,
// Author: Hanna Kulaieva 

#ifndef AI_PADDLE_HPP
#define AI_PADDLE_HPP

#include "Game_object.hpp"
#include "../Chipmunk2D/include/chipmunk.h"
#include "Puck.hpp"
#include <iostream>

class AI_paddle : public Game_object
{
public:
	AI_paddle	();
	AI_paddle	(AI_paddle const & inst);
	~AI_paddle	();
	AI_paddle &	operator=(AI_paddle const & inst);

	bool		checkProcess(Puck *puck);

private:
	int			_hitTime;

	bool 		_makeDecision(cpVect paddlePos, cpVect puckPos, int puckRadius, Puck *puck);
	bool		_defense(cpVect paddlePos, cpVect puckPos);
	bool		_move(cpVect paddlePos, cpVect puckPos);
	cpMouse		*_mouse;
};

#endif