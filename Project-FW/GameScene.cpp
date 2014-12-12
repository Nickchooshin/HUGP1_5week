#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "D3dDevice.h"

#include "ScriptQueueManager.h"
#include "DialogManager.h"

//
#include "Objects_Ani.h"

GameScene::GameScene() : m_pBackground(NULL),
	m_pGuest(NULL)
{
}
GameScene::~GameScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;

	if(m_pGuest!=NULL)
		delete m_pGuest ;
}

Scene* GameScene::scene()
{
	Scene *scene = new GameScene ;

	return scene ;
}

void GameScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	float fWinWidth = g_D3dDevice->GetWinWidth() ;
	float fWinHeight = g_D3dDevice->GetWinHeight() ;

	g_ScriptQueueManager->LoadScript("Resource/Data/sample.dat") ;

	m_pGuest = new CObjects_Ani ;
	m_pGuest->Init("Resource/Data/NPC/npc_body1.dat") ;
	m_pGuest->SetPosition(100, 500) ;
}

void GameScene::Destroy()
{
}

void GameScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	g_ScriptQueueManager->Update() ;

	m_pGuest->Update() ;
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	g_DialogManager->Render() ;

	m_pGuest->Render() ;
}