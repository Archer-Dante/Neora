.data

Transform1	dd 0041F675h ;state8xxx
TransBack1  dd 0041F60Ah ;state4xxxx
TurnBack1   dd 00413350h ;StateTurn
TurnBack2 	dd 0041336Fh
BackSt_9x_1 dd 0042ECAFh
BackSt_9x_2 dd 0042ED2Ch 

.code

State8xxx proc

		CMP EDX, 38
		JE plus140
		CMP EDX, 37
		JE plus140
		CMP EDX, 36
		JE plus140
		CMP EDX, 35
		JE plus140
		CMP EDX, 34
		JE plus140
		CMP EDX, 33
		JE plus140
		CMP EDX, 32
		JE plus140
		CMP EDX, 31
		JE plus140
		CMP EDX, 30
		JE plus140

		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EDX+70h],0
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EAX+318h],0
		JMP [Transform1]

plus140:
		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EDX+70h],0
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EAX+318h],8Ch
		JMP [Transform1]


State8xxx endp





StateMore proc

		PUSH EDX ;reserve
		PUSH EAX ;reserve
		PUSH ECX ;reserve
		PUSH EBX ;reserve
		PUSH EDI ;reserve
			
		CMP EAX,2000000 ; 2xxxyyy
		JL  [skip] ; Если меньше - в обычный код
		CMP EAX,2999999 ; 2999999
		JLE [State2xxxyyy]
		CMP EAX,3999999 ; 3999999
		JLE [State3xxxyyy]
		
		JMP [skip] ; если ни один из стейтов выше

State2xxxyyy:
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		CMP DWORD PTR DS:[ECX+88h],0 ; антибаг
		JNE [skip]
		
		SUB EAX, 2000000 ; 2xxxyyy

		MOV EBX,1000
		CDQ
		IDIV EBX
		CMP DWORD PTR DS:[ECX+308h],EAX
		JL [not_enough_mp]
		JMP [skip]
		
not_enough_mp:	
		MOV DWORD PTR DS:[ECX+70h],EDX
		MOV DWORD PTR DS:[ECX+88h],0
		JMP [skip]
		
;==============================================================
;====================== Time Stop State =======================
;==============================================================
State3xxxyyy:

		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		CMP DWORD PTR DS:[ECX+88h],0 ; антибаг
		JNE [skip]
		
		PUSH EBX ; сохраним адрес начала объектов

		SUB EAX,3000000 ; 3xxyzzz
		MOV ECX,10000
		CDQ
		IDIV ECX ; % в EAX, остаток в EDX
		
		CMP EAX, 0
		JE [skip_random]
		
		MOV EBX,EAX ; если число рандом не 0, то сохраним его на время после рассчета рандома
		PUSH 100 ; макс число рандома
		PUSH EDX ; резервируем остаток
		CALL DWORD PTR [random] ; result in EAX ~ EDX
		POP EAX ; перемещаем остаток в EAX для дальнейшего парсинга
		ADD ESP,4h ; выравниваем стек
		CMP EBX,EDX ; сравниваем (наш %) и (рандом %)
		JL [TS_no_random] ; если не хватило - допускаем, что урон просто пройдется по цели
		JMP [check_type]

skip_random:
		XCHG EAX,EDX ; отправляем в EAX остаток
check_type:
		MOV ECX,1000
		CDQ
		IDIV ECX ; оставит в EAX тип, а в EDX время
		
		XOR ECX,ECX
		POP EBX
		
		CMP EAX,0
		JE [ts_setup_0]
		CMP EAX,1
		JE [ts_setup_1]
		CMP EAX,2
		JE [ts_setup_2]
		JMP [skip]

ts_setup_0:
		CMP BYTE PTR DS:[EBX+ECX+4h],0
		JE [doesnt_exist_0]
		
		MOV EAX,DWORD PTR DS:[EBX+ECX*4+3ECh] 
		MOV DWORD PTR DS:[EAX+150h],EDX ; записываем объекту таймер

		doesnt_exist_0:
		INC ECX
		CMP ECX,1000
		JL [ts_setup_0]
		
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh] ; исходный владелец стейта
		MOV DWORD PTR DS:[EAX+150h],-1 ; помечаем его как неподверженного эффекту
		MOV DWORD PTR DS:[ts_timer],EDX ; запись времени ТС для движка
		
		MOV DWORD PTR DS:[ts_team],0 ; обнуление команды, чтобы ТС 0 работал после ТС 1
		MOV DWORD PTR DS:[ts_type],0 ; записываем Time Stop Type
		JMP [skip]

