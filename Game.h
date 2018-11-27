#ifndef GAME_H
#define GAME_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360


class Game
{
public:
	Game();
	virtual ~Game();
	bool init();
	bool loop();

	void readKeyboard(unsigned char key, int x, int y, bool press);
	void reshape(int width,int height);
	void render();
	
private:
	unsigned char keys[256];
};

#endif