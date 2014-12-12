#pragma once

#include "ScriptCommand.h"
#include "Dialogist.h"

class CScriptCommand_Ani : public CScriptCommand
{
private :
	char *m_strState ;
	Dialogist m_Dialogist ;

public :
	CScriptCommand_Ani(Dialogist dialogist, char *state) ;
	~CScriptCommand_Ani() ;

	void Update() ;
} ;