.Data

e1_t1_e9 dd 0042F554h
e1_t2_e9 dd 0042F54Fh
e1_t3_e9 dd 0042F594h ;0042F58Fh ; ���� ������������ ������� ����� ����������

e_finish dd 0043087Ch ; ���� ������ ��� ������� ����� ���� ��������� � ����������.
					  ; � ���� ���� �� ������������, �� ����� ��������� �������� �� ����
e50_back1 dd 0042E918h

back_to_effect_cmps  dd 004174ABh
back_to_effect_cmps2 dd 0042F5A9h
back_to_inv_cmps	 dd 0041753Bh
back_it_bypasses_inv dd 0041754Bh
.Code


itr_effect_1xxx_to_9xxx proc

; REPEATING CODE SHOULD BE REWORKED WITH PROCS AND CALLS	
	CMP EAX, 0
	JGE [skip_neg]
	NEG EAX ; invertion

skip_neg:

	CMP EAX,3 ; Ice Effect
	JE [Back1]
	CMP EAX, 3E8h ; 1000
	JL [Back2]  ; ���� ������ 1000, ������ �����
	
	PUSH EAX ; �����������
	PUSH EBX ; �����������
	PUSH ECX ; �����������
	PUSH EDX ; �����������

effect1xxx:
	CMP EAX, 7CFh ; 1999
	JG [effect2xxx]
	
	SUB EAX,3E8h ; -1000, �������� ����� ��� �����
	MOV EDX,DWORD PTR DS:[EBX+2FCh] ; �������� �� ���������� � �B�
	SUB EDX, EAX ; �������� �� �� ������ ����.
	CMP EDX, 0 ; ���������, ��� ���������� �������� �� ������ ����
	JGE [valid_1xxx]
	MOV EDX, 0 ; ���� ����� ���� � �����, ���������� 0, ����-���
	valid_1xxx:
	MOV DWORD PTR DS:[EBX+2FCh],EDX ; ���������� ���������� ��
	ADD DWORD PTR DS:[EBX+34Ch],EDX ; ������ HP Lost

	JMP [Back4]

effect2xxx:
	CMP EAX, 0BB7h ; 2999
	JG [effect3xxx]

	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type2] ; ��������� ���������, �� ������������ ����
	
	SUB EAX,7D0h ; -2000, ����� ��� ������
	ADD DWORD PTR DS:[EBX+2FCh],EAX ; ��������� ���������� ��

	wrong_type2:	
	JMP [Back4]

effect3xxx:
	CMP EAX, 0F9Fh ; 3999
	JG [effect4xxx]
	
	SUB EAX,0BB8h ; -3000
	ADD DWORD PTR DS:[EBX+2FCh],EAX ; ��������� ���������� ��

	JMP [Back4]

effect4xxx:
	CMP EAX, 1387h ; 4999
	JG [effect5xxx]

	SUB EAX,0FA0h ; -4000
	SUB DWORD PTR DS:[EBX+308h],EAX ; �������� ����
	ADD DWORD PTR DS:[EBX+350h],EAX ; ������ MP Lost

	JMP [Back4]
	
effect5xxx:
	CMP EAX, 176Fh ; 5999
	JG [effect6xxx]
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type5] ; ��������� ���������, �� ������������ ����
	
	SUB EAX,1388h ; -5000
	ADD DWORD PTR DS:[EBX+308h],EAX ; ��������� ����
	
	wrong_type5:	
	JMP [Back4]
	
effect6xxx:
	CMP EAX, 1B57h ; 6999
	JG [effect7xxx]

	SUB EAX,1770h ; -6000
	ADD DWORD PTR DS:[EBX+308h],EAX ; ��������� ����
	
	JMP [Back4]
	
effect7xxx:
	CMP EAX, 1F3Fh ; 7999
	JG [effect8xxx]
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type7] ; ��������� ���������, �� ������������ ����

	PUSH EAX ; �����������
	
	SUB EAX,1B58h ; -7000
	SUB DWORD PTR DS:[EDI+308h],EAX ; �������� ����
	ADD DWORD PTR DS:[EDI+350h],EAX

	POP EAX ; ���������������
	
	wrong_type7:	
	JMP [Back4]

