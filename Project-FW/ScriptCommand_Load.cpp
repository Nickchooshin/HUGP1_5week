#include "ScriptCommand_Load.h"
#include <string.h>
#include <windows.h>

#include "ScriptQueueManager.h"

CScriptCommand_Load::CScriptCommand_Load(char *script) : m_strScript(NULL)
{
	m_strScript = new char[strlen(script)+1] ;
	strcpy(m_strScript, script) ;
}
CScriptCommand_Load::~CScriptCommand_Load()
{
	if(m_strScript!=NULL)
		delete m_strScript ;
}

void CScriptCommand_Load::Update()
{
	char scriptpath[100] ;

	wsprintf(scriptpath, "Resource/Data/%s.dat", m_strScript) ;

	g_ScriptQueueManager->ClearQueue() ;
	g_ScriptQueueManager->LoadScript(scriptpath) ;

	m_bLife = false ;
}