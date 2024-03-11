.386
.Model Flat, StdCall
OPTION CASEMAP :NONE

include \masm32\include\windows.inc
include \masm32\include\masm32.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
include \masm32\include\debug.inc
includelib \masm32\lib\masm32.lib
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\debug.lib

include lf2.inc
include generic.inc
include itreff.inc
include itrkind.inc
include states.inc
include ai.inc
include window.inc
include replay.inc
include battle.inc
include regen.inc
include spawner.inc
include cursor.inc
include external.inc
include UI.inc

.data
memAlloc dd ?
solAlloc dd ?

.data?


.code
DllEntryPoint proc hInstDLL:DWORD, reason:DWORD, unused:DWORD

	mov eax,reason
	.if eax == DLL_PROCESS_ATTACH											; Called when our dll loaded
		invoke VirtualAlloc, NULL, 4000, MEM_COMMIT,PAGE_READWRITE
        mov memAlloc,eax  
        invoke VirtualAlloc, NULL, 20000, MEM_COMMIT,PAGE_READWRITE
        mov solAlloc,eax       
		call DLLStartup														; Memory patches and jmp patches
	.endif
	ret

DllEntryPoint endp

DLLStartup proc

	;===============Random stuff(generic.inc)===========
	invoke JmpPatch, 004201E3h, addr Max_HP	      ;Max_HP_of_opointed_objectsT0
	;invoke JmpPatch, 00420272h, addr opoint_kind
	invoke JmpPatch, 0042EE17h, addr Shaker	      ;Shake_It_Baby!
	;===================================================

	;=============itr kind(itrkind.inc)=================
	invoke JmpPatch, 0042FFF8h, addr itr_kind8
	invoke JmpPatch, 00417526h, addr itr_kind8_types
	;===================================================

	;=============itr effects(itreff.inc)===============
	invoke JmpPatch, 0042F54Ah, addr itr_effect_1xxx_to_9xxx 
	;===================================================

	;=================states(states.inc)================
	invoke JmpPatch, 0041F656h, addr State8xxx ; 140-frameless fix (+id list for +140)
	invoke JmpPatch, 0041F603h, addr StateMore ; Set X-coord, Y-coord, Z-coord and more
	invoke JmpPatch, 0041334Ah, addr StateTurn3x ; Turning State 30, 31, 32
	invoke JmpPatch, 0042EC9Eh, addr State9xxx ; Go to XXX Frame if hit something. XXX from 0 to 799

	;invoke WriteMem, 0040EC13h, addr doubleNOP,2 ; Keep it, Can be usuful
	;invoke WriteMem, 0040EC15h, addr oneNOP,1 ; Keep it, Can be usuful

	;invoke JmpPatch, 004177B9h, addr Hit_teammates
	;==================================================
	
	;===============Window Properities(window.inc)=========
	invoke JmpPatch, 00401B3Ch, addr Window_Size_2	 	
	invoke JmpPatch, 00401007h, addr Window_Size_3
	invoke JmpPatch, 00401050h, addr Window_Size_4 
	invoke JmpPatch, 0042386Dh, addr Window_Size_5
	invoke JmpPatch, 0043F03Dh, addr Window_Size_6
	invoke JmpPatch, 0043F08Bh, addr Window_Size_7
	invoke JmpPatch, 0041A0AEh, addr Window_Size   
	invoke JmpPatch, 0041A1DBh, addr Window_Size_8 
	invoke JmpPatch, 0041A8FEh, addr Window_Size_9 
	invoke JmpPatch, 0041BB87h, addr Window_Size_10 
	invoke JmpPatch, 0041BC32h, addr Window_Size_11 
	invoke JmpPatch, 0042A1BFh, addr Window_Size_12 		
	invoke JmpPatch, 00437B62h, addr Window_Size_13 
	invoke JmpPatch, 004384C4h, addr Window_Size_14 
	invoke JmpPatch, 0043852Ch, addr Window_Size_15
	;===================================================

	;=============== Replays (replay.inc)===============
	invoke JmpPatch, 004326D6h, addr comparator	 	
	;===================================================	
	
	;=============== Battle Mode (battle.inc)===========
	invoke JmpPatch, 0043947Fh, addr defence	 	
	;===================================================	
	
	;=============== Regen (regen.inc)==================
	invoke JmpPatch, 0041FAE5h, addr mana_speed	 	
	invoke JmpPatch, 0041F9E2h, addr hp_speed
	;===================================================	

	;=============== Spawner (regen.inc)================
	invoke JmpPatch, 0042D68Fh, addr SpawnerBoth1
	invoke JmpPatch, 0042D4C0h, addr SpawnerPlayer1
	invoke JmpPatch, 0042D3ADh, addr SpawnerCom1
	invoke JmpPatch, 00437664h, addr SpawnerComStages1	
	;===================================================	
	
	;=============== Cursor (cursor.inc)=================
	invoke JmpPatch, 00425EB1h, addr CursorFix1
	invoke JmpPatch, 0042873Eh, addr CursorFix2
	invoke JmpPatch, 0043B4ECh, addr CursorFix3
	invoke JmpPatch, 0043D048h, addr CursorFix4
	;===================================================
	
	;=============== External (External.inc)=================
	invoke JmpPatch, 00426EBEh, addr CS2img
	invoke JmpPatch, 00426ECDh, addr CS3img
	invoke JmpPatch, 00426EDCh, addr CS4img
	invoke JmpPatch, 00426EEBh, addr CS5img
	invoke JmpPatch, 00426EFAh, addr CS6img
	invoke JmpPatch, 00426F09h, addr FRAMEimg
	invoke JmpPatch, 00426F18h, addr WORDS0img
	invoke JmpPatch, 00426F27h, addr WORDS1img
	invoke JmpPatch, 00426F36h, addr WORDS2img
	invoke JmpPatch, 00426F45h, addr WORDS3img
	invoke JmpPatch, 00426F54h, addr WORDS4img
	invoke JmpPatch, 00426F63h, addr WORDS5img
	invoke JmpPatch, 00425F3Fh, addr MENU_CLIPimg
	invoke JmpPatch, 00425F53h, addr MENU_CLIP2img
	invoke JmpPatch, 00425F62h, addr MENU_CLIP3img
	invoke JmpPatch, 00425F71h, addr MENU_CLIP4img
	invoke JmpPatch, 00425F80h, addr MENU_CLIP5img
	invoke JmpPatch, 00425F8Fh, addr MENU_CLIP6img
	invoke JmpPatch, 00425FADh, addr ENDINGimg
	invoke JmpPatch, 004273BCh, addr PAUSEimg
	invoke JmpPatch, 004273D0h, addr DEMOimg
	invoke JmpPatch, 004273DFh, addr SCORE_BOARD1img
	invoke JmpPatch, 004273EEh, addr SCORE_BOARD2img
	invoke JmpPatch, 004273FDh, addr SCORE_BOARD3img
	invoke JmpPatch, 0042740Ch, addr SCORE_BOARD4img
	invoke JmpPatch, 0042741Bh, addr WIN_ALIVEimg
	invoke JmpPatch, 0042742Ah, addr WIN_DEADimg
	invoke JmpPatch, 00427439h, addr LOSE_DEADimg
	invoke JmpPatch, 0040C2CDh, addr CHARMENUimg
	invoke JmpPatch, 0040C2DCh, addr CM1img
	invoke JmpPatch, 0040C2EBh, addr CM2img
	invoke JmpPatch, 0040C2FAh, addr CM3img
	invoke JmpPatch, 0040C309h, addr CM4img
	invoke JmpPatch, 0040C318h, addr CM5img
	invoke JmpPatch, 0040C327h, addr CMAimg
	invoke JmpPatch, 0040C336h, addr CMA2img
	invoke JmpPatch, 0040C345h, addr CMC_img
	invoke JmpPatch, 0040C354h, addr RFACEimg
	;===================================================

	;=============== UI Manipulation (UI.inc)===========
	invoke WriteMem, 0041AF3Ah, addr opacity,2 ; Frame
	invoke WriteMem, 0042A5D2h, addr opacity,2 ; RFace
	invoke WriteMem, 0042A53Fh, addr opacity,2 ; Character Faces
	invoke WriteMem, 0042BE93h, addr opacity,2 ; ???
	invoke WriteMem, 0042BDEBh, addr opacity,2 ; ???
	invoke WriteMem, 0042AFA2h, addr opacity,2 ; ???
	invoke WriteMem, 0042BB5Dh, addr opacity,2 ; ???
	;===================================================
	;invoke WriteMem, 0042A1E1h, addr ResetCoord,2	; Activate by your choise,
	;invoke WriteMem, 0042A1E3h, addr ResetCoord,2  ; resets CHARMENU coords to zero
	;===================================================



	;call AI
	ret


