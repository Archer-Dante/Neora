.data

disable_menu_render 	dd	 0EBh
diff_back dd 0042D74Eh


.code


lock_game_mode proc

		MOV DWORD PTR DS:[451160h],1
		MOV DWORD PTR DS:[44D020h],1
		RET

lock_game_mode endp



;0041C5BD
;0041D7E8
;0041DB9C
;00429F5B
;0042A0C5
;0041C5BD
;0041D7E8





only_crazy proc

MOV ECX,00455610h
MOV DWORD PTR DS:[450C30h],-1
JMP [diff_back]

only_crazy endp             





;0042D71E - 29 1D 300C4500  - sub [00450C30],ebx
;0042D73E - C7 05 300C4500 02000000 - mov [00450C30],00000002
