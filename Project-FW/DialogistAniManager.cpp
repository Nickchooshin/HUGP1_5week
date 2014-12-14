#include "DialogistAniManager.h"
#include "Objects_Ani.h"
#include "Sprite.h"

#include "D3dDevice.h"

CDialogistAniManager::CDialogistAniManager() : m_pDriver(NULL), m_pDriverHand(NULL),
											   m_pGuest(NULL), m_pGuestMove(NULL),
											   m_pFront(NULL), m_pSeatB(NULL), m_pSeatF(NULL), m_pLamp(NULL),
											   m_pLineU(NULL), m_pLineD(NULL),
											   m_nAniState(0),
											   m_fAnimationTime(0.0f),
											   m_bGuestMove(false)
{
	float WinWidthHalf = g_D3dDevice->GetWinWidth() / 2.0f ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	m_pDriver = new CObjects_Ani ;
	m_pDriver->Init("Resource/Data/Driver.dat") ;
	m_pDriver->SetPosition(510.0f, WinHeight - 310.0f) ;

	m_pDriverHand = new CObjects_Ani ;
	m_pDriverHand->Init("Resource/Data/Driver_hand.dat") ;
	m_pDriverHand->SetPosition(496.0f, WinHeight - 464.0f) ;

	m_pGuestMove = new CObjects_Ani ;
	m_pGuestMove->Init("Resource/Data/NPC/npc_aboarding.dat") ;
	m_pGuestMove->SetPosition(288.0f, WinHeight - 380.0f) ;

	m_pFront = new CSprite ;
	m_pFront->Init("Resource/Image/Inside/inside_front.png") ;
	m_pFront->SetPosition(WinWidthHalf, WinHeight - 635.0f) ;

	m_pSeatB = new CSprite ;
	m_pSeatB->Init("Resource/Image/Inside/inside_seat_b.png") ;
	m_pSeatB->SetPosition(314.0f, WinHeight - 290.0f) ;
	
	m_pSeatF = new CSprite ;
	m_pSeatF->Init("Resource/Image/Inside/inside_seat_f.png") ;
	m_pSeatF->SetPosition(288.0f, WinHeight - 285.0f) ;
	
	m_pLamp = new CSprite ;
	m_pLamp->Init("Resource/Image/Inside/inside_lamp.png") ;
	m_pLamp->SetPosition(WinWidthHalf, WinHeight - 285.0f) ;

	m_pLineU = new CSprite ;
	m_pLineU->Init(600.0f, 50.0f, "Resource/Image/black.png") ;
	m_pLineU->SetPosition(WinWidthHalf, WinHeight + 25.0f) ;

	m_pLineD = new CSprite ;
	m_pLineD->Init(600.0f, 50.0f, "Resource/Image/black.png") ;
	m_pLineD->SetPosition(WinWidthHalf, -25.0f) ;
}
CDialogistAniManager::~CDialogistAniManager()
{
	if(m_pDriver!=NULL)
		delete m_pDriver ;
	if(m_pDriverHand!=NULL)
		delete m_pDriverHand ;
	if(m_pGuest!=NULL)
		delete m_pGuest ;
	if(m_pGuestMove!=NULL)
		delete m_pGuestMove ;

	if(m_pFront!=NULL)
		delete m_pFront ;
	if(m_pSeatB!=NULL)
		delete m_pSeatB ;
	if(m_pSeatF!=NULL)
		delete m_pSeatF ;
	if(m_pLamp!=NULL)
		delete m_pLamp ;

	if(m_pLineU!=NULL)
		delete m_pLineU ;
	if(m_pLineD!=NULL)
		delete m_pLineD ;
}

void CDialogistAniManager::SetAnimation(Dialogist dialogist, char *state)
{
	CObjects_Ani *pObject ;

	if(dialogist==DRIVER)
	{
		m_pDriver->SetAnimation(state) ;
		m_pDriverHand->SetAnimation(state) ;
	}
	else
	{
		if(m_pGuest!=NULL)
			m_pGuest->SetAnimation(state) ;
	}
}

void CDialogistAniManager::GuestGetOn(CObjects_Ani *pGuest)
{
	if(m_pGuest!=NULL)
		delete m_pGuest ;

	m_pGuest = pGuest ;
}

void CDialogistAniManager::GuestGetOff()
{
	delete m_pGuest ;
	m_pGuest = NULL ;
}

