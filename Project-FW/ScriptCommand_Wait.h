#pragma once

#include "ScriptCommand.h"

class CScriptCommand_Wait : public CScriptCommand
{
private :
	float m_fWaitTime ;

public :
	CScriptCommand_Wait(float fWaitTime) ;
	~CScriptCommand_Wait() ;

	void Update() ;
} ;