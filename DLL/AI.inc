.Data
AI_BALL1_1			dd 0040363Eh ; generic ball 1 part 1
AI_BALL1_2			dd 0040360Dh ; genierc ball 1 part 2
AI_BALL2_1			dd 00403731h ; generic ball 2 part 1
AI_BALL2_2			dd 00403700h ; generic ball 2 part 2
AI_DEEP1			dd 00403E90h
AI_DEEP2			dd 004041E4h
AI_JOHN1			dd 00403A8Bh
AI_JOHN2			dd 00403E83h
AI_HENRY1			dd 004041FEh
AI_HENRY2			dd 00404361h
AI_RUDOLF1			dd 0040437Bh
AI_RUDOLF2			dd 004044EDh
AI_LOUIS1			dd 00404507h
AI_LOUIS2			dd 004045FCh
AI_FIREN1			dd 00404616h
AI_FIREN2			dd 0040498Dh
AI_FREEZE1			dd 004049A7h
AI_FREEZE2			dd 00404C05h
AI_DENNIS1			dd 00405154h
AI_DENNIS2			dd 0040530Dh
AI_WOODY1			dd 00404DC8h
AI_WOODY2			dd 0040513Ah
AI_DAVIS1			dd 00404C1Fh
AI_DAVIS2			dd 00404DAEh
AI_SORCERER1		dd 0040556Ah
AI_SORCERER2		dd 00405761h
;======AI Customising stuff=======
db1					dd 004034E0h ; generally used in AI for finding absolute value
db2					dd 00417170h ; also something generally used
CHJ_edi				dd 00404A75h
CRA_edi				dd 0040546Ch
CLA_edi				dd 00405482h
;===========Davis stuff===========
Davis_return		dd 00404DAEh
Davis_C				dd 004450D0h
Davis_DP			dd 004060E1h
Davis_r1			dd 00404C1Fh
;============Deep stuff===========
Deep_Ball_1 		dd 00403885h
Deep_Ball_2 		dd 0040392Eh
Deep_Ball_3 		dd 004038DCh
Deep_Ball_4 		dd 0040392Eh
Deep_Ball_C 		dd 004450D0h
;===========RANGE stuff===========
Range1_1 			dd 0040AF4Dh
Range1_2 			dd 0040AE25h
Range2_1 			dd 0040B226h	
Range2_2 			dd 0040B22Bh
Range3_1 			dd 0040B2DEh
Range3_2 			dd 0040B364h
Range4_1 			dd 0040B39Bh
Range4_2			dd 0040B5C8h

.Code
Range1 proc

	
		cmp ecx,4
		je short return
		;cmp ecx,ID
		;je short return
		jmp  dword ptr [Range1_2]
return: jmp  dword ptr [Range1_1]
	
Range1 endp

Range2 proc
	
		cmp eax,4
		je short return
		;cmp eax,ID
		;je short return
		jmp  dword ptr [Range2_2]
return: jmp  dword ptr [Range2_1]
	
Range2 endp

Range3 proc
	
		cmp eax,4
		je short return
		;cmp eax,ID
		;je short return
		jmp  dword ptr [Range3_2]
return: jmp  dword ptr [Range3_1]
	
Range3 endp

Range4 proc
	
		cmp eax,4
		je short return
		;cmp eax,ID
		;je short return
		jmp dword ptr [Range4_2]
return: jmp dword ptr [Range4_1]
	
Range4 endp

AI_Deep proc
	
		CMP DWORD PTR DS:[EAX+6F4h],1
		JE short return
		;cmp dword ptr DS:[EAX+6F4h],ID
		;je short return
		jmp  dword ptr [AI_DEEP2]
return: jmp  dword ptr [AI_DEEP1]
	
AI_Deep endp

Deep_Ball proc

	cmp dword ptr ds:[ecx+6F4h],1 ; check if ID is 1
	je short return ; go to the normal D>A AI for Deep
	cmp dword ptr ds:[ecx+6F4h],55 ; check if ID is 55 (your character)
	je short Range_Other ; go to Range_Other part if ID is 55
	jmp dword ptr [Deep_Ball_2]
	return:
	jmp dword ptr [Deep_Ball_1]
	
