#include "Screen.h"
#include "ScreenEffect.h"

Screen::Screen()
: myScreenIsFinished(false)
, myNextScreen(0)
, m_played_effect(0)
{	
}

Screen::~Screen()
{	
}


void Screen::playEffect(ScreenEffect* effect)
{
	m_played_effect = effect;
}

void Screen::stopEffect()
{
	playEffect(0);
}

void Screen::display(sf::RenderTarget* screen_surface)
{
	if(m_played_effect!=0)
	{
		m_played_effect->display(screen_surface);
	}
	else
	{
		render(screen_surface);
	}
}

void Screen::setNextScreen(Screen *nextScreen) 
{
	myScreenIsFinished = true;
	myNextScreen = nextScreen;
	myNextScreen->entering();
}


Screen * Screen::getNextScreen(void) 
{
	myScreenIsFinished = false;
	return myNextScreen;
}


bool Screen::isScreenFinished(void) 
{
	return myScreenIsFinished;
}
