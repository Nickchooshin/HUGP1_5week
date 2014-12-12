#pragma once

#include "Dialogist.h"
#include <string>

class CButton ;

class CDialog_Choice : public IDialog
{
private :
	int m_nNum ;
	CButton **m_pDialog ;

public :
	CDialog_Choice() ;
	~CDialog_Choice() ;

	void Init(int num, char **text) ;

	void SetAlpha(float fAlpha) ;

	void Render() ;
} ;