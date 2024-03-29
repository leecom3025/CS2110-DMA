typedef unsigned int u32;
typedef unsigned short u16;
typedef int bool;

enum {RIGHT, LEFT};
enum { false, true };


#define REG_DISPCTL *(unsigned short *)0x4000000

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

#define MODE3 3
#define BG2_ENABLE (1<<10)

extern unsigned short *videoBuffer;

#define OFFSET(r, c, numcols) ((r)*(numcols) + (c))

#define COLOR(r,g,b) ((b)<<10 | (g)<<5 | (r))
#define RED COLOR(31,0,0)
#define BLUE COLOR(0,0,31)
#define GREEN COLOR(0,31,0)

#define CYAN COLOR(0, 31, 31)
#define MAGENTA COLOR(31, 0, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0
#define WHITE COLOR(31,31,31)
#define TRANSPARENT 0x3ff
// *** Input =========================================================

// Buttons

#define BUTTON_A	(1<<0)	//Z	
#define BUTTON_B	(1<<1)	//X
#define BUTTON_SELECT	(1<<2)	//Backspace
#define BUTTON_START	(1<<3)	//Enter
#define BUTTON_RIGHT	(1<<4)	//S
#define BUTTON_LEFT	(1<<5)	//A
#define BUTTON_UP	(1<<6)	//Up arrow
#define BUTTON_DOWN	(1<<7)
#define BUTTON_R	(1<<8)
#define BUTTON_L	(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130

typedef struct
{
	volatile int row;
	volatile int col;
	int direction; // left = - , right = +
	int speed;
} PLAYER;

typedef struct
{
	int row;
	int col;
	int speed;
	int rd;
	int cd;
	bool alive;

} BIRD;

typedef struct
{
	int row;
	int col;
	int rd;
	int cd;
	int size;
	unsigned short color;
} MOVOBJ;

/* DMA */

typedef struct
{								// ***********************************************************
	 const volatile void *src;	// We mark this as const which means we can assign it const
	 volatile void *dst;		// things without the compiler yelling but we can also pass it
	 volatile u32 cnt;		// things that are not const!
								// ***********************************************************
} DMAREC;

#define DMA ((volatile DMAREC *)0x040000B0)

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define START_ON_FIFO_EMPTY 0x30000000



// Prototypes

void setPixel(int row, int col, unsigned short color);
void drawRect(int row, int col, int height, int width, unsigned short color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void waitForVblank();
void fillScreen(unsigned short color);
void drawPicture(const unsigned short arr[]);
void drawRect(int row, int col, int height, int width, volatile unsigned short color);
void eraseimage(int row, int col, int height, int width);
void drawplayer(PLAYER);
void drawplayer_left(PLAYER player);
void drawplayer_right(PLAYER player);
void eraseplayer(PLAYER);
void drawbird(BIRD b);
void erasebird(BIRD bird);
