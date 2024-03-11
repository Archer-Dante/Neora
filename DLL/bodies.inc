.data

body_back_1	dd 0042E683h
body_back_2 dd 00430A67h
body_back_3 dd 0042E6DDh

bdy50_back  dd 0042E8A4h

regular_damage  dd 0042E767h
after_damage	dd 0042E792h

.code

weNeedMoarBodies proc
        
		IMUL ECX,DWORD PTR DS:[EDI+70h],1B0h ; получаем страницу фрейма
		FSTP ST
		ADD ECX,DWORD PTR DS:[EDI+368h] ; прибавляем страницу фрейма к нашему объекту, чтобы получить нужное
		LEA EDX,DWORD PTR DS:[ECX+95Ch] ; считываем в EDX количество существующих "bdy" в фрейме
		CMP DWORD PTR DS:[EDX],0 		; проверяем, что есть хотя бы 1 "bdy"
		JLE [not_match1] 				
		MOV EAX,DWORD PTR DS:[EDX+8]	; отправляемся к указателю на атрибуты "bdy"
										; следует заметить, что указатель только 1, даже если "bdy" несколько
										; это сделано потому, что по логике никакие "bdy" не пересекаются
										; по крайней мере в оригинале LF2 именно так
										; в этом случае мы получаем указатель на самый верхний (первый) "bdy",
										; который был настигнут атакой Itr
		
		
										
		CMP DWORD PTR DS:[EAX],999		; проверка, что этот "bdy" не меньше 999
		JLE [not_match1]				; если нет - уходим
		
		CMP DWORD PTR DS:[EAX],1999		; проверка, что этот "bdy" больше 1999
		JL [state1000]					; если меньше, то это 1000-1999
		
		CMP DWORD PTR DS:[EAX],2999		; проверка, что этот "bdy" больше 2999
		JL [state2000]					; если меньше, то это 2000-2999
		
		CMP DWORD PTR DS:[EAX],3999		; проверка, что этот "bdy" больше 3999
		JL [state3000]					; если меньше, то это 3000-3999
		
		CMP DWORD PTR DS:[EAX],4999		; проверка, что этот "bdy" больше 4999
		JL [state4000]					; если меньше, то это 4000-4999
		
		CMP DWORD PTR DS:[EAX],1000000000	; 1xxyyyzzzw
		JG [bdy_1xxyyyzzzww]
		JMP [not_match1] ; ДЛЯ УСТРАНЕНИЯ БАГОВ, КОГДА ПОПАДАЕТСЯ НЕИЗВЕСТНЫЙ BDY
		
state1000:
		MOV ECX,DWORD PTR DS:[EBX+368h]
		CMP DWORD PTR DS:[ECX+6F8h],0
		JNE [finish_xzzz]
		CMP DWORD PTR DS:[ECX+364h],5
		JE  [finish_xzzz]
		
		MOV ECX,DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],ECX	; назначаем объекту нашу команду (по умолчанию вместо ECX стоит 1)
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,1000					; получаем XXX из "bdy" 1xxx
		MOV DWORD PTR DS:[EDI+70h],ECX	; отправляем объект в кадр XXX						
		MOV DWORD PTR DS:[EBX+0B4h],3 ; даем Шейк Атакующему в 1\10 секунды
		MOV DWORD PTR DS:[EDI+0B4h],-3 ; даем Шейк Цели в 1\10 секунды
		JMP [finish_xzzz]	
		
state2000:	
		MOV ECX,DWORD PTR DS:[EBX+368h]
		CMP DWORD PTR DS:[ECX+6F8h],0
		JNE [finish_xzzz]
		CMP DWORD PTR DS:[ECX+364h],5
		JE  [finish_xzzz]
	
		MOV ECX,DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],ECX	
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,2000
		MOV DWORD PTR DS:[EDI+70h],ECX
		JMP [finish_xzzz]
		
state3000:	
		MOV ECX,DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],ECX	
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,3000
		MOV DWORD PTR DS:[EDI+70h],ECX
		MOV DWORD PTR DS:[EBX+0B4h],3 ; даем Шейк Атакующему в 1\10 секунды
		MOV DWORD PTR DS:[EDI+0B4h],-3 ; даем Шейк Цели в 1\10 секунды
		JMP [finish_xzzz]
		
