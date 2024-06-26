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
        
		IMUL ECX,DWORD PTR DS:[EDI+70h],1B0h ; �������� �������� ������
		FSTP ST
		ADD ECX,DWORD PTR DS:[EDI+368h] ; ���������� �������� ������ � ������ �������, ����� �������� ������
		LEA EDX,DWORD PTR DS:[ECX+95Ch] ; ��������� � EDX ���������� ������������ "bdy" � ������
		CMP DWORD PTR DS:[EDX],0 		; ���������, ��� ���� ���� �� 1 "bdy"
		JLE [not_match1] 				
		MOV EAX,DWORD PTR DS:[EDX+8]	; ������������ � ��������� �� �������� "bdy"
										; ������� ��������, ��� ��������� ������ 1, ���� ���� "bdy" ���������
										; ��� ������� ������, ��� �� ������ ������� "bdy" �� ������������
										; �� ������� ���� � ��������� LF2 ������ ���
										; � ���� ������ �� �������� ��������� �� ����� ������� (������) "bdy",
										; ������� ��� ��������� ������ Itr
		
		CMP DWORD PTR DS:[EAX],999		; ��������, ��� ���� "bdy" �� ������ 999
		JLE [not_match1]				; ���� ��� - ������
		
		CMP DWORD PTR DS:[EAX],1999		; ��������, ��� ���� "bdy" ������ 1999
		JL [bdy1000]					; ���� ������, �� ��� 1000-1999
		
		CMP DWORD PTR DS:[EAX],2999		; ��������, ��� ���� "bdy" ������ 2999
		JL [bdy2000]					; ���� ������, �� ��� 2000-2999
		
		CMP DWORD PTR DS:[EAX],3999		; ��������, ��� ���� "bdy" ������ 3999
		JL [bdy3000]					; ���� ������, �� ��� 3000-3999
		
		CMP DWORD PTR DS:[EAX],4999		; ��������, ��� ���� "bdy" ������ 4999
		JL [bdy4000]					; ���� ������, �� ��� 4000-4999
		
		JMP [not_match1] ; ��� ���������� �����, ����� ���������� ����������� BDY
		
		
bdy1000:
		MOV ECX,DWORD PTR DS:[EBX+368h]
		CMP DWORD PTR DS:[ECX+6F8h],0
		JNE [finish_xzzz]
		CMP DWORD PTR DS:[ECX+364h],5
		JE  [finish_xzzz]
		
		MOV ECX,DWORD PTR DS:[EBX+364h]
		MOV DWORD PTR DS:[EDI+364h],ECX	; ��������� ������� ���� ������� (�� ��������� ������ ECX ����� 1)
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,1000					; �������� XXX �� "bdy" 1xxx
		MOV DWORD PTR DS:[EDI+70h],ECX	; ���������� ������ � ���� XXX						
		MOV DWORD PTR DS:[EBX+0B4h],3 ; ���� ���� ���������� � 1\10 �������
		MOV DWORD PTR DS:[EDI+0B4h],-3 ; ���� ���� ���� � 1\10 �������
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
		MOV DWORD PTR DS:[EBX+0B4h],3 ; ���� ���� ���������� � 1\10 �������
		MOV DWORD PTR DS:[EDI+0B4h],-3 ; ���� ���� ���� � 1\10 �������
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
		JNZ SHORT [to_exit]
		CMP DWORD PTR DS:[EDI+2F4h],-1
		JNZ SHORT [to_exit]
		MOV EDX,DWORD PTR DS:[EBX+354h]
		MOV EAX,DWORD PTR DS:[ESI+EDX*4+3ECh]
		ADD DWORD PTR DS:[EAX+348h],ECX


to_exit:	JMP [after_damage]
		


bdy_rework endp

bdy_solo_hit_recall proc ; ���������� ����� bdy ��� ��������� �����

		MOV DWORD PTR DS:[EDI+280h],EDX ; ������������ ������ �� ������ � �������
			
			;PUSH EAX
			;PUSH ECX
			
			MOV EAX,DWORD PTR DS:[EDI+170h]
			MOV ECX,DWORD PTR SS:[EBP-20h]
			MOV DWORD PTR DS:[EAX+0],ECX

			;POP ECX
			;POP EAX


			JMP [solo_hit_recall]

