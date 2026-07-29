#ifndef GUARD_SHOW_MENU_H
#define GUARD_SHOW_MENU_H

#include "../global.h"
#include "../window.h"

#define VISIBLE_ITEMS 7
#define MENU_ITEM_COUNT (u8)NELEMS(MenuItems)
#define FONT_SIZE 1

// Configurable options
#define BONUS_MENU // Comment this out to disable the bonus menu page
#define BONUS_MENU_COUNT (u8)NELEMS(MenuBonusItems)

extern const u8 Menu_BGTiles[];
extern const u8 Menu_BGPal[];
extern const u16 Menu_BGMap[];

#ifdef BONUS_MENU
extern const u8 Menu_BG_BonusPal[];
#endif

struct MenuStruct 
{
    u8 cursorPos;
    u8 firstVisibleItem;
    u8 selectedItem;

    #ifdef BONUS_MENU
    bool8 isBonusPage;
    u8 bonusCursorPos;
    u8 bonusFirstVisibleItem;
    u8 bonusSelectedItem;
    #endif
};

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
    WINDOW_DESCRIPTION,
	WINDOW_COUNT,
};

// Title
extern const u8 gText_MenuTitle[];

// Menu Items
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

// Menu Item Descriptions
extern const u8 gText_MenuItemDesc_1[];
extern const u8 gText_MenuItemDesc_2[];
extern const u8 gText_MenuItemDesc_3[];
extern const u8 gText_MenuItemDesc_4[];
extern const u8 gText_MenuItemDesc_5[];
extern const u8 gText_MenuItemDesc_6[];
extern const u8 gText_MenuItemDesc_7[];
extern const u8 gText_MenuItemDesc_8[];
extern const u8 gText_MenuItemDesc_9[];
extern const u8 gText_MenuItemDesc_10[];

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

const u8 *const MenuItemDescriptions[] =
{
    gText_MenuItemDesc_1,
    gText_MenuItemDesc_2,
    gText_MenuItemDesc_3,
    gText_MenuItemDesc_4,
    gText_MenuItemDesc_5,
    gText_MenuItemDesc_6,
    gText_MenuItemDesc_7,
    gText_MenuItemDesc_8,
    gText_MenuItemDesc_9,
    gText_MenuItemDesc_10,
};

#ifdef BONUS_MENU
// Bonus Menu Title
extern const u8 gText_MenuBonusTitle[];

// Bonus Menu Items
extern const u8 gText_MenuBonusItem_1[];
extern const u8 gText_MenuBonusItem_2[];
extern const u8 gText_MenuBonusItem_3[];
extern const u8 gText_MenuBonusItem_4[];
extern const u8 gText_MenuBonusItem_5[];
extern const u8 gText_MenuBonusItem_6[];
extern const u8 gText_MenuBonusItem_7[];
extern const u8 gText_MenuBonusItem_8[];
extern const u8 gText_MenuBonusItem_9[];

// Bonus Menu Item Descriptions
extern const u8 gText_MenuBonusItemDescription_1[];
extern const u8 gText_MenuBonusItemDescription_2[];
extern const u8 gText_MenuBonusItemDescription_3[];
extern const u8 gText_MenuBonusItemDescription_4[];
extern const u8 gText_MenuBonusItemDescription_5[];
extern const u8 gText_MenuBonusItemDescription_6[];
extern const u8 gText_MenuBonusItemDescription_7[];
extern const u8 gText_MenuBonusItemDescription_8[];
extern const u8 gText_MenuBonusItemDescription_9[];

const u8 *const MenuBonusItems[] =
{
    gText_MenuBonusItem_1,
    gText_MenuBonusItem_2,
    gText_MenuBonusItem_3,
    gText_MenuBonusItem_4,
    gText_MenuBonusItem_5,
    gText_MenuBonusItem_6,
    gText_MenuBonusItem_7,
    gText_MenuBonusItem_8,
    gText_MenuBonusItem_9,
};

const u8 *const MenuBonusItemDescriptions[] =
{
    gText_MenuBonusItemDescription_1,
    gText_MenuBonusItemDescription_2,
    gText_MenuBonusItemDescription_3,
    gText_MenuBonusItemDescription_4,
    gText_MenuBonusItemDescription_5,
    gText_MenuBonusItemDescription_6,
    gText_MenuBonusItemDescription_7,
    gText_MenuBonusItemDescription_8,
    gText_MenuBonusItemDescription_9,
};
#endif

#endif // GUARD_SHOW_MENU_H