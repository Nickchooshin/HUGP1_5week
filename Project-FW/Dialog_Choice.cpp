#include "Dialog_Choice.h"
#include "Button.h"
#include "ButtonManager.h"

#include <Windows.h>

#include "D3dDevice.h"

CDialog_Choice::CDialog_Choice() : m_nNum(0),
								   m_pDialog(NULL)
{
	m_Dialogist = DRIVER ;
}
CDialog_Choice::~CDialog_Choice()
{
	if(m_pDialog!=NULL)
	{
		for(int i=0; i<m_nNum; i++)
			g_ButtonManager->DeleteButton(m_pDialog[i]) ;

		delete[] m_pDialog ;
	}
}

void CDialog_Choice::Init(int num, char **text)
{
	char filepath[100] ;

	m_nNum = num ;

	m_pDialog = new CButton*[m_nNum] ;

	for(int i=0; i<m_nNum; i++)
	{
		wsprintf(filepath, "Resource/Image/%s.png", text[i]) ;

		m_pDialog[i] = new CButton ;
		m_pDialog[i]->Init(filepath) ;
		m_pDialog[i]->SetActivate(false) ;

		g_ButtonManager->AddButton(m_pDialog[i]) ;
	}
}

void CDialog_Choice::SetAlpha(float fAlpha)
{
	int i ;
	float x = (g_D3dDevice->GetWinWidth() / 2.0f) + 100.0f ;
	float y = g_D3dDevice->GetWinHeight() - 500.0f ;
	float fAngle ;
	int nAlpha ;
	const float radius = 100.0f ;
	bool bActivate = (fAlpha==1.0f) ;

	for(i=0; i<m_nNum; i++)
	{
		fAngle = (225.0f + ((i * -45.0f) * fAlpha)) * 3.141592f / 180.0f ;
		m_pDialog[i]->SetPosition(x + (cos(fAngle) * radius), y + (sin(fAngle) * radius)) ;

		nAlpha = (int)(255.0f * fAlpha) ;
		m_pDialog[i]->SetAlpha(nAlpha) ;

		m_pDialog[i]->SetActivate(bActivate) ;
	}
}

const int CDialog_Choice::Choice() const
{
	int i ;

	for(i=0; i<m_nNum; i++)
	{
		if(m_pDialog[i]->BeClick())
			return i ;
	}

	return -1 ;
}

void CDialog_Choice::Render()
{
	for(int i=0; i<m_nNum; i++)
		m_pDialog[i]->Render() ;
}