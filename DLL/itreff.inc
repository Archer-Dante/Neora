
;itr effect
ef_r1		dd 0042EB1Ah
ef_r2		dd 0042EC6Dh
ef_r3		dd 0042EB43h
ie_r1		dd 0042FCBBh
ie_r2		dd 0042FD1Dh
;ie_c1		dd 00416FD0h
;ie_c2		dd 004170B0h


itr_effect_fall proc
 
	mov eax,dword ptr ss:[esp+0Ch]
	mov eax,dword ptr ds:[eax+2Ch]
	cmp eax,7
	je short no_injure
	cmp eax,8
	je short fall
	cmp eax,9
	je short change_team
	mov eax,dword ptr ds:[esi+edi*4+194h]
	jmp dword ptr [ef_r1]
r3:	jmp dword ptr [ef_r3]

change_team:
	mov eax, dword ptr ss:[esp+4]	
	mov eax, dword ptr ds:[esi+eax*4+194h]
	push ecx
	mov ecx, dword ptr ds:[eax+364h]
 
	mov eax,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[eax+368h] ; this line isn't needed, but i left it anyway
	mov dword ptr ds:[eax+364h],ecx
	pop ecx
	jmp dword ptr [ef_r2]
 
no_injure:
	mov eax,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[eax+368h]
	cmp dword ptr ds:[edx+6F8h],3
	je short r3
	jmp dword ptr [ef_r2]
 
fall:
	mov eax,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[eax+368h]
	cmp dword ptr ds:[edx+6F8h],3
	je short r3
	mov dword ptr ds:[eax+0B0h],50h
	jmp dword ptr [ef_r2]
 
itr_effect_fall endp

itr_effect proc
	
	cmp eax,3
	je short r1
	cmp eax,30
	je short r1
	cmp eax,6
	je e6
	cmp eax,6000
	jge short ie0
r2:	jmp dword ptr [ie_r2]
r1:	jmp dword ptr [ie_r1]
ie0:cmp eax,6400
	jl short frame
	cmp eax,8000
	jl short r2
	cmp eax,9000
	jl transform
	cmp eax,7000000
	jl short r2
	cmp eax,7400000
	jl dependent
	cmp eax,8000000
	jl short r2
	cmp eax,8400000
	jl frame_dependent
	cmp eax,1000000000
	jl short r2
	cmp eax,1400000000
	jl general
	cmp eax,1999000000
	jl short r2
	cmp eax,2000000000
	jl general					; Genevrier's Itr/Effect '1xxxyyyzzz'
	cmp eax,3400000000			; 'Eax' limits
	jl superdependent
	jmp short r2

frame:
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	cmp dword ptr ds:[edx+6F8h],0
	jnz r2
	mov ecx,dword ptr ds:[ecx+78h]
	imul ecx,ecx,178
	cmp dword ptr ds:[ecx+edx+7ACh],eax
	je r2
	sub eax,6000
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],eax
	jmp r2
	
