.Data
comp_back1	dd 004326EAh
comp_back2  dd 004326DEh

F7_rework_back dd 0042188Bh

F9_deny 		dd 00421828h
F9_proceed 		dd 0042181Eh
F9_rework_back  dd 004217EAh

F6_back_way1 dd 00416E7Fh
F6_back_way2 dd 00416E77h
F7_back_way1 dd 00416ECFh
F7_back_way2 dd 00416EC7h
F8_back_way1 dd 00416F2Fh
F8_back_way2 dd 00416F27h
F9_back_way1 dd 00416F81h
F9_back_way2 dd 00416F79h

act_rework_back dd 0043778Eh

Ind_Stages 	 dd 0042A041h
Change_Team  dd 0042A843h

Results_Delay 	dd 0041DB58h

limit_b_back	dd 0041FB28h
limit_b_back2 	dd 0041FA93h
limit_b_back3 	dd 0041FAD3h
 
shake_back 	dd 0042EE2Fh

spawner	dd 0043766Fh

db3_fix  dd 00423B2Dh

DropBoxLPfixb	dd 0043EA16h

.Code



comparator proc

		CMP [replay_switch],TRUE
		JE [skip]

		CMP EAX,DWORD PTR DS:[44F620h]
		JE SHORT [skip]
		JMP [comp_back2]
skip: 
		JMP [comp_back1]

comparator endp



F7_rework proc

		MOV EAX,DWORD PTR DS:[ESI]
		MOV EDX,DWORD PTR DS:[EAX+368h]
		MOV EDX,DWORD PTR DS:[EDX+0B0h]
		CMP EDX,0
		JLE [skip]
		
		start_hp_max:
		CMP DWORD PTR DS:[EDX+4],0
		JLE [start_hp]
		MOV ECX,DWORD PTR DS:[EDX+4]
		MOV DWORD PTR DS:[EAX+304h],ECX
		JMP [start_hp]
		skip_hp_max:
		MOV ECX,1F4h
		MOV DWORD PTR DS:[EAX+304h],ECX
		
		start_hp:
		CMP DWORD PTR DS:[EDX+0],0
		JLE [skip]
		MOV ECX,DWORD PTR DS:[EDX+0]
		MOV DWORD PTR DS:[EAX+2FCh],ECX
		MOV DWORD PTR DS:[EAX+300h],ECX
		JMP [start_hp_exist]

skip:
		MOV EAX,DWORD PTR DS:[ESI]
		MOV EDX,DWORD PTR DS:[EAX+304h]
		MOV DWORD PTR DS:[EAX+300h],EDX
		MOV EAX,DWORD PTR DS:[ESI]
		MOV ECX,DWORD PTR DS:[EAX+300h]
		MOV DWORD PTR DS:[EAX+2FCh],ECX
start_hp_exist:
		MOV ECX,1F4h ; regular value

		MOV EDX,DWORD PTR DS:[ESI]
		MOV EAX,DWORD PTR DS:[EDX+190h]
		CMP EAX,0
		JLE [no_max_mp]
		
		
			CMP DWORD PTR DS:[EAX+60h],0 ; max mp
			JLE [no_max_mp]
			MOV ECX,DWORD PTR DS:[EAX+60h] ; max mp
		
			CMP DWORD PTR DS:[EAX+70h],0 ; mana cap
			JLE [no_mp_cap]
			MOV ECX,DWORD PTR DS:[EAX+70h] ; mana cap
		
		no_max_mp:
		no_mp_cap:
		MOV DWORD PTR DS:[EDX+308h],ECX
		MOV DWORD PTR DS:[EDX+120h],0 ; resets poison
		MOV DWORD PTR DS:[EDX+12Ch],0 ; resets weak
		MOV DWORD PTR DS:[EDX+130h],0 ; resets silence
		MOV DWORD PTR DS:[EDX+134h],0 ; resets slow
		MOV DWORD PTR DS:[EDX+138h],0 ; resets confuse
		
		CMP DWORD PTR DS:[450C1Ch],66h
		JNE [no_life]
		
		PUSH EAX
		XOR EAX,EAX
		MOV EDX,1166E4h
		MOV ECX,6Eh
		MOV DWORD PTR DS:[EDX*4+EAX],ECX
		INC EAX
		MOV ECX,6F65h
		MOV DWORD PTR DS:[EDX*4+EAX],ECX
		ADD EAX,2
		MOV ECX,6172h
		MOV DWORD PTR DS:[EDX*4+EAX],ECX
		POP EAX

no_life:
		MOV DWORD PTR DS:[450BDCh],0 ; resets Round Finisher timer (bug from old LF2 versions)
		JMP [F7_rework_back]


F7_rework endp

