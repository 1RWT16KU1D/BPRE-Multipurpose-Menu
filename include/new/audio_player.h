#ifndef GUARD_AUDIO_PLAYER_H
#define GUARD_AUDIO_PLAYER_H

#include "../bg.h"
#include "../global.h"
#include "../window.h"
#include "../../src/config.h"

// Text colors
extern const struct TextColor sWhiteText;
extern const struct TextColor sBlackText;
extern const struct TextColor sRedText;
extern const struct TextColor sBlueText;
extern const struct TextColor sGreenText;
extern const struct TextColor sGrayText;
#define COLOR(color) &s##color##Text

// Don't touch!
#define VISIBLE_ITEMS 7
#define FONT_SIZE 1
#define FONT_SIZE_SMALL 0
#define VALUE_SONG_UNSET 0xFFFF

struct ImageData
{
    const u8 *tiles;
    const u8 *pal;
    const u16 *tilemap;
};

extern const struct ImageData gAudioPlayerBGData;
extern const struct BgTemplate sAudioPlayerBGTemplates[];
extern const struct WindowTemplate sAudioPlayerWindowTemplates[];

/// enums and structs
struct MenuStruct 
{
    u8 cursorPos;
    u8 firstVisibleItem;
    u8 selectedItem;
    bool8 menuItemFlags[MENU_ITEM_COUNT];

    // Music vars
    u16 mapMusic;
    u16 currentSong;

    // Blinking description
    u8 blinkTimer;
    bool8 shouldBlink;

    #ifdef BONUS_PAGE
    bool8 isBonusPage;
    u8 bonusCursorPos;
    u8 bonusFirstVisibleItem;
    u8 bonusSelectedItem;
    bool8 bonusMenuItemFlags[BONUS_PAGE_COUNT];
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
    BG_COUNT,
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

extern const u8 *const MenuItems[MENU_ITEM_COUNT];
extern const u8 *const MenuItemDescriptions[MENU_ITEM_COUNT];
extern const u16 MenuItemUnlockFlags[MENU_ITEM_COUNT];
extern const u16 MenuItemSongs[MENU_ITEM_COUNT];

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

extern const u8 *const MenuBonusItems[BONUS_PAGE_COUNT];
extern const u8 *const MenuBonusItemDescriptions[BONUS_PAGE_COUNT];
extern const u16 MenuBonusItemUnlockFlags[BONUS_PAGE_COUNT];
extern const u16 MenuBonusItemSongs[BONUS_PAGE_COUNT];

void ShowAudioPlayer(void);
void ShowAudioPlayer(void);
#endif

#endif // GUARD_SHOW_MENU_H
