.Data

all_stats_calculation_b		 dd 00413F24h

.Code



calculate_Max_MP proc

	; ECX � EDX �������� ��������� �� ID �������� (��� t0)
	; EDI - ��������� �� Frame ��������
	; ESI - ��������� �� Individual ��������

	
	PUSHA

	MOV ECX, DWORD PTR DS:[ESI+190h] ; ECX - ����� � ����� malloc �� Individual
	TEST ECX,ECX
	JZ [skip_all]









skip_all:



calculate_Max_MP endp








all_stats_calculation proc

	; ECX � EDX �������� ��������� �� ID �������� (��� t0)
	; EDI - ��������� �� Frame ��������
	; ESI - ��������� �� Individual ��������
	
		PUSHA

		MOV ECX,DWORD PTR DS:[ESI+368h] ; ������������ �� ������ ���� ������ �� t0
		CMP DWORD PTR DS:[ECX+6F8h],0 ; ������ ��� �� t0 ��������
		JG  [PERSONAL_ONLY]
		
		MOV ECX, DWORD PTR DS:[ESI+190h] ; ECX - ����� � ����� malloc �� Individual


; ������� ������ ������ � �����
ITEMS_ONLY:
		XOR EAX,EAX
		XOR EDX,EDX  
		XOR EBX,EBX  ; �������� �� ������ ������ ����
		
		stat_cleaning:
		MOV DWORD PTR DS:[ECX+EAX*4h],EBX ; ���������� ����� ����� ��������� ������
		INC EAX
		CMP EAX,20 						; 20 ������� ����� �������� Stat � Resist ����
		JL [stat_cleaning] 
		
		MOV EBP, 8h ; ��������� �������� � EBP (item stat)
		PUSH 8 ; ���������� ������, ����� ��������� ������� ������� �� ���������
		PUSH 8 ; �������� ����� EAX
		CALL [item_stats_calculator]
		ADD ESP,8
		; �� ������ ������ ���, ������ ��������� ��������� �������� � EBP � ���������
		
		MOV EBP, 30h ; ��������� �������� � EBP (item resist)
		PUSH 8 ; ���������� ������, ����� ��������� ������� ������� �� ���������
		PUSH 8 ; �������� ����� EAX
		CALL [item_stats_calculator]
		ADD ESP,8
		; �� ������ ������ ���, ������ ��������� ��������� �������� � EBP � ���������

		JMP [BUFFS_ONLY]

; �� �� �� - ������ ��������� ���������� ���� ������ ������ �� ���� �����
		item_stats_calculator:
		MOV EAX, DWORD PTR SS:[ESP+4]
		stat_EBP_next_item:
		LEA EBX, DWORD PTR DS:[EBX+80h]			; ������ EBX - ������ ����, �� ������ ����� +80h
				CMP DWORD PTR DS:[ECX+EBX],0	; ��������, ��� ��� ���� ���� (�� ID 0)
				JLE [empty_slot]
		LEA EDI, DWORD PTR DS:[EBX+EBP]			; � EBP �������� �� ������ ���� �� ������ ������� ����
		ADD EDX, DWORD PTR DS:[ECX+EDI]  		; "stat EBP affection" ������ � EDX ����� �������
				empty_slot:
		DEC EAX									; ��������� ���� ���������� �����
		CMP EAX,0
		JG [stat_EBP_next_item]
		
		LEA EAX,[EBP-8h] ; ������ �� EBP �������� �� ������� ����, � ������� +0 �������� ��� �����
		ADD DWORD PTR DS:[ECX+EAX],EDX		; stat_X ��������� ��� ����, ����������
		XOR EDX,EDX ; ��� ��� �� �������� �� ������ � ���� �� ����� �� ���� �����, �������� ����� ��������� ������
		ADD EBP,4h ; �� 1 ���� ������

		XOR EBX,EBX ; ������� ������� ��������
		DEC DWORD PTR SS:[ESP+8] ; ��������� ����� ���������� ��� ����� ������
		CMP DWORD PTR SS:[ESP+8],0
		JG [item_stats_calculator] ; ���� ��� ����� �������� - ���������
		RET




