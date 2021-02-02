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

	void setAvoiding(bool avoid);
	bool getAvoiding() const;

	void setTargetLoc(glm::vec2 target);
	glm::vec2 getTargetLoc() const;
	
	void setWhisker(glm::vec2 start, glm::vec2 end);
	void setFleeing(bool flee);
	bool getFleeing() const;

	void setDistance(glm::vec2 player, glm::vec2 target);
	int getDistance() const;
	friend class PlayScene;
	
private:

	glm::vec2 m_destination;
	glm::vec2 m_fleedestination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	glm::vec2 m_targetLoc;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	int m_distance;
	bool m_fleeing;
	bool m_avoiding;
	Line m_leftWhisker, m_rightWhisker, m_targetWhisker;

	// private function
	void m_Move();
};

#endif /* defined (__SPACE_SHIP__) */