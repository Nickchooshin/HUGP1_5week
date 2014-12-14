#include "Dialog.h"
#include "Sprite.h"

#include "D3dDevice.h"

CDialog::CDialog() : m_pDialog(NULL)
{
}
CDialog::~CDialog()
{
	if(m_pDialog!=NULL)
		delete m_pDialog ;
}

void CDialog::Init(char *text, Dialogist dialogist)
{
	float WinWidthHalf = g_D3dDevice->GetWinWidth() / 2.0f ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	char filename[100] ;
	wsprintf(filename, "Resource/Image/%s.png", text) ;

	m_pDialog = new CSprite ;
	m_pDialog->Init(filename) ;

	m_Dialogist = dialogist ;

	switch(m_Dialogist)
	{
	case GUEST :
		m_pDialog->SetPosition(WinWidthHalf, WinHeight - 330.0f) ;
		break ;

	case DRIVER :
		m_pDialog->SetPosition(WinWidthHalf, WinHeight - 500.0f) ;
		break ;
	}
}

void CDialog::SetAlpha(float fAlpha)
{
	int nAlpha = (int)(255.0f * fAlpha) ;

	m_pDialog->SetAlpha(nAlpha) ;
}

void CDialog::Render()
{
	m_pDialog->Render() ;
}