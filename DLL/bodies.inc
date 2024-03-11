.data

body_back_1	dd 0042E683h
body_back_2 dd 00430A67h
body_back_3 dd 0042E6DDh

untouchable_back  dd 0042E8A4h

regular_damage  dd 0042E767h
after_damage	dd 0042E792h

karters_attributes dd 00430DA0h
dmg_calc_rework_back dd 0042E75Bh


solo_hit_recall 	dd 0041787Fh
multi_hit_recall 	dd 004179F5h
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
		JL [bdy1000]					; если меньше, то это 1000-1999
		
		CMP DWORD PTR DS:[EAX],2999		; проверка, что этот "bdy" больше 2999
		JL [bdy2000]					; если меньше, то это 2000-2999
		
		CMP DWORD PTR DS:[EAX],3999		; проверка, что этот "bdy" больше 3999
		JL [bdy3000]					; если меньше, то это 3000-3999
		
		CMP DWORD PTR DS:[EAX],4999		; проверка, что этот "bdy" больше 4999
		JL [bdy4000]					; если меньше, то это 4000-4999
		
		JMP [not_match1] ; ДЛЯ УСТРАНЕНИЯ БАГОВ, КОГДА ПОПАДАЕТСЯ НЕИЗВЕСТНЫЙ BDY
		
		
bdy1000:
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
		
bdy2000:	
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
		
bdy3000:	
		MOV ECX,DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],ECX	
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,3000
		MOV DWORD PTR DS:[EDI+70h],ECX
		MOV DWORD PTR DS:[EBX+0B4h],3 ; даем Шейк Атакующему в 1\10 секунды
		MOV DWORD PTR DS:[EDI+0B4h],-3 ; даем Шейк Цели в 1\10 секунды
		JMP [finish_xzzz]
		
bdy4000:	
		MOV ECX,DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],ECX	
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,4000
		MOV DWORD PTR DS:[EDI+70h],ECX
		JMP [finish_xzzz]
	
finish_xzzz:
		JMP [body_back_2]	

not_match1:
		JMP [body_back_3]

weNeedMoarBodies endp




untouchable proc

		PUSH EDX
		PUSH ECX
		
		IMUL ECX,DWORD PTR DS:[EDI+70h],1B0h ; получаем страницу фрейма
		FSTP ST
		ADD ECX,DWORD PTR DS:[EDI+368h]
		LEA ECX,DWORD PTR DS:[ECX+95Ch] ;bdy
		CMP DWORD PTR DS:[ECX],0 	
		JLE [skip]
		MOV ECX,DWORD PTR DS:[ECX+8]
		MOV EDX,DWORD PTR DS:[ECX+20h]
		TEST EDX,EDX
		JNZ [untouchable_true]
skip:
		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+0B0h],50h
		JMP [untouchable_back]

untouchable_true:
		MOV EDX,DWORD PTR DS:[EDX]
		TEST EDX,EDX
		JZ [skip]

		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+0B0h],0
    	JMP [untouchable_back]

untouchable endp



bdy_rework proc


		SUB DWORD PTR DS:[EDI+2FCh],ECX
		ADD DWORD PTR DS:[EDI+34Ch],ECX
		MOV EAX,DWORD PTR DS:[EDI+368h]
		CMP DWORD PTR DS:[EAX+6F8h],0
		JNZ SHORT [exit]
		CMP DWORD PTR DS:[EDI+2F4h],-1
		JNZ SHORT [exit]
		MOV EDX,DWORD PTR DS:[EBX+354h]
		MOV EAX,DWORD PTR DS:[ESI+EDX*4+3ECh]
		ADD DWORD PTR DS:[EAX+348h],ECX


exit:	JMP [after_damage]
		


bdy_rework endp









bdy_solo_hit_recall proc ; записывает какой bdy был подвержен атаке

		MOV DWORD PTR DS:[EDI+280h],EDX ; оригинальная строка по записи № объекта
			
			;PUSH EAX
			;PUSH ECX
			
			MOV EAX,DWORD PTR DS:[EDI+170h]
			MOV ECX,DWORD PTR SS:[EBP-20h]
			MOV DWORD PTR DS:[EAX+0],ECX

			;POP ECX
			;POP EAX


			JMP [solo_hit_recall]

bdy_solo_hit_recall endp



