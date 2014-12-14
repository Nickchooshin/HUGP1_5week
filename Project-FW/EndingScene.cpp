#include "EndingScene.h"
#include "TitleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"

#include "DialogistAniManager.h"

#include "D3dDevice.h"

EndingScene::EndingScene() : m_pCredit(NULL),
							 m_pBlack(NULL), m_pBlack2(NULL),
							 m_pBGM(NULL),
							 m_nState(0),
							 m_fTime(0.0f)
{
}
EndingScene::~EndingScene()
{
	if(m_pCredit!=NULL)
		delete m_pCredit ;
	if(m_pBlack!=NULL)
		delete m_pBlack ;
	if(m_pBlack2!=NULL)
		delete m_pBlack2 ;
}

Scene* EndingScene::scene()
{
	Scene *scene = new EndingScene ;

	return scene ;
}

void EndingScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	float fWinWidth = g_D3dDevice->GetWinWidth() ;
	float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_pCredit = new CSprite ;
	m_pCredit->Init("Resource/Image/Ending/credit.png") ;
	m_pCredit->SetPosition(fWinWidth / 2.0f, -224.0f) ;

	m_pBlack = new CSprite ;
	m_pBlack->Init("Resource/Image/black.png") ;
	m_pBlack->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	m_pBlack->SetAlpha(0) ;

	m_pBlack2 = new CSprite ;
	m_pBlack2->Init("Resource/Image/black.png") ;
	m_pBlack2->SetPosition(fWinWidth / 2.0f, fWinHeight / 2.0f) ;
	m_pBlack2->SetAlpha(0) ;

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM-02.mp3", true, true) ;
}

void EndingScene::Destroy()
{
}

void EndingScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	g_DialogistAniManager->Update() ;

	if(m_nState==0)
	{
		if(m_fTime>=3.0f)
		{
			m_nState = 1 ;
			m_fTime = 0.0f ;

			m_pBlack->SetAlpha(128) ;
			g_DialogistAniManager->LineMove(0.0f) ;
			g_MusicManager->PlayMusic(m_pBGM, 0) ;
		}
		else
		{
			float fPercent = (m_fTime / 3.0f) ;
			int nAlpha = (int)(128.0f * fPercent) ;
			m_pBlack->SetAlpha(nAlpha) ;
			g_DialogistAniManager->LineMove(1.0f - fPercent) ;

			m_fTime += g_D3dDevice->GetTime() ;
		}
	}
	else if(m_nState==1)
	{
		if(m_fTime>=30.0f)
		{
			m_nState = 2 ;
			m_fTime = 0.0f ;

			m_pCredit->SetPosition(g_D3dDevice->GetWinWidth()/2.0f, 1372.0f) ;
		}
		else
		{
			float x = m_pCredit->GetPosition().x ;
			float y = -224.0f + (1148.0f * (m_fTime / 30.0f)) ;

			m_pCredit->SetPosition(x, y) ;

			m_fTime += g_D3dDevice->GetTime() ;
		}
	}
	else if(m_nState==2)
	{
		if(m_fTime>=5.0f)
		{
			g_MusicManager->StopMusic(0) ;
			g_DialogistAniManager->SetAnimation(DRIVER, "drive") ;
			g_SceneManager->ChangeScene(TitleScene::scene()) ;
			return ;
		}
		else
		{
			float fPercent = (m_fTime / 5.0f) ;
			int nAlpha = (int)(255.0f * fPercent) ;
			m_pBlack2->SetAlpha(nAlpha) ;

			m_fTime += g_D3dDevice->GetTime() ;
		}
	}
}

void EndingScene::Render()
{
	g_CameraManager->CameraRun() ;

	g_DialogistAniManager->Render() ;

	m_pBlack->Render() ;
	m_pCredit->Render() ;
	m_pBlack2->Render() ;
}