#include "ScriptCommand_Ani.h"
#include "DialogistAniManager.h"

#include "D3dDevice.h"

CScriptCommand_Ani::CScriptCommand_Ani(Dialogist dialogist, char *state) : m_Dialogist(dialogist),
																		   m_strState(NULL)
{
	m_strState = new char[strlen(state) + 1] ;
	strcpy(m_strState, state) ;
}
CScriptCommand_Ani::~CScriptCommand_Ani()
{
	if(m_strState!=NULL)
		delete[] m_strState ;
}

void CScriptCommand_Ani::Update()
{
	g_DialogistAniManager->SetAnimation(m_Dialogist, m_strState) ;

	m_bLife = false ;
}