bool CDialogistAniManager::AniSitDown()
{
	if(!m_bGuestMove)
	{
		m_pGuest->SetAlpha(0) ;
		m_pGuestMove->SetAlpha(255) ;
		m_pGuestMove->SetPosition(88.0f, m_pGuestMove->GetPositionY()) ;

		m_pGuestMove->SetAnimation("get_on") ;
		m_bGuestMove = true ;
	}

	if(m_nAniState==0)
	{
		if(m_pGuestMove->AnimationEnd())
		{
			m_nAniState = 1 ;
			m_pGuestMove->SetAnimation("sit_down") ;
			m_pGuestMove->SetPosition(288.0f, m_pGuestMove->GetPositionY()) ;
			m_fAnimationTime = 0.0f ;
		}
		else
		{
			float x = 88.0f + ((m_fAnimationTime / 1.2f) * 200.0f) ;
			float y = m_pGuestMove->GetPositionY() ;

			m_pGuestMove->SetPosition(x, y) ;
			m_fAnimationTime += g_D3dDevice->GetTime() ;
		}
	}
	else if(m_nAniState==1)
	{
		if(m_pGuestMove->AnimationEnd())
		{
			m_nAniState = 2 ;
			m_pGuestMove->SetAnimation("sit") ;
		}
	}
	else if(m_nAniState==2)
	{
		if(m_fAnimationTime>=1.0f)
		{
			m_pGuest->SetAlpha(255) ;
			m_pGuestMove->SetAlpha(0) ;

			m_nAniState = 0 ;
			m_bGuestMove = false ;
			m_fAnimationTime = 0.0f ;
			return true ;
		}
		else
		{
			int nAlpha = (int)(255.0f * (m_fAnimationTime / 1.0f)) ;
			m_pGuest->SetAlpha(nAlpha) ;
			m_pGuestMove->SetAlpha(255 - nAlpha) ;

			m_fAnimationTime += g_D3dDevice->GetTime() ;
		}
	}

	m_pGuestMove->Update() ;

	return false ;
}

bool CDialogistAniManager::AniSitUp()
{
	if(!m_bGuestMove)
	{
		m_pGuest->SetAlpha(255) ;
		m_pGuestMove->SetAlpha(0) ;
		m_pGuestMove->SetPosition(288.0f, m_pGuestMove->GetPositionY()) ;

		m_pGuestMove->SetAnimation("sit") ;
		m_bGuestMove = true ;
	}

	if(m_nAniState==0)
	{
		if(m_fAnimationTime>=1.0f)
		{
			m_pGuest->SetAlpha(0) ;
			m_pGuestMove->SetAlpha(255) ;

			m_nAniState = 1 ;
			m_fAnimationTime = 0.0f ;
			m_pGuestMove->SetAnimation("sit_up") ;
		}
		else
		{
			int nAlpha = (int)(255.0f * (m_fAnimationTime / 1.0f)) ;
			m_pGuest->SetAlpha(255 - nAlpha) ;
			m_pGuestMove->SetAlpha(nAlpha) ;

			m_fAnimationTime += g_D3dDevice->GetTime() ;
		}
	}
	else if(m_nAniState==1)
	{
		if(m_pGuestMove->AnimationEnd())
		{
			m_nAniState = 2 ;
			m_pGuestMove->SetAnimation("get_off") ;
		}
	}
	else if(m_nAniState==2)
	{
		if(m_pGuestMove->AnimationEnd())
		{
			m_nAniState = 0 ;
			m_bGuestMove = false ;
			m_pGuestMove->SetPosition(88.0f, m_pGuestMove->GetPositionY()) ;
			m_fAnimationTime = 0.0f ;
			return true ;
		}
		else
		{
			float x = 288.0f + ((m_fAnimationTime / 1.2f) * -200.0f) ;
			float y = m_pGuestMove->GetPositionY() ;

			m_pGuestMove->SetPosition(x, y) ;
			m_fAnimationTime += g_D3dDevice->GetTime() ;
		}
	}

	m_pGuestMove->Update() ;

	return false ;
}

void CDialogistAniManager::LineMove(float fPercent)
{
	float WinWidthHalf = g_D3dDevice->GetWinWidth() / 2.0f ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;
	float fY = 50.0f * fPercent ;

	m_pLineU->SetPosition(WinWidthHalf, (WinHeight + 25.0f) - fY) ;
	m_pLineD->SetPosition(WinWidthHalf, -25.0f + fY) ;
}

void CDialogistAniManager::Update()
{ 
	if(m_pGuest!=NULL)
		m_pGuest->Update() ;

	m_pDriver->Update() ;
	m_pDriverHand->Update() ;
}

void CDialogistAniManager::Render()
{
	m_pSeatB->Render() ;

	if(m_bGuestMove)
		m_pGuestMove->Render() ;
	if(m_pGuest!=NULL)
		m_pGuest->Render() ;

	m_pSeatF->Render() ;

	m_pDriver->Render() ;
	m_pDriverHand->Render() ;

	m_pFront->Render() ;
	//m_pLamp->Render() ;

	m_pLineU->Render() ;
	m_pLineD->Render() ;
}

void CDialogistAniManager::Swing()
{
}