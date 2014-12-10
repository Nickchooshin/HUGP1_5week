#pragma once

class CScriptCommand
{
protected :
	bool m_bLife ;

public :
	CScriptCommand() ;
	virtual ~CScriptCommand() ;

	virtual void Update() = 0 ;

	const bool BeLife() const ;
} ;