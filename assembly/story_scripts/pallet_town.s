.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

.global EventScript_PalletTown_FatGuy
.global EventScript_PalletTown_LittleGirl

EventScript_PalletTown_FatGuy:
    lock
    faceplayer

    setflag 0x1601
    setflag 0x1602
    setflag 0x1603
    @setflag 0x1604
    setflag 0x1605
    @setflag 0x1606
    setflag 0x1607
    setflag 0x1608
    @setflag 0x1609
    setflag 0x160A

    setflag 0x1611
    @setflag 0x1612
    setflag 0x1613
    setflag 0x1614
    @setflag 0x1615
    setflag 0x1616
    @setflag 0x1617
    setflag 0x1618
    setflag 0x1619

    msgbox gText_PalletTown_FatGuy_WillShowMenu MSG_NORMAL
    callasm ShowImage
    waitstate
    release
    end

EventScript_PalletTown_LittleGirl:
    lock
    faceplayer
    setflag 0x1800
    release
    end