bdy_solo_hit_recall endp

bdy_multi_hit_recall proc ; ���������� ����� bdy ��� ��������� �����

		MOV DWORD PTR DS:[EDI+EDX*4+280h],ECX ; ������������ ������ �� ������ � ��������


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

			; EBX - ���������
			; EDI - ������
			; ECX - ����
			; ESI - �������� �� ���������� ������� \ �������
			
			; EAX - �����
			; EDX - �����

			; ==== ���������� ����� ====
			; +0 - ��������� �� ��������� � Indiv ��������� ����������
			; +4 - ����� ���������� �������
			; +8 - �������� �� ���������� ������� \ ������� (�� �� � ESI ���)
			; +C - ��������� �� ����� �����, ��� ��������� ��������� ���� ITR �� ����� ����������
			; 		( ������������ �� ������ 0042E2EC ��� ������� MOV DWORD PTR SS:[ESP+C],EDX )
						; +0 - kind
						; +4 - x
						; +8 - y
						; +C - w
						; +10 - h
						; ....
						; +68 - bdefend
						; +6C - injury
						; ....
						; +8C - ��������� �� �������������� ��������� �� Neora
			; +10 - ???
			; +14 - ������� �� ����� ��������� �������������� ITR � BDY �� ��������������� ����� (?)
			; +68 - bdefend (� ������� ����� ����� ���� ����)
			; +6C - injury  (� ������� ����� ����� ���� ����)
			; +8C - ��������� �� �������������� ��������� �� Neora (� ������� ����� ����� ���� ���� + ������ "EBP-18h")

			PUSH EBX
			MOV EAX,DWORD PTR DS:[EBX+354h] ; ���������� ������ � ����������
			CMP EAX,99 ; ���� ��� ����������� ��������, �������� � ����, �� ������ "������ 99"
			JE [finish_it]
			MOV EBX,DWORD PTR DS:[ESI+EAX*4+3ECh] ; �������� ������� ������� ��� ���������� ������ �� ��� ������

			CALL [calculate_scaling] ; ���������� � ECX �������� "injury + scale_stat@scale_value"
			CALL [calculate_critical] ; ���������� � ECX �������� ����������� �� crit_power � ������ ������ �����
			CALL [calculate_resists] ; ���������� � ECX �������� ����� ����� ������������� ���� ����� � "dtype"
			
			
			
			MOV EAX,DWORD PTR DS:[EDI+368h]
			CMP DWORD PTR DS:[EAX+6F8h],0 ; t0
			JNE [finish_it] ; ������� call ���� ��������� ������ ��� t0; ���� ������ �� t0 - �������
			
			CALL [hp_regen_hurt_cd] ; ������� ����� ������ �� ������ ������ �� � ������ 
			CALL [mp_regen_hurt_cd] ; ������� ����� ������ �� ������ ������ �� � ������ 
			CALL [mp_regen_on_hurt] ; ����� �� ��� ��������� ����� �������

finish_it:	POP EBX
			JMP [dmg_calc_rework_back]
			
dmg_calc_rework endp

calculate_scaling proc
			PUSH ESI
			PUSH EDI
			
			MOV EDX, DWORD PTR SS:[EBP-18h] ; ����������� ��������� �� ����������� ������ ITR
			TEST EDX,EDX
			JZ [skip] ; ����������� ������
			MOV EAX, DWORD PTR SS:[EDX+4h] ; scale_stat � EAX
			MOV ESI, DWORD PTR SS:[EBX+190h] ; ���������� ������ � ����������
			MOV ESI, DWORD PTR SS:[ESI+EAX*4] ; �������� ������ ���� � ESI
			TEST ESI,ESI ; ��������� ��� ���� �� ����� 0
			JLE [skip]
			
			MOV EAX, DWORD PTR SS:[EDX+8h] ; scale_value � EAX
			TEST EAX,EAX ; ��������� ��� ���� �� ����� 0
			JLE [skip]
			IMUL EAX,ESI ; ����������� scale_stat � scale_value
			CDQ
			MOV EDI,100
			IDIV EDI ; ����� �� 100, �������� � EAX ���������������� ����
			
			ADD ECX,EAX ; ���������� ������������ ���� � �������� �� injury
			
			skip:
			POP EDI
			POP ESI
			RET
