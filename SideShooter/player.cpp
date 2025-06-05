#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"


player::~player()
{
	al_destroy_bitmap(image);
}
player::player(int HEIGHT)
{
	
	image = al_load_bitmap(kirbs[0]);
	x = 20;
	y = HEIGHT / 2;
	lives = 5;
	damageLvl = 0;
	speed = 7;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	score = 0;
}
void player::DrawPlayer()
{
	al_draw_bitmap(image, x,y, 0);
}
void player::MoveUp()
{
	y -= speed;
	if(y < 0)
		y = 0;
}
void player::MoveDown(int HEIGHT)
{
	y += speed;
	if(y > HEIGHT - boundy )
		y = HEIGHT - boundy;
}
void player::MoveLeft()
{
	x -= speed;
	if(x < 0)
		x = 0;
}
void player::MoveRight()
{
	x += speed;
	if(x > 300)
		x = 300;
}


const char* player::kirbs[5] = { "kirby0.png", "kirby1.png", "kirby2.png", "kirby3.png", "kirby4.png"
};
void player::removeLife() {
	lives--;
	damageLvl++;
	al_destroy_bitmap(image);
	image = al_load_bitmap(kirbs[damageLvl]);
	
}
