#ifndef GUARD_SHOW_MENU_H
#define GUARD_SHOW_MENU_H

#include "../global.h"
#include "../window.h"

// Text colors
static const struct TextColor sWhiteText =
{
	.bgColor = TEXT_COLOR_TRANSPARENT,
	.fgColor = TEXT_COLOR_WHITE,
	.shadowColor = TEXT_COLOR_DARK_GREY
};

static const struct TextColor sBlackText =
{
	.bgColor = TEXT_COLOR_TRANSPARENT,
	.fgColor = TEXT_COLOR_DARK_GREY,
	.shadowColor = TEXT_COLOR_LIGHT_GREY
};

static const struct TextColor sRedText =
{
	.bgColor = TEXT_COLOR_TRANSPARENT,
	.fgColor = TEXT_COLOR_RED,
	.shadowColor = TEXT_COLOR_LIGHT_GREY
};

static const struct TextColor sBlueText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_BLUE,
    .shadowColor = TEXT_COLOR_LIGHT_BLUE
};

static const struct TextColor sGreenText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_GREEN,
    .shadowColor = TEXT_COLOR_LIGHT_GREEN
};

static const struct TextColor sGrayText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_LIGHT_GREY,
    .shadowColor = TEXT_COLOR_DARK_GREY
};
#define COLOR(color) &s$##color##Text

// Configurable options
#define BONUS_PAGE // Comment this out to disable the bonus menu page

#define COLOR_MENU_TITLE COLOR(White) // Title text color
#define COLOR_DESCRIPTION COLOR(Gray) // Description text color
#define COLOR_MENU_ITEM COLOR(Black) // Menu item list color
#define COLOR_MENU_SELECTED_ITEM COLOR(White) // Selected menu item text color (including arrow)
#define COLOR_PREVIOUS_NEXT COLOR(Green) // Previous/Next page text color


// Don't touch!
#define VISIBLE_ITEMS 7
#define MENU_ITEM_COUNT (u8)NELEMS(MenuItems)
#define FONT_SIZE 1
#define FONT_SIZE_SMALL 0

#define BONUS_PAGE_COUNT (u8)NELEMS(MenuBonusItems)


/// enums and structs
struct MenuStruct 
{
    u8 cursorPos;
    u8 firstVisibleItem;
    u8 selectedItem;

    #ifdef BONUS_PAGE
    bool8 isBonusPage;
    u8 bonusCursorPos;
    u8 bonusFirstVisibleItem;
    u8 bonusSelectedItem;
    #endif
};

enum MenuStates
{
    MENU_STATE_INIT,
    MENU_STATE_RESET,
    MENU_STATE_INIT_BGS,
    MENU_STATE_LOAD_GFX,
    MENU_STATE_SHOW_BGS,
    MENU_STATE_INIT_WINDOWS,
    MENU_STATE_FADE_IN,
    MENU_STATE_START,
};

enum MenuBGs
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

    #ifdef BONUS_PAGE
    WINDOW_NEXT_PREVIOUS_PAGE_TEXT,
    #endif
	WINDOW_COUNT,
};


// Graphics
extern const u8 Menu_BGTiles[];
extern const u8 Menu_BGPal[];
extern const u16 Menu_BGMap[];

#ifdef BONUS_PAGE
extern const u8 Menu_BG_BonusPal[];
#endif

/* ========== String Declarations ========== */

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

#ifdef BONUS_PAGE
// Bonus Menu Title
extern const u8 gText_MenuBonusTitle[];

// Next/Previous Page Text
extern const u8 gText_MenuBonusNextPageR[];
extern const u8 gText_MenuBonusPreviousPageL[];

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