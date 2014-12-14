#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class EndingScene : public Scene
{
private :
	CSprite *m_pCredit ;
	CSprite *m_pBlack, *m_pBlack2 ;
	FMOD::Sound *m_pBGM ;

	int m_nState ;
	float m_fTime ;

public :
	static Scene* scene() ;

	EndingScene() ;
	virtual ~EndingScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;