transform:
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	cmp dword ptr ds:[edx+6F8h],0
	jnz r2
	mov ecx,dword ptr ds:[ecx+78h]
	imul ecx,ecx,178
	cmp dword ptr ds:[ecx+edx+7ACh],80
	je r2
	sub eax,8000
	cmp dword ptr ds:[edx+6F4h],eax
	je r2
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],0
	push ebx
	push esi
	add eax,4000
	mov ebx,esi
	mov ecx,dword ptr ds:[ebx+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	MOV ECX,DWORD PTR DS:[EBX+7D4h]
	LEA EDX,DWORD PTR DS:[EAX-0FA0h]
	XOR EAX,EAX
	CMP DWORD PTR DS:[ECX+4D82380h],EAX
	JLE short a
d:	MOV ESI,DWORD PTR DS:[ECX]
	CMP DWORD PTR DS:[ESI+6F4h],EDX
	JE short b
	MOV ESI,DWORD PTR DS:[EBX+7D4h]
	ADD EAX,1
	ADD ECX,4
	CMP EAX,DWORD PTR DS:[ESI+4D82380h]
	JL short d
	JMP short a
b:	MOV ECX,DWORD PTR DS:[EBX+7D4h]
	MOV ECX,DWORD PTR DS:[ECX+EAX*4h]
	MOV EAX,DWORD PTR DS:[EBX+EDI*4+194h]
	MOV DWORD PTR DS:[EAX+368h],ECX
a:	pop esi
	pop ebx
	jmp r2
	
general:
	push ebx
	mov edx,0
	mov ebx,1000000
	idiv ebx
	sub eax,1000
	push eax
	mov eax,edx
	mov edx,0
	mov ebx,1000
	idiv ebx
	push eax
	push edx
	
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	cmp dword ptr ds:[edx+6F8h],0
	jnz g1
	mov ecx,dword ptr ds:[ecx+78h]
	imul ecx,ecx,178
	pop eax
	cmp eax,999
	je short g4
	cmp eax,998
	je g5
	cmp dword ptr ds:[ecx+edx+7ACh],eax
	jnz g2
	
g4:	mov eax,dword ptr ss:[esp+4]
	add eax,6000
	cmp dword ptr ds:[ecx+edx+7ACh],eax
	jnz short g8
	mov eax,dword ptr ds:[ecx+edx+7ACh]
	mov dword ptr ss:[esp+4],eax
	
g8:	pop eax
	cmp eax,999
	je g3
	cmp dword ptr ds:[edx+6F4h],eax
	je g3
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+70h]
	push edx
	mov dword ptr ds:[ecx+70h],0
	add eax,4000
	mov ebx,esi
	mov ecx,dword ptr ds:[ebx+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	MOV ECX,DWORD PTR DS:[EBX+7D4h]
	LEA EDX,DWORD PTR DS:[EAX-0FA0h]
	XOR EAX,EAX
	CMP DWORD PTR DS:[ECX+4D82380h],EAX
	JLE short ga
gd:	MOV ESI,DWORD PTR DS:[ECX]
	CMP DWORD PTR DS:[ESI+6F4h],EDX
	JE short gb
	MOV ESI,DWORD PTR DS:[EBX+7D4h]
	ADD EAX,1
	ADD ECX,4
	CMP EAX,DWORD PTR DS:[ESI+4D82380h]
	JL short gd
	JMP short ga
gb:	MOV ECX,DWORD PTR DS:[EBX+7D4h]
	MOV ECX,DWORD PTR DS:[ECX+EAX*4h]
	MOV EAX,DWORD PTR DS:[EBX+EDI*4+194h]
	MOV DWORD PTR DS:[EAX+368h],ECX
ga:	mov esi,ebx
	pop edx
	
g3:	pop eax
	cmp eax,999
	je short g7
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],eax
	jmp short g6
g7:	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],edx
g6:	pop ebx
	jmp r2
	
	
g5:	cmp dword ptr ds:[ecx+edx+7ACh],11
	je g4
	cmp dword ptr ds:[ecx+edx+7ACh],16
	je g4
	jmp short g2
	
g1:	add esp,4
g2:	add esp,8
	pop ebx
	jmp r2
	
e6:	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	cmp dword ptr ds:[edx+6F8h],0
	jnz r2
	mov ecx,dword ptr ds:[ecx+78h]
	imul ecx,ecx,178
	cmp dword ptr ds:[ecx+edx+7ACh],150
	je r2
	cmp dword ptr ds:[ecx+edx+7ACh],156
	je r2
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],150
	jmp r2
	
dependent:
	sub eax,7000000
	mov ebx,1000
	mov edx,0
	idiv ebx
	xor ebx,ebx
	mov ebx,eax
	xor eax,eax
	mov eax,edx
	xor edx,edx
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h] 
	cmp dword ptr ds:[edx+6F4h],eax
	jnz r2
	xor eax,eax
	mov eax,ebx
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],eax
	jmp r2
	
frame_dependent:
	sub eax,8000000   ; take off the '8' in front
	mov ebx,1000
	mov edx,0
	idiv ebx
	xor ebx,ebx
	mov ebx,eax
	xor eax,eax
	mov eax,edx
	xor edx,edx  ; separate number #8XXXYYY into #XXX, #YYY. #XXX is stored in ebx, #YYY is stored in eax, EDX is cleared.
	mov ecx,dword ptr ds:[esi+edi*4+194h] 
	mov edx,dword ptr ds:[ecx+368h]
	cmp dword ptr ds:[edx+6F8h],0
	jnz r2
	mov ecx,dword ptr ds:[ecx+78h]
	imul ecx,ecx,178 
	cmp dword ptr ds:[ecx+edx+7ACh],eax
	jnz r2                                                 ; detect if frame is at indicated number #YYY. If not, normalize.
	xor eax,eax
	mov eax,ebx
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],eax             ; if frame is at indicated number, move character to frame at indicated number #XXX.
	jmp r2
	
superdependent:
	mov ebx,1000000000
	mov edx,0
	idiv ebx
	xor ebx,ebx
	push edx     ;  separates frame AXXXYYYZZZ into 'A, XXXYYYZZZ'. Remainder 'XXXYYYZZZ' is "pushed" into temporary memory.
	cmp eax,3   
	je s1
	cmp eax,2
	je d1          ; compare A. If A=2, go to case 1. If A=3 go to case 2.
	jmp r2
 
