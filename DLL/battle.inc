.Data

defence1	dd 004394D3h
crazyness	dd 0043A808h

.Code

defence proc 

		MOV EAX,DWORD PTR DS:[451BA8h]
		CMP DWORD PTR DS:[4513B4h],0
		JE SHORT jmp1
		MOV EDX,[battle_step]
		ADD DWORD PTR DS:[EAX*4+44D758h],EDX
		MOV EDX,[battle_limit]
		CMP DWORD PTR DS:[EAX*4+44D758h],EDX
		JLE SHORT jmp1
		MOV DWORD PTR DS:[EAX*4+44D758h],64h
		
jmp1:	CMP DWORD PTR DS:[4513B8h],0
		JE SHORT jmp2
		MOV EDX,[battle_step]
		NEG EDX
		ADD DWORD PTR DS:[EAX*4+44D758h],EDX
		CMP DWORD PTR DS:[EAX*4+44D758h],64h
		JGE SHORT jmp2
		MOV EDX,[battle_limit]
		MOV DWORD PTR DS:[EAX*4+44D758h],EDX

jmp2:	JMP [defence1]

defence endp


battle_diffucult proc


		CMP DWORD PTR DS:[458428h],1 ; check cheat
		JE [cheat_up]
		
cheat_down:
		SUB DWORD PTR DS:[450C30h],1
		
		CMP DWORD PTR DS:[450C30h],-1
		JNE [proceed]
		
		MOV DWORD PTR DS:[450C30h],2
		
		JMP [crazyness]

cheat_up:		
		SUB DWORD PTR DS:[450C30h],1
		
		CMP DWORD PTR DS:[450C30h],-2
		JNE [proceed]
		
		MOV DWORD PTR DS:[450C30h],2

proceed:		
		JMP [crazyness]
		

battle_diffucult endp












