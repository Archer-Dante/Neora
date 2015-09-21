.Data

HP_bars_changer dd 0041B03Ah

call_0043F010 dd 0043F010h
call_0043E9A0 dd 0043E9A0h
.Code


opacity proc
	PUSH 1
opacity endp

ResetCoord proc
	PUSH 0
ResetCoord endp

HP_bars_change proc

	PUSH EDX
	MOV EDX,DWORD PTR DS:[ECX+368h] ; data
	MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID
	CMP EDX, 52 ; Julian ID
	JE [demon_bar]
	CMP EDX, 53 ; Your ID
	JE [someone_bar]
	POP EDX



	CMP EDX,1000 ; нужно для работы хилки джона
	JGE SHORT [healing_normal]
	MOV EDX,DWORD PTR DS:[ECX+0E4h] ; проверка, что хилка есть
	
healing_normal:
	AND EDX,1
	MOV ECX,20 ; смещение в 20 пикселей для хп бара
	JE [go_to_push] ; если хилки нет, пропускаем строчку ниже и сразу идем в PUSH ECX оригинального кода
	ADD ECX,20 ; + 20 пикселей, если хилимся
	JMP [HP_bars_changer]



demon_bar:
	POP EDX

	CMP EDX,1000 ; нужно для работы хилки джона
	JGE SHORT [healing_special_1]
	MOV EDX,DWORD PTR DS:[ECX+0E4h] 
	
healing_special_1:
	AND EDX,1 
	MOV ECX,76 ; смещение для бара
	JE [go_to_push] 
	MOV ECX,86 ; смещение для особого вида подхилки
	JMP [HP_bars_changer]



someone_bar:
	POP EDX

	CMP EDX,1000
	JGE SHORT [healing_special_2]
	MOV EDX,DWORD PTR DS:[ECX+0E4h] 
	
healing_special_2:
	AND EDX,1 
	MOV ECX,96 ; 96 pixels shift, MAKE BAR FIRST in BARS.png!
	JE [go_to_push] 
	MOV ECX,106 ; 106 pixels shift, MAKE BAR FIRST in BARS.png!
	JMP [HP_bars_changer]
	
	


go_to_push:
	JMP [HP_bars_changer]
	
HP_bars_change endp




