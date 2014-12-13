#include "DialogistAniManager.h"
#include "Objects_Ani.h"

CDialogistAniManager::CDialogistAniManager() : m_pDriver(NULL), m_pDriverHand(NULL),
											   m_pGuest(NULL)
{
	m_pDriver = new CObjects_Ani ;
	m_pDriver->Init("Resource/Data/Driver.dat") ;
	m_pDriver->SetPosition(460.0f, 480.0f) ;

	m_pDriverHand = new CObjects_Ani ;
	m_pDriverHand->Init("Resource/Data/Driver_hand.dat") ;
	m_pDriverHand->SetPosition(460.0f, 480.0f) ;
}
CDialogistAniManager::~CDialogistAniManager()
{
	if(m_pDriver!=NULL)
		delete m_pDriver ;
	if(m_pDriverHand!=NULL)
		delete m_pDriverHand ;
	if(m_pGuest!=NULL)
		delete m_pGuest ;
}

void CDialogistAniManager::SetAnimation(Dialogist dialogist, char *state)
{
	CObjects_Ani *pObject ;

	if(dialogist==DRIVER)
	{
		m_pDriver->SetAnimation(state) ;
		m_pDriverHand->SetAnimation(state) ;
	}
	else
	{
		if(m_pGuest!=NULL)
			m_pGuest->SetAnimation(state) ;
	}
}

void CDialogistAniManager::Update()
{
	if(m_pGuest!=NULL)
		m_pGuest->Update() ;

	m_pDriver->Update() ;
	m_pDriverHand->Update() ;
}

void CDialogistAniManager::Render()
{
	if(m_pGuest!=NULL)
		m_pGuest->Render() ;

	m_pDriver->Render() ;
	m_pDriverHand->Render() ;
}