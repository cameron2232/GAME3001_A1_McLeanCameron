#pragma once
#ifndef _OBSTACLE_
#define _OBSTACLE_
#include "DisplayObject.h"

class Obstacle final : public DisplayObject
{
public:
	// constructors
	Obstacle();
	
	// destructor
	~Obstacle();
	
	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
};

#endif /* defined (_OBSTACLE_) */
