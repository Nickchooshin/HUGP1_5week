#include "ScriptCommand_Wait.h"

#include "D3dDevice.h"

CScriptCommand_Wait::CScriptCommand_Wait(float fWaitTime) : m_fWaitTime(fWaitTime)
{
}
CScriptCommand_Wait::~CScriptCommand_Wait()
{
}

void CScriptCommand_Wait::Update()
{
	m_fWaitTime -= g_D3dDevice->GetTime() ;

	if(m_fWaitTime<=0.0f)
		m_bLife = false ;
}