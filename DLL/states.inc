.data

Transform1	dd 0041F675h ;state8xxx
TransBack1  dd 0041F60Ah ;state4xxxx
TurnBack1   dd 00413350h ;StateTurn
TurnBack2 	dd 0041336Fh
BackSt_9x_1 dd 0042ECAFh
BackSt_9x_2 dd 0042ED2Ch

;state_turning
st_r1		dd 00414099h
st_r2		dd 00414243h
st_r3		dd 00414159h
;hit_teammates
ht_r1		dd 004177CAh
ht_r2		dd 00417866h
ht_r3		dd 0041780Bh

.code

State8xxx proc

		CMP EDX, 38
		JE plus140
		CMP EDX, 37
		JE plus140
		CMP EDX, 36
		JE plus140
		CMP EDX, 35
		JE plus140
		CMP EDX, 34
		JE plus140
		CMP EDX, 33
		JE plus140
		CMP EDX, 32
		JE plus140
		CMP EDX, 31
		JE plus140
		CMP EDX, 30
		JE plus140

		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EDX+70h],0
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EAX+318h],0
		JMP [Transform1]

plus140:
		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EDX+70h],0
		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
		MOV DWORD PTR DS:[EAX+318h],8Ch
		JMP [Transform1]


State8xxx endp





StateMore proc

		PUSH EDX ;reserve
		PUSH EAX ;reserve
		PUSH ECX ;reserve
		PUSH EBX ;reserve
			
		CMP EAX,9C40h ; 40000
		JL  [skip] ; Если меньше - в обычный код
		CMP EAX,0C34Fh ; 49999
		JLE [State4xxxx]
		CMP EAX,0EA5Fh ; 59999
		JLE [State5xxxx]
		CMP EAX,1116Fh ; 69999
		JLE [State6xxxx]
		CMP EAX,1387Fh ; 79999
		JLE [State7xxxx]
		
		JMP [skip] ; если ни один из стейтов выше

State4xxxx:
		SUB EAX, 9C40h ; 40000
		
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		MOV DWORD PTR DS:[ECX+10h],EAX ; change X of object
		FILD DWORD PTR DS:[ECX+10h] ; load X as float
		FSTP QWORD PTR DS:[ECX+58h] ; store it to float number zone

		JMP [skip]
		
State5xxxx:
		SUB EAX, 0C350h ; 50000
		
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		MOV DWORD PTR DS:[ECX+14h],EAX ; change Y of object
		FILD DWORD PTR DS:[ECX+14h] ; load Y as float
		FSTP QWORD PTR DS:[ECX+60h] ; store it to float number zone

		JMP [skip]
		
State6xxxx:
		SUB EAX, 0EA60h ; 60000
		
		MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		MOV DWORD PTR DS:[ECX+18h],EAX ; change Z of object
		FILD DWORD PTR DS:[ECX+18h] ; load Z as float
		FSTP QWORD PTR DS:[ECX+68h] ; store it to float number zone

		JMP [skip]

State7xxxx:
		;SUB EAX, 11170h ; 70000

		MOV EAX,DWORD PTR DS:[EBX+EDI*4h+3ECh]
		
		MOV EBX,DWORD PTR DS:[EDX+ECX+908h]
		CMP EBX, 64h; weapon kind 100
		JNE [skip]
	
		FLD DWORD PTR DS:[EDX+ECX+920h]
		FSTP QWORD PTR DS:[EAX+58h]
		FLD DWORD PTR DS:[EDX+ECX+924h]
		FSTP QWORD PTR DS:[EAX+60h]
		FLD DWORD PTR DS:[EDX+ECX+928h]
		FSTP QWORD PTR DS:[EAX+68h]
		
		JMP [skip]
		

skip:	
		POP EBX ;reserve	
		POP ECX ;reserve
		POP EAX ;reserve
		POP EDX ;reserve
		
		CMP EAX,2328 ; 9000
		JGE SHORT [recover_1]
		JMP [TransBack1]

recover_1:
		JMP [Transform1]


StateMore endp


StateTurn3x proc

		CMP EDX,1Eh ; State 30
		JE [State30]
		CMP EDX,1Fh ; State 31
		JE [State31]
		CMP EDX,20h ; State 32
		JE [State32]
		CMP EDX,12Dh ; State 301
		JMP [TurnBack1]

State30:
		CMP BYTE PTR DS:[ESI+82h],1h
		JGE [State30_3]
		ADD BYTE PTR DS:[ESI+82h],1h
		
State30_1:
		CMP BH, 1h
		JGE [State30_2]
		ADD BH, 1h
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]
		
State30_2:
		XOR BH,BH
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]
		
State30_3:
		MOV BYTE PTR DS:[ESI+82h],0h
		JMP [TurnBack2]



State31:
		MOV BH, 1h
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]

State32:
		XOR BH,BH ; set 0 WTF
		MOV BYTE PTR DS:[ESI+80h],BH
		JMP [TurnBack2]


StateTurn3x endp




State9xxx proc
	
	MOV EAX, DWORD PTR DS:[ECX+EDX+838h]
    CMP EAX,0BB8h ; 3000
	JE [Back1] ; regular code, for state 3000
	CMP EAX,2328h ; 9000 - minimum
	JL SHORT [Back2] ; regular code, for another states
	CMP EAX,2647h ; 9799 - limit
	JG SHORT [Back2] ; regular code, for another states
	

	SUB EAX, 2328h
	MOV DWORD PTR DS:[EBX+70h],EAX
	MOV DWORD PTR DS:[EBX+88h],0h
	FST QWORD PTR DS:[EBX+40h]
	FLD DWORD PTR DS:[ECX+EDX+848h]
	FSTP QWORD PTR DS:[EBX+50h]
	JMP [BackSt_9x_2]
	
Back1:
	JMP [BackSt_9x_1]
	
Back2:
	JMP [BackSt_9x_2]

State9xxx endp











