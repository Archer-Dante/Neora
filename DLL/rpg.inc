.Data

all_stats_calculation_b		 dd 00413F24h

.Code



calculate_Max_MP proc

	; ECX и EDX содержат указатель на ID страницу (при t0)
	; EDI - указатель на Frame страницу
	; ESI - указатель на Individual страницу

	
	PUSHA

	MOV ECX, DWORD PTR DS:[ESI+190h] ; ECX - место с датой malloc на Individual
	TEST ECX,ECX
	JZ [skip_all]









skip_all:



calculate_Max_MP endp








all_stats_calculation proc

	; ECX и EDX содержат указатель на ID страницу (при t0)
	; EDI - указатель на Frame страницу
	; ESI - указатель на Individual страницу
	
		PUSHA

		MOV ECX,DWORD PTR DS:[ESI+368h] ; подстраховка на случай если объект на t0
		CMP DWORD PTR DS:[ECX+6F8h],0 ; фильтр для не t0 объектов
		JG  [PERSONAL_ONLY]
		
		MOV ECX, DWORD PTR DS:[ESI+190h] ; ECX - место с датой malloc на Individual


; РАССЧЕТ ТОЛЬКО СТАТОВ С ВЕЩЕЙ
ITEMS_ONLY:
		XOR EAX,EAX
		XOR EDX,EDX  
		XOR EBX,EBX  ; смещение на начало первой вещи
		
		stat_cleaning:
		MOV DWORD PTR DS:[ECX+EAX*4h],EBX ; сбрасываем статы перед рассчетом заново
		INC EAX
		CMP EAX,20 						; 20 хватает чтобы очистить Stat и Resist поля
		JL [stat_cleaning] 
		
		MOV EBP, 8h ; начальное смещение в EBP (item stat)
		PUSH 8 ; количество статов, после обработки которых выходим из процедуры
		PUSH 8 ; максимум вещей EAX
		CALL [item_stats_calculator]
		ADD ESP,8
		; на выходе ничего нет, теперь указываем начальное смещение в EBP и повторяем
		
		MOV EBP, 30h ; начальное смещение в EBP (item resist)
		PUSH 8 ; количество статов, после обработки которых выходим из процедуры
		PUSH 8 ; максимум вещей EAX
		CALL [item_stats_calculator]
		ADD ESP,8
		; на выходе ничего нет, теперь указываем начальное смещение в EBP и повторяем

		JMP [BUFFS_ONLY]

; ня ня ня - няшная процедура считывания всех нужных статов из всех вещей
		item_stats_calculator:
		MOV EAX, DWORD PTR SS:[ESP+4]
		stat_EBP_next_item:
		LEA EBX, DWORD PTR DS:[EBX+80h]			; первый EBX - первая вещь, на каждом цикле +80h
				CMP DWORD PTR DS:[ECX+EBX],0	; проверка, что там есть вещь (не ID 0)
				JLE [empty_slot]
		LEA EDI, DWORD PTR DS:[EBX+EBP]			; в EBP смещение на нужный стат от начала массива вещи
		ADD EDX, DWORD PTR DS:[ECX+EDI]  		; "stat EBP affection" запись в EDX стата нужного
				empty_slot:
		DEC EAX									; уменьшаем счет оставшихся вещей
		CMP EAX,0
		JG [stat_EBP_next_item]
		
		LEA EAX,[EBP-8h] ; уберем из EBP смещение от массива вещи, и получим +0 смещение для статы
		ADD DWORD PTR DS:[ECX+EAX],EDX		; stat_X рассчитан для вещи, записываем
		XOR EDX,EDX ; так как мы прошлись по одному и тому же стату во всех вещах, обнуляем перед следующим статом
		ADD EBP,4h ; на 1 стат вперед

		XOR EBX,EBX ; очищаем счетчик смещений
		DEC DWORD PTR SS:[ESP+8] ; уменьшаем число оставшихся для цикла статов
		CMP DWORD PTR SS:[ESP+8],0
		JG [item_stats_calculator] ; если ещё статы остались - повторяем
		RET




