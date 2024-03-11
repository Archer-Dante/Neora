
.data
criminal_teams_back	dd 0042E6D8h








.code

better_criminals proc

                 ; using ECX cuz game waste it below anyway
		MOV ECX,DWORD PTR DS:[EBX+364h]  
		MOV DWORD PTR DS:[EDI+364h],ECX
		
		; rest of the original code to make it work properly
		MOV ECX,DWORD PTR DS:[EAX]
		SUB ECX,3E8h
		MOV DWORD PTR DS:[EDI+70h],ECX
		MOV EAX,3
		MOV DWORD PTR DS:[EBX+0B4h],EAX
		NEG EAX
		MOV DWORD PTR DS:[EDI+0B4h],EAX

		JMP [criminal_teams_back]


better_criminals endp