effect8xxx:
	CMP EAX, 2327h ; 8999
	JG [effect9xxx] 
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type8] ; ��������� ���������, �� ������������ ����
	
	SUB EAX,1F40h ; -8000
	SUB DWORD PTR DS:[EDI+308h],EAX ; �������� ����
	ADD DWORD PTR DS:[EDI+350h],EAX
	ADD DWORD PTR DS:[EBX+308h],EAX ; ��������� ����
	
	wrong_type8:	
	JMP [Back4]

effect9xxx:
	CMP EAX, 270Fh ; 9999
	JG [Back2_over9000] ; ������ ������, ������� �����.
	
	MOV EDX,DWORD PTR DS:[EDI+368h]
	CMP DWORD PTR DS:[EDX+6F8h],0
	JNZ [wrong_type9] ; ��������� ���������, �� ������������ ����

	PUSH EAX ; �����������
	
	SUB EAX,2328h ; -9000
	MOV DWORD PTR DS:[EDI+70h],EAX ; ���������� ����

	POP EAX ; ���������������
	
	wrong_type9:	
	JMP [Back4]

Back1: 
	JMP [e1_t1_e9] ; ���� ��� ��������� �����, �� ���� ������
Back2:
	JMP [e1_t2_e9] ; ���� �� �������� ������ ��������, ���� �� ���� �� ������
	
Back2_over9000:
	POP EDX
	POP ECX
	POP EBX
	POP EAX
	JMP [e1_t2_e9]
	
Back3:
	JMP [e_finish]
Back4:
	POP EDX ; ���������������
	POP ECX ; ���������������
	POP EBX ; ���������������
	POP EAX ; ���������������
	
	MOV ECX,DWORD PTR SS:[ESP+0Ch] ; ��������������� ����������� � ITR �������
	PUSH DWORD PTR DS:[ECX+28h] ; respond TAG
	MOV EAX,DWORD PTR DS:[EDI+10h] ; ����� ������������� ����, ����� �-����������
	
	JMP [e1_t3_e9] ; ��������� ���������

itr_effect_1xxx_to_9xxx endp





effect50 proc

		PUSH EDX
		PUSH ECX
		
		IMUL ECX,DWORD PTR DS:[EBX+70h],1B0h ; �������� �������� ������
		FSTP ST
		ADD ECX,DWORD PTR DS:[EBX+368h]
		LEA ECX,DWORD PTR DS:[ECX+958h] 
		CMP DWORD PTR DS:[ECX],0 	
		JLE [skip]
		MOV ECX,DWORD PTR DS:[ECX+8]
		MOV EDX,DWORD PTR DS:[ECX+2Ch] ; ������
		CMP EDX, 50
		JE [eff_50]
		
		IMUL ECX,DWORD PTR DS:[EDI+70h],1B0h ; �������� �������� ������
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
		MOV DWORD PTR DS:[EDI+70h],EDX
		MOV DWORD PTR DS:[EDI+0B0h],ECX
		JMP [e50_back1]

eff_50:
		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+0B0h],0
    	JMP [e50_back1]
    	
    	
untouchable_true:
		MOV EDX,DWORD PTR DS:[EDX]
		TEST EDX,EDX
		JZ [skip]

		POP ECX
		POP EDX
		MOV DWORD PTR DS:[EDI+0B0h],0
    	JMP [e50_back1]


effect50 endp





pierce_invincibles proc

	mov ecx,[ebx+2Ch] ; original code

	CMP ECX, 0
	JGE [skip] ; ??????? ???? ?? ??????????

	MOV EAX, 42h ; magic number, flags that effect was neg
	NEG ECX ; invertion

skip: 
	cmp ecx,04h ; original code
	JMP [back_to_effect_cmps]

pierce_invincibles endp


eff_chk_pierce_inv proc ; effect_check_for_pierce_invincibles

	mov eax,[ecx+2Ch] 		;original code

	; REPEATING CODE SHOULD BE REWORKED WITH PROCS AND CALLS
	CMP EAX, 0
	JGE [skip_neg] ; ??????? ???? ?? ??????????
	NEG EAX ; invertion

skip_neg:
	cmp eax,02h
	JMP [back_to_effect_cmps2]

eff_chk_pierce_inv endp



pierce_inv_checker proc

	mov edx,[ebx]				;original code (without it selfharm appears xD)

	CMP EAX, 42h
	JE [attack_invincible]

	cmp dword ptr [esi+08],00	;original code
	JMP [back_to_inv_cmps]

attack_invincible: 
	JMP [back_it_bypasses_inv]


pierce_inv_checker endp










