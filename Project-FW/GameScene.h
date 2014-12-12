#pragma once

#include "Scene.h"

class CSprite ;
class CObjects_Ani ;

class GameScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CObjects_Ani *m_pGuest ;

public :
	static Scene* scene() ;

	GameScene() ;
	virtual ~GameScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;