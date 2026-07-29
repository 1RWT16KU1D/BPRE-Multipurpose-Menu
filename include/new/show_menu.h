#ifndef GUARD_SHOW_MENU_H
#define GUARD_SHOW_MENU_H

#include "../global.h"
#include "../window.h"

extern const u8 Menu_BGTiles[];
extern const u16 Menu_BGMap[];
extern const u8 Menu_BGPal[];

static const struct TextColor sWhiteText =
{
	.bgColor = TEXT_COLOR_TRANSPARENT,
	.fgColor = TEXT_COLOR_WHITE,
	.shadowColor = TEXT_COLOR_DARK_GREY,
};

static const struct TextColor sBlackText =
{
	.bgColor = TEXT_COLOR_TRANSPARENT,
	.fgColor = TEXT_COLOR_DARK_GREY,
	.shadowColor = TEXT_COLOR_LIGHT_GREY,
};

static const struct TextColor sLightRedText =
{
	.bgColor = TEXT_COLOR_TRANSPARENT,
	.fgColor = TEXT_COLOR_LIGHT_RED,
	.shadowColor = TEXT_COLOR_RED,
};

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

enum MenuStates
{
    MENU_STATE_INIT = 0,
    MENU_STATE_RESET,
    MENU_STATE_INIT_BGS,
    MENU_STATE_LOAD_GFX,
    MENU_STATE_SHOW_BGS,
    MENU_STATE_INIT_WINDOWS,
    MENU_STATE_FADE_IN,
    MENU_STATE_START,
};

enum MenBGs
{
	BG_TEXT,
	BG_NIL,
	BG_NIL_2,
	BG_BACKGROUND,
};

enum MenuWindows
{
	WINDOW_TITLE,
    WINDOW_ITEMS,
	WINDOW_COUNT,
};

extern const u8 gText_MenuTitle[];
extern const u8 gText_MenuItems[];

#endif // GUARD_SHOW_MENU_H