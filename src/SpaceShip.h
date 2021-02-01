#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__
#include "DisplayObject.h"
#include "TextureManager.h"
#include "Line.h"


class SpaceShip final : public DisplayObject
{
public:
	// constructor(s)
	SpaceShip();

	// destructor
	~SpaceShip();
	
	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	// getters and setters
	void setDestination(glm::vec2 destination);
	void setFleeDestination(glm::vec2 destination, glm::vec2 player);
	void setArriveDestination(glm::vec2 destination, glm::vec2 player, glm::vec2 arrive);
	
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation() const;
	void setOrientation(glm::vec2 orientation);
	float getRotation() const;
	void setRotation(float angle);
	float getTurnRate() const;
	void setTurnRate(float rate);
	float getAccelerationRate() const;
	void setAccelerationRate(float rate);
	int getBehaviour() const;
	void setBehaviour(int behaviour);
	void setWhisker(glm::vec2 start, glm::vec2 end);
	void setFleeing(bool flee);
	bool getFleeing() const;
	friend class PlayScene;
	
private:

	glm::vec2 m_destination;
	glm::vec2 m_fleedestination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	int m_behaviour;
	bool m_Fleeing;
	Line m_leftWhisker, m_rightWhisker;

	// private function
	void m_Seek();
};

#endif /* defined (__SPACE_SHIP__) */