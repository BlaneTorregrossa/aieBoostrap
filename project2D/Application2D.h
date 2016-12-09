#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "Header.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();



protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;


	float m_cameraX, m_cameraY;
	float m_timer;
};



class Player 
{
private:

public:
	Player() {};
	
	Vector2 playerPosition = Vector2 (0.00f, 0.00f);


};

class Agent
{
public:


private:



};




