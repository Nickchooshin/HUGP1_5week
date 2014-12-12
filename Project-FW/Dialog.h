#pragma once

#include "Dialogist.h"

class CSprite ;

class CDialog : public IDialog
{
private :
	CSprite *m_pDialog ;

public :
	CDialog() ;
	~CDialog() ;

	void Init(char *text, Dialogist dialogist) ;

	void SetAlpha(float fAlpha) ;

	void Render() ;
} ;