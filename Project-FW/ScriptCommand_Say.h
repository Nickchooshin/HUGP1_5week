#pragma once

#include "ScriptCommand.h"
#include "Dialogist.h"

class CScriptCommand_Say : public CScriptCommand
{
private :
	enum State { DIALOG_FADEOUT=0, DIALOG_FADEIN } ;
	char *m_strText ;
	Dialogist m_Dialogist ;
	State m_State ;

public :
	CScriptCommand_Say(Dialogist dialogist, char *text) ;
	~CScriptCommand_Say() ;

	void Update() ;
} ;