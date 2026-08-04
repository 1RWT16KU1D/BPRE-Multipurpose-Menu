
//{{BLOCK(Menu_BG)

//======================================================================
//
//	Menu_BG, 256x160@4, 
//	+ palette 16 entries, not compressed
//	+ 47 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (flat), lz77 compressed, 32x20 
//	Total size: 32 + 328 + 264 = 624
//
//	Time-stamp: 2026-08-04, 17:00:26
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_BG_H
#define GRIT_MENU_BG_H

#define Menu_BGTilesLen 328
extern const unsigned char Menu_BGTiles[328];

#define Menu_BGMapLen 264
extern const unsigned short Menu_BGMap[132];

#define Menu_BGPalLen 32
extern const unsigned char Menu_BGPal[32];

#endif // GRIT_MENU_BG_H

//}}BLOCK(Menu_BG)
