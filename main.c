#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NUMOBJS 7
#define SCREENMAXHEIGHT 149

#include "myLib.h"
#include "text.h"

//images
#include "bg.h"
#include "playbg.h"
#include "mainch.h"
#include "mainchr.h"
#include "bird.h"


enum {SPLASH, GAME, WIN, LOSE, LEVELUP};
// Prototypes
int splash();
int game(int, int, int);
void win();
void lose();
int levelup();

int main()
{
	int seed = 0;
	int state = SPLASH;
	int level = 1;
	int life = 3;
	while(1)
	{
		switch(state)
		{
		case SPLASH:
			seed = splash();
			state = GAME;
			break;
		case GAME:
			state = game(seed, level, life);
			break;
		case WIN:
			win();
			state = GAME;
			break;
		case LOSE:
			lose();
			state = GAME;
			break;
		case LEVELUP:
			level = levelup(level);
			state = GAME;
		default:
			// handle error
			break;
		} // switch
	} // while
}		
int splash()
{
	int seed = 0;

	//unsigned short *ptr = videoBuffer;
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	drawPicture(bg);
	drawBigStringAtM(100, "Press Enter to start", YELLOW);
	drawStringAtM(130, "By Hyun Jong Lee", WHITE); 
	drawStringAtM(140, "1984 NINTENDO", GREEN); 

	while(!KEY_DOWN_NOW(BUTTON_START))
	{
		seed++;
	}
	while(KEY_DOWN_NOW(BUTTON_START));
	return seed;
}		
void win()			
{
	unsigned short *ptr = videoBuffer;
	int i = 0;
	for(i=0; i<38400; i++)
	{
		*ptr++ = GREEN;
	}
	drawString(50, 5, "You win!!", YELLOW);
	drawString(70, 5, "Press Start (Enter)", YELLOW);
	while(!KEY_DOWN_NOW(BUTTON_START));
	while(KEY_DOWN_NOW(BUTTON_START));
}

void lose()
{
	unsigned short *ptr = videoBuffer;
	int i = 0;
	for(i=0; i<38400; i++)
	{
		*ptr++ = RED;
	}
	drawString(50, 5, "LOSER!", YELLOW);
	drawString(70, 5, "Press Start (Enter)", YELLOW);
	while(!KEY_DOWN_NOW(BUTTON_START));
	while(KEY_DOWN_NOW(BUTTON_START));
	
	
}

int levelup(int level)
{
	unsigned short *ptr = videoBuffer;
	int i = 0;
	for(i=0; i<38400; i++)
	{
		*ptr++ = WHITE;
	}
	drawString(50, 5, "Level UP!", BLACK);

	
	for (volatile int k = 0; k < 100000; k++){
		k = k;
	}
	return level + 1;
}

int game(int seed, int level, int life)
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	PLAYER player; 
	PLAYER oldplayer;
	int NUMBIRD = level;//rand()%2 + 1;
	BIRD birds[NUMBIRD];
	BIRD oldbirds[NUMBIRD];

	int score, start_row, start_col, i;
	

	start_row = rand()%110;
	start_col = rand()%220;
	player.row = start_row;
	player.col = start_col;
	player.direction = 1;
	player.speed = 3;
	oldplayer = player;
	drawPicture(playbg);
	score = 0;


	srand(seed);
	for(i = 0; i <NUMBIRD; i++) 
	{
		birds[i].row = rand()%110 + 20;
		birds[i].col = rand()%220;
		birds[i].rd = 1;
		birds[i].cd = 1;
		birds[i].speed = 2;
		birds[i].alive = true;
		oldbirds[i] = birds[i];
	}
	
	

	// Game Loop
	
	while(1)
	{
	
		if(KEY_DOWN_NOW(BUTTON_RIGHT)) 
		{
			player.col += player.speed;
			player.direction = 1;
			if (player.col < 0) {
				player.col = 0;
			}
			if (player.col > 220) {
				player.col = 220;
			}
		}

		if(KEY_DOWN_NOW(BUTTON_LEFT)) 
		{
			player.col -= player.speed;
			player.direction = -1;
			if (player.col < 0) {
				player.col = 0;
			}
			if (player.col > 220) {
				player.col = 220;
			}	
		}

		if(KEY_DOWN_NOW(BUTTON_UP)) 
		{
			player.row -= player.speed;
			if (player.row <=0) {
				player.row = 0;
			}
		}else{
			if ((player.row > 93 && player.row < 100)  && (((player.col >= 0 && player.col <= 70) || (player.col>= 150 && player.col <= 220)))) {
	
			}else if ((player.row > 50 && player.row < 58) && (player.col >=70 && player.col <=150)){
			
			}else if (player.row == 12 && ( (player.col >= 19 && player.col <=72) || (player.col >= 148 && player.col <= 200) ) ){

			}else{
				player.row += player.speed;
				if (player.row > 115) {
					player.row = start_row;
					player.col = start_col;
					player.direction = 1;
					eraselife();
					life--;
				}
			}
		}

		if (score == level) {
			return LEVELUP;
		}		

		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			return GAME;
		}
		
		if(life < 0) 
		{
			return LOSE;
		}



		for(i = 0; i <NUMBIRD; i++) 
		{
			srand(seed);
			
			if (birds[i].alive == true){
				if (player.row + MAINCH_HEIGHT  > birds[i].row && player.row + MAINCH_HEIGHT < birds[i].row + BIRD_HEIGHT/2 + 2 ) {
					if (player.col + MAINCH_WIDTH > birds[i].col && player.col + MAINCH_WIDTH < birds[i].col + BIRD_WIDTH/2 + 3) {
						drawRect(birds[i].row, birds[i].col + 3, BIRD_WIDTH/2 + 2, BIRD_HEIGHT/2 , RED);
						birds[i].alive = false;
						erasescore();
						++score;
					}
				} 
				birds[i].row += birds[i].rd;
				birds[i].col += birds[i].cd;
				srand(rand()); // randomization
				if (birds[i].row < 50 ) {
					birds[i].row = 50;
					birds[i].rd = birds[i].speed * 1;
				} else if (birds[i].row > 100) {
					birds[i].row = 100;
					birds[i].rd = birds[i].speed * -1;
				}

				if (birds[i].col < 0 ) {
					birds[i].col = 0;
					birds[i].cd = birds[i].speed * 1;
				} else if (birds[i].col > 220) {
					birds[i].col = 220;
					birds[i].cd = birds[i].speed * -1;
				}
			}
		}
		waitForVblank();
		eraseplayer(oldplayer);

		drawplayer(player);		
		for(i = 0; i <NUMBIRD; i++) 
		{
			if (oldbirds[i].alive == true) {
				erasebird(oldbirds[i]);
			}
			if(birds[i].alive == true){

				drawbird(birds[i]);
			}
				oldbirds[i] = birds[i];
		}
		
		oldplayer = player;
		drawStuff(score, life, level);
		
	}
}
	
	
