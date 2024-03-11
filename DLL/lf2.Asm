; Based on Masm32 Dll Plugin Example for Damnation by Drakken
; Modified for LF2 by Silva
; Contributions by: genevrier

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
include itrkind.inc
include states.inc
include ai.inc
include window.inc

.data
memAlloc dd ?
solAlloc dd ?

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
	;invoke CallPatch,0041F9C9h, addr Health       ;HP_Regenerate
	;invoke WriteMem, 0041F9CEh, addr doubleNOP,2
	invoke JmpPatch, 004201E3h, addr Max_HP	      ;Max_HP_of_opointed_objects
	;invoke JmpPatch, 0041A6EDh, addr Hide_shadow ;Не актуально
	;invoke JmpPatch, 00420272h, addr opoint_kind
	invoke JmpPatch, 0042EE17h, addr Shaker	      ;Shake_It_Baby!
	;===================================================


	;=============itr kind(itrkind.inc)=================
	;invoke JmpPatch, 004297F0h, addr itr_kind8
	;invoke JmpPatch, 004297F5h, addr itr_kind8_2
	;===================================================


	;=============itr effects(itreff.inc)===============
	;invoke JmpPatch, 004297FAh, addr itr_effect_fall
	;invoke JmpPatch, 0042FCB1h, addr itr_effect
	;===================================================

	;=================states(states.inc)================
	invoke JmpPatch, 0041F656h, addr State8xxx
	;invoke JmpPatch, 0041408Bh, addr State_Turning
	;invoke JmpPatch, 004177B9h, addr Hit_teammates
	;==================================================
	
	;===================Loading Text(text.inc)============
	;invoke JmpPatch, 00424352h, addr Loading
	;invoke WriteMem, 00424357h, addr doubleNOP,2
	;=====================================================
	
	;====================Armor(armor.inc)====================
	;invoke JmpPatch,0042E67Fh, addr Armor_Knight 	;knight armor
	;invoke WriteMem,0042E684h, addr oneNOP,1
	;invoke JmpPatch,0042E6ECh, addr Armor_Louis		;louis armor
	;invoke WriteMem,0042E7F1h, addr FourNOP,4
	;invoke JmpPatch,0042E7CEh, addr Armor_Julian	;julian armor
	;=======================================================
	
	;============Perspective Tag(perspective.inc)===========
	;invoke JmpPatch, 004214D7h, addr perspective		
	;invoke JmpPatch, 0042D5CEh, addr perspective2
	;invoke JmpPatch, 0042D30Bh, addr perspective3
	;invoke JmpPatch, 0042D473h, addr perspective4
	;=====================================================
	
	
	;===============Window Properities(window.inc)=========
	invoke JmpPatch, 00401B3Ch, addr Window_Size_2	 	
	invoke JmpPatch, 00401007h, addr Window_Size_3
	invoke JmpPatch, 00401050h, addr Window_Size_4
	invoke JmpPatch, 0042386Dh, addr Window_Size_5
	invoke JmpPatch, 0043F03Dh, addr Window_Size_6
	invoke JmpPatch, 0043F08Bh, addr Window_Size_7
	invoke JmpPatch, 0041A0AEh, addr Window_Size	
	invoke JmpPatch, 0041A1DBh, addr Window_Size_8
	;===================================================

	call AI
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
	invoke JmpPatch, 00404C12h, addr AI_Davis
	invoke WriteMem, 00404C17h, addr doubleNOP,2
	;Sorcerer AI
	invoke JmpPatch, 0040555Dh, addr AI_Sorcerer
	invoke WriteMem, 00405562h, addr doubleNOP,2
	;=============================================
	
	ret
AI endp



End DllEntryPoint