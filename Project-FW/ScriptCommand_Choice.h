#pragma once

#include "ScriptCommand.h"
#include <string>

class CButton ;
class CDialog_Choice ;

class CScriptCommand_Choice : public CScriptCommand
{
private :
	enum State { FADEIN=0, CHOICE, FADEOUT, END } ;
	const int m_nNum ;
	char **m_strChoice, **m_strScript ;
	State m_State ;

	CDialog_Choice *m_pDialog_Choice ;
	int m_nChoice ;
	float m_nChoiceTime ;

public :
	CScriptCommand_Choice(int num, std::string *choice, std::string *script) ;
	~CScriptCommand_Choice() ;

	void Update() ;
} ;