bdy_multi_hit_recall proc ; записывает какой bdy был подвержен атаке

		MOV DWORD PTR DS:[EDI+EDX*4+280h],ECX ; оригинальная строка по записи № объектов


			PUSH EAX
			PUSH ECX
			
			MOV EAX,DWORD PTR DS:[EDI+170h]
			MOV ECX,DWORD PTR SS:[EBP-20h]
			MOV DWORD PTR DS:[EAX+EDX*4+0h],ECX

			POP ECX
			POP EAX


			JMP [multi_hit_recall]

bdy_multi_hit_recall endp







dmg_calc_rework proc
			; 0042E756h

			CALL [karters_attributes] ; poison, silence, slow, confuse reading

			; EBX - атакующий
			; EDI - жертва
			; ECX - урон
			; ESI - указание на количество игроков \ флажков
			
			; EAX - пусто
			; EDX - пусто

			; ==== Содержание стека ====
			; +0 - указатель на указатель с Indiv страницей атакующего
			; +4 - номер атакующего объекта
			; +8 - указание на количество игроков \ флажков (он же в ESI уже)
			; +C - указатель на часть стека, где полностью подгружен весь ITR со всеми атрибутами
			; 		( записывается по адресу 0042E2EC при команде MOV DWORD PTR SS:[ESP+C],EDX )
						; +0 - kind
						; +4 - x
						; +8 - y
						; +C - w
						; +10 - h
						; ....
						; +68 - bdefend
						; +6C - injury
						; ....
						; +8C - указатель на дополнительные параметры от Neora
			; +10 - ???
			; +14 - возврат из общей процедуры взаимодействия ITR и BDY на воспроизведение звука (?)
			; +68 - bdefend (в обычной части стека тоже есть)
			; +6C - injury  (в обычной части стека тоже есть)
			; +8C - указатель на дополнительные параметры от Neora (в обычной части стека тоже есть + аналог "EBP-18h")

			PUSH EBX
			MOV EAX,DWORD PTR DS:[EBX+354h] ; выделенная память у атакующего
			CMP EAX,99 ; фикс для нейтральных объектов, падающих с неба, их хозяин "объект 99"
			JE [finish_it]
			MOV EBX,DWORD PTR DS:[ESI+EAX*4+3ECh] ; получаем хозяина объекта для считывания статов из его данных

			CALL [calculate_scaling] ; возвращает в ECX значение "injury + scale_stat@scale_value"
			CALL [calculate_critical] ; возвращает в ECX значение помноженное на crit_power в случае успеха крита
			CALL [calculate_resists] ; возвращает в ECX значение после учета сопротивления цели урону в "dtype"
			
			
			
			MOV EAX,DWORD PTR DS:[EDI+368h]
			CMP DWORD PTR DS:[EAX+6F8h],0 ; t0
			JNE [finish_it] ; функции call ниже актуальны только для t0; если жертва не t0 - пропуск
			
			CALL [hp_regen_hurt_cd] ; заносит время отката до работы ренега хп в таймер 
			CALL [mp_regen_hurt_cd] ; заносит время отката до работы ренега мп в таймер 
			CALL [mp_regen_on_hurt] ; реген мп при получении урона жертвой

finish_it:	POP EBX
			JMP [dmg_calc_rework_back]
			
dmg_calc_rework endp




calculate_scaling proc
			PUSH ESI
			PUSH EDI
			
			MOV EDX, DWORD PTR SS:[EBP-18h] ; вытаскиваем указатель на расширенную память ITR
			TEST EDX,EDX
			JZ [skip] ; отсутствует память
			MOV EAX, DWORD PTR SS:[EDX+4h] ; scale_stat в EAX
			MOV ESI, DWORD PTR SS:[EBX+190h] ; выделенная память у атакующего
			MOV ESI, DWORD PTR SS:[ESI+EAX*4] ; получаем нужный стат в ESI
			TEST ESI,ESI ; проверяем что стат не равен 0
			JLE [skip]
			
			MOV EAX, DWORD PTR SS:[EDX+8h] ; scale_value в EAX
			TEST EAX,EAX ; проверяем что стат не равен 0
			JLE [skip]
			IMUL EAX,ESI ; перемножаем scale_stat и scale_value
			CDQ
			MOV EDI,100
			IDIV EDI ; делим на 100, получаем в EAX проскалированный урон
			
			ADD ECX,EAX ; прибавляем получившийся урон к обычному от injury
			
			skip:
			POP EDI
			POP ESI
			RET