s1:                    ; beginning of case 1 (requirements to activate effect are both 'Frame' and 'ID')
	xor eax,eax  ; clear eax (in case)
	pop eax      ; retrieve number #XXXYYYZZZ. Store into 'EAX' variable/register.
	mov ebx,1000
	idiv ebx
	xor ebx,ebx
	push eax                          ; separate number #XXXYYYZZZ into #XXXYYY and #ZZZ. "Push" number #XXXYYY into system memory.
	xor eax,eax
	mov eax,edx
	xor edx,edx                       ; move number #ZZZ into eax. Clear 'EDX' (in case).
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h] 
	cmp dword ptr ds:[edx+6F4h],eax     ; check ID with #ZZZ, if no match then normalize.
	jnz r2                                            
        cmp eax, 999     ; check for #999, if match then omit feature by auto-enabling effect (first by going to s2 for state check).
        jnz r2
	jmp s2
 
s2:
	xor eax,eax        ; clear 'Eax'
	xor ebx,ebx
	xor edx,edx
	xor ecx,ecx
	pop eax           ; retrieve number #XXXYYY and store in 'Eax'
	mov ebx,1000
	idiv ebx
	xor ebx,ebx
	push eax           ; separate number #XXXYYY into #XXX and #YYY. "Push" number #XXX into system memory.
	xor eax,eax
	mov eax,edx     
	xor edx,edx        ; move #YYY into 'Eax, and clear 'Edx'
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]	
	mov ecx,dword ptr ds:[ecx+78h]
	imul ecx,ecx,178
	cmp dword ptr ds:[ecx+edx+7ACh],eax  ; check state against number #YYY, if no match then normalize.
	jnz r2
        cmp eax, 999                                 ; check for 999, if match then omit feature by auto-enabling the effect
        jnz r2
	jmp s3
 
s3:
	pop eax                                              ; retrieve number #XXX and store in 'Eax'
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],eax               ; move character to frame indicated by #XXX
	jmp r2
 
d1:              ; beginning of case 2 (requirements to activate effect are both 'Frame' or 'ID')
    xor eax,eax              ; clear 'Eax (in case)
    pop eax                   ; retrieve number #XXXYYYZZZ and store in 'Eax'
	mov ebx,1000
	idiv ebx
	xor ebx,ebx
        push eax
	mov eax,edx
	xor edx,edx           ; separate into #XXXYYY and #ZZZ, store #ZZZ in 'Eax' and "push" #XXXYYY, clear 'Edx'
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h] 
	cmp dword ptr ds:[edx+6F4h],eax        ; check ID against #ZZZ, if no match then check state, otherwise enable effect (or)
	je d4
        cmp eax, 999     ; check for #999, if match then omit feature by auto-enabling effect (first by going to d3 for state check).
        je d3
	jmp d2
 
d2:
	xor eax,eax    ; clear 'Eax' (again)
	xor edx,edx
	xor ecx,ecx
	xor ebx,ebx
	pop eax        ; retrieve #XXXYYY and store in 'Eax'
	mov ebx,1000
	idiv ebx
	xor ebx,ebx
	push eax
	mov eax,edx
	xor edx,edx            ; separate #XXXYYY into #XXX and #YYY, store #YYY in 'Eax' and "push" #XXX into system memory. Clear 'Edx'.
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]	
	mov ecx,dword ptr ds:[ecx+78h]
	imul ecx,ecx,178
	cmp dword ptr ds:[ecx+edx+7ACh],eax     ; checking State against number #YYY, if no match then normalize
	je d4
	jmp r2
 
d3:
	xor eax,eax          ; clear 'Eax', 'Edx', 'Ecx', 'Ebx'
	xor edx,edx
	xor ecx,ecx
	xor ebx,ebx
	pop eax                ; retrieve #XXXYYY and store into 'Eax'
	mov ebx,1000
	idiv ebx
	xor ebx,ebx
	push eax
	mov eax,edx        
	xor edx,edx            ; separating #XXXYYY into #XXX and #YYY. #YYY stored in 'Eax'. #XXX "pushed" to temporary memory.
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	mov ecx,dword ptr ds:[ecx+78h]
	imul ecx,ecx,178
	cmp dword ptr ds:[ecx+edx+7ACh],eax     ; checking state against #YYY, if no match then normalize, otherwise enable effect (or)
	je d4
        cmp eax, 999                ; check for #999, if match then omit feature by auto-enabling effect, otherwise normalize
        je d4
	jmp r2
 
d4:
	pop eax                          ; retrieve number #XXX
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov edx,dword ptr ds:[ecx+368h]
	mov ecx,dword ptr ds:[esi+edi*4+194h]
	mov dword ptr ds:[ecx+70h],eax                  ; moving character to indicated frame #XXX
	jmp r2

itr_effect endp