F9_rework proc
		
		;MOV EAX,DWORD PTR DS:[EDX+6F4h] ; get id
		;CMP EAX,123 ; check if it's beer
		;JE [F9_save] ; saves beer for a weekend!
		
		; you can delete or comment any pair of lines to prevent original item breaking after F9
		MOV EAX,DWORD PTR DS:[EDX+6F8h] ; get type
		CMP EAX,0 ; characters
		JE SHORT [F9_save] ; this is fixing problem of killing enemies in Stages by pressing F9
		CMP EAX,1 ; breaks Stick, Knife, Boomerang, Hoe
		JE SHORT [F9_kill]
		CMP EAX,2 ; breaks heavies: Box, Stone and Louis Armor
		JE SHORT [F9_kill]
		CMP EAX,4 ; breaks Baseball
		JE SHORT [F9_kill]
		CMP EAX,6 ; break Milk and Bear
		JE SHORT [F9_kill]
     	JMP [F9_rework_back]

F9_kill:
		JMP [F9_proceed]
F9_save:
		JMP [F9_deny]				

		
F9_rework endp




; "Fn_custom_modes" procedures, where may be:
; 0 - VS mode
; 1 - Stage mode
; 2 - 1 on 1
; 3 - 2 on 2
; 4 - Battle Mode
; 5 - Demo
; You can customize F-keys rights below 
F6_custom_modes proc

		MOV ECX,1
		CMP DWORD PTR DS:[EAX],0 ;VS
		JE SHORT [F6_custom_back]
		CMP DWORD PTR DS:[EAX],1 ;Stage
		JE SHORT [F6_custom_back]
		; CMP DWORD PTR DS:[EAX],4 ; this example allows Battle Mode, remove comments to enable
		; JE SHORT [F6_custom_back] ; keep it, remove comments to enable
		JMP [F6_back_way2]

F6_custom_back:
		JMP [F6_back_way1]

F6_custom_modes endp


F7_custom_modes proc
		MOV ECX,1
		CMP DWORD PTR DS:[EAX],0 ;VS
		JE SHORT [F7_custom_back]
		CMP DWORD PTR DS:[EAX],1 ;Stage
		JE SHORT [F7_custom_back]
		; CMP DWORD PTR DS:[EAX],4 ; this example allows Battle Mode, remove comments to enable
		; JE SHORT [F6_custom_back] ; keep it, remove comments to enable
		JMP [F7_back_way2]

F7_custom_back:
		JMP [F7_back_way1]

F7_custom_modes endp

F8_custom_modes proc
		MOV ECX,1
		CMP DWORD PTR DS:[EAX],0 ;VS
		JE SHORT [F8_custom_back]
		CMP DWORD PTR DS:[EAX],1 ;Stage
		JE SHORT [F8_custom_back]
		; CMP DWORD PTR DS:[EAX],4 ; this example allows Battle Mode, remove comments to enable
		; JE SHORT [F6_custom_back] ; keep it, remove comments to enable
		JMP [F8_back_way2]

F8_custom_back:
		JMP [F8_back_way1]

F8_custom_modes endp

F9_custom_modes proc
		MOV ECX,1
		CMP DWORD PTR DS:[EAX],0 ;VS
		JE SHORT [F9_custom_back]
		CMP DWORD PTR DS:[EAX],1 ;Stage
		JE SHORT [F9_custom_back]
		; CMP DWORD PTR DS:[EAX],4 ; this example allows Battle Mode, remove comments to enable
		; JE SHORT [F6_custom_back] ; keep it, remove comments to enable
		JMP [F9_back_way2]

F9_custom_back:
		JMP [F9_back_way1]

F9_custom_modes endp

act_rework proc

		MOV ECX,DWORD PTR DS:[EAX+368h]
		MOV ECX,DWORD PTR DS:[ECX+6F8h]
		XOR EDX,EDX
		CMP ECX,0
		JE SHORT [allowed]
		CMP ECX,1
		JE SHORT [allowed]
		CMP ECX,2
		JE SHORT [allowed]
		CMP ECX,3
		JE SHORT [allowed]
		CMP ECX,4
		JE SHORT [allowed]
		CMP ECX,5
		JE SHORT [allowed]
		CMP ECX,6
		JE SHORT [allowed]
		MOV DWORD PTR DS:[EAX+8h],EDX
		MOV DWORD PTR DS:[EAX+364h],EDX
		MOV DWORD PTR DS:[EAX+14h],-12Ch
		FILD DWORD PTR DS:[EAX+14h]
		FSTP QWORD PTR DS:[EAX+60h]
	skip_act:
		JMP [finish]
		
