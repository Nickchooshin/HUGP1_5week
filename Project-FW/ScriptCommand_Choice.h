#pragma once

#include "ScriptCommand.h"
#include <string>

class CButton ;

class CScriptCommand_Choice : public CScriptCommand
{
private :
	enum State { CHOICE_FADEIN=0, CHOICE, CHOICE_FADEOUT } ;
	const int m_nNum ;
	char **m_strChoice, **m_strScript ;
	State m_State ;

public :
	CScriptCommand_Choice(int num, std::string *choice, std::string *script) ;
	~CScriptCommand_Choice() ;

	void Update() ;
} ;