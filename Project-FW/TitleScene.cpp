#include "TitleScene.h"
#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"

#include "Button.h"
#include "ButtonManager.h"

#include "DialogistAniManager.h"

#include "D3dDevice.h"

TitleScene::TitleScene() : m_pTitle(NULL),
						   m_pStart(NULL), m_pExit(NULL),
						   m_nState(0),
						   m_fTime(0.0f)
{
}
TitleScene::~TitleScene()
{
	if(m_pTitle!=NULL)
		delete m_pTitle ;
	if(m_pStart!=NULL)
		g_ButtonManager->DeleteButton(m_pStart) ;
	if(m_pExit!=NULL)
		g_ButtonManager->DeleteButton(m_pExit) ;
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

	m_pTitle = new CSprite ;
	m_pTitle->Init("Resource/Image/Title/Title_bg.png") ;
	m_pTitle->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;

	m_pStart = new CButton ;
	m_pStart->Init(180.0f, 40.0f, "Resource/Image/Title/Title_btn1.png") ;
	m_pStart->SetPosition(160.0f, fWinHeight - 500.0f) ;
	m_pStart->SetIndex(0, 1, 0, 0) ;
	m_pStart->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pStart) ;

	m_pExit = new CButton ;
	m_pExit->Init(180.0f, 40.0f, "Resource/Image/Title/Title_btn2.png") ;
	m_pExit->SetPosition(160.0f, fWinHeight - 640.0f) ;
	m_pExit->SetIndex(0, 1, 0, 0) ;
	m_pExit->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pExit) ;
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

	if(m_nState==0)
	{
		g_ButtonManager->Update() ;

		g_DialogistAniManager->Update() ;

		if(m_pStart->BeClick())
		{
			m_nState = 1 ;
		}
		else if(m_pExit->BeClick())
		{
			PostQuitMessage(0) ;
			return ;
		}
	}
	else if(m_nState==1)
	{
		if(m_fTime>=3.0f)
		{
			g_SceneManager->ChangeScene(GameScene::scene()) ;
			return ;
		}

		float fPercent = (m_fTime / 3.0f) ;
		int nAlpha = 255 - (int)(255.0f * fPercent) ;
		m_pTitle->SetAlpha(nAlpha) ;
		m_pStart->SetAlpha(nAlpha) ;
		m_pExit->SetAlpha(nAlpha) ;
		g_DialogistAniManager->LineMove(fPercent) ;

		m_fTime += g_D3dDevice->GetTime() ;
	}
}

void TitleScene::Render()
{
	g_CameraManager->CameraRun() ;

	g_DialogistAniManager->Render() ;
	m_pTitle->Render() ;

	m_pStart->Render() ;
	m_pExit->Render() ;
}