calculate_scaling endp

calculate_critical proc
			PUSH ESI
			PUSH EDI

			PUSH 100 ; ����� �������
			PUSH ECX ; �����������
			CALL DWORD PTR DS:[random]
			MOV EDI,EAX ; ��������� ������� � EDI
			POP ECX   ; ��������������� ������� ����
			ADD ESP,4 ; ���� �����

			MOV EDX, DWORD PTR SS:[EBP-18h] ; ����������� ��������� �� ����������� ������ ITR
			TEST EDX,EDX
			JZ [skip] ; ����������� ������
			MOV EAX, DWORD PTR SS:[EDX+0Ch] ; crit_chance � EAX
			MOV ESI, DWORD PTR SS:[EBX+190h] ; ���������� ������ � ����������
			TEST ESI,ESI
			JZ [skip] ; ����������� ������
			ADD EAX, DWORD PTR SS:[ESI+50h] ; �������� ������ ���� "crit_chance_total" � ���������� ��� �����
			
			CMP EAX,EDI
			JL [skip] ; ���� ���� ������ �������
			
			MOV EAX, DWORD PTR SS:[EDX+10h] ; crit_power �� ITR � EAX
			ADD EAX, DWORD PTR SS:[ESI+54h] ; �������� ������ ���� "crit_power_total" � ���������� ��� �����
			
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

			MOV EDX, DWORD PTR SS:[EBP-18h] ; ����������� ��������� �� ����������� ������ ITR
			TEST EDX,EDX
			JZ [skip] ; ����������� ������
			MOV EAX, DWORD PTR SS:[EDX+0h] ; dtype � EAX
			MOV ESI, DWORD PTR SS:[EDI+190h] ; ���������� ������
			MOV ESI, DWORD PTR SS:[ESI+EAX*4+28h] ; �������� ������ ������ � ESI
			TEST ESI,ESI ; ��������� ��� ������ �� ����� 0
			JLE [skip]

			MOV EAX,ECX ; �������� ��������� ����
			IMUL EAX,ESI
			CDQ
			MOV EDI,100
			IDIV EDI ; �������� � EAX ���������� �����, ������� �� �������
			SUB ECX,EAX ; �������� ��� �������� �� ECX (���������� ���������� �����)
			
			skip:
			POP EDI
			POP ESI
			RET
	
calculate_resists endp

hp_regen_hurt_cd proc
			
			MOV EDX, DWORD PTR DS:[EDI+190h] ; ���������� ������ � ����������
			MOV EAX, DWORD PTR DS:[EDX+78h] ; hp_regen_hurt_cd total
			TEST EAX,EAX 
			JLE [skip] ; �������, ���� ����� ������ 0 ��� �����������
			MOV DWORD PTR DS:[EDX+0D4h],EAX ; hp_regen_hurt_cd timer | ������� �� ��������� �� �����������
			
			skip:
			RET

hp_regen_hurt_cd endp

mp_regen_hurt_cd proc
			
			MOV EDX, DWORD PTR DS:[EDI+190h] ; ���������� ������ � ����������
			MOV EAX, DWORD PTR DS:[EDX+7Ch] ; mp_regen_hurt_cd total
			TEST EAX,EAX 
			JLE [skip] ; �������, ���� ����� ������ 0 ��� �����������
			MOV DWORD PTR DS:[EDX+0DCh],EAX ; mp_regen_hurt_cd timer | ������� �� ��������� �� �����������
			
			skip:
			RET

mp_regen_hurt_cd endp

mp_regen_on_hurt proc
			
			MOV EDX, DWORD PTR DS:[EDI+190h] ; ���������� ������ � ����������
			MOV EAX, DWORD PTR DS:[EDX+80h] ; mp_regen_on_hurt
			TEST EAX,EAX 
			JE [skip] ; �������, ���� ��� 0 ��� �������� �����������
			ADD DWORD PTR DS:[EDI+308h],EAX ; �������� �� ������
			
			skip:
			RET

mp_regen_on_hurt endp
















