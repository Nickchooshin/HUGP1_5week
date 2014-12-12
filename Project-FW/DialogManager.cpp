#include "DialogManager.h"

#include "D3dDevice.h"

CDialogManager::CDialogManager() : m_pGuest(NULL), m_pDriver(NULL),
								   m_fTime(0.0f)
{
}
CDialogManager::~CDialogManager()
{
	if(m_pGuest!=NULL)
		delete m_pGuest ;
	if(m_pDriver!=NULL)
		delete m_pDriver ;
}

bool CDialogManager::DialogFadeOut(Dialogist dialogist)
{
	IDialog *pDialog ;
	float fAlpha = 1.0f - (m_fTime / 0.5f) ;

	if(dialogist==GUEST)
		pDialog = m_pGuest ;
	else if(dialogist==DRIVER)
		pDialog = m_pDriver ;

	//
	if(pDialog==NULL)
		return true ;
	//

	if(fAlpha<=0.0f)
	{
		pDialog->SetAlpha(0.0f) ;
		m_fTime = 0.0f ;
		return true ;
	}
	else
		pDialog->SetAlpha(fAlpha) ;

	m_fTime += g_D3dDevice->GetTime() ;

	return false ;
}

bool CDialogManager::DialogFadeIn(Dialogist dialogist)
{
	IDialog *pDialog ;
	float fAlpha = (m_fTime / 0.5f) ;

	if(dialogist==GUEST)
		pDialog = m_pGuest ;
	else if(dialogist==DRIVER)
		pDialog = m_pDriver ;

	if(fAlpha>=1.0f)
	{
		pDialog->SetAlpha(1.0f) ;
		m_fTime = 0.0f ;
		return true ;
	}
	else
		pDialog->SetAlpha(fAlpha) ;

	m_fTime += g_D3dDevice->GetTime() ;

	return false ;
}

void CDialogManager::ChangeDialog(IDialog *dialog)
{
	IDialog **pDialog ;
	Dialogist dialogist = dialog->GetDialogist() ;

	if(dialogist==GUEST)
		pDialog = &m_pGuest ;
	else if(dialogist==DRIVER)
		pDialog = &m_pDriver ;

	delete (*pDialog) ;
	(*pDialog) = dialog ;
}

void CDialogManager::Render()
{
	if(m_pGuest!=NULL)
		m_pGuest->Render() ;
	if(m_pDriver!=NULL)
		m_pDriver->Render() ;
}