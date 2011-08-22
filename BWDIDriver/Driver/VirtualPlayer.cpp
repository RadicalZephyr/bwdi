
#include "VirtualPlayer.h"

#include "DLLMain.h"

void (__cdecl *UpdateGameHash)()  = (void(*)())0x0047CFC0;
void (__cdecl *CMDACT_GameHash)() = (void(*)())0x0047CC50;

/*
structures used internally in the hash functions:
00000000 hashStruct      struc ; (sizeof=0x10C)
00000000 hash            dw ?
00000002 hashType        db ?
00000003 regionVisionHash db ?
00000004 playerFlag      db ?                    ; base 16
00000005 minimapUnitBoxCount db ?
00000006 field_6         db ?
00000007 field_7         db ?
00000008 regionVisionID  dd ?
0000000C sprVisibilityHashing db 256 dup(?)
0000010C hashStruct      ends
0000010C
00000000 ; ---------------------------------------------------------------------------
00000000
00000000 hashPacket      struc ; (sizeof=0x7)
00000000 bID             db ?
00000001 bSeq            db ?
00000002 wSeqHash        dw ?
00000004 bVisibilityHash db ?
00000005 bVisibilityID   db ?
00000006 bMinimapBoxCount db ?
00000007 hashPacket      ends
*/

void VP_onInit()
{
}

void VP_onFrame(bool menu)
{
}

