

void drawChar(int row, int col,  char ch, unsigned short color);
void drawString(int row, int col,  char *str, unsigned short color);
void drawBigChar(int row, int col, char ch, unsigned short color);
void drawBigString(int row, int col,  char *str, unsigned short color);
void drawStringAtM(int row, char *str, unsigned short color);
void drawBigStringAtM(int row, char *str, unsigned short color);
void drawCleanString(int row, int col, char *str, unsigned short color);
void drawStuff(int score, int life, int level);
void eraselife();
void erasescore();

extern const unsigned char fontdata_6x8[12288];