state4000:	
		MOV ECX,DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],ECX	
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,4000
		MOV DWORD PTR DS:[EDI+70h],ECX
		JMP [finish_xzzz]
	
finish_xzzz:
		JMP [body_back_2]	


bdy_1xxyyyzzzww:	; ECX активно используется, как и EAX
		PUSH EAX
		PUSH EDX
		PUSH ECX
		PUSH EBX

		MOV EAX,DWORD PTR DS:[EAX] ; получаем № тела
		SUB EAX,1000000000 ; убираем фильтр от переменных
		MOV ECX,10000000
		CDQ
		IDIV ECX
		CMP EAX,0
		JE [zero_fix]
		
		MOV EBX,EAX ; если число рандом не 0, то сохраним его на время после рассчета рандома
		PUSH 100 ; макс число рандома
		PUSH EDX ; резервируем остаток
		CALL DWORD PTR [random] ; result in EAX ~ EDX
		POP EAX ; перемещаем остаток в EAX для дальнейшего парсинга
		ADD ESP,4h ; выравниваем стек
		CMP EBX,EDX ; сравниваем (наш %) и (рандом %)
		JL [skip] ; если не хватило - уходим сразу	
		
		JMP [target_f]
zero_fix:		
		XCHG EAX,EDX
target_f:
		POP EBX ; восстанавливаем адрес атакующего
		MOV ECX, 10000
		CDQ
		IDIV ECX ; достаем из EAX адрес, куда перейдет Цель
		CMP EAX, 799
		JG [attacker_f]
		MOV DWORD PTR DS:[EDI+70h],EAX
		MOV DWORD PTR DS:[EDI+88h],0

attacker_f:
		MOV EAX,EDX ; переносим остаток в EAX для нового деления
		MOV ECX,10
		CDQ
		IDIV ECX
		CMP EAX, 799
		JG [last_effect]
		MOV ECX, DWORD PTR DS:[EBX+70h]
		MOV DWORD PTR DS:[EBX+70h],EAX
		MOV DWORD PTR DS:[EBX+88h],0
		
last_effect:
		MOV EAX,EDX
		
		CMP EAX,0 ;
		JLE [not_match2]
		CMP EAX,1 ;
		JE [setup_1]
		CMP EAX,2 ;
		JE [setup_2]
		CMP EAX,3 ;
		JE [setup_3]
		CMP EAX,4 ;
		JE [setup_4]
		CMP EAX,5 ;
		JE [setup_5]
		CMP EAX,6 ;
		JE [setup_5]
		CMP EAX,7 ;
		JE [setup_5]
		JMP [not_match2]
		
		setup_1:
		MOV EAX, DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],EAX
		JMP [not_match2]
		
		setup_2:
		IMUL EAX,ECX,1B0h
		FSTP ST
		ADD EAX,DWORD PTR DS:[EBX+368h]
		LEA EAX,DWORD PTR DS:[EAX+958h] ; itr check
		CMP DWORD PTR DS:[EAX],0
		JLE [there_is_no_itr]
		
		MOV EAX,DWORD PTR DS:[EAX+8]
		MOV EAX,DWORD PTR DS:[EAX+44h] ; gets Injury
		SUB DWORD PTR DS:[EDI+2FCh],EAX
		CMP DWORD PTR DS:[EDI+2FCh],0
		JGE [dont_fix]
		MOV DWORD PTR DS:[EDI+2FCh],0
		dont_fix:
		ADD DWORD PTR DS:[EDI+34Ch],EAX ; HP Lost - target
		ADD DWORD PTR DS:[EBX+348h],EAX ; Attack  - attacker
		there_is_no_itr:
		JMP [not_match2]
		
		setup_3:
		MOV EAX, DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],EAX
		JMP [setup_2]
		
		setup_4:
		MOV DWORD PTR DS:[EBX+0B4h],3 
		MOV DWORD PTR DS:[EDI+0B4h],-3
		JMP [not_match2]
		
		setup_5:
		MOV DWORD PTR DS:[EBX+0B4h],3 
		MOV DWORD PTR DS:[EDI+0B4h],-3
		JMP [setup_1]
		
		setup_6:
		MOV DWORD PTR DS:[EBX+0B4h],3 
		MOV DWORD PTR DS:[EDI+0B4h],-3
		JMP [setup_2]
		
		setup_7:
		MOV DWORD PTR DS:[EBX+0B4h],3 
		MOV DWORD PTR DS:[EDI+0B4h],-3
		JMP [setup_3]
		
		
