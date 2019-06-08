
// Puck.hpp
// A header for the child class of Game_object.cpp.
// Initialises specific values for puck.
// Author: Hanna Kulaieva 

#ifndef PUCK_HPP
#define PUCK_HPP

#include "Game_object.hpp"
#include <iostream>

class Puck : public Game_object
{
public:
	Puck	();
	Puck	(Puck const & inst);
	~Puck	();
	Puck &	operator=(Puck const & inst);

private:

};

#endif