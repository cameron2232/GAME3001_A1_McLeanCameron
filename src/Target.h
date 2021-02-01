#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "DisplayObject.h"

class Target final : public DisplayObject {
public:
	Target();
	~Target();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void setTargetLoc();
	glm::vec2 getTargetLoc() const;

	
	void setDestination(glm::vec2 destination);
	glm::vec2 getDestination() const;
	void setMaxSpeed(float speed);

	void setArriving(bool arrive);
	bool getArriving() const;

	glm::vec2 Target::getTargetDirection() const;
	
	friend class PlayScene;
private:
	//void m_move();
	void m_checkBounds();
	void m_reset();
	glm::vec2 m_targetLoc;
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;


	float m_maxSpeed;
	bool m_Arriving;
	void m_MoveToArrive();
};


#endif /* defined (__TARGET__) */