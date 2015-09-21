.Data

comp_back1	dd 004326EAh
comp_back2  dd 004326DEh


.Code

comparator proc

		CMP [replay_switch],TRUE
		JE [skip]

		CMP EAX,DWORD PTR DS:[44F620h]
		JE SHORT [skip]
		JMP [comp_back2]
skip: 
		JMP [comp_back1]

comparator endp