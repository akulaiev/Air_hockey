
// AI_paddle.cpp
// A child class of Game_object.cpp.
// Initialises specific values for paddle, controlled by player and implements
// the methods for moving the opposite paddle,
// Author: Hanna Kulaieva 


#include "AI_paddle.hpp"

AI_paddle::AI_paddle	()
{
	objName = "AI_paddle";
	_radius = 25;
	_mass = 11;
	_moment = INFINITY;
	_friction = 0.3;
	_elasticity = 0.1;
	_filter.categories |= (1 << 2);
	_filter.categories |= (1 << 30);
	_filter.mask = 58;
	_collisionType = 2;
	_hitTime = 0;
	_mouse = NULL;
}

AI_paddle::AI_paddle	(AI_paddle const & inst)
{
	*this = inst;
}

AI_paddle::~AI_paddle	() {}

AI_paddle &	AI_paddle::operator=(AI_paddle const & inst)
{
	(void)inst;
	return (*this);
}

bool		AI_paddle::checkProcess(Puck *puck)
{
	cpVect	paddlePos;
	cpVect	puckPos;
	UInt32	curTime;

	paddlePos = cpBodyGetPosition(objBody);
	if (!_mouse)
	{
		_mouse = cpMouseNew(_gameSpace);
		cpFloat res = cpShapePointQuery(objShape, paddlePos, NULL);
		if (res <= 0)
			TouchBegan(paddlePos, _mouse, 1);
	}
	puckPos = cpBodyGetPosition(puck->objBody);
	curTime = SDL_GetTicks();
	if ((curTime - _hitTime) < 700)
		return _defense(paddlePos, puckPos);
	_makeDecision(paddlePos, puckPos, puck->getRadius(), puck);
	return true;
}

bool 		AI_paddle::_makeDecision(cpVect paddlePos, cpVect puckPos, int puckRadius, Puck *puck)
{
	if (puckPos.x > _cornerTopLeft.x + puckRadius && puckPos.x < _cornerTopRight.x - puckRadius &&
	puckPos.y > _cornerTopLeft.y + puckRadius && puckPos.y < 720 / 2 - puckRadius)
		return _move(paddlePos, puckPos);
	if (puckPos.y <= _cornerTopLeft.y && (puckPos.x < 122 || puckPos.x > 465))
	{
		cpBodySetPosition(puck->objBody, cpv(275, 341));
		cpBodySetVelocity(puck->objBody, cpvzero);
		SDL_Delay(250);
		return (true);
	}
	return _defense(paddlePos, puckPos);
}

bool		AI_paddle::_defense(cpVect paddlePos, cpVect puckPos)
{
	if (puckPos.y < paddlePos.y && abs(440 / 2 - puckPos.x) > 440 / 5)
		return _move(paddlePos, puckPos);
	puckPos.x = 440 / 4 + 440 / 2 * (puckPos.x / 440.0f);
	puckPos.y = 640 / 6;
	_move(paddlePos, puckPos);
	_hitTime = SDL_GetTicks() - _hitTime;
	return true;
}

bool		AI_paddle::_move(cpVect paddlePos, cpVect puckPos)
{
	int random = rand() % 20;
	cpFloat speed = 440 / (40.0 + random);
	cpVect delta = cpvsub(puckPos, paddlePos);
	cpFloat distance = cpvlength(delta);
	cpVect newPos = cpvzero;
	if (distance > speed)
	{
		newPos.x = paddlePos.x + speed / distance * delta.x;
		newPos.y = paddlePos.y + speed / distance * delta.y;
		TouchMoved(newPos, _mouse);
		placeObject();
		return (true);
	}
	return (false);
}
