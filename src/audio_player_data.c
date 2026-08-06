#include "../include/new/audio_player.h"

/* ========== Text Color Data ========== */
const struct TextColor sWhiteText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_WHITE,
    .shadowColor = TEXT_COLOR_DARK_GREY,
};

const struct TextColor sBlackText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_DARK_GREY,
    .shadowColor = TEXT_COLOR_LIGHT_GREY,
};

const struct TextColor sRedText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_RED,
    .shadowColor = TEXT_COLOR_LIGHT_GREY,
};

const struct TextColor sBlueText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_BLUE,
    .shadowColor = TEXT_COLOR_LIGHT_BLUE,
};

const struct TextColor sGreenText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_GREEN,
    .shadowColor = TEXT_COLOR_LIGHT_GREEN,
};

const struct TextColor sGrayText =
{
    .bgColor = TEXT_COLOR_TRANSPARENT,
    .fgColor = TEXT_COLOR_LIGHT_GREY,
    .shadowColor = TEXT_COLOR_DARK_GREY,
};


/* ========== Menu BG Data ========== */
const struct ImageData gAudioPlayerBGData =
{
    .tiles = Menu_BGTiles,
    .pal = Menu_BGPal,
    .tilemap = Menu_BGMap,
};


/* ========== BG Template Data ========== */
const struct BgTemplate sAudioPlayerBGTemplates[] =
{
    [BG_TEXT] =
    {
        .bg = BG_TEXT,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    [BG_NIL] =
    {
        .bg = BG_NIL,
        .charBaseIndex = 1,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    [BG_NIL_2] =
    {
        .bg = BG_NIL_2,
        .charBaseIndex = 2,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    },
    [BG_BACKGROUND] =
    {
        .bg = BG_BACKGROUND,
        .charBaseIndex = 3,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0,
    },
};


/* ========== Window Template Data ========== */
const struct WindowTemplate sAudioPlayerWindowTemplates[WINDOW_COUNT + 1] =
{
    [WINDOW_TITLE] =
    {
        .bg = BG_TEXT,
        .tilemapLeft = 21,
        .tilemapTop = 1,
        .width = 9,
        .height = 2,
        .paletteNum = 14,
        .baseBlock = 1,
    },
    [WINDOW_ITEMS] =
    {
        .bg = BG_TEXT,
        .tilemapLeft = 0,
        .tilemapTop = 1,
        .width = 19,
        .height = 14,
        .paletteNum = 14,
        .baseBlock = 19,
    },
    [WINDOW_DESCRIPTION] =
    {
        .bg = BG_TEXT,
        .tilemapLeft = 1,
        .tilemapTop = 16,
        .width = 30,
        .height = 4,
        .paletteNum = 14,
        .baseBlock = 285,
    },

    #ifdef BONUS_PAGE
    [WINDOW_NEXT_PREVIOUS_PAGE_TEXT] =
    {
        .bg = BG_TEXT,
        .tilemapLeft = 23,
        .tilemapTop = 6,
        .width = 7,
        .height = 4,
        .paletteNum = 14,
        .baseBlock = 405,
    },
    #endif
    DUMMY_WIN_TEMPLATE
};


/* ========== Menu Item Data ========== */
const u8 *const MenuItems[MENU_ITEM_COUNT] =
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

const u8 *const MenuItemDescriptions[MENU_ITEM_COUNT] =
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

const u16 MenuItemUnlockFlags[MENU_ITEM_COUNT] =
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
    0x160A,
};

const u16 MenuItemSongs[MENU_ITEM_COUNT] =
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
    0,
};


/* ========== Bonus Page Item Data ========== */
#ifdef BONUS_PAGE
const u8 *const MenuBonusItems[BONUS_PAGE_COUNT] =
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

const u8 *const MenuBonusItemDescriptions[BONUS_PAGE_COUNT] =
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

const u16 MenuBonusItemUnlockFlags[BONUS_PAGE_COUNT] =
{
    0x1611,
    0x1612,
    0x1613,
    0x1614,
    0x1615,
    0x1616,
    0x1617,
    0x1618,
    0x1619,
};

const u16 MenuBonusItemSongs[BONUS_PAGE_COUNT] =
{
    274,
    282,
    305,
    0,
    0,
    0,
    0,
    0,
    0,
};
#endif
