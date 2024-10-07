.Data 

players_sequence 		byte 8 DUP(00h)
players_menu_press_cd 	byte 8 DUP(00h)


.code
	
konami_code proc

	mov edx, offset players_menu_press_cd
	cmp byte ptr [edx+ebp], 0
	jg [sub_and_ret]
	
	mov edx, offset players_sequence
	cmp byte ptr [edx+ebp], 0
	je [key_1]
	cmp byte ptr [edx+ebp], 1
	je [key_2]
	cmp byte ptr [edx+ebp], 2
	je [key_3]
	cmp byte ptr [edx+ebp], 3
	je [key_4]
	cmp byte ptr [edx+ebp], 4
	je [key_5]
	cmp byte ptr [edx+ebp], 5
	je [key_6]
	cmp byte ptr [edx+ebp], 6
	je [key_7]
	cmp byte ptr [edx+ebp], 7
	je [key_8]
	cmp byte ptr [edx+ebp], 8
	je [key_9]
	cmp byte ptr [edx+ebp], 9
	je [key_10]
	cmp byte ptr [edx+ebp], 10
	jne [sub_and_ret]
	mov edx, offset players_sequence
	mov byte ptr [edx+ebp], 0  ; сбрасываем счётчик если 10 набралось
	call [konami_code_set_character] ; переходим в назначение персонажа
	; mov edx, 451288h
	; mov byte ptr [edx+ebp], 1 
	jmp [go_ret]
	
key_1:
	cmp byte ptr [eax+0CDh], 1 ; UP ^
	jne	[go_ret]
	jmp short [key_success]
key_2:
	cmp byte ptr [eax+0CDh], 1 ; UP ^
	jne	[go_ret]
	jmp short [key_success]
key_3:
	cmp byte ptr [eax+0CEh], 1 ; DOWN v
	jne	[go_ret]
	jmp short [key_success]
key_4:
	cmp byte ptr [eax+0CEh], 1 ; DOWN v
	jne	[go_ret]
	jmp short [key_success]
key_5:
	cmp byte ptr [eax+0CFh], 1 ; LEFT <
	jne	[go_ret]
	jmp short [key_success]
key_6:
	cmp byte ptr [eax+0D0h], 1 ; RIGHT >
	jne	[go_ret]
	jmp short [key_success]
key_7:
	cmp byte ptr [eax+0CFh], 1 ; LEFT <
	jne	[go_ret]
	jmp short [key_success]
key_8:
	cmp byte ptr [eax+0D0h], 1 ; RIGHT >
	jne	[go_ret]
	jmp short [key_success]
key_9:
	cmp byte ptr [eax+0D3h], 1 ; BLOCK D
	jne	[go_ret]
	jmp short [key_success]
key_10:
	cmp byte ptr [eax+0D1h], 1 ; ATTACK A
	jne	[go_ret]
	jmp short [key_success]
	
key_success:
	mov edx, offset players_sequence
	inc byte ptr [edx+ebp]		; увеличиваем на 1, т.к. верное нажатие
	mov edx, offset players_menu_press_cd
	mov byte ptr [edx+ebp], 5   ; назначаем кд нажатия на кнопку
	; mov byte ptr [451268h+ebp*4], 0;
	jmp short [go_ret]
	
sub_and_ret:
	sub byte ptr [edx+ebp], 1
	
go_ret:
	; restore original code and return
	add     esp, 18h
	xor     edx, edx
	push 	0042A653h
	ret

konami_code endp






darki_code proc

	mov edx, offset players_menu_press_cd
	cmp byte ptr [edx+ebp], 0
	jg [sub_and_ret]
	
	mov edx, offset players_sequence
	cmp byte ptr [edx+ebp], 0
	je [key_1]
	cmp byte ptr [edx+ebp], 1
	je [key_2]
	cmp byte ptr [edx+ebp], 2
	je [key_3]
	cmp byte ptr [edx+ebp], 3
	je [key_4]
	cmp byte ptr [edx+ebp], 4
	je [key_5]
	cmp byte ptr [edx+ebp], 5
	jne [sub_and_ret]
	mov edx, offset players_sequence
	mov byte ptr [edx+ebp], 0  ; сбрасываем счётчик если 10 набралось
	call [konami_code_set_character] ; переходим в назначение персонажа
	; mov edx, 451288h
	; mov byte ptr [edx+ebp], 1 
	jmp [go_ret]
	
key_1:
	cmp byte ptr [eax+0CDh], 1 ; UP ^
	jne	[go_ret]
	jmp short [key_success]
key_2:
	cmp byte ptr [eax+0CEh], 1 ; DOWN v
	jne	[go_ret]
	jmp short [key_success]
key_3:
	cmp byte ptr [eax+0CFh], 1 ; LEFT <
	jne	[go_ret]
	jmp short [key_success]
key_4:
	cmp byte ptr [eax+0D0h], 1 ; RIGHT >
	jne	[go_ret]
	jmp short [key_success]
key_5:
	cmp byte ptr [eax+0D3h], 1 ; BLOCK D
	jne	[go_ret]
	jmp short [key_success]
key_6:
	cmp byte ptr [eax+0D1h], 1 ; ATTACK A
	jne	[go_ret]
	jmp short [key_success]
	
key_success:
	mov edx, offset players_sequence
	inc byte ptr [edx+ebp]		; увеличиваем на 1, т.к. верное нажатие
	mov edx, offset players_menu_press_cd
	mov byte ptr [edx+ebp], 5   ; назначаем кд нажатия на кнопку
	; mov byte ptr [451268h+ebp*4], 0;
	jmp short [go_ret]
	
sub_and_ret:
	sub byte ptr [edx+ebp], 1
	
go_ret:
	; restore original code and return
	add     esp, 18h
	xor     edx, edx
	push 	0042A653h
	ret

darki_code endp








konami_code_set_character proc

	mov ecx, dword ptr DS:[452980h] ; пишем указатель на список всех загруженных dat-объектов
	xor edx, edx
	
inc_and_repeat:
	inc edx
	cmp edx, dword ptr DS:[452990h] ; счётчик сколько всего dat-объектов загружено
	jge short [finish_and_exit]
	
	; если ещё лимита объектов нет, проверяем что по текущему ID
	mov eax, dword ptr [ecx+edx*4]
	cmp dword ptr [eax+6F4h], 97 ; ID 97 
	jne short [inc_and_repeat]
	
	mov ecx, dword ptr [ebx+ebp*4+3ECh]
	mov dword ptr[451248h+ebp*4], edx
	mov dword ptr[ecx+368h], eax
	mov dword ptr[451268h+ebp*4], 1

finish_and_exit:
	ret
	

konami_code_set_character endp




konami_code_cancel_confirm proc
	
	
	mov eax, offset players_sequence
	cmp byte ptr [eax+ebp], 10
	jne short [go_ret]
	mov eax, 451288h
	mov byte ptr [eax+ebp], 1 

	; возврат и выход с восстановление оригинальных функций
go_ret: 	
	xor eax, eax ; это делали все функции до текущей изменяемой, вероятно для получения 0, который везде добавляется
	
	cmp dword ptr [ecx], 2
    jnz short [cf_true]
cf_false: ; нет прыжков, просто для наглядности
	push 0042ADF1h
	ret
cf_true:
	push 0042AE13h
	ret
	

konami_code_cancel_confirm endp



























