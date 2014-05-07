#include "myLib.h"
#include "playbg.h"
#include "mainch.h"
#include "mainchr.h"
#include "bird.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, volatile unsigned short color)
{
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;	
	}
}

void drawHollowRect(int r, int c, int width, int height, u16 color)
{
	for(int i = 0; i < width; i++) {
		setPixel(r + i, c, color);	
		setPixel(r + i, c + height, color);
	}
	for(int j = 0; j < height; j++) {
		setPixel(r, c + j, color);
		setPixel(r + width, c + j, color);
	}
	// right most pixel 
	setPixel(r + width, c + height, color);
}
	

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void fillScreen(volatile unsigned short color)
{
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (240*160) | DMA_SOURCE_FIXED | DMA_ON;
}

void drawPicture(const unsigned short arr[])
{
	DMA[3].src = arr;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (240*160) | DMA_ON;
}

void eraseimage(int row, int col, int height, int width)
{
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &playbg[OFFSET(row+r, col, 240)];
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[3].cnt = width | DMA_ON;	
	}
}


void drawplayer(PLAYER player)
{
	if (player.direction > 0) 
	{
		drawplayer_right(player);
	}else{
		drawplayer_left(player);
	}
}

void drawplayer_left(PLAYER player)
{
	int r, c;
	u16 color;
	for(r=0; r<MAINCH_HEIGHT; r++)
	{
		for(c = 0; c < MAINCH_WIDTH; c++) 
		{
			color = mainch[OFFSET(r,c, MAINCH_WIDTH)];
			if (TRANSPARENT != color && BLACK != color) 
			{
				setPixel(player.row + r, player.col + c, color);
			}
		}
		
	}
}

void drawplayer_right(PLAYER player)
{
	int r, c;
	u16 color;
	for(r=0; r<MAINCHR_HEIGHT; r++)
	{
		for(c = 0; c < MAINCHR_WIDTH; c++) 
		{
			u16 curr = videoBuffer[OFFSET(player.row+r, player.col+c, 240)];
			color = mainchr[OFFSET(r,c, MAINCHR_WIDTH)];	
			if ((TRANSPARENT != color && BLACK != color) || curr == BLACK) 
			{
				setPixel(player.row + r, player.col + c, color);
			}
		}
	}

}

void eraseplayer(PLAYER player)
{
	
	int r;
	for(r=0; r<MAINCH_HEIGHT; r++)
	{
		DMA[3].src = &playbg[OFFSET(player.row + r, player.col, PLAYBG_WIDTH)];
		DMA[3].dst = &videoBuffer[OFFSET(player.row + r, player.col, 240)];
		DMA[3].cnt = MAINCH_WIDTH | DMA_ON;	
	}
}

void drawbird(BIRD b) {
	int r, c;
	u16 color;
	drawHollowRect(b.row, b.col + 3, BIRD_WIDTH/2 + 2, BIRD_HEIGHT/2 , RED);
	for(r=0; r<BIRD_HEIGHT; r++)
	{
		for(c = 0; c < BIRD_WIDTH; c++) 
		{
			u16 curr = videoBuffer[OFFSET(b.row+r, b.col+c, 240)];
			color = bird[OFFSET(r,c, BIRD_WIDTH)];	
			if ((TRANSPARENT != color && BLACK != color) || curr == BLACK) 
			{
				setPixel((b.row) + r, (b.col) + c, color);
			}

		}
	
	}
}

void erasebird(BIRD bird) {
	int r;

	for(r=0; r<BIRD_HEIGHT; r++)
	{

		DMA[3].src = &playbg[OFFSET(bird.row + r, bird.col, PLAYBG_WIDTH)];
		DMA[3].dst = &videoBuffer[OFFSET(bird.row + r, bird.col, 240)];
		DMA[3].cnt = BIRD_WIDTH | DMA_ON;
	}
}
