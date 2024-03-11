.Data

e1_t1_e9 dd 0042F554h
e1_t2_e9 dd 0042F54Fh
e1_t3_e9 dd 0042F594h ;0042F58Fh ; куда возвращаются эффекты после выполнения

e_finish dd 0043087Ch ; куда уходят все эффекты после всех сравнений и выполнений.
					  ; В коде ниже не используется, но может сократить нагрузку на комп

.Code


itr_effect_1xxx_to_9xxx proc

	CMP EAX,3 ; Ice Effect
	JE [Back1]


state1xxx:
	CMP EAX, 3E8h ; 1000
	JL [Back2]  ; Если меньше 1000, уходим сразу
	CMP EAX, 7CFh ; 1999
	JG [state2xxx]
	

	PUSH EAX ; резервируем
	PUSH EBX ; резервируем
	PUSH ECX ; резервируем
	PUSH EDX ; резервируем
	
	SUB EAX,3E8h ; -1000, получаем число для урона
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; подключение к атакующему
	MOV EBX,DWORD PTR DS:[EDX+2FCh] ; получаем ХП атакующего в ЕBХ
	SUB EBX, EAX ; вычитаем из ХП нужный урон.
	CMP EBX, 0 ; проверяем, что полученное значение не меньше нуля
	JGE [valid_1xxx]
	MOV EBX, 0 ; если вдруг ушли в минус, выставляем 0, анти-баг
	valid_1xxx:
	MOV DWORD PTR DS:[EDX+2FCh],EBX ; записываем полученное хп

	POP EDX ; восстанавливаем
	POP ECX ; восстанавливаем
	POP EBX ; восстанавливаем
	POP EAX ; восстанавливаем
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату


	JMP [e1_t3_e9] ; завершаем обработку


state2xxx:
	CMP EAX, 0BB7h ; 2999
	JG [state3xxx]

	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type2] ; завершаем обработку, но обрабатываем звук

	PUSH EAX ; резервируем
	PUSH EBX ; резервируем
	PUSH ECX ; резервируем
	PUSH EDX ; резервируем
	
	SUB EAX,7D0h ; -2000, число для отхила
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; подключение к атакующему
	ADD DWORD PTR DS:[EDX+2FCh],EAX ; добавляем полученное хп

	POP EDX ; восстанавливаем
	POP ECX ; восстанавливаем
	POP EBX ; восстанавливаем
	POP EAX ; восстанавливаем
	
	wrong_type2:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату
	
	JMP [e1_t3_e9] ; завершаем обработку

state3xxx:
	CMP EAX, 0F9Fh ; 3999
	JG [state4xxx]

	PUSH EAX ; резервируем
	PUSH ECX ; резервируем
	PUSH EDX ; резервируем
	
	SUB EAX,0BB8h ; -3000
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; подключение к атакующему
	ADD DWORD PTR DS:[EDX+2FCh],EAX ; добавляем полученное хп

	POP EDX ; восстанавливаем
	POP ECX ; восстанавливаем
	POP EAX ; восстанавливаем

	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату
	
	JMP [e1_t3_e9] ; завершаем обработку

state4xxx:
	CMP EAX, 1387h ; 4999
	JG [state5xxx]

	PUSH EAX ; резервируем
	PUSH EBX ; резервируем
	PUSH ECX ; резервируем
	PUSH EDX ; резервируем
	
	SUB EAX,0FA0h ; -4000
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; подключение к атакующему
	SUB DWORD PTR DS:[EDX+308h],EAX ; отнимаем ману

	POP EDX ; восстанавливаем
	POP ECX ; восстанавливаем
	POP EBX ; восстанавливаем
	POP EAX ; восстанавливаем
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату
	
	JMP [e1_t3_e9] ; завершаем обработку



state5xxx:
	CMP EAX, 176Fh ; 5999
	JG [state6xxx]
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type5] ; завершаем обработку, но обрабатываем звук

	PUSH EAX ; резервируем
	PUSH EBX ; резервируем
	PUSH ECX ; резервируем
	PUSH EDX ; резервируем
	
	SUB EAX,1388h ; -5000
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; подключение к атакующему
	ADD DWORD PTR DS:[EDX+308h],EAX ; добавляем ману

	POP EDX ; восстанавливаем
	POP ECX ; восстанавливаем
	POP EBX ; восстанавливаем
	POP EAX ; восстанавливаем
	
	wrong_type5:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату
	
	JMP [e1_t3_e9] ; завершаем обработку



state6xxx:
	CMP EAX, 1B57h ; 6999
	JG [state7xxx]

	PUSH EAX ; резервируем
	PUSH EBX ; резервируем
	PUSH ECX ; резервируем
	PUSH EDX ; резервируем
	
	SUB EAX,1770h ; -6000
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; подключение к атакующему
	ADD DWORD PTR DS:[EDX+308h],EAX ; добавляем ману

	POP EDX ; восстанавливаем
	POP ECX ; восстанавливаем
	POP EBX ; восстанавливаем
	POP EAX ; восстанавливаем
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату
	
	JMP [e1_t3_e9] ; завершаем обработку


state7xxx:
	CMP EAX, 1F3Fh ; 7999
	JG [state8xxx]
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type7] ; завершаем обработку, но обрабатываем звук

	PUSH EAX ; резервируем
	
	SUB EAX,1B58h ; -7000
	SUB DWORD PTR DS:[EDI+308h], EAX ; отнимаем ману

	POP EAX ; восстанавливаем
	
	wrong_type7:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату
	
	JMP [e1_t3_e9] ; завершаем обработку



state8xxx:
	CMP EAX, 2327h ; 8999
	JG [state9xxx] 
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type8] ; завершаем обработку, но обрабатываем звук

	PUSH EAX ; резервируем
	PUSH EBX ; резервируем
	PUSH ECX ; резервируем
	PUSH EDX ; резервируем
	
	SUB EAX,1F40h ; -8000
	SUB DWORD PTR DS:[EDI+308h], EAX ; отнимаем ману
	
	MOV ECX,DWORD PTR DS:[EBX+0A0h] ; ?
	MOV EDX,DWORD PTR DS:[ESI+ECX*4+3ECh] ; подключение к атакующему
	ADD DWORD PTR DS:[EDX+308h],EAX ; добавляем ману
	
	POP EDX ; восстанавливаем
	POP ECX ; восстанавливаем
	POP EBX ; восстанавливаем
	POP EAX ; восстанавливаем
	
	wrong_type8:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату
	
	JMP [e1_t3_e9] ; завершаем обработку


state9xxx:
	CMP EAX, 270Fh ; 9999
	JG [Back2] ; больше некуда, поэтому валим.
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type9] ; завершаем обработку, но обрабатываем звук

	PUSH EAX ; резервируем
	
	SUB EAX,2328h ; -9000
	MOV DWORD PTR DS:[EDI+70h],EAX ; выставляем кадр

	POP EAX ; восстанавливаем
	
	wrong_type9:	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; восстанавливаем подключение к ITR сектору
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; кусок оригинального кода, берет Х-координату
	
	JMP [e1_t3_e9] ; завершаем обработку
	


Back1: 
	JMP [e1_t1_e9] ; Если это заморозка Фриза, то сюда уходим
Back2:
	JMP [e1_t2_e9] ; уход на проверку других эффектов, если ни один из списка
Back3:
	JMP [e_finish]

itr_effect_1xxx_to_9xxx endp
















