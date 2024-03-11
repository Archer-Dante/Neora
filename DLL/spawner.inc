.Data

spawner1	dd 0042D6A2h
spawner2	dd 0042D518h
spawner3	dd 0042D400h
spawner4	dd 0043766Fh


.Code

SpawnerBoth1 proc

		MOV ECX,DWORD PTR DS:[ESI]
		ADD ESP,8h
		ADD EAX,32h ; Можно заменить на "MOV EAX, N", где X - координата X, по которой должны спавниться игроки
		MOV DWORD PTR DS:[ECX+10h],EAX ; Если закомментить эту строку - спавн будет рандомный на всю ширину карты
		MOV EAX,DWORD PTR DS:[ESI]
		FILD DWORD PTR DS:[EAX+10h]
		FSTP QWORD PTR DS:[EAX+58h]
		
		JMP [spawner1]
		
SpawnerBoth1 endp

SpawnerPlayer1 proc

		ADD EAX,DWORD PTR DS:[EDI+4h]
		MOV EDX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[EDX+18h],EAX ; спавн игроков по Z. Можно заменить EAX на число, если хочется точной точки спавна
		MOV EAX,DWORD PTR DS:[ESI]	
		MOV DWORD PTR DS:[EAX+14h],0h ; спавн игроков по Y
		MOV EAX,DWORD PTR DS:[ESI]
		ADD ESP,10h
		FILD DWORD PTR DS:[EAX+10h] ; x ???
		FSTP QWORD PTR DS:[EAX+58h] ; x ???
		MOV EAX,DWORD PTR DS:[ESI]
		FILD DWORD PTR DS:[EAX+18h] ; z ???
		FSTP QWORD PTR DS:[EAX+68h] ; z ???
		MOV ECX,DWORD PTR DS:[ESI]
		FLDZ
		MOV EAX,DWORD PTR SS:[ESP+1Ch]
		FSTP QWORD PTR DS:[ECX+60h] ; y ???
		MOV EDX,DWORD PTR DS:[ESI]
		
ID_check:
		push ecx ; reserve
		push edx ; reserve
		MOV EDX,DWORD PTR DS:[ECX+368h] ; data-file
		MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID of object
		CMP EDX, 37h ; ID 55
		JE SHORT [Custom_Mp_Start]
		JMP [Regular_Mp_Start]

Custom_Mp_Start:
		pop edx ; reserve
		pop ecx ; reserve
		
		MOV DWORD PTR DS:[EDX+308h],0h ; стартовое число маны для игрока c ID 55
		JMP [Proceed]

Regular_Mp_Start:
		pop edx ; reserve
		pop ecx ; reserve
		
		MOV DWORD PTR DS:[EDX+308h],0C8h ; стартовое число маны для игрока - оригинал
		JMP [Proceed]

Proceed:		
		CMP DWORD PTR DS:[EAX],1h ; проверка, что если стадии, то ману давать сразу фулл
		JNZ SHORT [Get_Back]
		MOV ECX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[ECX+308h],1F4h ; стартовое число маны для режима стадий = 500

Get_Back:
		MOV EDX,DWORD PTR DS:[ESI]
		MOV DWORD PTR DS:[EDX+354h],EBX
		MOV EDI,EBP
		XOR EBP,EBP
		
		JMP [spawner2]

SpawnerPlayer1 endp




SpawnerCom1 proc

		ADD EAX,DWORD PTR DS:[EDI+4h]
		MOV EDX,DWORD PTR DS:[ESI+28h]
		MOV DWORD PTR DS:[EDX+18h],EAX ; спавн компов по Z. Можно заменить EAX на число, если хочется точной точки спавна
		MOV EAX,DWORD PTR DS:[ESI+28]
		MOV DWORD PTR DS:[EAX+14h],0h ; спавн компов по Y
		MOV EAX,DWORD PTR DS:[ESI+28h]
		ADD ESP,10h
		FILD DWORD PTR DS:[EAX+10h] ; x ???
		FSTP QWORD PTR DS:[EAX+58h] ; x ???
		MOV EAX,DWORD PTR DS:[ESI+28h]
		FILD DWORD PTR DS:[EAX+18h] ; z ???
		FSTP QWORD PTR DS:[EAX+68h] ; z ???
		MOV ECX,DWORD PTR DS:[ESI+28h]
		FLDZ
		MOV EAX,DWORD PTR SS:[ESP+1Ch]
		FSTP QWORD PTR DS:[ECX+60h]
		MOV EDX,DWORD PTR DS:[ESI+28h]
		
		
