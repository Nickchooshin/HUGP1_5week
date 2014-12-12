#include "ScriptCommand_Choice.h"
#include "Button.h"
#include "ButtonManager.h"

#include "Dialog_Choice.h"
#include "DialogManager.h"

#include "D3dDevice.h"

CScriptCommand_Choice::CScriptCommand_Choice(int num, std::string *choice, std::string *script) : m_nNum(num),
																								  m_strChoice(NULL), m_strScript(NULL),
																								  m_State(CHOICE_FADEOUT)
{
	char temp[100] ;

	m_strChoice = new char*[m_nNum] ;
	m_strScript = new char*[m_nNum] ;

	for(int i=0; i<m_nNum; i++)
	{
		m_strChoice[i] = new char[strlen(choice[i].c_str()) + 1] ;
		strcpy(m_strChoice[i], choice[i].c_str()) ;

		m_strScript[i] = new char[strlen(script[i].c_str()) + 1] ;
		strcpy(m_strScript[i], script[i].c_str()) ;
	}
}
CScriptCommand_Choice::~CScriptCommand_Choice()
{
	int i ;

	if(m_strChoice!=NULL)
	{
		for(i=0; i<m_nNum; i++)
			delete[] m_strChoice[i] ;

		delete[] m_strChoice ;
	}

	if(m_strScript!=NULL)
	{
		for(i=0; i<m_nNum; i++)
			delete[] m_strScript[i] ;

		delete[] m_strScript ;
	}
}

void CScriptCommand_Choice::Update()
{
	if(m_State==CHOICE_FADEOUT)
	{
		if( g_DialogManager->DialogFadeOut(DRIVER) )
		{
			CDialog_Choice *pDialog_Choice = new CDialog_Choice ;
			pDialog_Choice->Init(m_nNum, m_strChoice) ;
			pDialog_Choice->SetAlpha(0) ;

			g_DialogManager->ChangeDialog(pDialog_Choice) ;

			m_State = CHOICE_FADEIN ;
		}
	}
	else if(m_State==CHOICE_FADEIN)
	{
		if( g_DialogManager->DialogFadeIn(DRIVER) )
			m_State = CHOICE ;
	}
	else if(m_State==CHOICE)
	{
	}
	else
	{
	}
}