; РАССЧЕТ ТОЛЬКО СТАТОВ С БАФОВ
BUFFS_ONLY:
		XOR EAX,EAX
		MOV EBX, 480h-58h ; смещение на начало первого бафа
		
		
		MOV EBP, 8h ; начальное смещение в EBP (buff stat 0)
		PUSH 8  ; количество статов, после обработки которых выходим из процедуры
		PUSH 16 ; максимум бафов EAX
		CALL [buff_stats_calculator]
		ADD ESP,8
		
		MOV EBP, 30h ; начальное смещение в EBP (buff resist 0)
		PUSH 8  ; количество статов, после обработки которых выходим из процедуры
		PUSH 16 ; максимум бафов EAX
		CALL [buff_stats_calculator]
		ADD ESP,8

		JMP [PERSONAL_ONLY]


; ня ня ня - няшная процедура считывания всех нужных статов из всех бафов
		buff_stats_calculator:
		MOV EAX, DWORD PTR SS:[ESP+4]
		stat_EBP_next_buff:
		LEA EBX,[EBX+58h]					; первый EBX - первый баф, на каждом цикле +58h
				CMP DWORD PTR DS:[ECX+EBX],0; проверка, что у бафа есть ещё время действия
				JLE [no_active_buff]
		LEA EDI,[EBX+EBP]					; в EBP смещение на нужный стат от начала массива вещи
		ADD EDX, DWORD PTR DS:[ECX+EDI]		; "stat EBP affection" запись в EDX стата нужного
				no_active_buff:
		DEC EAX								; уменьшаем счет оставшихся вещей
		CMP EAX,0
		JG [stat_EBP_next_buff]
		
		LEA EAX,[EBP-8h] ; уберем из EBP смещение от массива вещи, и получим +0 смещение для статы
		ADD DWORD PTR DS:[ECX+EAX],EDX		; stat_X рассчитан для вещи, записываем
		XOR EDX,EDX ; так как мы прошлись по одному и тому же стату во всех вещах, обнуляем перед следующим статом
		ADD EBP,4h ; на 1 стат вперед

		MOV EBX, 480h-58h ; очищаем счетчик смещений
		DEC DWORD PTR SS:[ESP+8] ; уменьшаем число оставшихся для цикла статов
		CMP DWORD PTR SS:[ESP+8],0
		JG [buff_stats_calculator] ; если ещё статы остались - повторяем
		RET



; РАССЧЕТ ТОЛЬКО СТАТОВ ИЗ ШАПКИ ПЕРСОНАЖА
PERSONAL_ONLY:

		MOV ECX,DWORD PTR DS:[ESI+368h]
		MOV ECX,DWORD PTR DS:[ECX+0C0h] ; наличие шапочных данных
		TEST ECX,ECX
		JE [skip_all]
		
		MOV EDX,DWORD PTR DS:[ESI+190h] ; EDX - место с датой malloc на Individual
		XOR EBX,EBX
		
		add_stats:
		MOV EAX,DWORD PTR DS:[ECX+100h+EBX*4h]
		ADD DWORD PTR DS:[EDX+EBX*4h],EAX
		INC EBX
		CMP EBX,8
		JL [add_stats]
		
		ADD EDX,28h ; сдвигаемся дальше от Stat массива в Resist массив
		XOR EBX,EBX
		
		add_resists:
		MOV EAX,DWORD PTR DS:[ECX+150h+EBX*4h]
		ADD DWORD PTR DS:[EDX+EBX*4h],EAX
		INC EBX
		CMP EBX,8
		JL [add_resists]



skip_all:
		POPA ; приходит к нам, когда код кривой %)
		JMP [all_stats_calculation_b]


all_stats_calculation endp