DLLStartup endp

AI proc

	;=================Range Stuff=================
	invoke JmpPatch, 0040AE0Ah, addr Range1
	invoke WriteMem, 0040AE0Fh, addr FourNOP,4
	invoke JmpPatch, 0040B217h, addr Range2
	invoke JmpPatch, 0040B2CBh, addr Range3
	invoke JmpPatch, 0040B383h, addr Range4
	invoke JmpPatch, 00403878h, addr Deep_Ball
	invoke WriteMem, 0040387Dh, addr doubleNOP,2
	;=============================================
	
	;==================Other AIs==================
	;Generic D>A
	invoke JmpPatch, 00403608h, addr AI_Ball1
	;Generic D>A #2
	invoke JmpPatch, 004036FBh, addr AI_Ball2
	;Deep AI
	invoke JmpPatch, 00403E89h, addr AI_Deep
	invoke WriteMem, 00403E8Eh, addr doubleNOP,2
	;John AI
	invoke JmpPatch, 00403A7Eh, addr AI_John
	invoke WriteMem, 00403A83h, addr doubleNOP,2
	;Henry AI
	invoke JmpPatch, 004041F1h, addr AI_Henry
	invoke WriteMem, 004041F6h, addr doubleNOP,2
	;Rudolf AI
	invoke JmpPatch, 0040436Eh, addr AI_Rudolf
	invoke WriteMem, 00404373h, addr doubleNOP,2
	;Louis AI
	invoke JmpPatch, 004044FAh, addr AI_Louis
	invoke WriteMem, 004044FFh, addr doubleNOP,2
	;Firen AI
	invoke JmpPatch, 00404609h, addr AI_Firen
	invoke WriteMem, 0040460Eh, addr doubleNOP,2
	;Freeze AI
	invoke JmpPatch, 0040499Ah, addr AI_Freeze
	invoke WriteMem, 0040499Fh, addr doubleNOP,2
	;Dennis AI
	invoke JmpPatch, 00405147h, addr AI_Dennis
	invoke WriteMem, 0040514Ch, addr doubleNOP,2
	;Woody AI
	invoke JmpPatch, 00404DBBh, addr AI_Woody
	invoke WriteMem, 00404DC0h, addr doubleNOP,2
	;Davis AI
	;invoke JmpPatch, 00404C12h, addr AI_Davis
	;invoke WriteMem, 00404C17h, addr doubleNOP,2
	;Sorcerer AI
	invoke JmpPatch, 0040555Dh, addr AI_Sorcerer
	invoke WriteMem, 00405562h, addr doubleNOP,2
	;=============================================
	
	ret
AI endp



End DllEntryPoint