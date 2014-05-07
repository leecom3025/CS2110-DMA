#include <stdlib.h>
#include <string.h>

#include "myLib.h"
#include "text.h"
#include "playbg.h"

void drawChar(int row, int col, char ch, unsigned short color)
{
	int r,c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6) + ch*48])
			{
				setPixel(row+r, col+c, color);
			} 
		}
	}
}

void drawString(int row, int col,  char *str, unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col += 6;
	}
}
	
void drawBigChar(int row, int col, char ch, unsigned short color)
{
	int r,c;
	for(r=0; r<16; r++)
	{
		for(c=0; c<12; c++)
		{
			if(fontdata_6x8[OFFSET(r/2, c/2, 6) + ch*48])
			{ 
				setPixel(row + r, col + c, color);
			} 
		}
	}
}		
	
void drawBigString(int row, int col,  char *str, unsigned short color)
{
	while(*str)
	{
		drawBigChar(row, col, *str++, color);
		col += 12;
	}
}

void drawStringAtM(int row, char *str, unsigned short color) 
{
	int length = strlen(str);	
	length = length * 6;
	length = ((240 - length) / 2);
	drawString(row, length, str, color);
}

void drawBigStringAtM(int row, char *str, unsigned short color) 
{
	int length = strlen(str);	
	length = length * 12;
	length = ((240 - length) / 2);
	drawBigString(row, length, str, color);
}	

void drawCleanString(int row, int col, char *str, unsigned short color) 
{	
	
	eraseimage(row, col, 8, (strlen(str)*6)  + 6);
	drawString(row, col, str, color);
}

void drawStuff(int score, int life, int level)
{
	char *s_s, *s_level, *s_l;
	s_s = "Score: ";
	s_l = "Life: ";
	s_level = "Level: ";	

	drawString(135+0, 0, s_s, WHITE);
	drawString(135+8, 0, s_l, WHITE);
	drawString(135+16, 0, s_level, WHITE);
	drawChar(135+0, strlen(s_s)* 6, score+ 48, WHITE);
	drawChar(135+8, strlen(s_l)* 6, life+ 48, WHITE);
	drawChar(135+16, strlen(s_level)* 6, level+ 48, WHITE);
}

void eraselife(){
	char *s_l = "Life:    ";
	for (int i = 138; i < 151; i++) {
		for(int j = 0; j < (strlen(s_l)*6); j++) {
			setPixel(i, j, playbg[OFFSET(i,j,240)]);				

		}
	}

}

void erasescore(){
	char *s_s = "Score:    ";
	for (int i = 135; i < 168; i++) {
		for(int j = 0; j < (strlen(s_s)*6); j++) {
			setPixel(i, j, playbg[OFFSET(i,j,240)]);				

		}
	}
}
	
