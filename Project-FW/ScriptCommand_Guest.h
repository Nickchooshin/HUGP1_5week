#pragma once

#include "ScriptCommand.h"

class CObjects_Ani ;

class CScriptCommand_Guest : public CScriptCommand
{
private :
	char *m_strGuest ;
	bool m_bGetOn ;
	bool m_bGuestInit ;

public :
	CScriptCommand_Guest(char *guest) ;
	CScriptCommand_Guest() ;
	~CScriptCommand_Guest() ;

	void Update() ;
} ;