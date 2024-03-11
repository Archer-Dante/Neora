.Data

comp_back1	dd 004326EAh



.Code

comparator proc

		CMP EAX,DWORD PTR DS:[44F620h]
		JMP comp_back1

comparator endp