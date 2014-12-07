#include "Dialog.h"
#include "Sprite.h"

CDialog::CDialog() : m_pDialog(NULL),
					 m_Dialogist(NONE)
{
}
CDialog::~CDialog()
{
}

void CDialog::Init(char *filename, Dialogist dialogist)
{
	char temp[100] ;
	strcpy(temp, filename) ;
	wsprintf(filename, "Resource/Image/%s.png", temp) ;

	m_pDialog = new CSprite ;
	m_pDialog->Init(filename) ;

	m_Dialogist = dialogist ;

	switch(m_Dialogist)
	{
	case GUEST :
		m_pDialog->SetPosition(100.0f, 100.0f) ;
		break ;

	case DRIVER :
		m_pDialog->SetPosition(200.0f, 200.0f) ;
		break ;
	}
}

void CDialog::SetAlpha(int nAlpha)
{
	m_pDialog->SetAlpha(nAlpha) ;
}

const Dialogist CDialog::GetDialogist() const
{
	return m_Dialogist ;
}

void CDialog::Render()
{
	m_pDialog->Render() ;
}