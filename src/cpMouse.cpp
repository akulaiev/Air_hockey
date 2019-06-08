/* Copyright (c) 2008 Tommy Thorsen
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../includes/cpMouse.hpp"
#include <stdio.h>
#include <iostream>

static void mouseUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt) {
	int ome = damping;
	ome = gravity.x;

	cpMouse *mouse = (cpMouse *)cpBodyGetUserData(body);
	
	/*
	 *  Calculate the velocity based on the distance moved since the
	 *  last time we calculated velocity. We use a weighted average
	 *  of the new velocity and the old velocity to make everything
	 *  a bit smoother.
	 */
	const cpVect newVelocity = cpvmult(mouse->moved, 1.0f/dt);
	
	cpBodySetVelocity(body, cpvadd(cpvmult(cpBodyGetVelocity(body), 0.7f),
					 cpvmult(newVelocity, 0.3f)));
	
	mouse->moved = cpvzero;
}

static void mouseUpdatePosition(cpBody *body, cpFloat dt) {
	cpBody *tmp = body;
	tmp = NULL;
	int tm = dt;
	tm = 0;
}

cpMouse* cpMouseAlloc() {
	return (cpMouse *)malloc(sizeof(cpMouse));
}

cpMouse* cpMouseInit(cpMouse *mouse, cpSpace *space) {
	mouse->space = space;
	mouse->moved = cpvzero;
	
	mouse->body = cpBodyNew((cpFloat)11, (cpFloat)INFINITY);
	cpBodySetVelocityUpdateFunc(mouse->body, &mouseUpdateVelocity);
	cpBodySetPositionUpdateFunc(mouse->body, &mouseUpdatePosition);
	cpBodySetUserData(mouse->body, (void*)mouse);
	cpBodySetPosition(mouse->body, cpvzero);
	cpBodySetVelocity(mouse->body, cpvzero);
	
	mouse->joint1 = NULL;
	mouse->joint2 = NULL;
	
	cpSpaceAddBody(mouse->space, mouse->body);
	
	return mouse;
}

cpMouse* cpMouseNew(cpSpace *space) {
	return cpMouseInit(cpMouseAlloc(), space);
}

void cpMouseDestroy(cpMouse *mouse) {
	cpMouseRelease(mouse);
	
	cpSpaceRemoveBody(mouse->space, mouse->body);
	cpBodyFree(mouse->body);
}

void cpMouseFree(cpMouse *mouse) {
	if (mouse) {
		cpMouseDestroy(mouse);
		free(mouse);
	}
}

void cpMouseMove(cpMouse *mouse, const cpVect position) {
	mouse->moved = cpvadd(mouse->moved, cpvsub(position, cpBodyGetPosition(mouse->body)));
	cpBodySetPosition(mouse->body, position);
}

static cpConstraint* addMouseJoint(cpMouse *mouse, cpBody *body, cpVect offset) {
	cpConstraint *joint = cpPivotJointNew(mouse->body, body, cpvadd(cpBodyGetPosition(mouse->body), offset));
	cpConstraintSetMaxForce(joint, 20000);
	// cpConstraintSetMaxBias(joint, 0.5f);
	cpSpaceAddConstraint(mouse->space, joint);
	return joint;
}

void cpMouseGrab(cpMouse *mouse, const cpVect position, const bool lockAngle, int type) {
	cpMouseRelease(mouse);
	if (!type)
		cpBodySetPosition(mouse->body, position);
	else
		cpBodySetPosition(mouse->body, cpv(120, 81));
	cpShapeFilter filter;
	filter.mask = GRABABLE_MASK_BIT;
	cpShape *shape = cpSpacePointQueryNearest(mouse->space, cpBodyGetPosition(mouse->body), 0.0, filter, 0);
	if (shape) {
		if (lockAngle) {
			/*
			*  I'd like to just use one joint that would lock the angle
			*  for me, but that doesn't exist yet, so we'll set up two
			*  pivot joints between our bodies
			*/
			mouse->joint1 = addMouseJoint(mouse, cpShapeGetBody(shape), cpv(-5,0));
			mouse->joint2 = addMouseJoint(mouse, cpShapeGetBody(shape), cpv(5,0));
		} else {
			mouse->joint1 = addMouseJoint(mouse, cpShapeGetBody(shape), cpvzero);
		}
	}
}

void cpMouseRelease(cpMouse *mouse) {
	if (mouse->joint1) {
		cpSpaceRemoveConstraint(mouse->space, mouse->joint1);
		cpConstraintFree(mouse->joint1);
		mouse->joint1 = NULL;
	}
	if (mouse->joint2) {	
		cpSpaceRemoveConstraint(mouse->space, mouse->joint2);
		cpConstraintFree(mouse->joint2);
		mouse->joint2 = NULL;
	}
}

bool	TouchBegan (cpVect touchLocation, cpMouse *_mouse, int type)
{
	cpMouseGrab(_mouse, touchLocation, false, type);
	return (true);
}

void	TouchMoved (cpVect touchLocation, cpMouse *_mouse)
{
	cpMouseMove(_mouse, touchLocation);
}

void	TouchEnded (cpMouse *_mouse)
{
	cpMouseRelease(_mouse);
}

void	TouchCancelled (cpMouse *_mouse)
{
	cpMouseRelease(_mouse);
}
