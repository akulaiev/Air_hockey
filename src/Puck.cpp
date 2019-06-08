
// Puck.cpp
// A child class of Game_object.cpp.
// Initialises specific values for puck.
// Author: Hanna Kulaieva 

#include "Puck.hpp"

Puck::Puck	()
{
	objName = "Puck";
	_radius = 15;
	_mass = 5;
	_moment = cpMomentForCircle(_mass, 0, _radius, cpvzero);
	_friction = 0.5;
	_elasticity = 0.7;
	_filter.categories |= (1 << 3);
	_filter.categories |= (1 << 31);
	_filter.mask = 22;
	_collisionType = 3;
}

Puck::Puck	(Puck const & inst)
{
	*this = inst;
}

Puck::~Puck	() {}

Puck &	Puck::operator=(Puck const & inst)
{
	(void)inst;
	return (*this);
}
