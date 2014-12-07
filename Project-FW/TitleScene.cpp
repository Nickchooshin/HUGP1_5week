#include "TitleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "D3dDevice.h"

TitleScene::TitleScene() : m_pBackground(NULL)
{
}
TitleScene::~TitleScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
}

Scene* TitleScene::scene()
{
	Scene *scene = new TitleScene ;

	return scene ;
}

void TitleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	float fWinWidth = g_D3dDevice->GetWinWidth() ;
	float fWinHeight = g_D3dDevice->GetWinHeight() ;
}

void TitleScene::Destroy()
{
}

void TitleScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;
}

void TitleScene::Render()
{
	g_CameraManager->CameraRun() ;
}