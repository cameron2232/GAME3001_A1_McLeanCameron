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

	void setNode(glm::vec2 obstacle);
	void setTargetNode(glm::vec2 target, glm::vec2 obstacle, glm::vec2 player);

	glm::vec2 getTargetNode() const;

	glm::vec2 getNode1() const;
	glm::vec2 getNode2() const;
	glm::vec2 getNode3() const;
	glm::vec2 getNode4() const;

private:

	glm::vec2 m_node1, m_node2, m_node3, m_node4, m_targetnode;
};

#endif /* defined (_OBSTACLE_) */
