#include "../include/palette.h"
#include "../include/sound.h"

#include "../include/new/show_menu.h" 
#include "../include/bg.h"
#include "../include/decompress.h"
#include "../include/event_data.h"
#include "../include/gpu_regs.h"
#include "../include/graphics.h"
#include "../include/item.h"
#include "../include/list_menu.h"
#include "../include/international_string_util.h"
#include "../include/main.h"
#include "../include/malloc.h"
#include "../include/menu.h"
#include "../include/menu_helpers.h" 
#include "../include/overworld.h"
#include "../include/palette.h"
#include "../include/scanline_effect.h"
#include "../include/script.h"
#include "../include/string_util.h"

#include "../include/constants/field_weather.h"
#include "../include/constants/songs.h"

#include "../include/new/ram_locs.h"
#include "../include/new/Vanilla_functions.h"

#define gMenuStruct ((struct MenuStruct*) 0x203E008)
#define tilemapbuffer (*((u8**) 0x203E038)) 
#define BG_MAP_BYTES 0x800

bool8 *menuUnlockFlags;
#ifdef BONUS_PAGE
bool8 *bonusMenuUnlockFlags;
#endif

struct ImageData
{
    const u8 *tiles;
    const u8 *pal;
    const u16 *tilemap;
};

const struct ImageData MenuBGData =
{
    .tiles = Menu_BGTiles,
    .pal = Menu_BGPal,
    .tilemap = Menu_BGMap
};

static const struct BgTemplate sMenuBGTemplates[] =
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

static const struct WindowTemplate unusedArg sMenuWindowTemplates[WINDOW_COUNT + 1] =
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
        .tilemapTop = 8,
        .width = 7,
        .height = 4,
        .paletteNum = 14,
        .baseBlock = 405,
    },
    #endif
	//Base block 500 is used for frame tiles
	DUMMY_WIN_TEMPLATE
};

