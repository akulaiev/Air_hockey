
// CP_manipulate.hpp
// A header file for the class, that initialises Chipmunk physical engine and creates game space,
// as well as attaching objects' shaoes to their bodies.
// It also assignes all of their parameteres (density, friction. elastity etc.)
// and adds collision filters and groups. Collision handler methods are also in this file.
// Author: Hanna Kulaieva 

#ifndef CP_MANIPULATE_HPP
#define CP_MANIPULATE_HPP

#include <iostream>
#include <vector>
#include "Player_paddle.hpp"
#include "AI_paddle.hpp"
#include "Puck.hpp"

class CP_manipulate
{
public:
	CP_manipulate		();
	CP_manipulate		(CP_manipulate const & inst);
	~CP_manipulate		();
	CP_manipulate &	operator=(CP_manipulate const & inst);

	cpMouse			*getMouse();
	cpSpace			*getSpace();
	void			cpInit (Player_paddle *playerPaddle, AI_paddle *AIPaddle,
					Puck *puck);
	int				getBlueScore();
	int				getRedScore();

private:
	cpVect			_gravity;
	cpSpace			*_gameSpace;
	cpBody			*_table;
	cpBody			*_gTop;
	cpBody			*_gBottom;
	cpShape			*_goalTop;
	cpShape			*_goalBottom;
	cpShape			*_goalTopLeft;
	cpShape			*_goalTopRight;
	cpShape			*_goalTopBack;
	cpShape			*_goalBottomBack;
	cpShape			*_goalBottomLeft;
	cpShape			*_goalBottomRight;
	cpShape			*_leftBorder;
	cpShape			*_rightBorder;
	cpShape			*_topBorderLeft;
	cpShape			*_topBorderRight;
	cpShape			*_bottomBorderLeft;
	cpShape			*_bottomBorderRight;
	cpShape			*_middleBorder;
	cpMouse			*_mouse;
	const int		_wWidth;
	const int		_wHeight;
	int				_blueScore;
	int				_redScore;
};

#endif