skip:
		POP EBX
		POP ECX
		POP EDX
		POP EAX
		
not_match1:
		JMP [body_back_3]
		
not_match2:
		POP ECX
		POP EDX
		POP EAX
		JMP [body_back_2] ; если заменить на "body_back1" и "body_back3",
						  ; то атаки будут проходить не давая менять кадр

weNeedMoarBodies endp


hurtingBodies proc

		PUSH EAX
		PUSH ECX
		PUSH EDX
		
		MOV ECX, DWORD PTR DS:[EDI+368h] ; цель
		CMP DWORD PTR DS:[ECX+6F8h],0 ; избавляемся от багов при атаке не по Типам 0
		JNE [type_r]
		
		MOV ECX, DWORD PTR DS:[EBX+368h] ; атакующий
		CMP DWORD PTR DS:[ECX+6F8h],0 ; избавляемся от багов при атаке удерживаемым оружием
		JNE [type_r]
		
		IMUL ECX,DWORD PTR DS:[EDI+70h],1B0h
		FSTP ST
		ADD ECX,DWORD PTR DS:[EDI+368h]
		LEA EDX,DWORD PTR DS:[ECX+95Ch] 
		CMP DWORD PTR DS:[EDX],0 ; фикс, если ни одного bdy нету
		JE	[type_r]
		MOV EAX,DWORD PTR DS:[EDX+8]
		MOV EAX,DWORD PTR DS:[EAX]	

		CMP EAX,1000000; проверка, что этот "bdy" не меньше 1000000 (bdy 1XXYYYX)
		JLE [type_r]					; если нет - уходим
		CMP EAX,1999999; проверка, что этот "bdy" не меньше 1999999 (bdy 1XXYYYX)
		JLE [calculate]					; если фильтр сработал - это наш "bdy"

		JMP [type_r] ; любой неподходящий урон будет считаться типом 00


calculate:
		PUSH EBX
		
		SUB EAX, 1000000 ; получаем наши переменные
		MOV ECX, 10000   ; этим мы оставим в ECX только % вероятности
		CDQ
		IDIV ECX
		
		CMP EAX, 0
		JE [skip_random]
		
		MOV EBX,EAX ; если число рандом не 0, то сохраним его на время после рассчета рандома
		PUSH 100 ; макс число рандома
		PUSH EDX ; резервируем остаток
		CALL DWORD PTR [random] ; result in EAX ~ EDX
		POP EAX ; перемещаем остаток в EAX для дальнейшего парсинга
		ADD ESP,4h ; выравниваем стек
		CMP EBX,EDX ; сравниваем (наш %) и (рандом %)
		JL [no_chance] ; если не хватило - допускаем, что урон просто пройдется по цели
		JMP [check_percentage]

; ======================================================================================

skip_random:
		XCHG EAX,EDX ; отправляем в EAX остаток
check_percentage:
		POP EBX

		MOV ECX, 10 ; отсекаем тип урона от %
		CDQ
		IDIV ECX ; тип урона в EDX, % отражения в EAX

		CMP EAX,0 ; если отражается 0%
		JE [type_r] ; то уходим в простое нанесение урона
		
		
		PUSH EDX ; резервим тип урона
		CALL [gets_Injury_from_attacker]
		IMUL EAX,ECX ; умножаем урон на % отражения
		MOV ECX,100
		CDQ
		IDIV ECX ; делим результат ещё на 100, получаем возврвщаемый % урона
		POP EDX ; восстанавливаем тип урона

check_type: ; сюда нет переходов, метка-ориентир
		CMP EDX,0 ; damage type 0
		JE [Dtype_0]
		CMP EDX,1 ; damage type 1
		JE [Dtype_1]
		CMP EDX,2 ; damage type 2
		JE [Dtype_2]
		CMP EDX,3 ; damage type 3
		JE [Dtype_3]
		CMP EDX,4 ; damage type 4
		JE [Dtype_4]
		CMP EDX,5 ; damage type 5
		JE [Dtype_5]
		CMP EDX,6 ; damage type 6
		JE [Dtype_6]
		CMP EDX,7 ; damage type 7
		JE [Dtype_7]
		JMP [type_r] ; если не соответствует никакому типу урон будет нанесен как обычный, без спец тела

