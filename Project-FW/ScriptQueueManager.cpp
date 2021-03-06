#include "ScriptQueueManager.h"
#include <string.h>
#include <stdlib.h>

#include "LoadManager.h"
#include "ScriptCommand.h"
#include "ScriptCommand_Wait.h"
#include "ScriptCommand_Say.h"
#include "ScriptCommand_Choice.h"
#include "ScriptCommand_Load.h"
#include "ScriptCommand_Ani.h"
#include "ScriptCommand_Sound.h"
#include "ScriptCommand_Guest.h"

CScriptQueueManager::CScriptQueueManager() : m_pNowCommand(NULL),
											 m_bQueueEnd(true)
{
}
CScriptQueueManager::~CScriptQueueManager()
{
	ClearQueue() ;

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
		int len = strlen(command) ;

		if(len==4 && strcmp(command, "WAIT")==0)
		{
			float sec ;

			g_LoadManager->GetValue(sec) ;

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

			CScriptCommand *pCommand = new CScriptCommand_Say(dialogist, text) ;
			m_CommandQueue.push(pCommand) ;
		}
		else if(len==6 && strcmp(command, "CHOICE")==0)
		{
			int num ;
			std::string *pChoice, *pScript ;

			g_LoadManager->GetValue(num) ;
			pChoice = new std::string[num] ;
			pScript = new std::string[num] ;

			for(int i=0; i<num; i++)
			{
				g_LoadManager->GetString(temp) ;
				pChoice[i] = temp ;
			}

			for(int i=0; i<num; i++)
			{
				g_LoadManager->GetString(temp) ;
				pScript[i] = temp ;
			}

			CScriptCommand *pCommand = new CScriptCommand_Choice(num, pChoice, pScript) ;
			m_CommandQueue.push(pCommand) ;

			delete[] pChoice ;
			delete[] pScript ;
		}
		else if(len==4 && strcmp(command, "LOAD")==0)
		{
			g_LoadManager->GetString(temp) ;

			CScriptCommand *pCommand = new CScriptCommand_Load(temp) ;
			m_CommandQueue.push(pCommand) ;
		}
		else if(len==3 && strcmp(command, "ANI")==0)
		{
			Dialogist dialogist ;

			g_LoadManager->GetString(temp) ;
			len = strlen(temp) ;
			if(len==5 && strcmp(temp, "guest")==0)
				dialogist = GUEST ;
			else if(len==6 && strcmp(temp, "driver")==0)
				dialogist = DRIVER ;

			g_LoadManager->GetString(temp) ;

			CScriptCommand *pCommand = new CScriptCommand_Ani(dialogist, temp) ;
			m_CommandQueue.push(pCommand) ;
		}
		else if(len==5 && strcmp(command, "SOUND")==0)
		{
			int channel ;
			char sound[100] ;
			bool stream, loop ;

			g_LoadManager->GetCommand(command) ;
			g_LoadManager->GetValue(channel) ;

			CScriptCommand *pCommand ;

			if(strcmp(command, "PLAY")==0)
			{
				g_LoadManager->GetString(sound) ;

				g_LoadManager->GetString(temp) ;
				len = strlen(temp) ;
				if(len==6 && strcmp(temp, "STREAM")==0)
					stream = true ;
				else if(len==10 && strcmp(temp, "NON_STREAM")==0)
					stream = false ;

				g_LoadManager->GetString(temp) ;
				len = strlen(temp) ;
				if(len==4 && strcmp(temp, "LOOP")==0)
					loop = true ;
				else if(len==8 && strcmp(temp, "NON_LOOP")==0)
					loop = false ;

				pCommand = new CScriptCommand_Sound(channel, sound, stream, loop) ;
			}
			else if(strcmp(command, "STOP")==0)
			{
				pCommand = new CScriptCommand_Sound(channel) ;
			}

			m_CommandQueue.push(pCommand) ;
		}
		else if(len==5 && strcmp(command, "RADIO")==0)
		{
		}
		else if(len==5 && strcmp(command, "GUEST")==0)
		{
			g_LoadManager->GetCommand(command) ;
			
			CScriptCommand *pCommand ;

			if(strcmp(command, "GET_ON")==0)
			{
				g_LoadManager->GetString(temp) ;
				pCommand = new CScriptCommand_Guest(temp) ;
			}
			else if(strcmp(command, "GET_OFF")==0)
			{
				pCommand = new CScriptCommand_Guest() ;
			}

			m_CommandQueue.push(pCommand) ;
		}
	}

	g_LoadManager->CloseDat() ;

	if(m_pNowCommand==NULL)
	{
		m_pNowCommand = m_CommandQueue.front() ;
		m_CommandQueue.pop() ;
	}

	m_bQueueEnd = false ;

	return true ;
}

const bool CScriptQueueManager::BeQueueEnd() const
{
	return m_bQueueEnd ;
}

void CScriptQueueManager::ClearQueue()
{
	CScriptCommand *temp ;

	while(!m_CommandQueue.empty())
	{
		temp = m_CommandQueue.front() ;
		m_CommandQueue.pop() ;
		delete temp ;
	}
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