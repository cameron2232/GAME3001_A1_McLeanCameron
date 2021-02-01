#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	if (CollisionManager::lineRectCheck(m_pSpaceShip->m_leftWhisker.Start(), m_pSpaceShip->m_leftWhisker.End(),
		(m_pObstacle->getTransform()->position - glm::vec2(100.0f, 50.0f)), 200.0f, 100.0f))
	{
		//SoundManager::Instance().playSound("yay", 0);
		std::cout << "Colliding with obstacle!" << std::endl;
	}

	if (CollisionManager::lineRectCheck(m_pSpaceShip->m_targetWhisker.Start(), m_pSpaceShip->m_targetWhisker.End(),
		(m_pObstacle->getTransform()->position - glm::vec2(100.0f, 50.0f)), 200.0f, 100.0f))
	{
		std::cout << "No line of Sight!" << std::endl;
	}
	
	CollisionManager::AABBCheck(m_pSpaceShip, m_pTarget);

	if (m_pSpaceShip->getFleeing())
	{
		std::cout << "Updating current location..." << std::endl;
		m_pSpaceShip->setFleeDestination(m_pTarget->getTransform()->position, m_pSpaceShip->getTransform()->position);
	}

	if(m_pTarget->getArriving())
	{
		m_pSpaceShip->setArriveDestination(m_pTarget->getTransform()->position, m_pSpaceShip->getTransform()->position, m_pTarget->m_destination);
	}
	
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{

	EventManager::Instance().update();


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		//TheGame::Instance()->changeSceneState(START_SCENE);
		m_pTarget->setTargetLoc();
		m_pTarget->getTransform()->position = m_pTarget->getTargetLoc();
		m_pTarget->setEnabled(true);
		m_pTarget->setArriving(false);
		
		m_pSpaceShip->setRotation(0.0f);
		m_pSpaceShip->setBehaviour(1);
		m_pSpaceShip->getTransform()->position = glm::vec2(10.0f, 10.0f);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip->setEnabled(true);
		m_pSpaceShip->setFleeing(false);

		m_pObstacle->setEnabled(false);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		//TheGame::Instance()->changeSceneState(START_SCENE);
		m_pTarget->setTargetLoc();
		m_pTarget->getTransform()->position = m_pTarget->getTargetLoc();
		m_pTarget->setArriving(false);
		m_pTarget->setEnabled(true);

		m_pSpaceShip->setRotation(-45.0f);
		m_pSpaceShip->setBehaviour(1);
		m_pSpaceShip->getTransform()->position = glm::vec2(400.0f, 300.0f);
		m_pSpaceShip->setFleeDestination(m_pTarget->getTransform()->position, m_pSpaceShip->getTransform()->position);
		m_pSpaceShip->setEnabled(true);
		m_pSpaceShip->setFleeing(true);

		m_pObstacle->setEnabled(false);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		//Arrival
		m_pTarget->getTransform()->position = glm::vec2{ 600.0f, 500.0f };
		m_pTarget->setArriving(true);
		m_pTarget->setDestination(glm::vec2{ 100.0f, 300.0f });
		
		m_pTarget->setEnabled(true);

		m_pSpaceShip->setRotation(0.0f);
		m_pSpaceShip->setBehaviour(1);
		m_pSpaceShip->getTransform()->position = glm::vec2(600.0f, 300.0f);
		m_pSpaceShip->setArriveDestination(m_pTarget->getTransform()->position, m_pSpaceShip->getTransform()->position, m_pTarget->m_destination);
		m_pSpaceShip->setFleeing(false);

		m_pSpaceShip->setEnabled(true);

		m_pObstacle->setEnabled(false);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		m_pObstacle->setEnabled(true);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		m_pTarget->setEnabled(false);
		m_pTarget->setArriving(false);
		
		m_pSpaceShip->setEnabled(false);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setRotation(0.0f); //set angle to 0 degrees
		m_pSpaceShip->setFleeing(false);
	}

	
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pTarget = new Target();
	m_pTarget->setEnabled(false);
	addChild(m_pTarget);
	

	m_pObstacle = new Obstacle();
	m_pObstacle->getTransform()->position = glm::vec2(500.0f, 300.0f);
	m_pObstacle->setEnabled(false);
	addChild(m_pObstacle);

	// instantiating spaceship
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->setEnabled(false);
	m_pSpaceShip->setBehaviour(1);
	/*m_pSpaceShip->m_leftWhisker.SetLine(getTransform()->position,
		(getTransform()->position + Util::getOrientation(m_rotationAngle - 30) * 100.0f));*/
	addChild(m_pSpaceShip);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float speed = 10.0f;
	if(ImGui::SliderFloat("MaxSpeed", &speed, 0.0f, 100.0f))
	{
		m_pSpaceShip->setMaxSpeed(speed);
	}

	static float acceleration_rate = 2.0f;
	if(ImGui::SliderFloat("Acceleration Rate", &acceleration_rate, 0.0f, 50.0f))
	{
		m_pSpaceShip->setAccelerationRate(acceleration_rate);
	}

	static float angleInRadians = m_pSpaceShip->getRotation();
	if(ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	{
		m_pSpaceShip->setRotation(angleInRadians * Util::Rad2Deg);
	}

	static float turn_rate = 5.0f;
	if (ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pSpaceShip->setTurnRate(turn_rate);
	}
	
	if(ImGui::Button("Start"))
	{
		m_pSpaceShip->setEnabled(true);
	}

	ImGui::SameLine();
	
	if (ImGui::Button("Reset"))
	{

		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceShip->setEnabled(false);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setRotation(0.0f); //set angle to 0 degrees
		turn_rate = 5.0f;
		acceleration_rate = 2.0f;
		speed = 10.0f;
		angleInRadians = m_pSpaceShip->getRotation();
	}

	ImGui::Separator();

	static float targetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPosition[0], targetPosition[1]);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
