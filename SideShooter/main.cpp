#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "player.h"
#include "ghost.h"
#include "Arrow.h"
#include <iostream>

//prints when the player no longer has lives and displays score
void printEndScreen(ALLEGRO_FONT* font, int hits);

int main(void)
{

	const int WIDTH = 800;
	const int HEIGHT = 450;
	const int NUM_ArrowS = 5;
	const int NUM_ghostS = 10;
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	bool keys[5] = { false, false, false, false, false };


	//primitive variable
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	bool gameOver = false;


	//Allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_FONT* font = NULL;

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	al_install_keyboard();
	al_init_image_addon();
	al_init_native_dialog_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//object variables
	player myPlayer(HEIGHT);
	Arrow Arrows[NUM_ArrowS];
	ghost ghosts[NUM_ghostS];
	font = al_load_font("NiseJSRF.TTF", 32, 0);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	srand(time(NULL));

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (keys[UP])
				myPlayer.MoveUp();
			if (keys[DOWN])
				myPlayer.MoveDown(HEIGHT - 50);
			if (keys[LEFT])
				myPlayer.MoveLeft();
			if (keys[RIGHT])
				myPlayer.MoveRight();

			for (int i = 0; i < NUM_ArrowS; i++)
				Arrows[i].UpdateArrow(WIDTH);
			for (int i = 0; i < NUM_ghostS; i++)
				ghosts[i].Startghost(WIDTH, HEIGHT - 50);
			for (int i = 0; i < NUM_ghostS; i++)
				ghosts[i].Updateghost();
			for (int i = 0; i < NUM_ArrowS; i++)
				Arrows[i].CollideArrow(ghosts, NUM_ghostS);
			for (int i = 0; i < NUM_ghostS; i++)
				ghosts[i].Collideghost(myPlayer);
			if (myPlayer.getLives() <= 0) {//when player runs out of lives, start game over screen
				gameOver = true;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				for (int i = 0; i < NUM_ArrowS; i++)
					Arrows[i].FireArrow(myPlayer);
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			
			redraw = false;
			if (!gameOver) {
				
				myPlayer.DrawPlayer();
				for (int i = 0; i < NUM_ArrowS; i++)
					Arrows[i].DrawArrow();
				for (int i = 0; i < NUM_ghostS; i++)
					ghosts[i].Drawghost();
				//al_draw_text(font, al_map_rgb(255, 255, 255), 250, 300, 0, "TEST1");//test line
				//std::cout << "Life:" << myPlayer.getLives() << std::endl;//test line
				myPlayer.drawLives(font, Arrows[0].getHit());
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			else if (gameOver) {

				printEndScreen(font, Arrows[0].getHit());
				while (true) {
					al_wait_for_event(event_queue, &ev);
					if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {//any key to close
						done = true;
						break;
					}
				}
			}
		}

	}
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("Pause");
	return 0;
}

//prints when the player no longer has lives and displays score
void printEndScreen(ALLEGRO_FONT* font, int hits) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font, al_map_rgb(255, 0, 0), 250, 100, 0, "Game Over");
	al_draw_textf(font, al_map_rgb(255, 255, 255), 125, 200, 0, "Enemies Defeated: %d", hits);
	al_draw_text(font, al_map_rgb(255, 255, 255), 80, 300, 0, "Press any key to close");
	al_flip_display();
	std::cout << "TEST3" << std::endl;
}