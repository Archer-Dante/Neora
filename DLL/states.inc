.data
;state4xxx
Transform1	dd 0041F675h

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

  




;
;
;
;		CMP EAX,1F40h
;		JL SHORT exit1
;		CMP EAX,2327h
;		JGE SHORT exit1
;			
;		MOV ECX,DWORD PTR DS:[452980h]
;		LEA EDX,DWORD PTR DS:[EAX-1F40h]
;		XOR EAX,EAX
;		CMP DWORD PTR DS:[452990h],EAX
;		JLE SHORT sector3_8xxx
;		
;
;
;sector1_8xxx:
;		MOV ESI,DWORD PTR DS:[ECX]
;		CMP DWORD PTR DS:[ESI+6F4h],EDX
;		JE SHORT sector2_8xxx
;		MOV ESI,DWORD PTR DS:[452980h]
;		ADD EAX,1
;		ADD ECX,4
;		CMP EAX,DWORD PTR DS:[452990h]
;		JL SHORT sector1_8xxx
;		JMP SHORT sector3_8xxx
;		
;sector2_8xxx:	
;		MOV ECX,DWORD PTR DS:[452980h]
;		MOV ECX,DWORD PTR DS:[ECX+EAX*4]
;		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EAX+368h],ECX
;		
;sector3_8xxx:		
;		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EDX+70h],0
;		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EAX+318h],8Ch
;		JMP DWORD PTR DS:[Transform1]            
;  
;
;exit1:  JMP DWORD PTR DS:[Transform1]


    
    










    
State8xxx endp







































;		CMP EAX,1F40h ; 8000
;		JL SHORT state4xxx ; Если меньше текущего статуса
;		CMP EAX,2328h ; 9000
;		JGE SHORT state4xxx ; Больше или равно текущему статусу
;		jmp SHORT exit2 ; Если ничего не подошло, продолжаем обработку как в исходнике
;		
;exit1: 	jmp dword ptr [Transform1] ; Ссылка на адрес обычного кода
;exit2: 	jmp dword ptr [Transform3] ; Ссылка на адрес обычного кода
;		
;state4xxx:	
;		CMP EAX, 0EA60h ; 40 000
;		JL SHORT exit1 ; Если меньше 4 000 сваливаем в обычный код
;		CMP EAX, 0EE47h ; 40 999
;		JGE SHORT exit1 ; Если больше 4 000 сваливаем в обычный код
;		
;		
;		;Если меньше 8000, но не меньше 4000, то делаем код дальше.
;		MOV ECX,DWORD PTR DS:[452980h] ; добавляем h к мистическому хексу
;		LEA EDX,DWORD PTR DS:[EAX-0EA60h] ; вычитаем из 4ххх число 4000, оставляя ххх как ID (ПРОБЛЕМААААА!!!! 0FA0h )
;		XOR EAX,EAX 					; делаем проверку, не является ли текущий ID равен целевому
;		CMP DWORD PTR DS:[452990h],EAX
;		JLE SHORT sector3
;		
;sector1:	
;		MOV ESI,DWORD PTR DS:[ECX]
;		CMP DWORD PTR DS:[ESI+6F4h],EDX
;		JE SHORT sector2
;		MOV ESI,DWORD PTR DS:[452980h]
;		ADD EAX,1
;		ADD ECX,4
;		CMP EAX,DWORD PTR DS:[452990h]
;		JL SHORT sector1
;		JMP SHORT sector3
;
;sector2:
;		MOV ECX,DWORD PTR DS:[452980h]
;		MOV ECX,DWORD PTR DS:[ECX+EAX*4]
;		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EAX+368h],ECX
;
;sector3:
;		MOV EDX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EDX+70h],0 ; стартовый кадр
;		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		MOV DWORD PTR DS:[EAX+318h],0 ; +140 кадров
;		MOV EAX,DWORD PTR DS:[EBX+EDI*4+3ECh]
;		jmp Transform2 ; Ссылка на адрес обычного кода




















;timestop:
;	    CMP EAX,10000
;        jl return
;        CMP EAX,20000
;        jge return
;        sub eax,10000
;        push ecx
;        mov ecx,dword ptr ds:[memAlloc]
;        lea ecx,dword ptr ds:[ecx+edi*8]
;        mov dword ptr ds:[ecx+1],eax
;        mov byte ptr ds:[ecx],1
;        pop ecx
;        
;return: jmp Transform2

;
;State_Turning proc
;	
;;This 2 states allow you control the direction in a move (both ^, v, < and >). 
;;Imagine you use mark's Body Attack D>J, with state 85 or 86 you can turn back without stop.
;
;;State 86 merely allows you to use the direction key. 
;;State 85 does it similarly but additionally increments the frame number by 1. 
;
;;###This is mainly copy from the state of dash, I didn't understand most of it
;
;	cmp dword ptr ds:[edx+ecx+7ACh],5
;	je short r1
;	cmp dword ptr ds:[edx+ecx+7ACh],85
;	je short s85
;	cmp dword ptr ds:[edx+ecx+7ACh],86
;	je short s86
;	jmp dword ptr [st_r2]
;r1:	jmp dword ptr [st_r1]
;
;s85:push ecx
;	mov ecx,1
;	jmp short st0
;s86:push ecx
;	mov ecx,0
;st0:mov bl,byte ptr ds:[esi+0D0h]
;	mov dl,0
;	call c0
;	mov dl,1
;	call c0
;	pop ecx
;	jmp dword ptr [st_r2]
;
;c0:	cmp byte ptr ds:[esi+0D0h],dl
;	je short c1
;	cmp byte ptr ds:[esi+0CFh],dl
;	jnz short c1
;	mov byte ptr ds:[esi+80h],dl
;c1:	cmp byte ptr ds:[esi+80h],dl
;	jnz short c5
;	cmp dword ptr ds:[esi+70h],edi
;	je short c5
;	fxch st(1)
;	fcom qword ptr ds:[esi+40h]
;	fstsw ax
;	test dl,dl
;	jnz short c2
;	test ah,5
;	jpe short c4
;	jmp short c3
;c2:	test ah,41h
;	jnz short c4
;c3:	add dword ptr ds:[esi+70h],ecx
;c4:	fxch st(1)
;c5: retn
;
;State_Turning endp
;
;Hit_teammates proc
;	
;	mov eax,dword ptr ss:[esp+44h]
;	mov ebp,dword ptr ds:[esi+eax*4+194h]
;	mov eax,dword ptr ss:[ebp+364h]
;	push edx
;	mov edx,dword ptr ss:[esp+48h]
;	mov eax,dword ptr ds:[esi+edx*4+194h]
;	mov edx,dword ptr ds:[eax+70h]
;	mov eax,dword ptr ds:[eax+368h]
;	imul edx,edx,178h
;	cmp dword ptr ds:[edx+eax+7ACh],20
;	je short ht
;	pop edx
;	mov eax,dword ptr ss:[esp+44h]
;	mov ebp,dword ptr ds:[esi+eax*4+194h]
;	mov eax,dword ptr ss:[ebp+364h]
;	jmp dword ptr [ht_r1]
;	
;ht:	pop edx
;	mov eax,dword ptr ss:[esp+44h]
;	mov ebp,dword ptr ds:[esi+eax*4+194h]
;	mov eax,dword ptr ss:[ebp+364h]
;	cmp eax,dword ptr ds:[ebx+364h]
;	je short r2
;	test eax,eax
;	je short r2
;	cmp edx,8
;	je short r2
;	jmp dword ptr [ht_r3]
;r2: jmp dword ptr [ht_r2]
;
;Hit_teammates endp
