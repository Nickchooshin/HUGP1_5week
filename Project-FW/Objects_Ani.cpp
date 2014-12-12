#include "Objects_Ani.h"
#include "Sprite.h"
#include "LoadManager.h"

#include "D3dDevice.h"

CObjects_Ani::CObjects_Ani() : m_ImgSize(0, 0),
							   m_nNowFrame(0),
							   m_fAnimationTime(0.0f),
							   m_State(""), m_prevState("")
{
}
CObjects_Ani::~CObjects_Ani()
{
}

void CObjects_Ani::Init()
{
	Init("Resource/Data/default.dat") ;
}

void CObjects_Ani::Init(char *filepath)
{
	g_LoadManager->OpenDat(filepath) ;

	char item[100] ;
	char image_path[100] ;
	char start_state[100] ;
	Position start_index ;

	while(g_LoadManager->GetItem(item))
	{
		int len = strlen(item) ;

		if(len==5 && strcmp(item, "IMAGE")==0)
		{
			g_LoadManager->GetString(image_path) ;
		}
		else if(len==4 && strcmp(item, "SIZE")==0)
		{
			g_LoadManager->GetValue(m_ImgSize.x) ;
			g_LoadManager->GetValue(m_ImgSize.y) ;
		}
		else if(len==11 && strcmp(item, "STATE_FRAME")==0)
		{
			char state[100] ;

			g_LoadManager->GetString(state) ;
			g_LoadManager->GetValue(m_nStateFrame[state]) ;
		}
		else if(len==11 && strcmp(item, "STATE_INDEX")==0)
		{
			char state[100] ;

			g_LoadManager->GetString(state) ;
			g_LoadManager->GetValue(m_StateIndex[state].x) ;
			g_LoadManager->GetValue(m_StateIndex[state].y) ;
		}
		else if(len==11 && strcmp(item, "START_STATE")==0)
		{
			g_LoadManager->GetString(start_state) ;
		}
	}

	g_LoadManager->CloseDat() ;
	
	SetAnimation(start_state) ;
	start_index = m_StateIndex[start_state] ;

	m_pSprite = new CSprite ;
	m_pSprite->Init((float)m_ImgSize.x, (float)m_ImgSize.y, image_path) ;
	m_pSprite->SetTextureUV((float)(start_index.x * m_ImgSize.x), (float)(start_index.y * m_ImgSize.y),
							(float)((start_index.x+1) * m_ImgSize.x), (float)((start_index.y+1) * m_ImgSize.y)) ;
}

void CObjects_Ani::SetAnimation(char *state)
{
	m_State = state ;
}

void CObjects_Ani::Update()
{
	Animation() ;
}

void CObjects_Ani::Animation()
{
	// Animatiuon Frame, Index
	int MaxFrame ;
	Position Index ;

	MaxFrame = m_nStateFrame[m_State] ;
	Index = m_StateIndex[m_State] ;

	// Animation
	m_fAnimationTime += g_D3dDevice->GetTime() ;

	if(m_fAnimationTime>=0.2f || (m_State!=m_prevState))
	{
		if(m_State!=m_prevState)
		{
			m_fAnimationTime = 0.0f ;
			m_nNowFrame = 0 ;
		}

		int Frame = (int)(m_fAnimationTime / 0.2f) ;
		m_fAnimationTime -= Frame * 0.2f ;
		m_nNowFrame += Frame ;
		m_nNowFrame %= MaxFrame ;

		float left, top, right, bottom ;
		left = (float)((Index.x + m_nNowFrame) * m_ImgSize.x) ;
		top = (float)((Index.y) * m_ImgSize.y) ;
		right = (float)((Index.x + m_nNowFrame+1) * m_ImgSize.x) ;
		bottom = (float)((Index.y+1) * m_ImgSize.y) ;

		m_pSprite->SetTextureUV(left, top, right, bottom) ;
	}

	m_prevState = m_State ;
}