ID_check_Com:
		push ecx ; reserve
		push edx ; reserve
		MOV EDX,DWORD PTR DS:[ECX+368h] ; data-file
		MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID of object
		CMP EDX, 37h ; ID 55
		JE SHORT [Custom_Mp_Start_Com]
		JMP [Regular_Mp_Start_Com]		


Custom_Mp_Start_Com:
		pop edx ; reserve
		pop ecx ; reserve
		
		MOV DWORD PTR DS:[EDX+308h],0h ; стартовое число маны для компа c ID 55
		JMP [Proceed_Com]		

Regular_Mp_Start_Com:
		pop edx ; reserve
		pop ecx ; reserve
		
		MOV DWORD PTR DS:[EDX+308h],0C8h ; стартовое число маны для компа - оригинал
		JMP [Proceed_Com]
		
Proceed_Com:		
		CMP DWORD PTR DS:[EAX],1h ; проверка, что если стадии, то ману давать сразу фулл
		JNZ SHORT [Get_Back_Com]
		MOV ECX,DWORD PTR DS:[ESI+28h]
		MOV DWORD PTR DS:[ECX+308h],1F4h ; стартовое число маны для режима стадий = 500

Get_Back_Com:
		JMP [spawner3]

SpawnerCom1 endp






SpawnerComStages1 proc

		CMP DWORD PTR DS:[EBX+0B0h],100000 ; F4240, filter 1xxxxx
		JGE SHORT [no_random]

random_on:
		ADD EAX,DWORD PTR DS:[EBX+0B0h] ; С учетом рандома
		ADD ESP,8
		MOV EDX,EAX
		JMP [spawner4]	

no_random:		
		MOV EAX,DWORD PTR DS:[EBX+0B0h] ; Без учета рандома
		SUB EAX,100000
		ADD ESP,8
		MOV EDX,EAX
		JMP [spawner4]

SpawnerComStages1 endp




StartDataZ proc

		MOV ECX,1F4h
		MOV DWORD PTR DS:[ESI+3F8h],EAX
		MOV DWORD PTR DS:[ESI+2F4h],EAX
		MOV DWORD PTR DS:[ESI+2F8h],EAX
		MOV DWORD PTR DS:[ESI+354h],63h
		
		PUSH EDI
		CMP DWORD PTR DS:[44D020h],0
		JNE [regular_hp]
		MOV EDI,DWORD PTR DS:[ESI+368h]
		MOV EDI,DWORD PTR DS:[EDI+0B0h]
		CMP EDI,0
		JLE [regular_hp]
		MOV DWORD PTR DS:[ESI+2FCh],EDI ;hp
		MOV DWORD PTR DS:[ESI+300h],EDI ;darkred hp
		MOV DWORD PTR DS:[ESI+304h],EDI
		JMP [next1]
		regular_hp:
		MOV DWORD PTR DS:[ESI+304h],500
		MOV DWORD PTR DS:[ESI+2FCh],ECX ;hp
		MOV DWORD PTR DS:[ESI+300h],ECX ;darkred hp
next1:	POP EDI

		MOV DWORD PTR DS:[ESI+308h],500
		MOV DWORD PTR DS:[ESI+360h],EAX
		MOV DWORD PTR DS:[ESI+324h],EAX
		MOV DWORD PTR DS:[ESI+328h],EAX
		MOV DWORD PTR DS:[ESI+32Ch],EAX
		MOV DWORD PTR DS:[ESI+33Ch],EAX

		MOV DWORD PTR DS:[ESI+2E8h],1000
		MOV DWORD PTR DS:[ESI+2ECh],1000
		MOV DWORD PTR DS:[ESI+2F0h],1000
		MOV DWORD PTR DS:[ESI+3FCh],-1000
		MOV DWORD PTR DS:[ESI+400h],-1000
		POP EDI ; original
		POP ESI ; original
		POP EBX ; original
		RETN ; original

StartDataZ endp















