#include "ScriptCommand_Say.h"
#include <string.h>

#include "Dialog.h"
#include "DialogManager.h"

CScriptCommand_Say::CScriptCommand_Say(char *text, Dialogist dialogist) : m_cText(NULL),
																		  m_Dialogist(dialogist),
																		  m_State(DIALOG_FADEOUT)
{
	m_cText = new char[strlen(text)+1] ;
	strcpy(m_cText, text) ;
}
CScriptCommand_Say::~CScriptCommand_Say()
{
	if(m_cText!=NULL)
		delete []m_cText ;
}

void CScriptCommand_Say::Update()
{
	if(m_State==DIALOG_FADEOUT)
	{
		if( g_DialogManager->DialogFadeOut(m_Dialogist) )
		{
			CDialog *pDialog = new CDialog ;
			pDialog->Init(m_cText, m_Dialogist) ;
			pDialog->SetAlpha(0) ;

			g_DialogManager->ChangeDialog(pDialog) ;

			m_State = DIALOG_FADEIN ;
		}
	}
	else if(m_State==DIALOG_FADEIN)
	{
		if( g_DialogManager->DialogFadeIn(m_Dialogist) )
			m_bLife = false ;
	}
}