static void VBlankCB_Image(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void MainCB2_Image(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

// This file's functions
static void CleanWindow(u8 windowId);
static void CommitWindow(u8 windowId);
static void CleanWindows(void);
static void CommitWindows(void);

static void InitMenuFlags(void);
static void Task_ImageFadeIn(u8 taskId);
static void Task_ImageWaitForKeyPress(u8 taskId);
static void Task_ImageFadeOut(u8 taskId);
static void PrintMenuTitle(void);
static void PrintMenuItems(void);
static void PrintMenuItemDescription(void);
#ifdef BONUS_PAGE
static void PrintNextPreviousPageText(void);
#endif
static void PrintMenuGUI(void);

static void CleanWindow(u8 windowId)
{
	FillWindowPixelBuffer(windowId, PIXEL_FILL(0));
}

static void CleanWindows(void)
{
	for (u32 i = 0; i < WINDOW_COUNT; ++i)
		CleanWindow(i);
}

static void CommitWindow(u8 windowId)
{
	CopyWindowToVram(windowId, COPYWIN_BOTH);
	PutWindowTilemap(windowId);
}

static void CommitWindows(void)
{
	for (u32 i = 0; i < WINDOW_COUNT; ++i)
		CommitWindow(i);
}

static void InitMenuFlags(void)
{
    for (u8 i = 0; i < MENU_ITEM_COUNT; ++i)
        gMenuStruct->menuItemFlags[i] = FlagGet(MenuItemUnlockFlags[i]);

    #ifdef BONUS_PAGE
    for (u8 i = 0; i < BONUS_PAGE_COUNT; ++i)
        gMenuStruct->bonusMenuItemFlags[i] = FlagGet(MenuBonusItemUnlockFlags[i]);
    #endif

}

static void LoadMenuBG(void)
{
    const struct ImageData *img = &MenuBGData;
    CpuFastFill16(0, (void*)BG_CHAR_ADDR(0), BG_CHAR_SIZE * 4);
    CpuFastFill16(0, tilemapbuffer, BG_MAP_BYTES);

    // Tiles
    DecompressAndCopyTileDataToVram(BG_BACKGROUND, img->tiles, 0, 0, 0);

    // Map
    LZDecompressWram(img->tilemap, tilemapbuffer);

    // Palette
    #ifdef BONUS_PAGE
    LoadPalette(gMenuStruct->isBonusPage ? Menu_BG_BonusPal : img->pal, 0, 0x20);
    #else
    LoadPalette(img->pal, 0, 0x20);
    #endif
}

static void CB2_FullImage(void)
{
    switch (gMain.state)
    {
        case MENU_STATE_INIT:
        default:
            gMenuStruct->cursorPos = 0;
            gMenuStruct->firstVisibleItem = 0;
            gMenuStruct->selectedItem = 0;

            gMenuStruct->menuItemFlags = Calloc(MENU_ITEM_COUNT * sizeof(bool8));
            gMenuStruct->mapMusic = GetCurrentMapMusic();

            #ifdef BONUS_PAGE
            gMenuStruct->isBonusPage = FALSE;
            gMenuStruct->bonusCursorPos = 0;
            gMenuStruct->bonusFirstVisibleItem = 0;
            gMenuStruct->bonusSelectedItem = 0;

            gMenuStruct->bonusMenuItemFlags = Calloc(BONUS_PAGE_COUNT * sizeof(bool8));
            #endif

            #ifdef KEEP_PLAYING_MUSIC
            gMenuStruct->currentSong = 0xFFFF; // Set to an invalid song number to prevent the "Now Playing" text from showing up when the menu is first opened
            #endif

            InitMenuFlags();
            SetBGMVolume_SuppressHelpSystemReduction(160);
            SetVBlankCallback(NULL);

            DmaFill16(3, 0, VRAM, VRAM_SIZE);
            DmaFill32(3, 0, OAM, OAM_SIZE);
            DmaFill16(3, 0, PLTT, PLTT_SIZE);

            gMain.state++;
            break;

        case MENU_STATE_RESET:
            ScanlineEffect_Stop();
            ResetTasks();
            ResetSpriteData();
            ResetTempTileDataBuffers();
            ResetPaletteFade();
            FreeAllSpritePalettes();

            gMain.state++;
            break;

        case MENU_STATE_INIT_BGS:
            tilemapbuffer = Calloc(BG_MAP_BYTES);

            ResetBgsAndClearDma3BusyFlags(0);
            InitBgsFromTemplates(0, sMenuBGTemplates, NELEMS(sMenuBGTemplates));
            SetBgTilemapBuffer(BG_BACKGROUND, tilemapbuffer);

            ChangeBgX(BG_BACKGROUND, 0, 0);
            ChangeBgY(BG_BACKGROUND, 0, 0);
            ChangeBgX(BG_TEXT, 0, 0);
            ChangeBgY(BG_TEXT, 0, 0);

            gMain.state++;
            break;

        case MENU_STATE_LOAD_GFX:
            LoadMenuBG();
            gMain.state++;
            break;

        case MENU_STATE_SHOW_BGS:
            if (!free_temp_tile_data_buffers_if_possible())
            {
                ShowBg(BG_TEXT);
                ShowBg(BG_BACKGROUND);

                CopyBgTilemapBufferToVram(BG_BACKGROUND);

                gMain.state++;
            }
            break;

        case MENU_STATE_INIT_WINDOWS:
            InitWindows(sMenuWindowTemplates);
            DeactivateAllTextPrinters();

            gMain.state++;
            break;

        case MENU_STATE_FADE_IN:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
            PlaySE(SE_WIN_OPEN);
            gMain.state++;
            break;

        case MENU_STATE_START:
            SetVBlankCallback(VBlankCB_Image);
            PrintMenuGUI();

            CreateTask(Task_ImageFadeIn, 0);
            SetMainCallback2(MainCB2_Image);

            gMain.state = 0;
            break;
    }
}

static void Task_ImageFadeIn(u8 taskId)
{
    if (!gPaletteFade->active)
        gTasks[taskId].func = Task_ImageWaitForKeyPress;
}

static void UpdateMenuSelection(bool8 movingDown)
{
    u8 *cursorPos;
    u8 *firstVisibleItem;
    u8 *selectedItem;
    u8 itemCount;

    #ifdef BONUS_PAGE
    if (gMenuStruct->isBonusPage)
    {
        cursorPos = &gMenuStruct->bonusCursorPos;
        firstVisibleItem = &gMenuStruct->bonusFirstVisibleItem;
        selectedItem = &gMenuStruct->bonusSelectedItem;
        itemCount = BONUS_PAGE_COUNT;
    }
    else
    #endif
    {
        cursorPos = &gMenuStruct->cursorPos;
        firstVisibleItem = &gMenuStruct->firstVisibleItem;
        selectedItem = &gMenuStruct->selectedItem;
        itemCount = MENU_ITEM_COUNT;
    }

    if (movingDown)
    {
        if (*cursorPos == VISIBLE_ITEMS - 1)
        {
            if (*selectedItem == itemCount - 1)
                return;

            PlaySE(SE_SELECT);
            (*firstVisibleItem)++;
        }
        else
        {
            PlaySE(SE_SELECT);
            (*cursorPos)++;
        }
    }
    else
    {
        if (*cursorPos == 0)
        {
            if (*selectedItem == 0)
                return;

            PlaySE(SE_SELECT);
            (*firstVisibleItem)--;
        }
        else
        {
            PlaySE(SE_SELECT);
            (*cursorPos)--;
        }
    }

    *selectedItem = *firstVisibleItem + *cursorPos;
    PrintMenuItems();
    PrintMenuItemDescription();
}

static void Task_ImageWaitForKeyPress(u8 taskId)
{
    if (gMain.newKeys & A_BUTTON)
    {
        // Return early if not unlocked
        #ifdef BONUS_PAGE
        if (gMenuStruct->isBonusPage)
        {
            if (!gMenuStruct->bonusMenuItemFlags[gMenuStruct->bonusSelectedItem])
                return;
        }
        else
        #endif
        {
            if (!gMenuStruct->menuItemFlags[gMenuStruct->selectedItem])
                return;
        }

        #ifndef KEEP_PLAYING_MUSIC
        if (gMenuStruct->isPlaying)
            return;

        #ifdef BONUS_PAGE
        if (gMenuStruct->isBonusPage)
        {
            if (!gMenuStruct->bonusMenuItemFlags[gMenuStruct->bonusSelectedItem])
                return;
        }
        else
        #endif
        {
            if (!gMenuStruct->menuItemFlags[gMenuStruct->selectedItem])
                return;
        }
        #endif
        gMenuStruct->isPlaying = TRUE;

        u16 songNum;
        #ifdef BONUS_PAGE
        if (gMenuStruct->isBonusPage)
            songNum = MenuBonusItemSongs[gMenuStruct->bonusSelectedItem];
        else
        #endif
            songNum = MenuItemSongs[gMenuStruct->selectedItem];

        if (gMenuStruct->currentSong == songNum)
            return;

        PlaySE(SE_SELECT);
        FadeOutAndPlayNewMapMusic(songNum, 8);
        #ifdef KEEP_PLAYING_MUSIC
        gMenuStruct->currentSong = songNum;
        #endif
        PrintMenuItemDescription();
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        #ifndef KEEP_PLAYING_MUSIC
        if (gMenuStruct->isPlaying)
        #endif
        {
            #ifndef KEEP_PLAYING_MUSIC
            gMenuStruct->isPlaying = FALSE;
            FadeOutAndPlayNewMapMusic(gMenuStruct->mapMusic, 8);
            #endif
            PrintMenuItemDescription();
        }
        #ifndef KEEP_PLAYING_MUSIC
        else
        #endif
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_ImageFadeOut;
        }
    }
    else if (JOY_NEW_AND_REPEATED(DPAD_UP))
    {
        #ifndef KEEP_PLAYING_MUSIC
        if (gMenuStruct->isPlaying)
            return;
        #endif
        UpdateMenuSelection(FALSE);
    }
    else if (JOY_NEW_AND_REPEATED(DPAD_DOWN))
    {
        #ifndef KEEP_PLAYING_MUSIC
        if (gMenuStruct->isPlaying)
            return;
        #endif
        UpdateMenuSelection(TRUE);
    }
    #ifdef BONUS_PAGE
    else if (gMain.newKeys & (L_BUTTON | R_BUTTON))
    {
        #ifndef KEEP_PLAYING_MUSIC
        if (gMenuStruct->isPlaying)
            return;
        #endif
        bool8 nextIsBonusPage = (gMain.newKeys & R_BUTTON) ? TRUE : FALSE;
        if (gMenuStruct->isBonusPage != nextIsBonusPage)
        {
            gMenuStruct->isBonusPage = nextIsBonusPage;
            PlaySE(SE_WIN_OPEN);
            LoadMenuBG();
            CopyBgTilemapBufferToVram(BG_BACKGROUND);
            PrintMenuGUI();
        }
    }
    #endif
}

// Free the tilemap buffer and return to the previous CB
static void Task_ImageFadeOut(u8 taskId)
{
    if (!gPaletteFade->active)
    {
        Free(tilemapbuffer);
        tilemapbuffer = NULL;

        ScriptContext2_Disable();
        gMain.state = MENU_STATE_INIT;

        PlaySE(SE_PC_OFF);
        BGMVolumeMax_EnableHelpSystemReduction();
        SetMainCallback2(CB2_ReturnToFieldContinueScript);
        DestroyTask(taskId);
    }
}

// Print the menu title to the screen
static void PrintMenuTitle(void)
{
    const u8 *titleText = gText_MenuTitle;
    #ifdef BONUS_PAGE
    if (gMenuStruct->isBonusPage)
        titleText = gText_MenuBonusTitle;
    #endif

    CleanWindow(WINDOW_TITLE);
    WindowPrint(WINDOW_TITLE, FONT_SIZE, 3, 0, COLOR_MENU_TITLE, 0, titleText);
    CommitWindow(WINDOW_TITLE);
}

// Print menu items to the screen
static void PrintMenuItems(void)
{
    const u8 *const *items = MenuItems;
    u8 firstVisibleItem;
    u8 cursorPos;
    u8 selectedItem;
    u8 itemCount;
    bool8 *unlockFlags;

    #ifdef BONUS_PAGE
    if (gMenuStruct->isBonusPage)
    {
        items = MenuBonusItems;
        firstVisibleItem = gMenuStruct->bonusFirstVisibleItem;
        cursorPos = gMenuStruct->bonusCursorPos;
        selectedItem = gMenuStruct->bonusSelectedItem;
        itemCount = BONUS_PAGE_COUNT;
        unlockFlags = gMenuStruct->bonusMenuItemFlags;
    }
    else
    #endif
    {
        firstVisibleItem = gMenuStruct->firstVisibleItem;
        cursorPos = gMenuStruct->cursorPos;
        selectedItem = gMenuStruct->selectedItem;
        itemCount = MENU_ITEM_COUNT;
        unlockFlags = gMenuStruct->menuItemFlags;

    }

    CleanWindow(WINDOW_ITEMS);

    u8 itemText[24];

    for (u8 i = 0; i < VISIBLE_ITEMS; ++i)
    {
        u8 item = firstVisibleItem + i;
        if (item >= itemCount)
            break;

        if (i == cursorPos && item == selectedItem)
        {
            if (unlockFlags[item])
            {
                StringCopy(itemText, (const u8[]){CHAR_ARROW_RIGHT, EOS});
                StringAppend(itemText, items[item]);
            }
            else
                StringCopy(itemText, (const u8[]){CHAR_HYPHEN, CHAR_HYPHEN, EOS});
            WindowPrint(WINDOW_ITEMS, FONT_SIZE, 4, i * 16, COLOR_MENU_SELECTED_ITEM, 0, itemText);
        }
        else
        {
            if (unlockFlags[item])
                StringCopy(itemText, items[item]);
            else
                StringCopy(itemText, (const u8[]){CHAR_HYPHEN, CHAR_HYPHEN, EOS});
            WindowPrint(WINDOW_ITEMS, FONT_SIZE, 4, i * 16, COLOR_MENU_ITEM, 0, itemText);
        }
    }

    CommitWindow(WINDOW_ITEMS);
}

static void PrintMenuItemDescription(void)
{
    u8 selectedItem;
    const u8 * const *itemNames;
    const u8 * const *itemDescriptions;
    const bool8 *itemFlags;

    CleanWindow(WINDOW_DESCRIPTION);

    #ifdef BONUS_PAGE
    if (gMenuStruct->isBonusPage)
    {
        selectedItem = gMenuStruct->bonusSelectedItem;
        itemNames = MenuBonusItems;
        itemDescriptions = MenuBonusItemDescriptions;
        itemFlags = gMenuStruct->bonusMenuItemFlags;
    }
    else
    #endif
    {
        selectedItem = gMenuStruct->selectedItem;
        itemNames = MenuItems;
        itemDescriptions = MenuItemDescriptions;
        itemFlags = gMenuStruct->menuItemFlags;
    }

    #ifdef KEEP_PLAYING_MUSIC
    if (gMenuStruct->isPlaying
        && gMenuStruct->currentSong == (
    #ifdef BONUS_PAGE
        gMenuStruct->isBonusPage ? MenuBonusItemSongs[selectedItem]
        :
    #endif
        MenuItemSongs[selectedItem]))
    {
        u8 nowPlayingText[32];

        StringCopy(gStringVar4, itemNames[selectedItem]);

        StringCopy(nowPlayingText, gText_NowPlayingSong);
        StringAppend(nowPlayingText, gStringVar4);

        WindowPrint(WINDOW_DESCRIPTION, FONT_SIZE, 0, 0, COLOR_DESCRIPTION, 0, nowPlayingText);
        CommitWindow(WINDOW_DESCRIPTION);
        return;
    }
    #endif

    WindowPrint(WINDOW_DESCRIPTION, FONT_SIZE, 0, 0, COLOR_DESCRIPTION, 0, itemFlags[selectedItem] ? itemDescriptions[selectedItem] : gText_ItemDescriptionNotAvailable);
    CommitWindow(WINDOW_DESCRIPTION);
}

// Print the next/previous page text to the screen
#ifdef BONUS_PAGE
static void PrintNextPreviousPageText(void)
{
    CleanWindow(WINDOW_NEXT_PREVIOUS_PAGE_TEXT);
    if (gMenuStruct->isBonusPage)
        WindowPrint(WINDOW_NEXT_PREVIOUS_PAGE_TEXT, FONT_SIZE_SMALL, 0, 0, COLOR_PREVIOUS_NEXT, 0, gText_MenuBonusPreviousPageL);
    else
        WindowPrint(WINDOW_NEXT_PREVIOUS_PAGE_TEXT, FONT_SIZE_SMALL, 0, 0, COLOR_PREVIOUS_NEXT, 0, gText_MenuBonusNextPageR);
    CommitWindow(WINDOW_NEXT_PREVIOUS_PAGE_TEXT);
}
#endif

// Print the menu GUI text to the screen
static void PrintMenuGUI(void)
{
    // Prevent tilemap glitches
    CleanWindows();
    CommitWindows();

    PrintMenuTitle();
    PrintMenuItems();
    PrintMenuItemDescription();

    #ifdef BONUS_PAGE
    PrintNextPreviousPageText();
    #endif
}

void ShowImage(void)
{
    ScriptContext2_Enable();
    gMain.state = MENU_STATE_INIT;
    SetMainCallback2(CB2_FullImage);
}
