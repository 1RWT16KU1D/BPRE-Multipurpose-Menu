#ifndef GUARD_SHOW_MENU_H
#define GUARD_SHOW_MENU_H

#include "../global.h"
#include "../window.h"

extern const u8 Menu_BGTiles[];
extern const u8 Menu_BGMap[];
extern const u16 Menu_BGPal[];

#define DUMMY_WIN_TEMPLATE          \
{                                   \
    0xFF,                           \
    0,                              \
    0,                              \
    0,                              \
    0,                              \
    0,                              \
    0,                              \
}

enum BGs
{
	BG_TEXT,
	BG_NIL,
	BG_NIL_2,
	BG_BACKGROUND,
};

enum
{
	WINDOW_TITLE,
    WINDOW_ITEMS,
	WINDOW_COUNT,
};

#endif // GUARD_SHOW_MENU_H