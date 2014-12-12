#include "ScriptCommand_Say.h"
#include <string.h>

#include "Dialog.h"
#include "DialogManager.h"

CScriptCommand_Say::CScriptCommand_Say(Dialogist dialogist, char *text) : m_Dialogist(dialogist),
																		  m_strText(NULL),
																		  m_State(DIALOG_FADEOUT)
{
	m_strText = new char[strlen(text)+1] ;
	strcpy(m_strText, text) ;
}
CScriptCommand_Say::~CScriptCommand_Say()
{
	if(m_strText!=NULL)
		delete []m_strText ;
}

void CScriptCommand_Say::Update()
{
	if(m_State==DIALOG_FADEOUT)
	{
		if( g_DialogManager->DialogFadeOut(m_Dialogist) )
		{
			CDialog *pDialog = new CDialog ;
			pDialog->Init(m_strText, m_Dialogist) ;
			pDialog->SetAlpha(0) ;

			g_DialogManager->ChangeDialog(pDialog) ;

			m_State = DIALOG_FADEIN ;
		}
	}
	else
	{
		if( g_DialogManager->DialogFadeIn(m_Dialogist) )
			m_bLife = false ;
	}
}