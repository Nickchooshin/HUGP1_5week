#pragma once

class CScriptCommand
{
protected :
	bool m_bLife ;

public :
	CScriptCommand() ;
	~CScriptCommand() ;

	virtual void Update() = 0 ;

	const bool BeLife() const ;
} ;