#include "player.h"
#include "ghost.h"

class Arrow
{
public:
	Arrow();
	~Arrow();
	void DrawArrow();
	void FireArrow(player &Player);
	void UpdateArrow(int WIDTH);
	void CollideArrow(ghost ghosts[], int cSize);
	int getHit() { return hit; };
private:
	int x;
	int y;
	bool live;
	int speed;
	int hit = 0;
	ALLEGRO_BITMAP *image;
};

