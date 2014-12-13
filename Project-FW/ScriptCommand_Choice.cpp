#include "ScriptCommand_Choice.h"
#include "Button.h"
#include "ButtonManager.h"

#include "Dialog_Choice.h"
#include "DialogManager.h"
#include "ScriptQueueManager.h"

#include "D3dDevice.h"

CScriptCommand_Choice::CScriptCommand_Choice(int num, std::string *choice, std::string *script) : m_nNum(num),
																								  m_strChoice(NULL), m_strScript(NULL),
																								  m_State(FADEOUT),
																								  m_pDialog_Choice(NULL),
																								  m_nChoice(-1),
																								  m_nChoiceTime(0.0f)
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
	if(m_State==FADEOUT)
	{
		if( g_DialogManager->DialogFadeOut(DRIVER) )
		{
			m_pDialog_Choice = new CDialog_Choice ;
			m_pDialog_Choice->Init(m_nNum, m_strChoice) ;
			m_pDialog_Choice->SetAlpha(0) ;

			g_DialogManager->ChangeDialog(m_pDialog_Choice) ;

			m_State = FADEIN ;
		}
	}
	else if(m_State==FADEIN)
	{
		if( g_DialogManager->DialogFadeIn(DRIVER) )
			m_State = CHOICE ;
	}
	else if(m_State==CHOICE)
	{
		m_nChoice = m_pDialog_Choice->Choice() ;

		if(m_nChoice!=-1 || m_nChoiceTime>=2.0f)
			m_State = END ;

		m_nChoiceTime += g_D3dDevice->GetTime() ;
	}
	else
	{
		if( g_DialogManager->DialogFadeOut(DRIVER) )
		{
			if(m_nChoice!=-1)
			{
				char scriptpath[100] ;
			
				wsprintf(scriptpath, "Resource/Data/Script/%s.dat", m_strScript[m_nChoice]) ;

				//g_ScriptQueueManager->ClearQueue() ;
				g_ScriptQueueManager->LoadScript(scriptpath) ;
			}

			m_bLife = false ;
		}
	}
}