Dtype_0:
		CMP DWORD PTR DS:[EBX+160h],0
		JLE [Reflect_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EBX+160h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Reflect_DMG]
Dtype_1:
		CMP DWORD PTR DS:[EBX+164h],0
		JLE [Reflect_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EBX+164h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Reflect_DMG]
Dtype_2:
		CMP DWORD PTR DS:[EBX+168h],0
		JLE [Reflect_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EBX+168h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Reflect_DMG]
Dtype_3:
		CMP DWORD PTR DS:[EBX+16Ch],0
		JLE [Reflect_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EBX+16Ch] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Reflect_DMG]
Dtype_4:
		CMP DWORD PTR DS:[EBX+170h],0
		JLE [Reflect_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EBX+170h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Reflect_DMG]
Dtype_5:
		CMP DWORD PTR DS:[EBX+174h],0
		JLE [Reflect_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EBX+174h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Reflect_DMG]
Dtype_6:
		CMP DWORD PTR DS:[EBX+178h],0
		JLE [Reflect_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EBX+178h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Reflect_DMG]
Dtype_7:
		CMP DWORD PTR DS:[EBX+17Ch],0
		JLE [Reflect_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EBX+17Ch] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Reflect_DMG]

Reflect_DMG:		
		SUB DWORD PTR DS:[EBX+2FCh],EAX ; вычитаем хп у атакующего
		CMP DWORD PTR DS:[EBX+2FCh],0
		JG [its_alive]
		MOV DWORD PTR DS:[EBX+70h],0
		MOV DWORD PTR DS:[EBX+88h],0		
its_alive:
		ADD DWORD PTR DS:[EBX+34Ch],EAX ; добавляем HP Lost
		ADD DWORD PTR DS:[EDI+348h],EAX ; добавляем защищающемуся Attack
		
; ======================================================================================
		
DMG_target:
		CALL [gets_Injury_from_attacker]
		MOV EAX,ECX ; перенесем урон в EAX, чтобы проще было работать
		CMP EDX,0 ; damage type 0 to recieve
		JE [Dtype_0_t]
		CMP EDX,1 ; damage type 1 to recieve
		JE [Dtype_1_t]
		CMP EDX,2 ; damage type 2 to recieve
		JE [Dtype_2_t]
		CMP EDX,3 ; damage type 3 to recieve
		JE [Dtype_3_t]
		CMP EDX,4 ; damage type 4 to recieve
		JE [Dtype_4_t]
		CMP EDX,5 ; damage type 5 to recieve
		JE [Dtype_5_t]
		CMP EDX,6 ; damage type 6 to recieve
		JE [Dtype_6_t]
		CMP EDX,7 ; damage type 7 to recieve
		JE [Dtype_7_t]
		
Dtype_0_t:
		CMP DWORD PTR DS:[EDI+160h],0
		JLE [Taking_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EDI+160h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Taking_DMG]
Dtype_1_t:
		CMP DWORD PTR DS:[EDI+164h],0
		JLE [Taking_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EDI+164h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Taking_DMG]
Dtype_2_t:
		CMP DWORD PTR DS:[EDI+168h],0
		JLE [Taking_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EDI+168h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Taking_DMG]
Dtype_3_t:
		CMP DWORD PTR DS:[EDI+16Ch],0
		JLE [Taking_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EDI+16Ch] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Taking_DMG]
Dtype_4_t:
		CMP DWORD PTR DS:[EDI+170h],0
		JLE [Taking_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EDI+170h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Taking_DMG]
Dtype_5_t:
		CMP DWORD PTR DS:[EDI+174h],0
		JLE [Taking_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EDI+174h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Taking_DMG]
Dtype_6_t:
		CMP DWORD PTR DS:[EDI+178h],0
		JLE [Taking_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EDI+178h] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Taking_DMG]
