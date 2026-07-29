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
		.tilemapLeft = 22,
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

    #ifdef BONUS_MENU
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

static void Task_ImageFadeIn(u8 taskId);
static void Task_ImageWaitForKeyPress(u8 taskId);
static void Task_ImageFadeOut(u8 taskId);
static void PrintMenuTitle(void);
static void PrintMenuItems(void);
static void PrintMenuItemDescription(void);
#ifdef BONUS_MENU
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
    #ifdef BONUS_MENU
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

            #ifdef BONUS_MENU
            gMenuStruct->isBonusPage = FALSE;
            gMenuStruct->bonusCursorPos = 0;
            gMenuStruct->bonusFirstVisibleItem = 0;
            gMenuStruct->bonusSelectedItem = 0;
            #endif

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

    #ifdef BONUS_MENU
    if (gMenuStruct->isBonusPage)
    {
        cursorPos = &gMenuStruct->bonusCursorPos;
        firstVisibleItem = &gMenuStruct->bonusFirstVisibleItem;
        selectedItem = &gMenuStruct->bonusSelectedItem;
        itemCount = BONUS_MENU_COUNT;
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
    if (gMain.newKeys & B_BUTTON)
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_ImageFadeOut;
    }
    else if (gMain.newKeys & DPAD_UP)
    {
        UpdateMenuSelection(FALSE);
    }
    else if (gMain.newKeys & DPAD_DOWN)
    {
        UpdateMenuSelection(TRUE);
    }
    #ifdef BONUS_MENU
    else if (gMain.newKeys & (L_BUTTON | R_BUTTON))
    {
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
        gMain.state = 0;

        PlaySE(SE_PC_OFF);
        SetMainCallback2(CB2_ReturnToFieldContinueScript);
        DestroyTask(taskId);
    }
}

// Print the menu title to the screen
static void PrintMenuTitle(void)
{
    const u8 *titleText = gText_MenuTitle;
    #ifdef BONUS_MENU
    if (gMenuStruct->isBonusPage)
        titleText = gText_MenuBonusTitle;
    #endif

    CleanWindow(WINDOW_TITLE);
    WindowPrint(WINDOW_TITLE, FONT_SIZE, 0, 0, &sWhiteText, 0, titleText);
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

    #ifdef BONUS_MENU
    if (gMenuStruct->isBonusPage)
    {
        items = MenuBonusItems;
        firstVisibleItem = gMenuStruct->bonusFirstVisibleItem;
        cursorPos = gMenuStruct->bonusCursorPos;
        selectedItem = gMenuStruct->bonusSelectedItem;
        itemCount = BONUS_MENU_COUNT;
    }
    else
    #endif
    {
        firstVisibleItem = gMenuStruct->firstVisibleItem;
        cursorPos = gMenuStruct->cursorPos;
        selectedItem = gMenuStruct->selectedItem;
        itemCount = MENU_ITEM_COUNT;
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
            StringCopy(itemText, (const u8[]){CHAR_ARROW_RIGHT, EOS});
            StringAppend(itemText, items[item]);
            WindowPrint(WINDOW_ITEMS, FONT_SIZE, 0, i * 16, &sWhiteText, 0, itemText);
        }
        else
        {
            StringCopy(itemText, items[item]);
            WindowPrint(WINDOW_ITEMS, FONT_SIZE, 4, i * 16, &sBlackText, 0, itemText);
        }
    }

    CommitWindow(WINDOW_ITEMS);
}

// Print the description of the selected menu item to the screen
static void PrintMenuItemDescription(void)
{
    u8 selectedItem;

    CleanWindow(WINDOW_DESCRIPTION);

    #ifdef BONUS_MENU
    if (gMenuStruct->isBonusPage)
    {
        selectedItem = gMenuStruct->bonusSelectedItem;
        WindowPrint(WINDOW_DESCRIPTION, FONT_SIZE, 0, 0, &sWhiteText, 0, MenuBonusItemDescriptions[selectedItem]);
    }
    else
    #endif
    {
        selectedItem = gMenuStruct->selectedItem;
        WindowPrint(WINDOW_DESCRIPTION, FONT_SIZE, 0, 0, &sWhiteText, 0, MenuItemDescriptions[selectedItem]);
    }
    CommitWindow(WINDOW_DESCRIPTION);
}

// Print the next/previous page text to the screen
#ifdef BONUS_MENU
static void PrintNextPreviousPageText(void)
{
    CleanWindow(WINDOW_NEXT_PREVIOUS_PAGE_TEXT);
    if (gMenuStruct->isBonusPage)
        WindowPrint(WINDOW_NEXT_PREVIOUS_PAGE_TEXT, FONT_SIZE - 1, 0, 0, &sBlackText, 0, gText_MenuBonusPreviousPageL);
    else
        WindowPrint(WINDOW_NEXT_PREVIOUS_PAGE_TEXT, FONT_SIZE - 1, 0, 0, &sBlackText, 0, gText_MenuBonusNextPageR);
    CommitWindow(WINDOW_NEXT_PREVIOUS_PAGE_TEXT);
}
#endif

// Print the menu GUI text to the screen
static void PrintMenuGUI(void)
{
    CleanWindows();
    CommitWindows();

    PrintMenuTitle();
    PrintMenuItems();
    PrintMenuItemDescription();

    #ifdef BONUS_MENU
    PrintNextPreviousPageText();
    #endif
}

void ShowImage(void)
{
    ScriptContext2_Enable();
    gMain.state = 0;
    SetMainCallback2(CB2_FullImage);
}
