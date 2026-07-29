.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_PalletTown_FatGuy
EventScript_PalletTown_FatGuy:
    lock
    faceplayer
    msgbox gText_PalletTown_FatGuy_WillShowImage MSG_NORMAL
    callasm ShowImage
    waitstate
    release
    end
