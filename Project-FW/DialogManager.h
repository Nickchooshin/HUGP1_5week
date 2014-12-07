#pragma once

#include "Singleton.h"
#include "Dialogist.h"

class CDialog ;

class CDialogManager : public Singleton<CDialogManager>
{
private :
	CDialog *m_pGuest, *m_pDriver ;
	float m_fTime ;

public :
	CDialogManager() ;
	~CDialogManager() ;

	bool DialogFadeOut(Dialogist dialogist) ;
	bool DialogFadeIn(Dialogist dialogist) ;

	void ChangeDialog(CDialog *dialog) ;

	void Render() ;
} ;

#define g_DialogManager CDialogManager::GetInstance()