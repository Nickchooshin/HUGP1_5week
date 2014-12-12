#include "DialogistAniManager.h"
#include "Objects_Ani.h"

CDialogistAniManager::CDialogistAniManager() : m_pDriver(NULL), m_pGuest(NULL)
{
	m_pDriver = new CObjects_Ani ;
	m_pDriver->Init("Resource/Data/Driver.dat") ;
	m_pDriver->SetPosition(420.0f, 500.0f) ;
}
CDialogistAniManager::~CDialogistAniManager()
{
	if(m_pDriver!=NULL)
		delete m_pDriver ;
	if(m_pGuest!=NULL)
		delete m_pGuest ;
}

void CDialogistAniManager::SetAnimation(Dialogist dialogist, char *state)
{
	CObjects_Ani *pObject ;

	if(dialogist==DRIVER)
		pObject = m_pDriver ;
	else
		pObject = m_pGuest ;

	if(pObject!=NULL)
		pObject->SetAnimation(state) ;
}

void CDialogistAniManager::Update()
{
	if(m_pGuest!=NULL)
		m_pGuest->Update() ;

	m_pDriver->Update() ;
}

void CDialogistAniManager::Render()
{
	if(m_pGuest!=NULL)
		m_pGuest->Render() ;

	m_pDriver->Render() ;
}