#ifndef GUARD_SHOW_MENU_H
#define GUARD_SHOW_MENU_H

#include "../global.h"
#include "../window.h"

struct MenuStruct 
{
    u8 cursorPos;
    u8 selectedItem;
    u8 scrollOffset;
    u8 visibleStart;
    u8 visibleSelection;
};

#define VISIBLE_ITEMS 7
#define MENU_ITEM_COUNT NELEMS(MenuItems)

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

extern const u8 gText_MenuItem_1[];
extern const u8 gText_MenuItem_2[];
extern const u8 gText_MenuItem_3[];
extern const u8 gText_MenuItem_4[];
extern const u8 gText_MenuItem_5[];
extern const u8 gText_MenuItem_6[];
extern const u8 gText_MenuItem_7[];
extern const u8 gText_MenuItem_8[];
extern const u8 gText_MenuItem_9[];
extern const u8 gText_MenuItem_10[];

const u8 *const MenuItems[] =
{
    gText_MenuItem_1,
    gText_MenuItem_2,
    gText_MenuItem_3,
    gText_MenuItem_4,
    gText_MenuItem_5,
    gText_MenuItem_6,
    gText_MenuItem_7,
    gText_MenuItem_8,
    gText_MenuItem_9,
    gText_MenuItem_10,
};
#endif // GUARD_SHOW_MENU_H