#pragma once

#include "Dialogist.h"

class CSprite ;

class CDialog
{
private :
	CSprite *m_pDialog ;
	Dialogist m_Dialogist ;

public :
	CDialog() ;
	~CDialog() ;

	void Init(char *filename, Dialogist dialogist) ;

	void SetAlpha(int nAlpha) ;

	const Dialogist GetDialogist() const ;

	void Render() ;
} ;