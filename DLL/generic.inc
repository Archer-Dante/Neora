.Data
;mp recover
MP_normal	dd 0041FAD8h
MP_hack 	dd 0041FAF8h
;opoint HP
Max_HP1		dd 004201F2h
Max_HP2		dd 00420223h
;hiding shadow
hs_r1		dd 0041A770h
hs_r2		dd 0041A6F4h

;opoint_kinds
opoints_r   dd 004202D1h
;shaker
shake_back1 dd 0042EE49h
shake_back2 dd 0042EE4Fh
shake_back3 dd 0042EE62h


.Code

opoint_kind proc
	
	CMP DWORD PTR DS:[ECX+7FCh],2
	jl return
	mov eax, DWORD PTR DS:[ECX+7FCh]
	dec eax
	MOV EDX,DWORD PTR DS:[EBX+EDI*4+194h]
	MOV DWORD PTR DS:[EDX+98h],eax
	MOV EAX,DWORD PTR DS:[EBX+ESI*4+194h]
	MOV DWORD PTR DS:[EAX+98h],-1
	MOV ECX,DWORD PTR DS:[EBX+EDI*4+194h]
	MOV DWORD PTR DS:[ECX+9Ch],ESI
	MOV EDX,DWORD PTR DS:[EBX+ESI*4+194h]
	MOV DWORD PTR DS:[EDX+0A0h],EDI
	MOV EAX,DWORD PTR DS:[EBX+EDI*4+194h]
	MOV ECX,DWORD PTR DS:[EBX+ESI*4+194h]
	MOV EDX,DWORD PTR DS:[EAX+364h]
	MOV DWORD PTR DS:[ECX+364h],EDX	
return:
	jmp [opoints_r]

opoint_kind endp

Health proc
	
	MOV ECX,DWORD PTR DS:[EBX+EDI*4h+194h] ;ignore this
	MOV EDX,DWORD PTR DS:[ECX+368h] ; ignore this
	MOV EDX,DWORD PTR DS:[EDX+6F4h] ; ignore this
h:	cmp edx,55 ; check if ID is 55
	je short @HP_check_1 ;if it's not 55 then jump to normal procedure
	
	jmp short @HP_normal ;otherwise just recover hp normally
	
	@HP_check_1:
	cmp dword ptr ds:[eax+300h],250 ; compare dark red with 250
	jl short @HP_LowDarkRed_1 ; if its lower than jump to LowDarkRed
	cmp dword ptr ds:[eax+2fch],250 ; compare red hp with 250
	jl short @HP_LowRed_1 ; if its lower then jump to LowRed
	jmp short @HP_normal ;otherwise just recover hp normally
	@HP_LowDarkRed_1:
	add dword ptr ds:[eax+300h],5 ; add 5 to dark red hp
	@HP_LowRed_1:
	add DWORD PTR DS:[EAX+2FCh],4 ; add 4 to red hp
	retn
	
	@HP_normal:
	add DWORD PTR DS:[EAX+2FCh],1 ; add 1 to
	retn

Health endp

MP proc
	
	cmp edx,51 ; check if ID is 51 (Firzen)
	je short @MP_1 ; jump to @MP_1 if ID is 51
	cmp edx,52 ; check if ID is 52 (Julian)
	je short @MP_1 ; jump to @MP_1 if ID is 52
	cmp edx,55 ; check if ID is 55 (your character)
	je short @MP_2 ; jump to @MP_2 if ID is 55
	jmp dword ptr [MP_normal]
	
	@MP_1: ; for Firzen & Julian
	cdq ; ignore this
	sub eax,edx  ; ignore this
	sar eax,1 ; add 1 point more compare with normal (normal = 1)
	jmp dword ptr [MP_normal]
	
	@MP_2: ; for the ID 55
	;cmp dword ptr ds:[ecx+308h],250 ; check if mp is greater than 250
	;JG @Decrease_MP
	cdq ; ignore this
	sub eax,edx ; ignore this
	sar eax,2 ; add 2 point more compare with normal
	jmp dword ptr [MP_normal]
	
	@Decrease_MP: ;when mp is more than 250
	mov eax, dword ptr ds:[ecx+308h] ; move mana into eax
	sub eax,1 ; decrease eax(mana) by 1
	jmp dword ptr [MP_hack]

MP endp

Max_HP proc
	
	cmp ecx,5 ; Check if ID is 5 (Rudolf)
	je short HP_10 ; go to the 10 HP part
	cmp ecx,52 ; Check if ID is 5 (Julian)
	je short HP_10 ; go to the 10 HP part
	;cmp ecx,55 ; Put your character or object's ID here
	;je short HP_125 ; go to the 125 HP part
	jmp dword ptr [Max_HP2]
	
	HP_10:
	mov ecx,100 ; 10 HP for Rudolf's Double and Julian's Mirror Image
	jmp dword ptr [Max_HP1]
	
	HP_125:
	mov ecx,125 ; 125 HP if you spawn your character or object (normal = 500)
	jmp dword ptr [Max_HP1]	

Max_HP endp

Hide_shadow proc
	
	cmp eax,0DFh
	je short r1
	cmp eax,55	; put ID you want to hide shadow
	je short r1
	jmp dword ptr [hs_r2]
r1:	jmp dword ptr [hs_r1]

Hide_shadow endp


Shaker proc
 
MOV DWORD PTR DS:[EBX+0B4h],3 ;”правление задержкой атакующего в TU
MOV ECX,DWORD PTR SS:[ESP+0Ch]
MOV DWORD PTR DS:[EDI+0B4h],-3 ;”правление задержкой защищающегос€ в TU
MOV EAX,DWORD PTR DS:[ECX+20h]
CMP EAX,4
JGE short shake1
CMP DWORD PTR DS:[ECX+24h],0
JNZ short shake1
MOV DWORD PTR DS:[EBX+0ECh],4
JMP short shake2
MOV DWORD PTR DS:[EBX+0ECh],EAX
CMP DWORD PTR DS:[ECX+24h],0
JLE short shake3

shake1:
JMP DWORD ptr [shake_back1]

shake2:
JMP DWORD ptr [shake_back2]

shake3:
JMP DWORD ptr [shake_back3]

Shaker endp