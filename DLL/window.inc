.Data

Window_back1	dd 0041A0FBh
Window_back2 	dd 0041A103h
Window_back3 	dd 00401B48h
Window_back4 	dd 00401011h
Window_back5 	dd 00401075h
Window_back6 	dd 0042387Ch
Window_back7 	dd 0043F044h
Window_back8 	dd 0043F092h
Window_back9	dd 0041A27Ah
Window_back10	dd 0041A197h
Window_back11	dd 0041A103h
Window_back12	dd 0041A208h
Window_back13	dd 0041A90Eh
Window_back14	dd 0041A910h
Window_back15	dd 0041BB96h
Window_back16	dd 0041BC4Bh
Window_back17	dd 0041BC43h
Window_back18	dd 0042A1C9h
Window_back19	dd 004010EDh
Window_back20	dd 00437B68h
Window_back21	dd 004384EAh
Window_back22	dd 0043854Dh

name_back 	dd 00401B8Ch




.Code

Window_Size proc

		MOV EAX,DWORD PTR DS:[ECX+ESI*4+1BC0h]
		TEST EAX,EAX
		JNZ jnz_01
		CMP DWORD PTR DS:[ECX+ESI*4+13F0h],0
		JNZ jnz_02
		XOR EAX,EAX
		MOV DWORD PTR SS:[ESP+1Ch],EAX
		
		PUSH EBX
		MOV EBX,[win_width]
		CMP DWORD PTR DS:[ECX],EBX
		JLE SHORT jle_03
		POP EBX
		
		MOV EDX,DWORD PTR DS:[452984h]
		MOV EDI,DWORD PTR DS:[ECX]
		MOV EAX,DWORD PTR DS:[EDX+ESI*4+0DB0h]
		SUB EAX,[win_width]
		IMUL EAX,DWORD PTR DS:[450BC4h]
		CDQ
		SUB EDI,[win_width]

window_proceed:
		JMP DWORD PTR [Window_back1]
jnz_01:
		JMP DWORD PTR [Window_back9]
jnz_02:
		JMP DWORD PTR [Window_back10]
jle_03:
		POP EBX
		JMP DWORD PTR [Window_back11]

Window_Size endp


Window_Size_2 proc
	

		;MOV ECX,DWORD PTR DS:[44D78Ch]
		MOV ECX,[win_width] ; width: 1024
		;MOV EDX,DWORD PTR DS:[44D790h]
		MOV EDX,[win_height] ; height: 768
		JMP [Window_back3]


Window_Size_2 endp


Window_Size_3 proc
	
		;PUSH 226h
		PUSH [win_height]
		;PUSH 31Ah
		PUSH [win_width]

		JMP [Window_back4]


Window_Size_3 endp


Window_Size_4 proc
	
		MOV ECX,DWORD PTR SS:[ESP+4h]
		MOV EDX,DWORD PTR SS:[ESP+8h]
		MOV EAX,DWORD PTR SS:[ESP+0Ch]
		PUSH EAX
		XOR EAX,EAX
		PUSH EAX
		PUSH EAX
		PUSH EDX
		PUSH [win_height]
		PUSH [win_width]
		PUSH EAX
		PUSH EAX
		PUSH ECX
		CALL DWORD PTR DS:[4575DCh]

		JMP [Window_back5]


Window_Size_4 endp


Window_Size_5 proc
	
		PUSH EAX
		PUSH [win_height]
		PUSH [win_width]
		PUSH 0h
		PUSH 0h

		JMP [Window_back6]

Window_Size_5 endp

Window_Size_6 proc
	
		MOV EDX,[win_width]
		CMP EAX,EDX

		JMP [Window_back7]

Window_Size_6 endp


Window_Size_7 proc
	
		MOV EDX,[win_height]
		CMP EAX,EDX

		JMP [Window_back8]

Window_Size_7 endp


Window_Size_8 proc
	
		MOV EAX,DWORD PTR DS:[ECX+ESI*4+13F0h]
		MOV ECX,DWORD PTR DS:[EDI]
		MOV DWORD PTR SS:[ESP+20h],EAX
		LEA EAX,DWORD PTR DS:[ESI*4+0DB0h]
		MOV DWORD PTR SS:[ESP+1Ch],EAX
		MOV EAX,DWORD PTR DS:[EAX+EDI]
		SUB EAX,[win_width]
		IMUL EAX,DWORD PTR DS:[450BC4h]
		SUB ECX,[win_width]

		JMP [Window_back12]

Window_Size_8 endp



Window_Size_9 proc
	
		CMP EAX,[win_width]
		JL Window_blabla1
		MOV EDX,[win_width]
		LEA EAX,DWORD PTR DS:[ECX+ECX+1h]

		JMP [Window_back13]
		
Window_blabla1:
		JMP [Window_back14]

Window_Size_9 endp


Window_Size_10 proc

		MOV EDX,DWORD PTR DS:[452984h]
		MOV EAX,DWORD PTR DS:[EDX]
		SUB EAX,[win_width] ;важная часть, определяет границу карты относительно экрана вычитанием
		CMP ESI,EAX	

		JMP [Window_back15]

Window_Size_10 endp

Window_Size_11 proc

		MOV EAX,DWORD PTR DS:[452984h]
		MOV EBX,DWORD PTR DS:[EAX]
		

		LEA EAX,DWORD PTR DS:[EBX] ;решить
		SUB EAX,[win_width] ; добавлено
		
		CMP EDI,EAX
		JLE SHORT Window_blabla2
		JMP [Window_back17]
 
Window_blabla2:
		JMP [Window_back16]

Window_Size_11 endp


Window_Size_12 proc

		PUSH [win_height]
		PUSH [win_width]
		
		JMP [Window_back18]

Window_Size_12 endp


Window_Size_13 proc 

		SUB ESI,[win_width]
		
		JMP [Window_back20]

Window_Size_13 endp

Window_Size_14 proc 

		MOV ECX,15h
		SUB ECX,EAX
		IMUL ECX,ECX,2Bh
		MOV EAX,66666667h
		IMUL ECX
		SAR EDX,2
		MOV EAX,EDX
		PUSH 0
		SHR EAX,1Fh
		ADD EAX,EDX
		PUSH EAX
		PUSH [win_width]
		PUSH ESI
		PUSH 0

		JMP [Window_back21]

Window_Size_14 endp

Window_Size_15 proc 

		IMUL EAX,EAX,2Bh
		MOV ECX,EAX
		MOV EAX,66666667h
		IMUL ECX
		SAR EDX,2
		MOV ECX,EDX
		PUSH 0
		SHR ECX,1Fh
		ADD ECX,EDX
		PUSH ECX
		PUSH [win_width]
		PUSH ESI
		PUSH 0

		JMP [Window_back22]

Window_Size_15 endp



Application_Name proc
		
		XOR ECX,ECX
		XOR EDX,EDX
		XOR EAX,EAX
		
		MOV EDI,00455CB8h
		LEA ESI,[GameName]
		
	leigth_calc:
		MOV DL,BYTE PTR DS:[ESI+ECX]
		INC ECX
		CMP DL,00h
		JNE [leigth_calc]
		
	write_string:
		MOV AL, BYTE PTR DS:[ESI+EDX]
		MOV BYTE PTR DS:[EDI+EDX*2],AL
		ADD EDX,1
		DEC ECX
		CMP ECX,0
		JNE [write_string]
		
		JMP [name_back]

Application_Name endp










