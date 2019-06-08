
// CP_manipulate.cpp
// A class, that initialises Chipmunk physical engine and creates game space,
// as well as attaching objects' shaoes to their bodies.
// It also assignes all of their parameteres (density, friction. elastity etc.)
// and adds collision filters and groups. Collision handler methods are also in this file.
// Author: Hanna Kulaieva 

#include "CP_manipulate.hpp"

CP_manipulate::CP_manipulate	() : _gameSpace(NULL), _table(NULL),
_gTop(NULL), _gBottom(NULL), _goalTop(NULL),
_goalBottom(NULL), _goalTopLeft(NULL), _goalTopRight(NULL),
_goalBottomBack(NULL), _goalBottomLeft(NULL), _goalBottomRight(NULL),
_leftBorder(NULL), _rightBorder(NULL), _topBorderLeft(NULL),
_topBorderRight(NULL), _bottomBorderLeft(NULL), _bottomBorderRight(NULL),
_middleBorder(NULL), _mouse(NULL), _wWidth(584), _wHeight(720), _blueScore(0),
_redScore(0) {}

CP_manipulate::CP_manipulate	(CP_manipulate const & inst) : _wWidth(584), _wHeight(720)
{
	*this = inst;
}

CP_manipulate::~CP_manipulate	()
{
	if (_gameSpace)
		cpSpaceDestroy(_gameSpace);
	if (_gTop)
		cpBodyDestroy(_gTop);
	if (_gBottom)
		cpBodyDestroy(_gBottom);
	if (_goalTop)
		cpShapeDestroy(_goalTop);
	if (_goalBottom)
		cpShapeDestroy(_goalBottom);
	if(_goalTopLeft)	
		cpShapeDestroy(_goalTopLeft);
	if(_goalTopRight)	
		cpShapeDestroy(_goalTopRight);
	if(_goalBottomBack)	
		cpShapeDestroy(_goalBottomBack);
	if(_goalBottomLeft)	
		cpShapeDestroy(_goalBottomLeft);
	if(_goalBottomRight)	
		cpShapeDestroy(_goalBottomRight);
	if (_table)
		cpBodyDestroy(_table);
	if (_leftBorder)
		cpShapeDestroy(_leftBorder);
	if (_rightBorder)
		cpShapeDestroy(_rightBorder);
	if(_topBorderLeft)
		cpShapeDestroy(_topBorderLeft);
	if(_topBorderRight)
		cpShapeDestroy(_topBorderRight);
	if(_bottomBorderLeft)
		cpShapeDestroy(_bottomBorderLeft);
	if(_bottomBorderRight)
		cpShapeDestroy(_bottomBorderRight);
	if(_middleBorder)
		cpShapeDestroy(_middleBorder);
}

CP_manipulate &			CP_manipulate::operator=(CP_manipulate const & inst)
{
	_gameSpace = inst._gameSpace;
	_table = inst._table;
	_gTop = inst._gTop;
	_gBottom = inst._gBottom;
	_goalTop = inst._goalTop;
	_goalBottom = inst._goalBottom;
	_goalTopLeft = inst._goalTopLeft;
	_goalTopRight = inst._goalTopRight;
	_goalBottomBack = inst._goalBottomBack;
	_goalBottomLeft = inst._goalBottomLeft;
	_goalBottomRight = inst._goalBottomRight;
	_leftBorder = inst._leftBorder;
	_rightBorder = inst._rightBorder;
	_topBorderLeft = inst._topBorderLeft;
	_topBorderRight = inst._topBorderRight;
	_bottomBorderLeft = inst._bottomBorderLeft;
	_bottomBorderRight = inst._bottomBorderRight;
	_middleBorder = inst._middleBorder;
	_mouse = inst._mouse;
	return (*this);
}

cpBool			collisionTypeOne(cpArbiter *arb, cpSpace *space, void *data)
{
	cpShape			*a;
	cpShape			*b;
	cpShape			*puck;
	int				*score;

	cpArbiterGetShapes(arb, &a, &b);
	if (cpShapeGetCollisionType(a) == 3)
		puck = a;
	else
		puck = b;
	cpBodySetPosition(cpShapeGetBody(puck), cpv(275, 341));
	cpBodySetVelocity(cpShapeGetBody(puck), cpvzero);
	SDL_Delay(150);
	score = reinterpret_cast <int*> (data);
	(*score)++;
	return (true);
}

