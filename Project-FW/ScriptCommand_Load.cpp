#include "ScriptCommand_Load.h"
#include <string.h>
#include <windows.h>

#include "ScriptQueueManager.h"

CScriptCommand_Load::CScriptCommand_Load(char *script) : m_cScript(NULL)
{
	m_cScript = new char[strlen(script)+1] ;
	strcpy(m_cScript, script) ;
}
CScriptCommand_Load::~CScriptCommand_Load()
{
	if(m_cScript!=NULL)
		delete m_cScript ;
}

void CScriptCommand_Load::Update()
{
	char scriptpath[100] ;

	wsprintf(scriptpath, "Resource/Data/%s.dat", m_cScript) ;

	g_ScriptQueueManager->ClearQueue() ;
	g_ScriptQueueManager->LoadScript(scriptpath) ;

	m_bLife = false ;
}