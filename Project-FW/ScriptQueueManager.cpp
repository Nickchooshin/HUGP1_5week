#include "ScriptQueueManager.h"
#include <string.h>
#include <stdlib.h>

#include "LoadManager.h"
#include "ScriptCommand.h"
#include "ScriptCommand_Wait.h"
#include "ScriptCommand_Say.h"

CScriptQueueManager::CScriptQueueManager() : m_pNowCommand(NULL),
											 m_bQueueEnd(true)
{
}
CScriptQueueManager::~CScriptQueueManager()
{
	CScriptCommand *temp ;

	while(!m_CommandQueue.empty())
	{
		temp = m_CommandQueue.front() ;
		m_CommandQueue.pop() ;
		delete temp ;
	}

	if(m_pNowCommand!=NULL)
		delete m_pNowCommand ;
}

bool CScriptQueueManager::LoadScript(char *filename)
{
	if( !g_LoadManager->OpenDat(filename) )
		return false ;

	char command[100] ;
	char temp[100] ;

	while(g_LoadManager->GetCommand(command))
	{
		// wait, say, choice, :, jump, switch, load
		int len = strlen(command) ;

		if(len==4 && strcmp(command, "WAIT")==0)
		{
			float sec ;

			g_LoadManager->GetString(temp) ;
			sec = (float)strtod(temp, NULL) ;

			CScriptCommand *pCommand = new CScriptCommand_Wait(sec) ;
			m_CommandQueue.push(pCommand) ;
		}
		else if(len==3 && strcmp(command, "SAY")==0)
		{
			Dialogist dialogist ;
			char text[100] ;

			g_LoadManager->GetString(temp) ;
			len = strlen(temp) ;
			if(len==5 && strcmp(temp, "guest")==0)
				dialogist = GUEST ;
			else if(len==6 && strcmp(temp, "driver")==0)
				dialogist = DRIVER ;

			g_LoadManager->GetString(temp) ;
			strcpy(text, temp) ;

			CScriptCommand *pCommand = new CScriptCommand_Say(text, dialogist) ;
			m_CommandQueue.push(pCommand) ;
		}
		else if(len==6 && strcmp(command, "CHOICE")==0)
		{
		}
		else if(len==4 && strcmp(command, "LOAD")==0)
		{
		}
	}

	g_LoadManager->CloseDat() ;

	m_pNowCommand = m_CommandQueue.front() ;
	m_CommandQueue.pop() ;

	m_bQueueEnd = false ;

	return true ;
}

void CScriptQueueManager::Update()
{
	if(m_bQueueEnd)
		return ;

	m_pNowCommand->Update() ;

	if(!m_pNowCommand->BeLife())
	{
		if(m_pNowCommand!=NULL)
		{
			delete m_pNowCommand ;
			m_pNowCommand = NULL ;
		}

		m_bQueueEnd = m_CommandQueue.empty() ;
		if(!m_bQueueEnd)
		{
			m_pNowCommand = m_CommandQueue.front() ;
			m_CommandQueue.pop() ;
		}
	}
}