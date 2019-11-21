#include <stdint.h>

#define DISPLAY_HEIGHT 				320
#define DISPLAY_WIDTH 				240

#define COLOR_RED 						0xF800
#define COLOR_BLUE 						0x001F
#define COLOR_GREEN 					0x07E0
#define COLOR_BLACK						0x0000
#define COLOR_WHITE						0xFFFF



extern uint16_t DISPLAY [76800];

void k_rect(uint16_t* display, int x, int y, int dx, int dy, uint16_t color);

void k_fill(uint16_t* display, uint16_t color);

void k_printchar(uint16_t* display, uint8_t* sim, int x, int y, uint16_t color);

void k_print_string(uint16_t* display, char* str, int x, int y, int space, uint16_t color);

void k_draw(uint16_t* display, int x, int y,  uint16_t color);

void k_draw_line(uint16_t* display, int x1, int y1, int x2, int y2,  uint16_t color);

void k_print_string_invers(uint16_t* display, char* str, int x, int y, int length, uint16_t color);
/*

	А	128
	Б	129		
	В	130 
	Г	131
	Д	132
	Е	133
	Ж	134
	З	135
	И	136
	Й	137
	К	138
	Л	139
	М	140
	Н	141
	О	142
	П	143
	Р	144
	С	145
	Т	146
	У	147
	Ф	148
	Ч	149
	Ц	150
	Ч	151
	Ш	152
	Щ	153
	Ъ	154
	Ы	155
	Ь	156
	Э	157
	Ю	148
	Я	159
	а	160
	б	161
	в	162
	г	163
	д	164
	е	165
	ж	166
	з	167
	и	168
	й	169
	к	170
	л	171
	м	172
	н	173
	о	174
	п	175
	р	176
	с	177
	т	178
	у	179
	ф	180
	х	181
	ц	182
	ч	183
	ш	184
	щ	185
	ъ	186
	ы	187
	ь	188
	э	189	
	ю	190
	я	191

*/