ts_setup_1:
		PUSH ESI
		MOV ESI,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV ESI,DWORD PTR DS:[ESI+364h] ; команда в ESI
		MOV DWORD PTR DS:[ts_team],ESI ; записываем кто сопротивляется TS
		
	next_object_s1:
		CMP BYTE PTR DS:[EBX+ECX+4h],0
		JE [doesnt_exist_1]
		
		MOV EAX,DWORD PTR DS:[EBX+ECX*4+3ECh] 
		CMP DWORD PTR DS:[EAX+364h],ESI ; проверка команды
		MOV DWORD PTR DS:[EAX+150h],EDX ; записываем объекту таймер
		JNE [doesnt_exist_1]
		MOV DWORD PTR DS:[EAX+150h],-1 ; если равна, то даем сопротивление ТС

		doesnt_exist_1:
		INC ECX
		CMP ECX,1000
		JL [next_object_s1]
		

		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh] ; исходный владелец стейта
		MOV DWORD PTR DS:[EAX+150h],-1 ; помечаем его как неподверженного эффекту
		MOV DWORD PTR DS:[ts_timer],EDX ; запись времени ТС для движка
		MOV DWORD PTR DS:[ts_type],1 ; записываем Time Stop Type
		POP ESI
		JMP [skip]


ts_setup_2:
		CMP BYTE PTR DS:[EBX+ECX+4h],0
		JE [doesnt_exist_2]
		
		MOV EAX,DWORD PTR DS:[EBX+ECX*4+3ECh] 
		MOV DWORD PTR DS:[EAX+150h],EDX ; записываем объекту таймер

		doesnt_exist_2:
		INC ECX
		CMP ECX,1000
		JL [ts_setup_2]
		
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh] ; исходный владелец стейта
		MOV DWORD PTR DS:[EAX+150h],-1 ; помечаем его как неподверженного эффекту
		MOV DWORD PTR DS:[ts_timer],EDX ; запись времени ТС для движка
		
		MOV DWORD PTR DS:[ts_team],0 ; обнуление команды, чтобы ТС 0 работал после ТС 1
		MOV DWORD PTR DS:[ts_type],2 ; записываем Time Stop Type
		JMP [skip]

TS_no_random:
		POP EBX
;==============================================================

skip:	
		POP EDI ;reserve
		POP EBX ;reserve	
		POP ECX ;reserve
		POP EAX ;reserve
		POP EDX ;reserve
		
		CMP EAX,2328h ; 9000
		JGE SHORT [recover_1]
		JMP [TransBack1]

recover_1:
		JMP [Transform1]


StateMore endp


StateTurn3x proc

		CMP EDX,1Eh ; State 30
		JE [State30]
		CMP EDX,1Fh ; State 31
		JE [State31]
		CMP EDX,12Dh ; State 301
		JMP [TurnBack1]

State30:
		MOV BH, 1h
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]

State31:
		XOR BH,BH ; set 0 WTF
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]


StateTurn3x endp




State9xxx proc
	
	MOV EAX, DWORD PTR DS:[ECX+EDX+838h]
    CMP EAX,0BB8h ; 3000
	JE [Back1] ; regular code, for state 3000
	CMP EAX,2328h ; 9000 - minimum
	JL SHORT [Back2] ; regular code, for another states
	CMP EAX,2647h ; 9799 - limit
	JG SHORT [Back2] ; regular code, for another states
	

	SUB EAX, 2328h
	MOV DWORD PTR DS:[EBX+70h],EAX
	MOV DWORD PTR DS:[EBX+88h],0h
	FST QWORD PTR DS:[EBX+40h]
	FLD DWORD PTR DS:[ECX+EDX+848h]
	FSTP QWORD PTR DS:[EBX+50h]
	JMP [BackSt_9x_2]
	
Back1:
	JMP [BackSt_9x_1]
	
Back2:
	JMP [BackSt_9x_2]

State9xxx endp