total_bar_rework proc

		; most of code here is just copy from exe

		PUSH ESI
		PUSH EDI
		PUSH EBX
		PUSH EBP
		SUB ESP,10h
		XOR ESI,ESI
		XOR EDI,EDI

		MOV DWORD PTR SS:[ESP+0Ch],8
		MOV EBP,DWORD PTR SS:[ESP+24h]
	
	; ======================================================================
	; Обработка синего фона игры, фоны для баров хп \ мп и иконки персонажей
	; ======================================================================
	
		repeat_it:
			PUSH EBP
			PUSH 0
			PUSH 1
			PUSH -1
			PUSH EDI
			PUSH ESI
			MOV ECX,DWORD PTR DS:[4511A8h]
			CALL [call_0043F010]
		
		MOV EAX,8
		MOV EDX,DWORD PTR DS:[458B00h]
		SUB EAX,DWORD PTR SS:[ESP+0Ch]
		CMP BYTE PTR DS:[EDX+EAX+4],0
		JNZ [skip_com]
		ADD EAX,0Ah
		CMP BYTE PTR DS:[EDX+EAX+4],0
		JE [skip_both]

	; ======================================================================
	; Отрисовка мини-иконок персонажей
	; ======================================================================
	
		skip_com:
			MOV EBX,DWORD PTR DS:[EDX+EAX*4+3ECh]
			LEA EAX,DWORD PTR DS:[EDI+7]
			PUSH EBP
			PUSH 0
			LEA ECX,DWORD PTR DS:[ESI+9]
			MOV EDX,DWORD PTR DS:[EBX+368h]
			
			PUSH 0
			PUSH -1
			PUSH EAX
			PUSH ECX
			MOV ECX,DWORD PTR DS:[EDX+728h]
			CALL [call_0043F010]
		
		CMP DWORD PTR DS:[EBX+2FCh],0
		JLE [object_is_dead]
		
	; ======================================================================
	; Картеровские отрисовки циферок! Уиии! (только динамические) \ Основа для циферок
	; ======================================================================
		
			MOV ECX,DWORD PTR DS:[44FD7Ch]
			MOV EDX,DWORD PTR DS:[ECX]
			PUSH DWORD PTR DS:[EDX]
			CALL [call_0043E9A0]
			
	; ======================================================================
	; Основа для полосок
	; ======================================================================
			
			MOV DWORD PTR SS:[ESP+8],EBX
			MOV EBX,EAX
			PUSH EBP
			CALL [call_0043E9A0]
		
		MOV EBP,EAX
		MOV ECX,DWORD PTR SS:[ESP+8]
		MOV EAX,DWORD PTR DS:[ECX+300h]
		CMP DWORD PTR DS:[ECX+2FCh],EAX
		JE [hp_matched_or_full]
		
			IMUL EAX,EAX,7Ch
			CDQ
			IDIV DWORD PTR DS:[ECX+304h]
			TEST EDX,EDX
			JE [dont_fix_1]
			INC EAX
		
		dont_fix_1:
			PUSH 0CC0020h
			LEA EDX,DWORD PTR DS:[EDI+10h]
			PUSH 1Eh
			PUSH 0
			LEA ECX,DWORD PTR DS:[ESI+39h]
			PUSH EBX
			PUSH 0Ah
			PUSH EAX
			PUSH EDX
			PUSH ECX
			PUSH EBP
			CALL DWORD PTR DS:[4575DCh]
			MOV ECX,DWORD PTR SS:[ESP+8]
			
		hp_matched_or_full:
		IMUL EAX,DWORD PTR DS:[ECX+2FCh],7Ch
		CDQ
		IDIV DWORD PTR DS:[ECX+304h]
		TEST EDX,EDX
		JE [dont_fix_2]
		INC EAX
		
		dont_fix_2:
		MOV EDX,DWORD PTR DS:[ECX+0E0h]
		PUSH 0CC0020h
		CMP EDX,3E8h
		JGE [no_ik8_heal]
		MOV EDX,DWORD PTR DS:[ECX+0E4h]
		
		no_ik8_heal:
		AND EDX,1
		MOV ECX,14h
		JE [skip_pixel_shift_1]
		ADD ECX,14h
		
		skip_pixel_shift_1:
			PUSH ECX
			LEA EDX,DWORD PTR DS:[EDI+10h]
			PUSH 0
			PUSH EBX
			LEA ECX,DWORD PTR DS:[ESI+39h]
			PUSH 0Ah	; высота картинки
			PUSH EAX	; ширина картинки
			PUSH EDX
			PUSH ECX
			PUSH EBP
			CALL DWORD PTR DS:[4575DCh]
			
			PUSH 0CC0020h
			LEA EDX,DWORD PTR DS:[EDI+24h]
			PUSH 0Ah	
			PUSH 0		
			LEA ECX,DWORD PTR DS:[ESI+39h]
			PUSH EBX
			PUSH 0Ah	; высота картинки
			PUSH 7Ch	; ширина картинки
			PUSH EDX
			PUSH ECX
			PUSH EBP
			CALL DWORD PTR DS:[4575DCh]
			
		; IT'S MANA TIME!
			
		MOV ECX,DWORD PTR SS:[ESP+8]
		
		MOV EDX,DWORD PTR DS:[ECX+190h]
		MOV EDX,DWORD PTR DS:[EDX+60h]
		TEST EDX,EDX
		JZ[no_custom_max_mp]
		
		IMUL EAX,DWORD PTR DS:[ECX+308h],7Ch
		MOV ECX,EDX
		CDQ
		IDIV ECX
		JMP SHORT [check_if_zero]
		
		no_custom_max_mp:
		IMUL EAX,DWORD PTR DS:[ECX+308h],7Ch
		MOV ECX,1F4h
		CDQ
		IDIV ECX
		
		check_if_zero:
		TEST EDX,EDX
		JE [dont_fix_3]
		INC EAX
		
		dont_fix_3:
			PUSH 0CC0020h
			LEA EDX,DWORD PTR DS:[EDI+24h]
			PUSH 0
			PUSH 0
			LEA ECX,DWORD PTR DS:[ESI+39h]
			PUSH EBX
			PUSH 0Ah
			PUSH EAX
			PUSH EDX
			PUSH ECX
			PUSH EBP
			CALL DWORD PTR DS:[4575DCh]
			
			PUSH EBP                     	; /hDC
			PUSH EBX                     	; |/hDC
			CALL DWORD PTR DS:[447028h]		; |\DeleteDC
			CALL DWORD PTR DS:[447028h]		; \DeleteDC
			
		; создание строки в буфере для динамичных цифр
			
		MOV EBX,DWORD PTR SS:[ESP+8]
		MOV EBP,DWORD PTR SS:[ESP+24h]
		MOV DWORD PTR SS:[ESP],EDI
		MOV DWORD PTR SS:[ESP+4],ESI
		MOV EAX,DWORD PTR DS:[EBX+304h]
		MOV ECX,0Ah
		MOV ESI,DWORD PTR DS:[EBX+2FCh]
		MOV EDI,00455CB8h
		XOR EBX,EBX
		
			repeater_1:
				CDQ
				IDIV ECX
				XCHG EAX,EDX
				STOS BYTE PTR ES:[EDI]
				XCHG EAX,EDX
				INC EBX
				TEST EAX,EAX
				JNZ [repeater_1]
				
		MOV AL,CL
		INC EBX
		STOS BYTE PTR ES:[EDI]
		MOV EAX,ESI
		XOR ESI,ESI
		
			repeater_2:
				INC ESI
				CDQ
				IDIV ECX
				XCHG EAX,EDX
				STOS BYTE PTR ES:[EDI]
				XCHG EAX,EDX
				INC EBX
				TEST EAX,EAX
				JNZ [repeater_2]
				
		IMUL EAX,ESI,9
		MOV ESI,DWORD PTR SS:[ESP+4]
		SUB ESI,EAX
		ADD ESI,72h
		MOV EDI,DWORD PTR SS:[ESP]
		ADD EDI,0Fh
		
		; отрисовка динамичных цифр
		
			repeater_3:
				XOR EDX,EDX
				PUSH EBP
				PUSH 0
				MOV DL,BYTE PTR DS:[EBX+455CB7h]
				PUSH 1
				PUSH EDX ; смещение по X
				PUSH EDI ; смещение по Y
				PUSH ESI
				MOV ECX,DWORD PTR DS:[44FD7Ch]
				CALL [call_0043F010]
				ADD ESI,9
				DEC EBX
				JG [repeater_3]
				
		; Статическая часть
				
		LEA ESI,DWORD PTR DS:[EDI+14h]
		MOV EDX,DWORD PTR SS:[ESP+8]
		MOV ECX,10 ; символ-разделитесь (картинка на 10 месте) и одновременно делитель в парсе
		MOV EDI,00455CB8h ; адрес буфера
		MOV ESI,DWORD PTR DS:[EDX+308h] ; резервируем значение нашей маны, т.к. все регистры полетят по ходу парса
		
		MOV EBX, DWORD PTR DS:[EDX+190h]
		MOV EBX, DWORD PTR DS:[EBX+60h]
		TEST EBX,EBX
		MOV EAX,1F4h
		JZ [skip_if_no_max_mp]
		MOV EAX,DWORD PTR DS:[EDX+190h]
		MOV EAX,DWORD PTR DS:[EAX+60h] ; если макс мана есть - записываем её
		skip_if_no_max_mp:
		XOR EBX,EBX
		
			repeater_4:
				CDQ 		 ; сброс
				IDIV ECX	 ; получаем крайнюю правую цифру в EDX (делим на 10)
				XCHG EAX,EDX ; остаток в EAX
				STOS BYTE PTR ES:[EDI] ; записываем остаток из EAX в буфер, смещаем EDI+1 байт
				XCHG EAX,EDX ; возвращаем частное в EAX для дальнейшего парса
				INC EBX		 ; увеличиваем счетчик символов в строке
				TEST EAX,EAX	
				JNZ [repeater_4] ; если в EAX ещё что-то осталось - продолжим парс числа
		
		MOV AL,CL ; копируем 10-ку (или символ "\") в EAX для записи в буфер
		INC EBX ; учтем и этот символ
		STOS BYTE PTR ES:[EDI] ; записываем символ-разделитесь в буфер
		MOV EAX,ESI ; теперь принимаемся за ранее зарезервированное число текущей маны
		XOR ESI,ESI	; ESI больше не нужен, сбросим от мусора

			repeater_5:
				INC ESI		
				CDQ			; сброс
				IDIV ECX
				XCHG EAX,EDX
				STOS BYTE PTR ES:[EDI]
				XCHG EAX,EDX
				INC EBX
				TEST EAX,EAX
				JNZ [repeater_5]
		
		IMUL EAX,ESI,9
		MOV ESI,DWORD PTR SS:[ESP]
		ADD ESI,23h
		MOV EDI,DWORD PTR SS:[ESP+4]
		SUB EDI,EAX
		ADD EDI,72h

			repeater_6:
				XOR EDX,EDX
				PUSH EBP
				PUSH 0
				MOV DL,BYTE PTR DS:[EBX+455CB7h] ; забирается из буфера номер нужной цифры из BARS.png
				PUSH 1
				PUSH EDX ; цифра на картинке BARS.ong кладется для обработки функцией
				PUSH ESI ; смещение y
				PUSH EDI ; смещение х
				MOV ECX,DWORD PTR DS:[44FD7Ch]
				CALL [call_0043F010]
				ADD EDI,9 ; отступ цифр друг от друга
				DEC EBX	  ; переход к следующей цифре (каждая цифра обрабатывается отдельно)
				JG [repeater_6]
		
		MOV EBX,DWORD PTR SS:[ESP+8]
		MOV ESI,DWORD PTR SS:[ESP+4]
		MOV EDI,DWORD PTR SS:[ESP]
		
		object_is_dead:
			MOV EDX,DWORD PTR DS:[EBX+364h]
			XOR ECX,ECX
			CMP EDX,1
			JNZ [not_team_1]
			MOV ECX,DWORD PTR DS:[44F888h]
		not_team_1:
			CMP EDX,2
			JNZ [not_team_2]
			MOV ECX,DWORD PTR DS:[44FCBCh]
		not_team_2:
			CMP EDX,3
			JNZ [not_team_3]
			MOV ECX,DWORD PTR DS:[44FB68h]
		not_team_3:
			CMP EDX,4
			JNZ [not_team_4]
			MOV ECX,DWORD PTR DS:[44FAF8h]
		not_team_4:
			TEST ECX,ECX ; есть ли команда вообще
			JE [skip_both] ; если нет - пропуск отрисовки флажка
			
			PUSH EBP
			LEA EAX,DWORD PTR DS:[ESI+5]
			PUSH 0
			PUSH 1
			PUSH 0FEh
			PUSH EDI
			PUSH EAX
			CALL [call_0043F010]
			
		skip_both:
			ADD ESI,0C6h
			CMP ESI,318h
			JL [skip_wtf]
			XOR ESI,ESI
			ADD EDI,36h
			skip_wtf:
			DEC DWORD PTR SS:[ESP+0Ch]
			JG [repeat_it]

		ADD ESP,10h
		POP EBP
		POP EBX
		POP EDI
		POP ESI
		
		RETN 4






total_bar_rework endp




