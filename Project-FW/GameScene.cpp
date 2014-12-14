#include "GameScene.h"
#include "EndingScene.h"
#include "SceneManager.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "ButtonManager.h"

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

	g_ScriptQueueManager->LoadScript("Resource/Data/Script/sample.dat") ;
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

	g_ButtonManager->Update() ;

	g_DialogistAniManager->Update() ;

	g_ScriptQueueManager->Update() ;

	if(g_ScriptQueueManager->BeQueueEnd())
	{
		for(int i=0; i<32; i++)
			g_MusicManager->StopMusic(i) ;
		g_SceneManager->ChangeScene(EndingScene::scene()) ;
		return ;
	}
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	g_DialogistAniManager->Render() ;

	g_DialogManager->Render() ;
}