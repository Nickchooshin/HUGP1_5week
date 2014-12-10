#pragma once

#include "ScriptCommand.h"
#include "Dialogist.h"

class CScriptCommand_Load : public CScriptCommand
{
private :
	char *m_cScript ;

public :
	CScriptCommand_Load(char *script) ;
	~CScriptCommand_Load() ;

	void Update() ;
} ;