;##This part just customize the range, you can simply use 'je short return' above
	Range_Other:
	mov edx,dword ptr ss:[esp+14h]
	mov ebp,dword ptr ds:[esi+edx*4+194h]
	fld qword ptr ss:[ebp+40h]
	mov ebx,dword ptr ds:[eax+10h]
	call dword ptr [Deep_Ball_C]
	mov ecx,dword ptr ss:[ebp+10h]
	lea edx,dword ptr ds:[ecx+eax*2]
	sub edx,ebx
	push edx
	call dword ptr [db1]
	add esp,4
	cmp eax,100 ; lower boundary 100
	jle short Out_of_range ; won't use D>A when <= 100
	mov eax,dword ptr ss:[esp+14h]
	mov ebp,dword ptr ds:[esi+eax*4+194h]
	fld qword ptr ss:[ebp+40h]
	call dword ptr [Deep_Ball_C]
	mov ecx,dword ptr ss:[ebp+10h]
	lea edx,dword ptr ds:[ecx+eax*2]
	sub edx,ebx
	push edx
	call dword ptr [db1]
	add esp,4
	cmp eax,300 ; upper boundary 300
	jge short Out_of_range ; won't use D>A when >= 300
	jmp	 dword ptr [Deep_Ball_3]
	Out_of_range:
	jmp dword ptr [Deep_Ball_4]

Deep_Ball endp

AI_John proc
	
		CMP DWORD PTR DS:[EDX+6F4h],2
		JE short return
		;cmp dword ptr DS:[EDX+6F4h],ID
		;je short return
		jmp  dword ptr [AI_JOHN2]
return: jmp  dword ptr [AI_JOHN1]
	
AI_John endp

AI_Henry proc
	
		CMP DWORD PTR DS:[EAX+6F4h],4
		JE short return
		;CMP DWORD PTR DS:[EAX+6F4h],ID
		;JE short return
		jmp  dword ptr [AI_HENRY2]
return: jmp  dword ptr [AI_HENRY1]
	
AI_Henry endp

AI_Rudolf proc
	
		CMP DWORD PTR DS:[EAX+6F4h],5
		JE short return
		;CMP DWORD PTR DS:[EAX+6F4h],ID
		;JE short return
		jmp dword ptr [AI_RUDOLF2]
return:	jmp dword ptr [AI_RUDOLF1]
	
AI_Rudolf endp

AI_Louis proc
	
		CMP DWORD PTR DS:[EAX+6F4h],6
		JE short return
		;cmp dword ptr DS:[EAX+6F4h],ID
		;je short return
		jmp  dword ptr [AI_LOUIS2]
return: jmp  dword ptr [AI_LOUIS1]
	
AI_Louis endp

AI_Firen proc
	
		CMP DWORD PTR DS:[EDX+6F4h],7
		JE short return
		;cmp dword ptr DS:[EDX+6F4h],ID
		;je short return
		jmp  dword ptr [AI_FIREN2]
return: jmp  dword ptr [AI_FIREN1]
	
AI_Firen endp

AI_Freeze proc
	
		CMP DWORD PTR DS:[EAX+6F4h],8
		JE short return
		;CMP DWORD PTR DS:[EAX+6F4h],ID
		;JE short return
		CMP DWORD PTR DS:[EAX+6F4h],42
		JE short ca0
		jmp dword ptr [AI_FREEZE2]
return: jmp dword ptr [AI_FREEZE1]

;##This is an AI customised to perform attacks sensitively to distance

ca0:mov edx,dword ptr ds:[esi+ebp*4+194h]
	mov eax,dword ptr ds:[edx+10h]
	sub eax,dword ptr ds:[ecx+10h]
	push eax
	call dword ptr [db1]
	add esp,4
	cmp eax,500
	jl short ca5
	cmp eax,575
	jl short ca1
	cmp eax,625
	jl short ca5
	cmp eax,700
	jge short ca5
