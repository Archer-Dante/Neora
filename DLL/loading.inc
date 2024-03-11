.data
fix_hidden   db "hidden:",00
fix_silence  db "silence:",00
fix_slow	 db "slow:",00
fix_confuse  db "confuse:",00
fix_sound    db "sound:",0000
weapon_hp		db "weapon_hp:",00
new_pierce 	db "pierce:",00
base_hp 	db "base_hp:",00

right_data dd 0040F2EBh
wrong_data dd 0040F2EDh

.code


Loading_Rework proc

		LEA EDX,DWORD PTR SS:[EBP+90h]
		LEA EDI,[weapon_hp]           	; заменяем MOV на LEA, т.к. нам нужен адрес переменной, а не она сама
										; это из-за того, что в регистр просто не поместится вся переменная
		LEA ESI,DWORD PTR SS:[ESP+70h]
		MOV ECX,0Bh
		REPE CMPSB [EDI],[ESI]
		; если не оно, переходим к проверке наших атрибутов
		JNZ [new_base_hp]
		JMP [right_data]

new_base_hp:
		LEA EDX,DWORD PTR SS:[EBP+0B0h] 
		LEA EDI,[base_hp]           	
		LEA ESI,DWORD PTR SS:[ESP+70h]
		MOV ECX,9
		REPE CMPSB [EDI],[ESI]
		JNZ [wrong]
		JMP [right_data]

wrong:
		JMP [wrong_data]

		
Loading_Rework endp
