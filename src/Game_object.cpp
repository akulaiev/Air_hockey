
// Game_object.cpp
// A parent class for all of the physical game objects: paddles and puck.
// It has method for copying objects' sprites to renderer and method for initialising
// objects' shapes.
// Author: Hanna Kulaieva 

#include "Game_object.hpp"

Game_object::Game_object	()
{
	objWidth = 0;
	objHeight = 0;
	objSurface = NULL;
	objBody = NULL;
	_cornerTopLeft = cpv(45, 40);
	_cornerTopRight = cpv(535, 40);
	_cornerBottomLeft = cpv(45, 680);
	_cornerBottomRight = cpv(535, 680);
	_filter.categories = 0;
	_filter.group = 0;
	_filter.mask = 0;
}

Game_object::Game_object	(Game_object const & inst)
{
	*this = inst;
}

Game_object::~Game_object	() {}

Game_object &				Game_object::operator=(Game_object const & inst)
{
	objShape = inst.objShape;
	objBody = inst.objBody;
	objWidth = inst.objWidth;
	objHeight = inst.objHeight;
	objSurface = inst.objSurface;
	objName = inst.objName;
	_renderer = inst._renderer;
	_gameSpace = inst._gameSpace;
	_moment = inst._moment;
	_radius = inst._radius;
	_mass = inst._mass;
	_friction = inst._friction;
	_elasticity = inst._elasticity;
	_filter = inst._filter;
	_collisionType = inst._collisionType;
	_cornerTopLeft = inst._cornerTopLeft;
	_cornerTopRight = inst._cornerTopRight;
	_cornerBottomLeft = inst._cornerBottomLeft;
	_cornerBottomRight = inst._cornerBottomRight;
	return (*this);
}

void			Game_object::setRenderer(SDL_Renderer *renderer)
{
	_renderer = renderer;
}

void			Game_object::initObjShape(cpSpace *gameSpace, cpVect objPos)
{
	_gameSpace = gameSpace;
	objBody = cpSpaceAddBody(_gameSpace, cpBodyNew(_mass, _moment));
	cpBodySetPosition(objBody, objPos);
	cpBodySetVelocity(objBody, cpvzero);
	objShape = cpSpaceAddShape(_gameSpace, cpCircleShapeNew(objBody, _radius, cpvzero));
	cpShapeSetFriction(objShape, _friction);
	cpShapeSetElasticity(objShape, _elasticity);
	cpShapeSetFilter(objShape, _filter);
	cpShapeSetCollisionType(objShape, _collisionType);
}

void			Game_object::placeObject()
{
	SDL_Rect dest;

	if (!objHeight && !objWidth)
		SDL_QueryTexture(objSurface, NULL, NULL, &objHeight, &objWidth);
	dest.x = cpBodyGetPosition(objBody).x;
	dest.y = cpBodyGetPosition(objBody).y;
	dest.w = objHeight;
	dest.h = objWidth;
	if (SDL_RenderCopy(_renderer, objSurface, NULL, &dest))
	{
		std::cout << "Couldn't copy renderer" << std::endl;
		exit(5);
	}
}

int				Game_object::getRadius()
{
	return (_radius);
}