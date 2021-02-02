#include "Obstacle.h"


#include "SoundManager.h"
#include "TextureManager.h"

Obstacle::Obstacle()
{
	TextureManager::Instance()->load("../Assets/textures/tetrisbutbad.png", "obstacle");

	auto size = TextureManager::Instance()->getTextureSize("obstacle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);
	
	setType(OBSTACLE);
	getRigidBody()->isColliding = false;

	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
}

Obstacle::~Obstacle()
= default;

void Obstacle::draw()
{
	TextureManager::Instance()->draw("obstacle", 
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Obstacle::update()
{
	
}

void Obstacle::clean()
{
	
}

void Obstacle::setNode(glm::vec2 obstacle)
{
	m_node1 = { obstacle.x - 200, obstacle.y - 125 }; //top left
	m_node2 = { obstacle.x + 200, obstacle.y - 125 }; //top right
	m_node3 = { obstacle.x - 200, obstacle.y + 125 }; //bottom left
	m_node4 = { obstacle.x + 200, obstacle.y + 125 }; //bottom right
}

void Obstacle::setTargetNode(glm::vec2 target, glm::vec2 obstacle, glm::vec2 player)
{
	if (target.x > obstacle.x) //if target x is greater than obstacle x
	{
		if(target.y > obstacle.y) //if target y is greater than obstacle y (NODE QUADRANT 4)
		{
			if(player.y < obstacle.y) //if player y is less than obstacle y
			{
				m_targetnode = m_node2; 
			}
			else if(player.y >= obstacle.y) //if player y is greater than or equal to obstacle y
			{
				m_targetnode = m_node3;
			}
		}

		else if(target.y < obstacle.y) //if target y is less than obstacle y and target x is greater than obstacle x  (NODE QUADRANT 2)
		{
			if(player.y >= obstacle.y) //if player y is greater than obstacle y
			{
				m_targetnode = m_node1;
			}
			else if(player.y < obstacle.y) //if player y is less than obstacle y
			{
				m_targetnode = m_node2;
			}
		}
	}
	else if(target.x < obstacle.x) //if target x is less than obstacle x
	{
		if (target.y > obstacle.y) //if target y is greater than obstacle y (NODE 3 QUADRANT)
		{
			if(player.y > obstacle.y) //if player y is greater than obstacle y
			{
				m_targetnode = m_node4;
			}
			else if(player.y < obstacle.y) //if player y is less than obstacle y
			{
				m_targetnode = m_node1;
			}
		}
		else if(target.y < obstacle.y) //if target y is less than obstacle y (NODE QUADRANT 1)
		{
			if(player.y >= obstacle.y) //if player y is greater than obstacle y
			{
				m_targetnode = m_node2;
			}
			else if(player.y < obstacle.y) //if player y is less than obstacle y
			{
				m_targetnode = m_node1;
			}
		}
	}
	std::cout << "x: " << m_targetnode.x << " y: " << m_targetnode.y << std::endl;
}

glm::vec2 Obstacle::getTargetNode() const
{
	std::cout << "x: " << m_targetnode.x << "y: " << m_targetnode.y << std::endl;
	return m_targetnode;
}

glm::vec2 Obstacle::getNode1() const
{
	return m_node1;
}

glm::vec2 Obstacle::getNode2() const
{
	return m_node2;
}

glm::vec2 Obstacle::getNode3() const
{
	return m_node3;
}

glm::vec2 Obstacle::getNode4() const
{
	return m_node4;
}
