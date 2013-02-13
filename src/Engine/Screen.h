#ifndef _SCREEN_
#define _SCREEN_

namespace sf{
class RenderTarget;
class Event;
}

class ScreenEffect;

class Screen {

	friend class ScreenEffect;
private:

	bool myScreenIsFinished;
	Screen *myNextScreen;
	ScreenEffect* m_played_effect;

protected:

	Screen();
	void setNextScreen(Screen *nextScreen);
	void playEffect(ScreenEffect* effect);
	void stopEffect();
	virtual void render(sf::RenderTarget* screen_surface) = 0;

public:

	virtual ~Screen();

	bool isScreenFinished();
	Screen *getNextScreen();

	void display(sf::RenderTarget* screen_surface);

	virtual void entering() {}
	virtual void handleEvent(const sf::Event& Event) = 0;
    virtual void update(int elapsedTimeMS) =0;
};

#endif