allowed:
		PUSH ECX 							; bug-fix of floating bottles
		
		MOV DWORD PTR DS:[EAX+8],14h
		MOV EDX,DWORD PTR DS:[450BB4h]
		ADD EDX,-31Ah
		CMP DWORD PTR DS:[EAX+10h],EDX
		SETG CL
		MOV BYTE PTR DS:[EAX+80h],CL
		MOV ECX,DWORD PTR DS:[EBX+0C8h]
		
		CMP ECX,800 ; frame limit, ~ xxx yyy zz
		JL [regular_act] ; if regular type - skip
		PUSH EAX ;reserve object
		PUSH EBX ;reserve level
		
		PUSH 64h ; 100
		PUSH ECX ; reserve act
		CALL DWORD PTR [random] ; result in EAX ~ EDX
		MOV ECX, EAX ; result of random goes to ECX
		POP EAX ; restore act in EAX
		CDQ
		MOV EBX, 100
		IDIV EBX ; divide ACT on 100, gets %
		CMP EDX, ECX
		JL [not_enough_percentage]
		
		CDQ 
		MOV EBX, 1000
		IDIV EBX ; gets yyy in ECX
		ADD ESP,4
		POP EBX
		POP EAX
		MOV DWORD PTR DS:[EAX+70h],EDX
		JMP [after_act]
		
not_enough_percentage:
		CDQ 
		MOV EBX, 1000
		IDIV EBX ; gets xxx in EDX
		MOV ECX, EAX
		ADD ESP,4
		POP EBX
		POP EAX
		MOV DWORD PTR DS:[EAX+70h],ECX
		JMP [after_act]
		
regular_act:
		MOV DWORD PTR DS:[EAX+70h],ECX

after_act:	
		MOV DWORD PTR DS:[EAX+364h],5
		MOV ECX,DWORD PTR DS:[EBX+0CCh]
		MOV DWORD PTR DS:[EAX+14h],ECX
		FILD DWORD PTR DS:[EAX+14h]
		FSTP QWORD PTR DS:[EAX+60h]
		FLDZ
		FSTP QWORD PTR DS:[EAX+48h]
		
		POP ECX   							; bug-fix of floating bottles
		CMP ECX,6 							; bug-fix of floating bottles
		JNE [finish]						; bug-fix of floating bottles
		MOV DWORD PTR DS:[EAX+14h],-12Ch	; bug-fix of floating bottles
		FILD DWORD PTR DS:[EAX+14h]			; bug-fix of floating bottles
		FSTP QWORD PTR DS:[EAX+60h]			; bug-fix of floating bottles

finish:
		JMP [act_rework_back]


act_rework endp

Independent_Stages proc
	
repeatJG:
		LODS DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[EAX+364],0 ; was EDX and always had 1 here, 0 is hack for now
		DEC ECX
		JG SHORT [repeatJG]
		
 		JMP [Ind_Stages]
 		
Independent_Stages endp


ChangeAble_teams proc

		CMP [Unlock_Teams],TRUE
		JNE [Lock_Teams]

		MOV ECX, 2
		MOV DWORD PTR DS:[EBP*4+451288h],ECX
		JMP [Change_Team]
		
Lock_Teams:
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,1
		NEG ECX
		SBB ECX,ECX
		ADD ECX,3
		JMP [Change_Team]


		

ChangeAble_teams endp

Result_Sound_Delay proc

		MOV ECX,DWORD PTR DS:[450BDCh]
		ADD ECX,1
		CMP ECX,50
		MOV DWORD PTR DS:[450BDCh],ECX
		JMP [Results_Delay]

Result_Sound_Delay endp








main_Shake proc
 		
 		XOR EAX,EAX
 		MOV AL, BYTE PTR DS:[shake_value]
		CMP DWORD PTR DS:[EBX+0B4h],0
		JL SHORT [victim]
		MOV DWORD PTR DS:[EBX+0B4h],EAX
victim:
		MOV ECX,DWORD PTR SS:[ESP+0Ch]
		NEG EAX
		MOV DWORD PTR DS:[EDI+0B4h],EAX
		JMP [shake_back]

main_Shake endp



Stage_Spawn_Coords proc

		CMP DWORD PTR DS:[EBX+0B0h],100000 ; F4240, filter 1xxxxx
		JGE SHORT [no_random]

random_on:
		ADD EAX,DWORD PTR DS:[EBX+0B0h] ; С учетом рандома
		ADD ESP,8
		MOV EDX,EAX
		JMP [spawner]	

no_random:		
		MOV EAX,DWORD PTR DS:[EBX+0B0h] ; Без учета рандома
		SUB EAX,100000
		ADD ESP,8
		MOV EDX,EAX
		JMP [spawner]

Stage_Spawn_Coords endp


dropbox3_fix proc

		CMP DWORD PTR DS:[EAX+1Eh],002E002Eh
		JNE [skip]
		
		MOV DWORD PTR DS:[EAX+1Eh],002E0031h
		MOV DWORD PTR DS:[EAX+22h],0066006Ch
		MOV DWORD PTR DS:[EAX+26h],00000069h

skip:
		PUSH EBX
		PUSH ESI
		PUSH EDI
		PUSH EBP
		MOV EBP,ESP
		JMP [DropBoxLPfixb]


dropbox3_fix endp























