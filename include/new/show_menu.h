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
#define COLOR(color) &s##color##Text

/* ========== Configurable Options ========== */
#define BONUS_PAGE // Comment this out to disable the bonus menu page
#define VAR_CURRENT_SONG 0x51FF // Last var available
#define FLAG_UNLOCK_BONUS_PAGE 0x1800 // The flag that unlocks the bonus page

#define COLOR_MENU_TITLE COLOR(White) // Title text color
#define COLOR_DESCRIPTION COLOR(White) // Description text color
#define COLOR_MENU_ITEM COLOR(Black) // Menu item list color
#define COLOR_MENU_SELECTED_ITEM COLOR(White) // Selected menu item text color (including arrow)
#define COLOR_PREVIOUS_NEXT COLOR(White) // Previous/Next page text color


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
    bool8 *menuItemFlags;
    bool8 isPlaying;
    u16 mapMusic;
    u16 currentSong;

    #ifdef BONUS_PAGE
    bool8 isBonusPage;
    u8 bonusCursorPos;
    u8 bonusFirstVisibleItem;
    u8 bonusSelectedItem;
    bool8 *bonusMenuItemFlags;
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
extern const u8 gText_ItemDescriptionNotAvailable[];
extern const u8 gText_NowPlayingSong[];

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

const u16 MenuItemUnlockFlags[] =
{
    0x1601,
    0x1602,
    0x1603,
    0x1604,
    0x1605,
    0x1606,
    0x1607,
    0x1608,
    0x1609,
    0x160A
};

const u16 MenuItemSongs[] =
{
    300,
    314,
    280,
    0,
    0,
    0,
    0,
    0,
    0,
    0
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

const u16 MenuBonusItemUnlockFlags[] =
{
    0x1611,
    0x1612,
    0x1613,
    0x1614,
    0x1615,
    0x1616,
    0x1617,
    0x1618,
    0x1619
};

const u16 MenuBonusItemSongs[] =
{
    274,
    282,
    305,
    0,
    0,
    0,
    0,
    0,
    0
};
#endif

#endif // GUARD_SHOW_MENU_H