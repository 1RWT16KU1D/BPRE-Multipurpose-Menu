#pragma once

/* ========== Configurable Options ========== */
#define BONUS_PAGE // Comment this out if you don't want a bonus page
#define VAR_AUDIO_PLAYER_PAGE 0x51FC // 0 = main page, 1 = bonus page
#define VAR_AUDIO_PLAYER_MAIN_INDEX 0x51FD // Last selected index on main page
#define VAR_AUDIO_PLAYER_BONUS_INDEX 0x51FE // Last selected index on bonus page
#define VAR_CURRENT_SONG 0x51FF // Var that stores the last played song
#define FLAG_UNLOCK_BONUS_PAGE 0x1800 // The flag that unlocks the bonus page
#define BLINK_TIMER 45 // Blink every 45 frames. Around 3/2s on 60 fps

#define COLOR_MENU_TITLE COLOR(White) // Title text color
#define COLOR_DESCRIPTION COLOR(White) // Description text color
#define COLOR_MENU_ITEM COLOR(Black) // Menu item list color
#define COLOR_MENU_SELECTED_ITEM COLOR(White) // Selected menu item text color (including arrow)
#define COLOR_PREVIOUS_NEXT COLOR(White) // Previous/Next page text color

#define MENU_ITEM_COUNT 10 // Number of songs in the menu
#define BONUS_PAGE_COUNT 9 // Number of songs in the bonus page
