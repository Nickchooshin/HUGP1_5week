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
#include "DialogistAniManager.h"

GameScene::GameScene() : m_pBackground(NULL)
{
}
GameScene::~GameScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
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

	g_DialogistAniManager->Update() ;
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	g_DialogManager->Render() ;

	g_DialogistAniManager->Render() ;
}