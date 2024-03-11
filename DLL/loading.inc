.data
fix_hidden   db "hidden:",00
fix_silence  db "silence:",00
fix_slow	 db "slow:",00
fix_confuse  db "confuse:",00
fix_sound    db "sound:",0000
weapon_hp		db "weapon_hp:",00
new_pierce 	db "pierce:",00
new_shp 	db "shp:",00
new_smp 	db "smp:",00

right_data dd 0040F2EBh
wrong_data dd 0040F2EDh

Player_Stat dd 0042D50Ch
Com_AI_Stat dd 0042D400h



.code


Loading_Rework proc

		LEA EDX,DWORD PTR SS:[EBP+90h]
		LEA EDI,[weapon_hp]           	; заменяем MOV на LEA, т.к. нам нужен адрес переменной, а не она сама
										; это из-за того, что в регистр просто не поместится вся переменная
		LEA ESI,DWORD PTR SS:[ESP+70h]
		MOV ECX,0Bh
		REPE CMPSB [EDI],[ESI]
		; если не оно, переходим к проверке наших атрибутов
		JNZ [shp]
		JMP [right_data]
shp:
		LEA EDX,DWORD PTR SS:[EBP+0B0h] 
		LEA EDI,[new_shp]           	
		LEA ESI,DWORD PTR SS:[ESP+70h]
		MOV ECX,4
		REPE CMPSB [EDI],[ESI]
		JNZ [smp]
		JMP [right_data]
smp:
		LEA EDX,DWORD PTR SS:[EBP+0B4h] 
		LEA EDI,[new_smp]           	
		LEA ESI,DWORD PTR SS:[ESP+70h]
		MOV ECX,4
		REPE CMPSB [EDI],[ESI]
		JNZ [wrong]
		JMP [right_data]

wrong:
		JMP [wrong_data]

		
Loading_Rework endp








Player_Stats proc

		MOV EDX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[EDX+308h],0C8h ; стартовое число маны
		
		PUSH EDX
		PUSH EAX
		PUSH ECX
		
		MOV ECX, DWORD PTR DS:[EDX+368h]
		MOV EAX, DWORD PTR DS:[ECX+0B0h]
		CMP EAX, 0
		JLE [skip_shp]
		MOV DWORD PTR DS:[EDX+2FCh],EAX
		MOV DWORD PTR DS:[EDX+300h],EAX
		MOV DWORD PTR DS:[EDX+304h],EAX
		skip_shp:
		
		MOV ECX, DWORD PTR DS:[EDX+368h]
		MOV EAX, DWORD PTR DS:[ECX+0B4h]
		CMP EAX, 0
		JLE [skip_smp]
		MOV DWORD PTR DS:[EDX+308h],EAX
		skip_smp:
		
		POP ECX
		POP EAX
		POP EDX
		
		CMP DWORD PTR DS:[EAX],1 ; если режим стадий, то перезапись на 500 маны
		JNZ SHORT [stage_m]
		MOV ECX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[ECX+308h],1F4h
stage_m:
		JMP [Player_Stat]

Player_Stats endp






Computer_Stats proc

		MOV EDX,DWORD PTR DS:[ESI+28h]
		MOV DWORD PTR DS:[EDX+308h],0C8h
		
		PUSH EDX
		PUSH EAX
		PUSH ECX
		
		MOV ECX, DWORD PTR DS:[EDX+368h]
		MOV EAX, DWORD PTR DS:[ECX+0B0h]
		CMP EAX, 0
		JLE [skip_shp]
		MOV DWORD PTR DS:[EDX+2FCh],EAX
		MOV DWORD PTR DS:[EDX+300h],EAX
		MOV DWORD PTR DS:[EDX+304h],EAX
		skip_shp:
		
		MOV ECX, DWORD PTR DS:[EDX+368h]
		MOV EAX, DWORD PTR DS:[ECX+0B4h]
		CMP EAX, 0
		JLE [skip_smp]
		MOV DWORD PTR DS:[EDX+308h],EAX
		skip_smp:
		
		POP ECX
		POP EAX
		POP EDX
		
		CMP DWORD PTR DS:[EAX],1 ; если режим стадий, то перезапись на 500 маны
		JNZ SHORT [stage_m]
		MOV ECX,DWORD PTR DS:[ESI+28h]
		MOV DWORD PTR DS:[ECX+308h],1F4h
stage_m:
		JMP [Com_AI_Stat]

Computer_Stats endp