ca1:mov eax,dword ptr ds:[edx+18h]
	sub eax,dword ptr ds:[ecx+18h]
	push eax
	call dword ptr [db1]
	add esp,4
	cmp eax,8
	jge short ca5
	;push 0Fh
	;push 5Ah
	;call dword ptr [db2]
	;add esp,8
	;test eax,eax
	;jnz short ca5
	mov eax,dword ptr ds:[esi+ebp*4+194h]
	mov edi,dword ptr ds:[esi+edi*4+194h]
	mov ecx,dword ptr ds:[eax+10h]
	cmp ecx,dword ptr ds:[edi+10h]
	jle short CBA
	jmp dword ptr [CRA_edi]	
CBA:jmp dword ptr [CLA_edi]
	
ca5:mov edx,dword ptr ds:[esi+ebp*4+194h]
	mov eax,dword ptr ds:[edx+10h]
	sub eax,dword ptr ds:[ecx+10h]
	push eax
	call dword ptr [db1]
	add esp,4
	cmp eax,425
	jl short r2
	cmp eax,500
	jl short ca6
	cmp eax,575
	jl short r2
	cmp eax,625
	jge short r2
ca6:mov eax,dword ptr ds:[edx+18h]
	sub eax,dword ptr ds:[ecx+18h]
	push eax
	call dword ptr [db1]
	add esp,4
	cmp eax,8
	jge short r2
	;push 0Fh
	;push 5Ah
	;call dword ptr [db2]
	;add esp,8
	;test eax,eax
	;jnz short r2
	jmp dword ptr [CHJ_edi]
	
r2:	jmp dword ptr [AI_FREEZE2]

AI_Freeze endp

AI_Dennis proc
	
		CMP DWORD PTR DS:[EDX+6F4h],9
		JE short return
		;cmp dword ptr DS:[EDX+6F4h],ID
		;je short return
		jmp  dword ptr [AI_DENNIS2]
return: jmp  dword ptr [AI_DENNIS1]
	
AI_Dennis endp

AI_Woody proc
	
		CMP DWORD PTR DS:[EDX+6F4h],10
		JE short return
		;cmp dword ptr DS:[EDX+6F4h],ID
		;je short return
		jmp  dword ptr [AI_WOODY2]
return: jmp  dword ptr [AI_WOODY1]
	
AI_Woody endp

AI_Davis proc
		
		CMP DWORD PTR DS:[EAX+6F4h],0Bh		 ;  davis
		je davis_ai
		;CMP DWORD PTR DS:[EAX+6F4h],ID
		je davis_ai
		jmp return
		
