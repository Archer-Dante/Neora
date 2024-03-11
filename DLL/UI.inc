.Data

HP_bars_changer dd 0041B03Ah

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



	CMP EDX,1000 ; нужно для работы хилки джона
	JGE SHORT [healing_normal]
	MOV EDX,DWORD PTR DS:[ECX+0E4h] ; проверка, что хилка есть
	
healing_normal:
	AND EDX,1
	MOV ECX,20 ; смещение в 20 пикселей для хп бара
	JE [go_to_push] ; если хилки нет, пропускаем строчку ниже и сразу идем в PUSH ECX оригинального кода
	ADD ECX,20 ; + 20 пикселей, если хилимся
	JMP [HP_bars_changer]



demon_bar:
	POP EDX

	CMP EDX,1000 ; нужно для работы хилки джона
	JGE SHORT [healing_special_1]
	MOV EDX,DWORD PTR DS:[ECX+0E4h] 
	
healing_special_1:
	AND EDX,1 
	MOV ECX,76 ; смещение для бара
	JE [go_to_push] 
	MOV ECX,86 ; смещение для особого вида подхилки
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