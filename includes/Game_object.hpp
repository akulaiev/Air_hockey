
// Game_object.hpp
// A header file of the class for all of the physical game objects: paddles and puck.
// It has method for copying objects' sprites to renderer and method for initialising
// objects' shapes.
// Author: Hanna Kulaieva 

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "../Chipmunk2D/include/chipmunk.h"
#include "../SDL2/include/SDL.h"
#include "cpMouse.hpp"
#include <iostream>

class Game_object
{
public:

	Game_object				();
	Game_object				(Game_object const & inst);
	virtual ~Game_object	();
	Game_object &	operator=(Game_object const & inst);

	void					setRenderer(SDL_Renderer *renderer);
	void					initObjShape(cpSpace *gameSpace, cpVect objPos);
	void					placeObject();

	cpShape					*objShape;
	cpBody					*objBody;
	int						objWidth;
	int						objHeight;
	SDL_Texture				*objSurface;
	std::string				objName;

	int						getRadius();

protected:

	SDL_Renderer			*_renderer;
	cpSpace					*_gameSpace;
	cpFloat					_moment;
	cpFloat					_radius;
	cpFloat					_mass;
	cpFloat					_friction;
	cpFloat					_elasticity;
	cpShapeFilter			_filter;
	int						_collisionType;
	cpVect					_cornerTopLeft;
	cpVect					_cornerTopRight;
	cpVect					_cornerBottomLeft;
	cpVect					_cornerBottomRight;
};

#endif