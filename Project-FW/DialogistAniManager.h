#pragma once

#include "Singleton.h"
#include "Dialogist.h"

class CObjects_Ani ;

class CDialogistAniManager : public Singleton<CDialogistAniManager>
{
private :
	CObjects_Ani *m_pDriver, *m_pGuest ;

public :
	CDialogistAniManager() ;
	~CDialogistAniManager() ;

	void SetAnimation(Dialogist dialogist, char *state) ;

	void Update() ;

	void Render() ;
} ;

#define g_DialogistAniManager CDialogistAniManager::GetInstance()