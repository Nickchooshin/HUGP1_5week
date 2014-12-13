#pragma once

#include "Singleton.h"
#include "Dialogist.h"

class IDialog ;

class CDialogManager : public Singleton<CDialogManager>
{
private :
	IDialog *m_pGuest, *m_pDriver ;
	float m_fTime ;

public :
	CDialogManager() ;
	~CDialogManager() ;

	bool DialogFadeOut(Dialogist dialogist) ;
	bool DialogFadeIn(Dialogist dialogist) ;

	void ChangeDialog(IDialog *dialog) ;
	void DeleteDialog(Dialogist dialogist) ;

	void Render() ;
} ;

#define g_DialogManager CDialogManager::GetInstance()