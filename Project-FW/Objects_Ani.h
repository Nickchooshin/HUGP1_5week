#pragma once

#include "Objects.h"
#include <string>
#include <map>

typedef struct _SIZE
{
	int x ;
	int y ;

	_SIZE() : x(0),
			  y(0)
	{}
	_SIZE(int X, int Y) : x(X),
						  y(Y)
	{}

	const _SIZE operator+(_SIZE size)
	{
		_SIZE temp ;
		temp.x = x + size.x ;
		temp.y = y + size.y ;

		return temp ;
	}
	const _SIZE& operator=(_SIZE size)
	{
		x = size.x ;
		y = size.y ;

		return *this ;
	}
	const _SIZE& operator+=(_SIZE size)
	{
		*this = *this + size ;

		return *this ;
	}
	//
	const bool operator<(_SIZE size) const
	{
		return (this->x + this->y) < (size.x + size.y) ;
	}
} Size, Position ;

class CObjects_Ani : public CObjects
{
private :
	Size m_ImgSize ;
	int m_nNowFrame ;
	std::map<std::string, int> m_nStateFrame ;
	std::map<std::string, Position> m_StateIndex ;

	float m_fAnimationTime ;
	std::string m_State, m_prevState ;
	bool m_bAnimationEnd ;

public :
	CObjects_Ani() ;
	~CObjects_Ani() ;

	void Init() ;
	void Init(char *filepath) ;

	void SetAnimation(char *state) ;

	const bool AnimationEnd() const ;

	void Update() ;
private :
	void Animation() ;
} ;