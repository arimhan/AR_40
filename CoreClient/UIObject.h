#pragma once
#include "Object2D.h"

class AUIObject : public AObject2D
{
public:
	bool	Frame() override;
	bool	Render() override;
};
class AImageIObject : public AUIObject
{
public:
	float	m_fAlpha = 0.0f;
	bool	m_bFadeIn = false;
	bool	m_bFadeOut = false;
public:
	bool	Init() override;
	bool	Frame() override;
	bool	Render() override;
	void	FadeIn();
	void	FadeOut();
};
class AButtonObject : public AUIObject
{
public:
	bool Frame() override;
	bool Render() override;
};