; ������� ������ ������ � �����
BUFFS_ONLY:
		XOR EAX,EAX
		MOV EBX, 480h-58h ; �������� �� ������ ������� ����
		
		
		MOV EBP, 8h ; ��������� �������� � EBP (buff stat 0)
		PUSH 8  ; ���������� ������, ����� ��������� ������� ������� �� ���������
		PUSH 16 ; �������� ����� EAX
		CALL [buff_stats_calculator]
		ADD ESP,8
		
		MOV EBP, 30h ; ��������� �������� � EBP (buff resist 0)
		PUSH 8  ; ���������� ������, ����� ��������� ������� ������� �� ���������
		PUSH 16 ; �������� ����� EAX
		CALL [buff_stats_calculator]
		ADD ESP,8

		JMP [PERSONAL_ONLY]


; �� �� �� - ������ ��������� ���������� ���� ������ ������ �� ���� �����
		buff_stats_calculator:
		MOV EAX, DWORD PTR SS:[ESP+4]
		stat_EBP_next_buff:
		LEA EBX,[EBX+58h]					; ������ EBX - ������ ���, �� ������ ����� +58h
				CMP DWORD PTR DS:[ECX+EBX],0; ��������, ��� � ���� ���� ��� ����� ��������
				JLE [no_active_buff]
		LEA EDI,[EBX+EBP]					; � EBP �������� �� ������ ���� �� ������ ������� ����
		ADD EDX, DWORD PTR DS:[ECX+EDI]		; "stat EBP affection" ������ � EDX ����� �������
				no_active_buff:
		DEC EAX								; ��������� ���� ���������� �����
		CMP EAX,0
		JG [stat_EBP_next_buff]
		
		LEA EAX,[EBP-8h] ; ������ �� EBP �������� �� ������� ����, � ������� +0 �������� ��� �����
		ADD DWORD PTR DS:[ECX+EAX],EDX		; stat_X ��������� ��� ����, ����������
		XOR EDX,EDX ; ��� ��� �� �������� �� ������ � ���� �� ����� �� ���� �����, �������� ����� ��������� ������
		ADD EBP,4h ; �� 1 ���� ������

		MOV EBX, 480h-58h ; ������� ������� ��������
		DEC DWORD PTR SS:[ESP+8] ; ��������� ����� ���������� ��� ����� ������
		CMP DWORD PTR SS:[ESP+8],0
		JG [buff_stats_calculator] ; ���� ��� ����� �������� - ���������
		RET



; ������� ������ ������ �� ����� ���������
PERSONAL_ONLY:

		MOV ECX,DWORD PTR DS:[ESI+368h]
		MOV ECX,DWORD PTR DS:[ECX+0C0h] ; ������� �������� ������
		TEST ECX,ECX
		JE [skip_all]
		
		MOV EDX,DWORD PTR DS:[ESI+190h] ; EDX - ����� � ����� malloc �� Individual
		XOR EBX,EBX
		
		add_stats:
		MOV EAX,DWORD PTR DS:[ECX+100h+EBX*4h]
		ADD DWORD PTR DS:[EDX+EBX*4h],EAX
		INC EBX
		CMP EBX,8
		JL [add_stats]
		
		ADD EDX,28h ; ���������� ������ �� Stat ������� � Resist ������
		XOR EBX,EBX
		
		add_resists:
		MOV EAX,DWORD PTR DS:[ECX+150h+EBX*4h]
		ADD DWORD PTR DS:[EDX+EBX*4h],EAX
		INC EBX
		CMP EBX,8
		JL [add_resists]



skip_all:
		POPA ; �������� � ���, ����� ��� ������ %)
		JMP [all_stats_calculation_b]


all_stats_calculation endp