.Data

FPS_back   dd 0043D13Eh

tt_proceed dd 00413119h
tt_blocked dd 004143C6h

ts_sub_back dd 0041DD4Fh

ts_timer dd ?
ts_team  dd ?
ts_type  dd ?

ts_fix	 dd 0043D159h

.Code


TimeStop proc
		CMP DWORD PTR DS:[ts_timer],0
		JE [proceed]
		
		CMP DWORD PTR DS:[ts_team],0
		JNE [ts_setup_1]
		
		CMP DWORD PTR DS:[ts_type],2
		JE [ts_setup_2]
		
ts_setup_0:
		CMP DWORD PTR DS:[ESI+158h],-1
		JE [proceed]
		CMP DWORD PTR DS:[ESI+158h],0
		JE [new_object]

		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+158h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������
		
ts_setup_1:
		MOV EAX,DWORD PTR DS:[ts_team]
		CMP EAX,DWORD PTR DS:[ESI+364h] ; ��������, ��� ������� ��
		JE [proceed]

		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+158h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������
		
ts_setup_2:
		MOV EAX,DWORD PTR DS:[ESI+368h]
		CMP DWORD PTR DS:[EAX+6F8h],0
		JE [proceed]

		MOV DWORD PTR DS:[ESI+0B4h],3
		SUB DWORD PTR DS:[ESI+158h],1
		JMP [blocked] ; ���������� ������, ��������� ���������� ����������
		
new_object:
		MOV EAX, DWORD PTR DS:[ts_timer]
		MOV DWORD PTR DS:[ESI+158h],EAX
		JMP [blocked]

proceed:
		MOV EAX,DWORD PTR DS:[ESI+368h]
		MOV EBP,DWORD PTR DS:[EAX+6F8h]
		JMP [tt_proceed]
		
blocked:
		MOV EAX,DWORD PTR DS:[ESI+368h]
		MOV EBP,DWORD PTR DS:[EAX+6F8h]
		JMP [tt_blocked]


TimeStop endp





FPS_rework proc

		MOV EBX,3 ; fast value in F5 mode
		CMP DWORD PTR DS:[44D02Ch],0 ; check if F5 is enabled
		JE SHORT [change_fps]
		
		MOV EBX,33 ; regular FPS
		
		CMP DWORD PTR DS:[450BDCh],1 ; check if round close to ends up
		JLE [change_fps]
		CMP DWORD PTR DS:[450BDCh],18h ; check timer of round ending
		JGE [regular]
		ADD EBX,65 ; end round slow motion

change_fps:
		JMP [FPS_back]

regular:
		MOV EBX,33 ; regular FPS
		JMP [FPS_back]

FPS_rework endp





TS_substactor proc
	
		CMP BYTE PTR DS:[44FCB0h],1 ; �������� �� �����
		JE [skip]
		
		MOV EAX, DWORD PTR DS:[ts_timer]
		CMP EAX,0 ; ���������, ���� �� ��
		JE [skip]
		
		SUB DWORD PTR DS:[ts_timer],1
	
skip:	
		MOV EAX,DWORD PTR DS:[450BDCh]
		JMP [ts_sub_back]

TS_substactor endp

 

TS_menu_fix proc

	CMP DWORD PTR DS:[44D020h],0
	JE [skip]
	MOV DWORD PTR DS:[ts_timer],0

skip:
	MOV EAX,DWORD PTR DS:[457BC8h]
	JMP [ts_fix]

TS_menu_fix endp