davis_ai:		
		CMP DWORD PTR DS:[ECX+308h],96h
		JLE a		     ;  jmp a
		MOV EDX,DWORD PTR DS:[ESI+EBP*4+194h]
		MOV EAX,DWORD PTR DS:[EDX+10h]
		SUB EAX,DWORD PTR DS:[ECX+10h]
		PUSH EAX
		CALL [db1]
		ADD ESP,4
		CMP EAX,118h
		JGE a		   ;  jmp a
		MOV EDX,DWORD PTR DS:[EDX+18h]
		SUB EDX,DWORD PTR DS:[ECX+18h]
		PUSH EDX
		CALL [db1]
		ADD ESP,4
		CMP EAX,1Eh
		JGE a		      ;  jmp a
		PUSH 0Ah
		PUSH 5Dh
		CALL [db2]
		ADD ESP,8h
		TEST EAX,EAX
		JNZ a		      ;  jmp a
		MOV EDX,DWORD PTR DS:[ESI+EDI*4+194h]
		MOV BL,BYTE PTR DS:[EDX+80h]
		TEST BL,BL
		JNZ b		     ;  jmp b
		MOV ECX,DWORD PTR DS:[ESI+EBP*4+194h]
		MOV EAX,DWORD PTR DS:[EDX+10h]
		MOV ECX,DWORD PTR DS:[ECX+10h]
		CMP ECX,EAX
		JG @c		      ;  jmp c
		
		b:
		CMP BL,1								 ;  b
		JNZ a		      ;  jmp a
		MOV ECX,DWORD PTR DS:[ESI+EBP*4+194h]
		MOV EAX,DWORD PTR DS:[EDX+10h]
		MOV ECX,DWORD PTR DS:[ECX+10h]
		CMP ECX,EAX
		JGE a		      ;  jmp a
		JLE d		     ;  jmp d
		@c:
		MOV BYTE PTR DS:[EDX+0D7h],3   ;c
		
		d:
		POP EDI								  ;  d
		POP EBP
		POP EBX
		MOV EAX,1
		POP ESI
		ADD ESP,8
		RETN 1Ch
		
		a:
		MOV EAX,DWORD PTR DS:[ESI+EDI*4+194h]     ;  a
		MOV EDX,DWORD PTR DS:[EAX+70h]
		MOV EAX,DWORD PTR DS:[EAX+368h]
		IMUL EDX,EDX,178h
		CMP DWORD PTR DS:[EDX+EAX+7D0h],122h
		JNZ e		      ;  jmp e
		MOV ECX,DWORD PTR DS:[ESI+EBP*4+194h]
		CMP DWORD PTR DS:[ECX+14h],0
		JGE e		     ;  jmp e
		MOV EDX,DWORD PTR DS:[ESI+EDI*4+194h]
		MOV BYTE PTR DS:[EDX+0CBh],0
		MOV EAX,DWORD PTR DS:[ESI+EDI*4+194h]
		
		e:
		MOV BYTE PTR DS:[EAX+0D2h],1
		PUSH 5h								   ;  e
		PUSH 5Eh
		CALL [db2]
		ADD ESP,8h
		TEST EAX,EAX
		JE f		      ;  jmp f
		MOV EAX,DWORD PTR SS:[ESP+28h]
		CMP EAX,10h
		JE f		      ;  jmp f
		CMP EAX,8h
		JNZ return				    ;  jmp to end
		
		f:
		MOV ECX,DWORD PTR SS:[ESP+1Ch]		    ;  f
		MOV EBX,DWORD PTR DS:[ESI+ECX*4+194h]
		MOV EBP,DWORD PTR DS:[ESI+EDI*4+194h]
		MOV EDX,DWORD PTR DS:[EBX+10h]
		FLD QWORD PTR SS:[EBP+40h]
		MOV DWORD PTR SS:[ESP+20h],EDX
		CALL [Davis_C]
		SUB EAX,DWORD PTR SS:[EBP+10h]
		ADD EAX,DWORD PTR SS:[ESP+20h]
		PUSH EAX
		CALL [db1]
		ADD ESP,4
		CMP EAX,64h
		JGE return		      ;  jmp to end
		MOV EAX,DWORD PTR DS:[EBX+18h]
		MOV ECX,EBP
		SUB EAX,DWORD PTR DS:[ECX+18h]
		PUSH EAX
		CALL [db1]
		ADD ESP,4
		CMP EAX,7
		JGE return		      ;  jmp to end
		CMP DWORD PTR DS:[ECX+308h],0C8h
		JLE return		      ;  jmp to end
		MOV AL,BYTE PTR DS:[ECX+80h]
		TEST AL,AL
		JNZ g		      ;  jmp g    
		MOV EDX,DWORD PTR SS:[ESP+20h]
		CMP DWORD PTR DS:[ECX+10h],EDX
		JL dp
		g:
		CMP AL,1								 ;  g
		JNZ return		     ;  jmp davis 3
		MOV EAX,DWORD PTR SS:[ESP+20h]
		CMP DWORD PTR DS:[ECX+10h],EAX
		JG dp				   ;  jmp davis 3
return: jmp Davis_return
dp:		jmp Davis_DP
    
AI_Davis endp

AI_Sorcerer proc

;##Somehow the D>J of Sorcerer is not here, only the D^J and the DvJ is contained below. 
		CMP DWORD PTR DS:[ECX+6F4h],34
		JE short return
		;CMP DWORD PTR DS:[ECX+6F4h],ID
		;JE short return
		jmp  dword ptr [AI_SORCERER2]
return: jmp  dword ptr [AI_SORCERER1]
	
AI_Sorcerer endp

AI_Ball1  proc
		cmp eax,2
		je short return
		;cmp eax,ID
		;je short return
		jmp  dword ptr [AI_BALL1_2]
return:	jmp  dword ptr [AI_BALL1_1]

AI_Ball1  endp

AI_Ball2 proc
		cmp eax,2
		je short return
		;cmp eax,ID
		;je short return
		jmp  dword ptr [AI_BALL2_2]
return:	jmp  dword ptr [AI_BALL2_1]

AI_Ball2 endp

