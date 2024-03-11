ARMOR_KNIGHT1		dd 0042E688h
ARMOR_KNIGHT2		dd 0042E6ECh
ARMOR_LOUIS1		dd 0042E6F5h
ARMOR_LOUIS2		dd 0042E7CEh
ARMOR_JULIAN1		dd 0042E7D5h
ARMOR_JULIAN2		dd 0042E80Ah
ARMOR_JULIAN3		dd 0042FDF2h

Armor_Knight proc
		MOV ECX,DWORD PTR DS:[ECX+6F4h]; line over written
		CMP ECX,37
		je short return
		;cmp ecx,id
		;je short return
		jmp  dword ptr [ARMOR_KNIGHT2]
return: jmp  dword ptr [ARMOR_KNIGHT1]

Armor_Knight endp

Armor_Louis proc
		CMP ECX,6 
		je short return
		;CMP ECX,ID
		;je short return
		jmp dword ptr [ARMOR_LOUIS2]
return: jmp dword ptr [ARMOR_LOUIS1]

Armor_Louis endp

Armor_Julian proc
		CMP ECX,52 
		je short return
		CMP ECX,55
		je short arm_0
		;CMP ECX,ID
		;je return2
		jmp return2
return: jmp dword ptr [ARMOR_JULIAN1]

;##customise the recover speed of armor below
arm_0:	mov eax,dword ptr ds:[esi+edi*4+194h]
		cmp dword ptr ds:[eax+0B8h],36			; the speed, was 15 for Julian
		jg return2
		mov eax,dword ptr ds:[esi+ebx*4+194h]
		mov eax,dword ptr ds:[eax+368h]
		mov eax,dword ptr ds:[eax+6F4h]
		cmp eax,0D6h
		je return2
		cmp eax,0D0h
		je return2
		jmp dword ptr [ARMOR_JULIAN3]
		
return2:jmp dword ptr [ARMOR_JULIAN2]

Armor_Julian endp















