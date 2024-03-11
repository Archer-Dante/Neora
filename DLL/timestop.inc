.data
timeStop db FALSE

;loop2
loop2_r		dd 004067F6h

;frame update
frame_r1 dd 0041FB04h
frame_r2 dd 0041FB0Bh

;movement
mov_r1 dd 0041E652h
mov_r2 dd 0041E657h

;frame sh*t
frameshit_r1 dd 0041E35Bh
frameshit_r2 dd 0041E364h

;shaking
shaking_r dd 0042F2D6h

;create object
co_r dd 004064A6h

;timestop_opoint
ts_opoint1 dd 0041FC89h
ts_opoint2 dd 004203B4h

.code

timestop_opoint proc
	
	cmp timeStop, FALSE
	je normal
	push eax
	mov eax,dword ptr ds:[memAlloc]
	lea eax, dword ptr ds:[eax+edi*8]
	cmp byte ptr ds:[eax],1
	pop eax
	jnz skip
	
normal:
	CMP DWORD PTR DS:[ECX+7FCh],EDX
	MOV DWORD PTR SS:[ESP+38h],ECX
	JLE skip
	jmp [ts_opoint1]

skip:
	jmp [ts_opoint2]	

timestop_opoint endp

create_object proc
    
    MOV DWORD PTR DS:[ESI+418h],EBX
    pushad
    mov esi, dword ptr ss:[esp+24h]
	
    cmp esi, 400
    jg not_start
	
    mov ecx,dword ptr ds:[memAlloc]
    lea ecx,dword ptr ds:[ecx+esi*8]
    mov byte ptr ds:[ecx],0
    mov dword ptr ds:[ecx+1],0
    
    mov ecx,dword ptr ds:[solAlloc]
    lea ecx,dword ptr ds:[ecx+esi*8]
   	mov dword ptr ds:[ecx],777
   	
    jmp return
    
not_start:    
    cmp timeStop,FALSE
    je return
    cmp edi,400
    jg return
    mov esi, dword ptr ss:[esp+20h]
    mov eax,dword ptr ds:[memAlloc]
    lea eax, dword ptr ds:[eax+edi*8] ;creator
    mov cl, byte ptr ds:[eax]
 	mov ebx,dword ptr ds:[memAlloc]    
    lea ebx, dword ptr ds:[ebx+esi*8] ;opointed thingy
    mov byte ptr ds:[ebx],cl
    mov ecx,dword ptr ds:[eax+1]
    mov dword ptr ds:[ebx+1],ecx
    
    
return:
	popad
    jmp [co_r]
create_object endp

shaking proc
    
    cmp timeStop,TRUE
    je return
    mov dword ptr ds:[edx+0b4h],-3

    return:
    jmp [shaking_r]

shaking endp

time_loop proc
    
    MOV EDX,DWORD PTR DS:[450B90h]
    pushad
    mov eax,0
    mov timeStop, FALSE
    looop:
    cmp byte ptr ds:[458B00h+eax+4],0
    je chk_chk_boom
    mov ebx,dword ptr ds:[memAlloc]
    lea ebx,dword ptr ds:[ebx+eax*8]
    cmp byte ptr ds:[ebx],1
    jnz skip
    mov timeStop,TRUE
    jmp return

chk_chk_boom:
	mov ebx,dword ptr ds:[memAlloc]
	lea ebx,dword ptr ds:[ebx+eax*8]
	mov byte ptr ds:[ebx],0
	mov dword ptr ds:[ebx+1],0    
	
skip:
    inc eax
    cmp eax,190h
    jl looop    
return:
    popad
    ret

time_loop endp

frame_shit proc
    
    MOV ECX,DWORD PTR DS:[450B90h]
    cmp timeStop, FALSE
    je disabled
    push eax
    mov eax,dword ptr ds:[memAlloc]
    lea eax,dword ptr ds:[eax+esi*8]
    cmp byte ptr ds:[eax],1
    pop eax
    jnz skip
disabled:
    jmp [frameshit_r1]
    
skip:
    jmp [frameshit_r2]

frame_shit endp

movement proc
    MOV ECX,DWORD PTR DS:[EBX+EDI*4+194h]
    cmp timeStop, FALSE
    je disabled
    push eax
    mov eax,dword ptr ds:[memAlloc]
    lea eax,dword ptr ds:[eax+edi*8]
    cmp byte ptr ds:[eax],1
    pop eax
    jnz skip
disabled:
    jmp [mov_r1]
    
skip:
    jmp [mov_r2]    

movement endp

frame_update proc
    
    MOV ECX,DWORD PTR DS:[EBX+EDI*4+194h]
    cmp timeStop, FALSE
    je disabled
    push eax
    mov eax,dword ptr ds:[memAlloc]
    lea eax,dword ptr ds:[eax+edi*8]
    cmp byte ptr ds:[eax],1
    pop eax
    jnz skip
disabled:    
    jmp [frame_r1]
    
skip:
    jmp [frame_r2]
frame_update endp

loop2 proc
    
    push eax
    mov eax,dword ptr ss:[esp+18h]
    mov ecx,dword ptr ds:[memAlloc]
    lea eax,dword ptr ds:[ecx+eax*8]
    cmp dword ptr ds:[eax+1],0
    jle remove_timestop
    add dword ptr ds:[eax+1],-1
    jmp return
	
remove_timestop:
    mov byte ptr ds:[eax],0
    
return:    
    pop eax
    
    MOV ECX,DWORD PTR DS:[EAX+368h]
    jmp [loop2_r]
    
loop2 endp