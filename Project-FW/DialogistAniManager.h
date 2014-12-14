#pragma once

#include "Singleton.h"
#include "Dialogist.h"

class CObjects_Ani ;
class CSprite ;

class CDialogistAniManager : public Singleton<CDialogistAniManager>
{
private :
	CObjects_Ani *m_pDriver, *m_pDriverHand ;
	CObjects_Ani *m_pGuest, *m_pGuestMove ;
	CSprite *m_pFront, *m_pSeatB, *m_pSeatF, *m_pLamp ;
	CSprite *m_pLineU, *m_pLineD ;

	int m_nAniState ;
	float m_fAnimationTime ;
	bool m_bGuestMove ;

public :
	CDialogistAniManager() ;
	~CDialogistAniManager() ;

	void SetAnimation(Dialogist dialogist, char *state) ;
	void GuestGetOn(CObjects_Ani *pGuest) ;
	void GuestGetOff() ;

	bool AniSitDown() ;
	bool AniSitUp() ;
	void LineMove(float fPercent) ;

	void Update() ;

	void Render() ;
private :
	void Swing() ;
} ;

#define g_DialogistAniManager CDialogistAniManager::GetInstance()