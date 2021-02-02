#include "Target.h"


#include "SoundManager.h"

#include "TextureManager.h"
#include "Util.h"


Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/Circle.png","circle");

	const auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
	setMaxSpeed(2.0f);



	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("circle", x, y, 0, 255, false);
}



void Target::update()
{

	
	
	if(m_arriving == true)
	{
		m_MoveToArrive();
	}
	//m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::setTargetLoc()
{
	m_targetLoc.x = 500.0f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
	m_targetLoc.y = 600.0f * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

glm::vec2 Target::getTargetLoc() const
{
	return m_targetLoc;
}

void Target::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}

glm::vec2 Target::getDestination() const
{
	return m_destination;
}


void Target::setMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

void Target::setArriving(bool arrive)
{
	m_arriving = arrive;
}

bool Target::getArriving() const
{
	return m_arriving;
}

glm::vec2 Target::getTargetDirection() const
{
	return m_targetDirection;
}


//void Target::m_move()
//{
//	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
//}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
}

void Target::m_MoveToArrive()
{
	m_targetDirection = m_destination - getTransform()->position;
	
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}