cpBool			collisionTypeTwo(cpArbiter *arb, cpSpace *space, void *data)
{
	cpShape			*a;
	cpShape			*b;
	cpShape			*puck;
	int				*score;

	cpArbiterGetShapes(arb, &a, &b);
	if (cpShapeGetCollisionType(a) == 3)
		puck = a;
	else
		puck = b;
	cpBodySetPosition(cpShapeGetBody(puck), cpv(275, 341));
	cpBodySetVelocity(cpShapeGetBody(puck), cpvzero);
	SDL_Delay(150);
	score = reinterpret_cast <int*> (data);
	(*score)++;
	return (true);
}

void			CP_manipulate::cpInit (Player_paddle *playerPaddle, AI_paddle *AIPaddle,
Puck *puck)
{
	cpShapeFilter	border;
	cpShapeFilter	midBorder;

	border.categories |= (1 << 4);
	border.categories |= (1 << 31);
	border.mask = 14;
	midBorder.categories |= (1 << 5);
	midBorder.categories |= (1 << 31);
	midBorder.mask = 6;
	_gravity = cpvzero;
	_gameSpace = cpSpaceNew();
	cpSpaceSetGravity(_gameSpace, _gravity);

	_table = cpBodyNewStatic();
	_gTop = cpBodyNewStatic();
	_gBottom = cpBodyNewStatic();
	cpBodySetPosition(_table, cpvzero);
	_goalTop = cpSpaceAddShape(_gameSpace, cpSegmentShapeNew(_gTop,
	cpv(122, 23), cpv(465, 23), 0));
	_goalBottom = cpSpaceAddShape(_gameSpace, cpSegmentShapeNew(_gBottom,
	cpv(122, 654), cpv(465, 654), 0));
	_goalTopLeft = cpSpaceAddShape(_gameSpace, cpSegmentShapeNew(_gTop,
	cpv(122, 23), cpv(122, 0), 0));
	_goalTopRight = cpSpaceAddShape(_gameSpace, cpSegmentShapeNew(_gTop,
	cpv(465, 23), cpv(465, 0), 0));
	_goalTopBack = cpSpaceAddShape(_gameSpace, cpSegmentShapeNew(_gTop,
	cpv(122, -10), cpv(465, 0), -10));
	_goalBottomRight = cpSpaceAddShape(_gameSpace, cpSegmentShapeNew(_gBottom,
	cpv(465, 654), cpv(465, _wHeight), 0));
	_goalBottomLeft = cpSpaceAddShape(_gameSpace, cpSegmentShapeNew(_gBottom,
	cpv(122, 654), cpv(122, _wHeight), 0));
	_goalBottomBack = cpSpaceAddShape(_gameSpace, cpSegmentShapeNew(_gBottom,
	cpv(122, 730), cpv(465, 730), 0));
	_leftBorder = cpSpaceAddShape(_gameSpace,
	cpSegmentShapeNew(_table, cpv(23, 23), cpv(23, 654), 0));
	_rightBorder = cpSpaceAddShape(_gameSpace,
	cpSegmentShapeNew(_table, cpv(511, 23), cpv(511, 654), 0));
	_topBorderLeft = cpSpaceAddShape(_gameSpace,
	cpSegmentShapeNew(_table, cpv(23, 23), cpv(122, 23), 0));
	_topBorderRight = cpSpaceAddShape(_gameSpace,
	cpSegmentShapeNew(_table, cpv(465, 23), cpv(511, 23), 0));
	_bottomBorderLeft = cpSpaceAddShape(_gameSpace,
	cpSegmentShapeNew(_table, cpv(23, 654), cpv(122, 654), 0));
	_bottomBorderRight = cpSpaceAddShape(_gameSpace,
	cpSegmentShapeNew(_table, cpv(465, 654), cpv(511, 654), 0));
	_middleBorder = cpSpaceAddShape(_gameSpace,
	cpSegmentShapeNew(_table, cpv(23, _wHeight / 2 - 25), cpv(511, _wHeight / 2 - 25), 0));
	cpShapeSetFriction(_leftBorder, 0.9);
	cpShapeSetFriction(_rightBorder, 0.9);
	cpShapeSetFriction(_topBorderLeft, 0.9);
	cpShapeSetFriction(_topBorderRight, 0.9);
	cpShapeSetFriction(_bottomBorderLeft, 0.9);
	cpShapeSetFriction(_bottomBorderRight, 0.9);
	cpShapeSetDensity(_leftBorder, 1.1);
	cpShapeSetDensity(_rightBorder, 1.1);
	cpShapeSetDensity(_topBorderLeft, 1.1);
	cpShapeSetDensity(_topBorderRight, 1.1);
	cpShapeSetDensity(_bottomBorderRight, 1.1);
	cpShapeSetDensity(_bottomBorderLeft, 1.1);
	cpShapeSetElasticity(_leftBorder, 0.1);
	cpShapeSetElasticity(_rightBorder, 0.1);
	cpShapeSetElasticity(_topBorderLeft, 0.1);
	cpShapeSetElasticity(_topBorderRight, 0.1);
	cpShapeSetElasticity(_bottomBorderLeft, 0.1);
	cpShapeSetElasticity(_bottomBorderRight, 0.1);
	cpShapeSetCollisionType(_leftBorder, 5);
	cpShapeSetCollisionType(_rightBorder, 5);
	cpShapeSetCollisionType(_topBorderLeft, 5);
	cpShapeSetCollisionType(_topBorderRight, 5);
	cpShapeSetCollisionType(_bottomBorderLeft, 5);
	cpShapeSetCollisionType(_bottomBorderRight, 5);
	cpShapeSetCollisionType(_middleBorder, 6);
	cpShapeSetCollisionType(_goalTopLeft, 7);
	cpShapeSetCollisionType(_goalTopRight, 7);
	cpShapeSetCollisionType(_goalTop, 7);
	cpShapeSetCollisionType(_goalTopBack, 7);
	cpShapeSetCollisionType(_goalBottomRight, 8);
	cpShapeSetCollisionType(_goalBottomLeft, 8);
	cpShapeSetCollisionType(_goalBottomBack, 8);
	cpShapeSetCollisionType(_goalBottom, 8);
	cpShapeSetFilter(_leftBorder, border);
	cpShapeSetFilter(_rightBorder, border);
	cpShapeSetFilter(_topBorderLeft, border);
	cpShapeSetFilter(_topBorderRight, border);
	cpShapeSetFilter(_bottomBorderLeft, border);
	cpShapeSetFilter(_bottomBorderRight, border);
	cpShapeSetFilter(_middleBorder, midBorder);
	cpShapeSetFilter(_goalTopLeft, border);
	cpShapeSetFilter(_goalBottomLeft, border);
	cpShapeSetFilter(_goalTopRight, border);
	cpShapeSetFilter(_goalBottomRight, border);
	cpShapeSetFilter(_goalTopBack, border);
	cpShapeSetFilter(_goalBottomBack, border);
	cpShapeSetFilter(_goalTop, midBorder);
	cpShapeSetFilter(_goalBottom, midBorder);
	playerPaddle->initObjShape(_gameSpace, cpv(405, 582));
	AIPaddle->initObjShape(_gameSpace, cpv(120, 81));
	puck->initObjShape(_gameSpace, cpv(275, 341));
	_mouse = cpMouseNew(_gameSpace);
	cpCollisionHandler *handleeCollBlue = cpSpaceAddCollisionHandler(_gameSpace, 7, 3);
	handleeCollBlue->beginFunc = &collisionTypeOne;
	handleeCollBlue->userData = &_blueScore;
	cpCollisionHandler *handleeCollRed = cpSpaceAddCollisionHandler(_gameSpace, 8, 3);
	handleeCollRed->beginFunc = &collisionTypeTwo;
	handleeCollRed->userData = &_redScore;
}

cpMouse			*CP_manipulate::getMouse()
{
	return (_mouse);
}

cpSpace			*CP_manipulate::getSpace()
{
	return (_gameSpace);
}

int				CP_manipulate::getBlueScore()
{
	return (_blueScore);
}

int				CP_manipulate::getRedScore()
{
	return (_redScore);
}
