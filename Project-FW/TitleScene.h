#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;
class CButton ;

class TitleScene : public Scene
{
private :
	CSprite *m_pTitle ;
	CButton *m_pStart, *m_pExit ;
	FMOD::Sound *m_pBGM ;

	int m_nState ;
	float m_fTime ;

public :
	static Scene* scene() ;

	TitleScene() ;
	virtual ~TitleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;