Dtype_7_t:
		CMP DWORD PTR DS:[EDI+17Ch],0
		JLE [Taking_DMG] ; если сопротивления урону равно 0, то сразу идем в нанесение урона.
		MOV ECX, DWORD PTR DS:[EDI+17Ch] ; берем % сопротивления урону
		CALL [Calculate_DMG_RESIST]
		JMP [Taking_DMG]

Taking_DMG:
		SUB DWORD PTR DS:[EDI+2FCh],EAX ; вычитаем хп у атакующего
		ADD DWORD PTR DS:[EDI+34Ch],EAX ; добавляем HP Lost
		ADD DWORD PTR DS:[EBX+348h],EAX ; добавляем защищающемуся Attack
		JMP [bdy_done]

; ======================================================================================

Calculate_DMG_RESIST:
		PUSH ESI
		MOV ESI,EAX ; резервируем начальный урон, который должен получить враг до учета сопротивления
		IMUL EAX,ECX ; перемножаем Урон на % Сопротивления
		MOV ECX,100
		IDIV ECX ; делим на 100, получаем сколько урона будет ВЫТЕРПЛЕНО
		SUB ESI,EAX ; вычитаем из изначального урона ОТРЕЗИСТЕННЫЙ
		MOV EAX,ESI ; перемещаем результат в EAX
		POP ESI
		RET

gets_Injury_from_attacker:
		CMP DWORD PTR DS:[EBX+70h],0
		JLE [zero_fix]
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h
		FSTP ST
		ADD ECX,DWORD PTR DS:[EBX+368h]
		LEA ECX,DWORD PTR DS:[ECX+958h] 			
		MOV ECX,DWORD PTR DS:[ECX+8]
		MOV EDX,DWORD PTR DS:[ECX+64h] ; gets Damage Type in EDX
		MOV ECX,DWORD PTR DS:[ECX+44h] ; gets Injury in ECX
		RET ; result in ECX, type of Injury in EDX
		
	zero_fix:		
		IMUL ECX,DWORD PTR DS:[EBX+74h],1B0h ; если 70-й почему-то пустой, то будет браться с 74
		FSTP ST
		ADD ECX,DWORD PTR DS:[EBX+368h]
		LEA ECX,DWORD PTR DS:[ECX+958h] 			
		MOV ECX,DWORD PTR DS:[ECX+8]
		MOV EDX,DWORD PTR DS:[ECX+64h] ; gets Damage Type in EDX
		MOV ECX,DWORD PTR DS:[ECX+44h] ; gets Injury in ECX
		RET ; result in ECX, type of Injury in EDX
		
; ======================================================================================

type_r: ; для завершени
		POP EDX
		POP ECX
		POP EAX

		SUB DWORD PTR DS:[EDI+2FCh],ECX
		ADD DWORD PTR DS:[EDI+34Ch],ECX
		JMP [regular_damage]
		
no_chance: ; если не хватило рандома, урон просто пройдется по цели
		POP EBX
		POP EDX
		POP ECX
		POP EAX

		SUB DWORD PTR DS:[EDI+2FCh],ECX
		ADD DWORD PTR DS:[EDI+34Ch],ECX
		JMP [regular_damage]
		
bdy_done:
		POP EDX
		POP ECX
		POP EAX
		MOV DWORD PTR DS:[EBX+0B4h],3 ; даем Шейк Атакующему в 1\10 секунды
		MOV DWORD PTR DS:[EDI+0B4h],-3 ; даем Шейк Цели в 1\10 секунды
		JMP [after_damage]
		
cold_weapon:
		
		

hurtingBodies endp




bdy50 proc

		PUSH EDX
		PUSH ECX
		
		IMUL ECX,DWORD PTR DS:[EDI+70h],1B0h ; получаем страницу фрейма
		FSTP ST
		ADD ECX,DWORD PTR DS:[EDI+368h]
		LEA ECX,DWORD PTR DS:[ECX+95Ch] ;bdy
		CMP DWORD PTR DS:[ECX],0 	
		JLE [skip]
		MOV ECX,DWORD PTR DS:[ECX+8]
		MOV EDX,DWORD PTR DS:[ECX]
		CMP EDX, 50
		JE [bdy_50]
skip:
		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+0B0h],50h
		JMP [bdy50_back]

bdy_50:
		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+0B0h],0
    	JMP [bdy50_back]
    	

bdy50 endp


















