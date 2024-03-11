.386
.Model Flat, StdCall
OPTION CASEMAP :NONE

include C:\masm32\include\windows.inc
include C:\masm32\include\masm32.inc
include C:\masm32\include\user32.inc
include C:\masm32\include\kernel32.inc
include C:\masm32\include\debug.inc
includelib C:\masm32\lib\masm32.lib
includelib C:\masm32\lib\user32.lib
includelib C:\masm32\lib\kernel32.lib
includelib C:\masm32\lib\debug.lib

include lf2.inc
include addresses.inc
include itrkind.inc
include itreff.inc
include states.inc
include window.inc
include battle.inc
include regen.inc
include cursor.inc
include external.inc
include UI.inc
include hack.inc
include bodies.inc
include loading.inc
include time.inc 
include rpg.inc 
include event.inc
include stage.inc

.data
memAlloc dd ?
solAlloc dd ?
; as long as you're using Neora you're agreed and accept rule to keep this string as it is 
copycat  db "Neora Engine by Archer-Dante aka EdL",00


		;====================================================================================
		;================================= Configuration Block ==============================
		;====================================================================================
		GameName		db "LF2: Neora Engine 2.09",00 ; Name of the Game Window
		win_width   		dd 794		; Game window width  in pixels. "794" is default
		win_height  		dd 550 		; Game window height in pixels. "550" is default
		
		shake_value 		db 3 			; Value of both Shaking effect on attack. "3" is default
		
		slow_motion 		db 1 			; Slow Motion at the end of Round. (1 - on, 0 - off)
		slow_power  		dd 65 		; "65" is recommend value of slow power
		
		replay_switch		db 1			; Makes game Always counts replay file as valid. (1 - on, 0 - off)
		
		battle_limit		dd 1000		; Battle Mode defence limit. (ex.300 = 3.0), "300" is default
		battle_step		dd 100		; Increasing and Decreasing step of defence change (ex.50 = 0.5), "50" is default
		
		Menu_Picture_R	dd 0			; Resets CHARMENU.png picture coords to 0 by x\y axis. (1 - on, 0 - off)
		Unlock_Teams		dd 1			; Allows to change Team in Stage Mode. (1 - on, 0 - off)
		F7_for_dead		dd 1			; Allows to use F7 after round ends. (1 - on, 0 - off)
		;====================================================================================

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

	;=============itr kind(itrkind.inc)=================
	invoke JmpPatch, 0042FFF8h, addr itr_kind8
	invoke JmpPatch, 00417526h, addr itr_kind8_types
	invoke JmpPatch, 00417A6Eh, addr itr_specials
	;===================================================

	;=============itr effects(itreff.inc)===============
	invoke JmpPatch, 0042F54Ah, addr itr_effect_1xxx_to_9xxx 
	invoke JmpPatch, 0042E90Fh, addr effect50 			; contains part of Untouchable work
	;===================================================

	;=================states(states.inc)================
	invoke JmpPatch, 0041F656h, addr State8xxx ; 140-frameless fix (+id list for +140)
	invoke JmpPatch, 0041F603h, addr StateMore ; Set X-coord, Y-coord, Z-coord, TimeStop State and more
	invoke JmpPatch, 0041334Ah, addr StateTurn3x ; Turning State 30, 31
	invoke JmpPatch, 0042EC9Eh, addr State9xxx ; Go to XXX Frame if hit something. XXX from 0 to 799
	;==================================================

	;===============Window Properities(window.inc)=========
	invoke JmpPatch, 00401B85h, addr Application_Name
	invoke WriteMem, 00401B9Ch, addr oneNOP,7 ; Annoying Karter

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
	
	;=============== Stage (stage.inc)=================
	invoke JmpPatch, 0042E6B0h, addr better_criminals
	;===================================================

	;=============== Replays (replay.inc)===============
	invoke JmpPatch, 004326D6h, addr comparator	 	
	;===================================================	
	
	;=============== Battle Mode (battle.inc)===========
 	invoke JmpPatch, 0043947Fh, addr defence			; enhance defence limits 
 	invoke JmpPatch, 0043A7F6h, addr battle_diffucult	; allows to choose CRAZY! in Battle Mode
	;===================================================	
	
	;=============== Regen (regen.inc)==================
	invoke JmpPatch, 0041F9E2h, addr hp_regen
	invoke WriteMem, 0041F9C3h, addr oneNOP,14			; removes original HP to Dark HP binding (part 1)
	invoke WriteMem, 0041F9D1h, addr oneNOP,14			; removes original HP to Dark HP binding (part 2)
	invoke WriteMem, 0041F9DFh, addr oneNOP,3			; removes original HP to Dark HP binding (part 3)

	invoke JmpPatch, 0041FA48h, addr mana_regen	 	
	invoke WriteMem, 0041FA4Dh, addr oneNOP,15
	invoke WriteMem, 0041FA5Ch, addr oneNOP,15
	invoke WriteMem, 0041FA6Bh, addr oneNOP,15
	invoke WriteMem, 0041FA7Ah, addr oneNOP,14
	invoke WriteMem, 0041FA89h, addr oneNOP,15
	invoke WriteMem, 0041FA98h, addr oneNOP,15
	invoke WriteMem, 0041FAA7h, addr oneNOP,15
	invoke WriteMem, 0041FAB6h, addr oneNOP,15
	invoke WriteMem, 0041FAC5h, addr oneNOP,15
	invoke WriteMem, 0041FAD4h, addr oneNOP,15
	invoke WriteMem, 0041FAE3h, addr oneNOP,15
	invoke WriteMem, 0041FAF2h, addr oneNOP,15
	invoke WriteMem, 0041FB01h, addr oneNOP,15
	invoke WriteMem, 0041FB10h, addr oneNOP,15
	invoke WriteMem, 0041FB1Fh, addr oneNOP,9
	
	invoke CallPatch,00418223h, addr bottle_limit
	invoke CallPatch,00418154h, addr bottle_limit
	
	invoke JmpPatch, 004370FEh, addr stage_refill	 
	invoke WriteMem, 00437103h, addr oneNOP,5
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
	invoke JmpPatch, 0040C363h, addr spark
	;===================================================

	;=============== UI Manipulation (UI.inc)===========
	invoke WriteMem, 0041AF3Ah, addr opacity,2 ; Frame
	invoke WriteMem, 0042A5D2h, addr opacity,2 ; RFace first phase
	invoke WriteMem, 0042A53Fh, addr opacity,2 ; Character Faces
	invoke WriteMem, 0042BE93h, addr opacity,2 ; ???
	invoke WriteMem, 0042BDEBh, addr opacity,2 ; ???
	invoke WriteMem, 0042AFA2h, addr opacity,2 ; ???
	invoke WriteMem, 0042BB5Dh, addr opacity,2 ; ???
	
	invoke WriteMem, 0041AF85h, addr opacity,2 ; small icons in status-bar
	invoke WriteMem, 0042A415h, addr opacity,2 ; CMA.png + CMA2.png
	invoke WriteMem, 0042A444h, addr opacity,2 ; ???
	invoke WriteMem, 0042AAA0h, addr opacity,2 ; ???
	invoke WriteMem, 0042AB09h, addr opacity,2 ; RFace second phase
	
	;invoke JmpPatch, 0041B01Fh, addr HP_bars_change
	
	invoke JmpPatch, 0041AF20h, addr total_bar_rework ; complete rehook of original game bar-draw procedure
	
	invoke WriteMem, 0041F523h, addr numbersFix,1 ; fix debug info in corner
	;===================================================

	;===================================================
			CMP [Menu_Picture_R],TRUE
			JNE [no_ResetCoord]
	invoke WriteMem, 0042A1E1h, addr ResetCoord,2 ; resets CHARMENU coords to zero
	invoke WriteMem, 0042A1E3h, addr ResetCoord,2 ; resets CHARMENU coords to zero
			no_ResetCoord:
	;===================================================

	;=============== Hacked Regulars (hack.inc)==========
	;invoke JmpPatch, 00416E6Dh, addr F6_custom_modes ; Allows F6 in Stage mode (or custom list)
	;invoke JmpPatch, 00416EBDh, addr F7_custom_modes ; Allows F7 in Stage mode (or custom list)
	;invoke JmpPatch, 00416F1Dh, addr F8_custom_modes ; Allows F8 in Stage mode (or custom list)
	;invoke JmpPatch, 00416F71h, addr F9_custom_modes ; Allows F9 in Stage mode (or custom list)
	
	invoke JmpPatch, 0042184Eh, addr F7_rework  ; now cures Poison, Weak, Silence and Confuse
	invoke JmpPatch, 004217D0h, addr F9_rework  ; now is does NOT killing characters if used not in VS
												; also there is a filter by ID or type, if you're 
												; using item-key-objects in your maps or stages

	invoke JmpPatch, 00437719h, addr act_rework  		; allows to use "act:" not only with type 0 and 5
	
			CMP [F7_for_dead],TRUE
			JNE [no_F7_after_end]	
	invoke WriteMem, 00416EE0h, addr oneNOP,9 			; Allows to use F7 after round ends, like in 1.9 version!
			no_F7_after_end:
	
	;invoke JmpPatch, 0042A037h, addr Independent_Stages    ; Makes All players be in Independent team
															; disable if u're using "ChangeAble_teams" (below)
															; and on the contrary
	invoke JmpPatch, 0042A837h, addr ChangeAble_teams 	; Allows players choose Team in Stage Mode
														; Must be disabled if u're using "Independent_Stages"
	invoke JmpPatch, 0041DB46h, addr Result_Sound_Delay  	; time before sound play after last fighter defeated
														 	; has regular LF2 value, so you can keep it work
	invoke JmpPatch, 0042EE0Eh, addr main_Shake	      	; Allows to change Shaking via Config Block
	
	invoke JmpPatch, 00437664h, addr Stage_Spawn_Coords
	
	invoke JmpPatch, 0043EA10h, addr dropbox3_fix		; fixes game crash after being affected by Dropbox 3+
	invoke WriteMem, 0043EA15h, addr oneNOP,1	
	
	invoke JmpPatch, 00413697h , addr heavy_walking_speed_fix		; fixes PDK bug
	invoke JmpPatch, 0041373Ch, addr heavy_walking_speedz_fix		; fixes PDK bug
	invoke JmpPatch, 00413A36h , addr heavy_running_speed_fix		; fixes PDK bug
	invoke JmpPatch, 00413A5Fh , addr heavy_running_speedz_fix		; fixes PDK bug
	;===================================================


	;==============body kinds(bodies.inc)===============
	;invoke JmpPatch, 0042E677h, addr weNeedMoarBodies
	;invoke WriteMem, 0042E67Ch, addr oneNOP,7
	;invoke JmpPatch, 0042E89Ah, addr untouchable
	;invoke JmpPatch, 0042E75Bh, addr bdy_rework
	
	
	
	
	;invoke JmpPatch, 00417879h, addr bdy_solo_hit_recall 	; allows game engine track which bdy of target was
															; attacked (for 1 target on hit)
	;invoke JmpPatch, 004179EEh, addr bdy_multi_hit_recall 	; allows game engine track which bdy of target was
															; attacked (for 2+ targets at once or multihit)
															
	invoke JmpPatch, 0042E756h, addr dmg_calc_rework ; makes resists and stats works on
	;===================================================




	;================ Memory Relocation ================
	;= don't change anything till u dunno what u doing =
	
	; this block sets free 81,82 and 83 bytes for use
	invoke WriteMem, 00417246h, addr MakeByte1,1
	invoke WriteMem, 00417226h, addr MakeByte1,1
	invoke WriteMem, 0041769Ah, addr MakeByte1,1
	invoke WriteMem, 00430975h, addr MakeByte1,1
	invoke WriteMem, 004176B7h, addr MakeByte1,1
	invoke WriteMem, 00412A7Eh, addr MakeByte2,1
	invoke WriteMem, 00430953h, addr MakeByte1,1
	invoke WriteMem, 00412CC6h, addr MakeByte1,1

	;===================================================
	
	;================ Loading Rework ================	
	invoke WriteMem, 00447F68h, addr fix_hidden,8     ; change "hiden:" to "hidden:" attribute                
	invoke WriteMem, 00447F80h, addr fix_silence,9	  ; change "manacle:" to "silence:" attribute
	invoke WriteMem, 00447FACh, addr fix_confuse,9	  ; change "confus:" to "confuse:" attribute
	invoke WriteMem, 0044860Ch, addr fix_sound,8	  ; change "respond:" to "sound:" attribute
	invoke WriteMem, 00448613h, addr cleaner,1		  ; memory fix
	
	invoke JmpPatch, 0040F2D3h, addr Loading_Rework
	invoke JmpPatch, 004110D2h, addr Loading_Rework_SlowAttr ; change "delay:" to "slow:" attribute (except armor)
	invoke JmpPatch, 0042D4EFh, addr Player_Stats	
	invoke JmpPatch, 0042D3E1h, addr Computer_Stats
	invoke JmpPatch, 00410795h, addr Loading_Rework_ohp		; adds "ohp:" attribute to opoint
	invoke JmpPatch, 004201E3h, addr ohp					; makes "ohp:" feature possible
	invoke JmpPatch, 004111D4h, addr Loading_Rework_bdy		; adds lots of features for bdy
	invoke JmpPatch, 00410EB8h, addr Loading_Rework_itr		; adds lots of features for itr	

	invoke JmpPatch, 00402402h, addr Initialization			; initializes everything in game since exe launch
	;===================================================

	;============== Time Tracing (time.inc) ============
	invoke JmpPatch, 0043D12Dh, addr FPS_rework 		; + adds slow motion in every round end on last hit
	invoke JmpPatch, 0041310Dh, addr TimeStop 			; TimeStop Engine
	invoke JmpPatch, 0041DD4Ah, addr TS_substactor		; part of TS Engine
	
	invoke JmpPatch, 0043D154h, addr TS_menu_fix        ; resets TS while game in menu
	invoke JmpPatch, 00421191h, addr TS_fire_disable	; disables flame particles while TimeStop
	invoke JmpPatch, 00407DCAh, addr TS_JanC1_disable	; removes Tail from Jan Chase while TS
	invoke JmpPatch, 0040DA72h, addr TS_Fa_disable_1	; fixes HP substract from Balls while TS
	invoke JmpPatch, 00408378h, addr TS_Fa_disable_2	; fixes HP substract from Balls while TS
	invoke JmpPatch, 0041A12Fh, addr TS_bg_stop_1 			; stops HK Coliseum BG
	invoke WriteMem, 0041A134h, addr oneNOP,4 				; fix code
	invoke JmpPatch, 0041A1BDh, addr TS_bg_stop_2 			; stops all another BGs
	;===================================================


	;==================   Real RPG   ===================
	;invoke JmpPatch, 00413F1Fh, addr all_stats_calculation ; calculates Stats and Resists in real time
	
	;invoke JmpPatch, 00413F1Fh, addr calculate_Max_MP
	;===================================================



	;===============================================================
	; All codes below made only for demo or experimental expirience
	; There nothing of public nor useful, so u can juse ignore it
	;===============================================================
	;=======================   Event Only   ========================
;	MOV DWORD PTR DS:[451160h],1 ; в стадию
;	MOV DWORD PTR DS:[450C30h],-1 ; только Crazy
;	
;	invoke CallPatch, 00432114h, addr lock_game_mode ; сразу перейти к выбору перса
;	
;	invoke WriteMem,  0042A4EBh, addr oneNOP, 6 ; отрубаем возможность вернуться назад
;	invoke WriteMem,  0042A4D7h, addr oneNOP, 12 ; отрубаем звук клика назад по меню
;	invoke WriteMem,  00429F9Bh, addr disable_menu_render, 1 ; отрубаем отрисовку меню (блик перехода)
;	
;	invoke JmpPatch,  0042D749h, addr only_crazy ; не даем менять сложность
	;===============================================================


	ret


DLLStartup endp





End DllEntryPoint