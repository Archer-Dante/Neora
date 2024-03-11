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
		MOV DWORD PTR DS:[EDX+18],EAX ; спавн компов по Z. Можно заменить EAX на число, если хочется точной точки спавна
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

		ADD EAX,DWORD PTR DS:[EBX+0B0h] ; добавление рандомного числа к точки призыва по X
		;MOV EAX,DWORD PTR DS:[EBX+0B0h] ; Заменить этой строкой строчку выше, чтобы отключить рандом
		ADD ESP,8
		MOV EDX,EAX
		
		JMP [spawner4]

SpawnerComStages1 endp














