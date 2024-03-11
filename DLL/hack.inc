.Data
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
Change_Team  dd 0042A84Ah

Results_Delay 	dd 0041DB58h

limit_b_back	dd 0041FB28h
limit_b_back2 	dd 0041FA93h
limit_b_back3 	dd 0041FAD3h
 

.Code



F7_rework proc

		MOV EAX,DWORD PTR DS:[ESI]
		MOV ECX,1F4h
		CMP DWORD PTR DS:[EAX+304h],ECX
		JGE [skip]
		MOV DWORD PTR DS:[EAX+304h],ECX

skip:
		MOV EAX,DWORD PTR DS:[ESI]
		MOV EDX,DWORD PTR DS:[EAX+304h]
		MOV DWORD PTR DS:[EAX+300h],EDX
		MOV EAX,DWORD PTR DS:[ESI]
		MOV ECX,DWORD PTR DS:[EAX+300h]
		MOV DWORD PTR DS:[EAX+2FCh],ECX
		MOV EDX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[EDX+308h],1F4h
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

		MOV ECX, 2
		MOV DWORD PTR DS:[EBP*4+451288h],ECX
		JMP [Change_Team]

ChangeAble_teams endp

Result_Sound_Delay proc

		MOV ECX,DWORD PTR DS:[450BDCh]
		ADD ECX,1
		CMP ECX,50
		MOV DWORD PTR DS:[450BDCh],ECX
		JMP [Results_Delay]

Result_Sound_Delay endp







limit_breaker proc

			MOV ECX,DWORD PTR DS:[ESI+304h]
			CMP ECX,DWORD PTR DS:[ESI+2FCh]
			JGE SHORT [j1]
			MOV DWORD PTR DS:[ESI+2FCh],ECX
		j1:
			CMP ECX,DWORD PTR DS:[ESI+300h]
			JGE SHORT [j2]
			MOV DWORD PTR DS:[ESI+300h],ECX
		j2:
			MOV ECX,1F4h
			MOV EAX,DWORD PTR DS:[ESI+308h]
			CMP EAX,ECX
			JG SHORT [j3]
			TEST EAX,EAX
			JGE SHORT [j4]
			XOR ECX,ECX
		j3:
			MOV DWORD PTR DS:[ESI+308h],ECX
		j4:
			JMP [limit_b_back]

limit_breaker endp



limit_breaker2 proc

			MOV EAX,DWORD PTR DS:[ESI+300h] ; dark hp
			JMP [limit_b_back2]

limit_breaker2 endp


limit_breaker3 proc

			MOV ECX,DWORD PTR DS:[ESI+300h] ; dark hp
			JMP [limit_b_back3]

limit_breaker3 endp








