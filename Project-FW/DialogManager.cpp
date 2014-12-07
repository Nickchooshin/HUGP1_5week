#include "DialogManager.h"
#include "Dialog.h"

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
	CDialog *pDialog ;
	int nAlpha = 255 - (int)((m_fTime / 0.5f) * 255.0f) ;

	if(dialogist==GUEST)
		pDialog = m_pGuest ;
	else if(dialogist==DRIVER)
		pDialog = m_pDriver ;

	//
	if(pDialog==NULL)
		return true ;
	//

	if(nAlpha<0)
	{
		pDialog->SetAlpha(0) ;
		m_fTime = 0.0f ;
		return true ;
	}
	else
		pDialog->SetAlpha(nAlpha) ;

	m_fTime += g_D3dDevice->GetTime() ;

	return false ;
}

bool CDialogManager::DialogFadeIn(Dialogist dialogist)
{
	CDialog *pDialog ;
	int nAlpha = (int)((m_fTime / 0.5f) * 255.0f) ;

	if(dialogist==GUEST)
		pDialog = m_pGuest ;
	else if(dialogist==DRIVER)
		pDialog = m_pDriver ;

	if(nAlpha>255)
	{
		pDialog->SetAlpha(255) ;
		m_fTime = 0.0f ;
		return true ;
	}
	else
		pDialog->SetAlpha(nAlpha) ;

	m_fTime += g_D3dDevice->GetTime() ;

	return false ;
}

void CDialogManager::ChangeDialog(CDialog *dialog)
{
	CDialog **pDialog ;
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