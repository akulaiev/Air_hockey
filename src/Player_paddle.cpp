
// Player_paddle.cpp
// A child class of Game_object.cpp.
// Initialises specific values for paddle, controlled by player.
// Author: Hanna Kulaieva 

#include "Player_paddle.hpp"

Player_paddle::Player_paddle	()
{
	objName = "Player_paddle";
	_radius = 25;
	_mass = 11;
	_moment = (cpFloat)INFINITY;
	_friction = 0.3;
	_elasticity = 0.1;
	_filter.categories |= (1 << 1);
	_filter.categories |= (1 << 30);
	_filter.mask = 60;
	_collisionType = 1;
}

Player_paddle::Player_paddle	(Player_paddle const & inst)
{
	*this = inst;
}

Player_paddle::~Player_paddle	() {}

Player_paddle &	Player_paddle::operator=(Player_paddle const & inst)
{
	(void)inst;
	return (*this);
}
