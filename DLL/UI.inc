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



	CMP EDX,1000 ; ����� ��� ������ ����� �����
	JGE SHORT [healing_normal]
	MOV EDX,DWORD PTR DS:[ECX+0E4h] ; ��������, ��� ����� ����
	
healing_normal:
	AND EDX,1
	MOV ECX,20 ; �������� � 20 �������� ��� �� ����
	JE [go_to_push] ; ���� ����� ���, ���������� ������� ���� � ����� ���� � PUSH ECX ������������� ����
	ADD ECX,20 ; + 20 ��������, ���� �������
	JMP [HP_bars_changer]



demon_bar:
	POP EDX

	CMP EDX,1000 ; ����� ��� ������ ����� �����
	JGE SHORT [healing_special_1]
	MOV EDX,DWORD PTR DS:[ECX+0E4h] 
	
healing_special_1:
	AND EDX,1 
	MOV ECX,76 ; �������� ��� ����
	JE [go_to_push] 
	MOV ECX,86 ; �������� ��� ������� ���� ��������
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
	; ��������� ������ ���� ����, ���� ��� ����� �� \ �� � ������ ����������
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
	; ��������� ����-������ ����������
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
	; ������������ ��������� �������! ����! (������ ������������) \ ������ ��� �������
	; ======================================================================
		
			MOV ECX,DWORD PTR DS:[44FD7Ch]
			MOV EDX,DWORD PTR DS:[ECX]
			PUSH DWORD PTR DS:[EDX]
			CALL [call_0043E9A0]
			
	; ======================================================================
	; ������ ��� �������
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
			PUSH 0Ah	; ������ ��������
			PUSH EAX	; ������ ��������
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
			PUSH 0Ah	; ������ ��������
			PUSH 7Ch	; ������ ��������
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
			
		; �������� ������ � ������ ��� ���������� ����
			
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
		
		; ��������� ���������� ����
		
			repeater_3:
				XOR EDX,EDX
				PUSH EBP
				PUSH 0
				MOV DL,BYTE PTR DS:[EBX+455CB7h]
				PUSH 1
				PUSH EDX ; �������� �� X
				PUSH EDI ; �������� �� Y
				PUSH ESI
				MOV ECX,DWORD PTR DS:[44FD7Ch]
				CALL [call_0043F010]
				ADD ESI,9
				DEC EBX
				JG [repeater_3]
				
		; ����������� �����
				
		LEA ESI,DWORD PTR DS:[EDI+14h]
		MOV EDX,DWORD PTR SS:[ESP+8]
		MOV ECX,10 ; ������-����������� (�������� �� 10 �����) � ������������ �������� � �����
		MOV EDI,00455CB8h ; ����� ������
		MOV ESI,DWORD PTR DS:[EDX+308h] ; ����������� �������� ����� ����, �.�. ��� �������� ������� �� ���� �����
		
		MOV EBX, DWORD PTR DS:[EDX+190h]
		MOV EBX, DWORD PTR DS:[EBX+60h]
		TEST EBX,EBX
		MOV EAX,1F4h
		JZ [skip_if_no_max_mp]
		MOV EAX,DWORD PTR DS:[EDX+190h]
		MOV EAX,DWORD PTR DS:[EAX+60h] ; ���� ���� ���� ���� - ���������� �
		skip_if_no_max_mp:
		XOR EBX,EBX
		
			repeater_4:
				CDQ 		 ; �����
				IDIV ECX	 ; �������� ������� ������ ����� � EDX (����� �� 10)
				XCHG EAX,EDX ; ������� � EAX
				STOS BYTE PTR ES:[EDI] ; ���������� ������� �� EAX � �����, ������� EDI+1 ����
				XCHG EAX,EDX ; ���������� ������� � EAX ��� ����������� �����
				INC EBX		 ; ����������� ������� �������� � ������
				TEST EAX,EAX	
				JNZ [repeater_4] ; ���� � EAX ��� ���-�� �������� - ��������� ���� �����
		
		MOV AL,CL ; �������� 10-�� (��� ������ "\") � EAX ��� ������ � �����
		INC EBX ; ����� � ���� ������
		STOS BYTE PTR ES:[EDI] ; ���������� ������-����������� � �����
		MOV EAX,ESI ; ������ ����������� �� ����� ����������������� ����� ������� ����
		XOR ESI,ESI	; ESI ������ �� �����, ������� �� ������

			repeater_5:
				INC ESI		
				CDQ			; �����
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
				MOV DL,BYTE PTR DS:[EBX+455CB7h] ; ���������� �� ������ ����� ������ ����� �� BARS.png
				PUSH 1
				PUSH EDX ; ����� �� �������� BARS.ong �������� ��� ��������� ��������
				PUSH ESI ; �������� y
				PUSH EDI ; �������� �
				MOV ECX,DWORD PTR DS:[44FD7Ch]
				CALL [call_0043F010]
				ADD EDI,9 ; ������ ���� ���� �� �����
				DEC EBX	  ; ������� � ��������� ����� (������ ����� �������������� ��������)
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
			TEST ECX,ECX ; ���� �� ������� ������
			JE [skip_both] ; ���� ��� - ������� ��������� ������
			
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




