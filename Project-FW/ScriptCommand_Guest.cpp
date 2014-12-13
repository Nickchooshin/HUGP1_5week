#include "ScriptCommand_Guest.h"
#include "Objects_Ani.h"
#include "DialogistAniManager.h"

#include "D3dDevice.h"

CScriptCommand_Guest::CScriptCommand_Guest(char *guest) : m_strGuest(NULL),
														  m_bGetOn(true),
														  m_bGuestInit(false)
{
	m_strGuest = new char[strlen(guest) + 1] ;
	strcpy(m_strGuest, guest) ;
}
CScriptCommand_Guest::CScriptCommand_Guest() : m_strGuest(NULL),
											   m_bGetOn(false),
											   m_bGuestInit(false)
{
}
CScriptCommand_Guest::~CScriptCommand_Guest()
{
	if(m_strGuest!=NULL)
		delete[] m_strGuest ;
}

void CScriptCommand_Guest::Update()
{
	if(m_bGetOn)
	{
		if(!m_bGuestInit)
		{
			float WinHeight = g_D3dDevice->GetWinHeight() ;
			char filepath[100] ;

			wsprintf(filepath, "Resource/Data/NPC/%s.dat", m_strGuest) ;

			CObjects_Ani *pGuest = new CObjects_Ani ;
			pGuest->Init(filepath) ;
			pGuest->SetPosition(288.0f, WinHeight - 380.0f) ;

			g_DialogistAniManager->GuestGetOn(pGuest) ;

			m_bGuestInit = true ;
		}

		if( !g_DialogistAniManager->SitDown() )
			return ;

		m_bLife = false ;
	}
	else
	{
		if( !g_DialogistAniManager->SitUp() )
			return ;

		g_DialogistAniManager->GuestGetOff() ;
		m_bLife = false ;
	}
}