calculate_scaling endp

calculate_critical proc
			PUSH ESI
			PUSH EDI

			PUSH 100 ; лимит рандома
			PUSH ECX ; резервируем
			CALL DWORD PTR DS:[random]
			MOV EDI,EAX ; результат рандома в EDI
			POP ECX   ; восстанавливаем текущий урон
			ADD ESP,4 ; фикс стека

			MOV EDX, DWORD PTR SS:[EBP-18h] ; вытаскиваем указатель на расширенную память ITR
			TEST EDX,EDX
			JZ [skip] ; отсутствует память
			MOV EAX, DWORD PTR SS:[EDX+0Ch] ; crit_chance в EAX
			MOV ESI, DWORD PTR SS:[EBX+190h] ; выделенная память у атакующего
			TEST ESI,ESI
			JZ [skip] ; отсутствует память
			ADD EAX, DWORD PTR SS:[ESI+50h] ; получаем нужный стат "crit_chance_total" и складываем оба крита
			
			CMP EAX,EDI
			JL [skip] ; если шанс меньше рандома
			
			MOV EAX, DWORD PTR SS:[EDX+10h] ; crit_power от ITR в EAX
			ADD EAX, DWORD PTR SS:[ESI+54h] ; получаем нужный стат "crit_power_total" и складываем оба крита
			
			IMUL EAX,ECX
			CDQ
			MOV EDI,100
			IDIV EDI
			
			MOV ECX,EAX
			
			skip:
			POP EDI
			POP ESI
			RET
			
calculate_critical endp

calculate_resists proc

			PUSH ESI
			PUSH EDI

			MOV EDX, DWORD PTR SS:[EBP-18h] ; вытаскиваем указатель на расширенную память ITR
			TEST EDX,EDX
			JZ [skip] ; отсутствует память
			MOV EAX, DWORD PTR SS:[EDX+0h] ; dtype в EAX
			MOV ESI, DWORD PTR SS:[EDI+190h] ; выделенная жертвы
			MOV ESI, DWORD PTR SS:[ESI+EAX*4+28h] ; получаем нужный резист в ESI
			TEST ESI,ESI ; проверяем что резист не равен 0
			JLE [skip]

			MOV EAX,ECX ; копируем наносимый урон
			IMUL EAX,ESI
			CDQ
			MOV EDI,100
			IDIV EDI ; получаем в EAX количество урона, которое не пройдет
			SUB ECX,EAX ; вычитаем это значение из ECX (количества наносимого урона)
			
			skip:
			POP EDI
			POP ESI
			RET
	
calculate_resists endp

hp_regen_hurt_cd proc
			
			MOV EDX, DWORD PTR DS:[EDI+190h] ; выделенная память у атакующего
			MOV EAX, DWORD PTR DS:[EDX+78h] ; hp_regen_hurt_cd total
			TEST EAX,EAX 
			JLE [skip] ; пропуск, если время отката 0 или отсутствует
			MOV DWORD PTR DS:[EDX+0D4h],EAX ; hp_regen_hurt_cd timer | счетчик до зарешения на регенерацию
			
			skip:
			RET

hp_regen_hurt_cd endp

mp_regen_hurt_cd proc
			
			MOV EDX, DWORD PTR DS:[EDI+190h] ; выделенная память у атакующего
			MOV EAX, DWORD PTR DS:[EDX+7Ch] ; mp_regen_hurt_cd total
			TEST EAX,EAX 
			JLE [skip] ; пропуск, если время отката 0 или отсутствует
			MOV DWORD PTR DS:[EDX+0DCh],EAX ; mp_regen_hurt_cd timer | счетчик до зарешения на регенерацию
			
			skip:
			RET

mp_regen_hurt_cd endp

mp_regen_on_hurt proc
			
			MOV EDX, DWORD PTR DS:[EDI+190h] ; выделенная память у атакующего
			MOV EAX, DWORD PTR DS:[EDX+80h] ; mp_regen_on_hurt
			TEST EAX,EAX 
			JE [skip] ; пропуск, если там 0 или параметр отсутствует
			ADD DWORD PTR DS:[EDI+308h],EAX ; прибавка мп жертве
			
			skip:
			RET

mp_regen_on_hurt endp
















