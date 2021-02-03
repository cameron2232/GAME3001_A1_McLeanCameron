#include "SpaceShip.h"


#include "Game.h"
#include "Util.h"

SpaceShip::SpaceShip()
{
	TextureManager::Instance()->load("../Assets/textures/MarvinUp.png", "spaceship");

	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);
	setMaxSpeed(3.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setAccelerationRate(5.0f);
	setTurnRate(4.0f);

	SoundManager::Instance().load("../Assets/audio/Explosion.ogg", "tetrisclear", SOUND_SFX);
	SoundManager::Instance().setSoundVolume(75);
	
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	TextureManager::Instance()->draw("spaceship", 
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, false);

	//Util::DrawLine(getTransform()->position, m_destination);
	/*Util::DrawLine(m_leftWhisker.Start(), m_leftWhisker.End());
	Util::DrawLine(m_rightWhisker.Start(), m_rightWhisker.End());*/
	Util::DrawLine(m_targetWhisker.Start(), m_targetWhisker.End());
}

void SpaceShip::update()
{
	m_leftWhisker.SetLine(getTransform()->position,
		(getTransform()->position + Util::getOrientation(m_rotationAngle-30) * 100.0f)); 
	m_rightWhisker.SetLine(getTransform()->position,
		(getTransform()->position + Util::getOrientation(m_rotationAngle + 30) * 100.0f));
	m_targetWhisker.SetLine(getTransform()->position,
		getTargetLoc());

	if(!m_colliding)
	{
		m_Move();
	}
	
		

	//m_Move();

}

void SpaceShip::clean()
{
}


glm::vec2 SpaceShip::getOrientation() const
{
	return m_orientation;
}

float SpaceShip::getTurnRate() const
{
	return m_turnRate;
}

float SpaceShip::getAccelerationRate() const
{
	return m_accelerationRate;
}

float SpaceShip::getRotation() const
{
	return m_rotationAngle;
}

bool SpaceShip::getAvoiding() const
{
	return m_avoiding;
}

void SpaceShip::setTurnRate(float rate)
{
	m_turnRate = rate;
}

void SpaceShip::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void SpaceShip::setAvoiding(bool avoid)
{
	m_avoiding = avoid;
}

void SpaceShip::setOrientation(const glm::vec2 orientation)
{
	m_orientation = orientation;
}

void SpaceShip::setDestination(const glm::vec2 destination) // send player to target location
{
	m_destination = destination;
	//std::cout << m_destination.x << std::endl << m_destination.y;
}

void SpaceShip::setFleeDestination(glm::vec2 destination, glm::vec2 player) 
{
	/*m_destination.x = -1 * (destination.x);
	m_destination.y = -1 * (destination.y);*/
	m_destination.x = (player.x + (player.x - destination.x));
	m_destination.y = (player.y + (player.y - destination.y));
	//std::cout << m_destination.x << std::endl << m_destination.y;
	
}

void SpaceShip::setArriveDestination(glm::vec2 target, glm::vec2 player, glm::vec2 arrive)
{
	m_destination.x = arrive.x + (target.x - player.x);
	m_destination.y = arrive.y + (target.y - player.y);
	
}


void SpaceShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}



void SpaceShip::setFleeing(bool flee)
{
	m_fleeing = flee;
}

bool SpaceShip::getFleeing() const
{
	return m_fleeing;
}

void SpaceShip::setColliding(bool collision)
{
	m_colliding = collision;
}

bool SpaceShip::getColliding() const
{
	return m_colliding;
}

void SpaceShip::setDistance(glm::vec2 player, glm::vec2 target)
{
	m_distance = sqrt(((target.x - player.x) * (target.x - player.x)) + ((target.y - player.y) * (target.y - player.y)));
	std::cout << m_distance << std::endl;
}

int SpaceShip::getDistance() const
{
	return m_distance;
}

glm::vec2 SpaceShip::getTargetLoc() const
{
	return m_targetLoc;
}

void SpaceShip::setTargetLoc(glm::vec2 target)
{
	m_targetLoc = target;
}


void SpaceShip::setWhisker(glm::vec2 start, glm::vec2 end)
{
	m_targetWhisker.SetLine(start, end);
}

void SpaceShip::setRotation(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

void SpaceShip::m_Move()
{

	auto deltaTime = TheGame::Instance()->getDeltaTime();

	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}



	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
	
	// direction with magnitude
	
}






