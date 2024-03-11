.Data

mp_back	dd 0041FAEBh
hp_back	dd 0041F9E8h

.Code

mana_speed proc
	
	push ecx ; reserve
	push edx ; reserve
	push ebx ; reserve
	push edi ; reserve

	MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh] ; connetion to object
	MOV EDX,DWORD PTR DS:[ECX+368h] ; data-file
	MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID of object
	CMP EDX, 37h ; 55 ID
	JE  [mp_mod]
	CMP EDX, 33h ; Firzen ID
	JE  [mp_boss]
	CMP EDX, 34h ; Julian ID
	JE  [mp_boss]
	JMP [mp_std]
	
	mp_mod:
	pop edi ; reserve
	pop ebx ; reserve
    pop edx ; reserve
    pop ecx ; reserve
    ADD ECX, 0Ah ; mega-regen
    ADD DWORD PTR DS:[ESI+308h],0

    JMP [mp_back]
    
    mp_std:
	pop edi ; reserve
	pop ebx ; reserve
    pop edx ; reserve
    pop ecx ; reserve
    ADD DWORD PTR DS:[ESI+308h],0 ; standart regen

    JMP [mp_back]
    
    mp_boss:
	pop edi ; reserve
	pop ebx ; reserve
    pop edx ; reserve
    pop ecx ; reserve
    ADD ECX, 1h ; +1 special mp for Julian & Firzen
    ADD DWORD PTR DS:[ESI+308h],0

    JMP [mp_back]
    
mana_speed endp

hp_speed proc
	
	push ecx ; reserve
	push edx ; reserve
	push ebx ; reserve
	push edi ; reserve

	MOV ECX,DWORD PTR DS:[EBX+EDI*4h+3ECh] ; connetion to object
	MOV EDX,DWORD PTR DS:[ECX+368h] ; data-file
	MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ID of object
	CMP EDX, 37h ; 55 ID
	JE  [hp_mod]
	JMP [hp_std]
	
	hp_mod:
	pop edi ; reserve
	pop ebx ; reserve
    pop edx ; reserve
    pop ecx ; reserve
    ADD DWORD PTR DS:[ESI+2FCh],0Ah

    JMP [hp_back]
    
    hp_std:
	pop edi ; reserve
	pop ebx ; reserve
    pop edx ; reserve
    pop ecx ; reserve
    ADD DWORD PTR DS:[ESI+2FCh],1 ; standart regen

    JMP [hp_back]
    
hp_speed endp