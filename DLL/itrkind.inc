.data

ik8_back1	dd 0043002Dh
ik8_back2	dd 0043087Ch

ik8_fix1	dd 00417535h
ik8_fix2	dd 00417A10h
	
.code
itr_kind8 proc
	

	CMP EDX,8
	JE kind8_dvx_X ; standart
	
	CMP EDX,800  ; Type 0
	JE kind8_dvx_X ; standart
	CMP EDX,801
	JE kind8_dvx_X_Y
	CMP EDX,802
	JE kind8_dvx_Y
	CMP EDX,803
	JE kind8_X
	CMP EDX,804
	JE kind8_X_Y
	CMP EDX,805
	JE kind8_Y
	CMP EDX,806
	JE kind8_dvx

	CMP EDX,810  ; Type 1
	JE kind8_dvx_X ; standart
	CMP EDX,811
	JE kind8_dvx_X_Y
	CMP EDX,812
	JE kind8_dvx_Y
	CMP EDX,813
	JE kind8_X
	CMP EDX,814
	JE kind8_X_Y
	CMP EDX,815
	JE kind8_Y
	CMP EDX,816
	JE kind8_dvx
	
	CMP EDX,820  ; Type 2
	JE kind8_dvx_X ; standart
	CMP EDX,821
	JE kind8_dvx_X_Y
	CMP EDX,822
	JE kind8_dvx_Y
	CMP EDX,823
	JE kind8_X
	CMP EDX,824
	JE kind8_X_Y
	CMP EDX,825
	JE kind8_Y
	CMP EDX,826
	JE kind8_dvx
	
	CMP EDX,830  ; Type 3
	JE kind8_dvx_X ; standart
	CMP EDX,831
	JE kind8_dvx_X_Y
	CMP EDX,832
	JE kind8_dvx_Y
	CMP EDX,833
	JE kind8_X
	CMP EDX,834
	JE kind8_X_Y
	CMP EDX,835
	JE kind8_Y	
	CMP EDX,836
	JE kind8_dvx
	
	CMP EDX,840  ; Type 4
	JE kind8_dvx_X ; standart
	CMP EDX,841
	JE kind8_dvx_X_Y
	CMP EDX,842
	JE kind8_dvx_Y
	CMP EDX,843
	JE kind8_X
	CMP EDX,844
	JE kind8_X_Y
	CMP EDX,845
	JE kind8_Y
	CMP EDX,846
	JE kind8_dvx
	
	CMP EDX,850  ; Type 5
	JE kind8_dvx_X ; standart
	CMP EDX,851
	JE kind8_dvx_X_Y
	CMP EDX,852
	JE kind8_dvx_Y
	CMP EDX,853
	JE kind8_X
	CMP EDX,854
	JE kind8_X_Y
	CMP EDX,855
	JE kind8_Y
	CMP EDX,856
	JE kind8_dvx
	
	CMP EDX,860  ; Type 6
	JE kind8_dvx_X ; standart
	CMP EDX,861
	JE kind8_dvx_X_Y
	CMP EDX,862
	JE kind8_dvx_Y
	CMP EDX,863
	JE kind8_X
	CMP EDX,864
	JE kind8_X_Y
	CMP EDX,865
	JE kind8_Y
	CMP EDX,866
	JE kind8_dvx
	
	CMP EDX,870  ; Complex of Types: 1,2,4,6
	JE kind8_dvx_X ; standart
	CMP EDX,871
	JE kind8_dvx_X_Y
	CMP EDX,872
	JE kind8_dvx_Y
	CMP EDX,873
	JE kind8_X
	CMP EDX,874
	JE kind8_X_Y
	CMP EDX,875
	JE kind8_Y
	CMP EDX,876
	JE kind8_dvx

	JMP [ik8_back1]

kind8_dvx_X:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD DWORD PTR DS:[EAX+14h] ; загружает dvx из itr
	FISTP DWORD PTR DS:[EBX+70h] ; ставит кадр как в dvx
	
	FLD QWORD PTR DS:[EDI+58h] ; загружает X основного объекта
	FSTP QWORD PTR DS:[EBX+58h] ; записывает Х копирующего объекта
	
	FLD QWORD PTR DS:[EDI+68h] ; загружает Z основного объекта
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; записывает Z копирующего объекта
	JMP [ik8_return]
	
kind8_dvx_X_Y:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD DWORD PTR DS:[EAX+14h] ; загружает dvx из itr
	FISTP DWORD PTR DS:[EBX+70h] ; ставит кадр как в dvx
	
	FLD QWORD PTR DS:[EDI+58h] ; загружает X основного объекта
	FSTP QWORD PTR DS:[EBX+58h] ; записывает Х копирующего объекта
	
	FLD QWORD PTR DS:[EDI+60h] ; загружает Y основного объекта
	FSTP QWORD PTR DS:[EBX+60h] ; записывает Y копирующего объекта
	
	FLD QWORD PTR DS:[EDI+68h] ; загружает Z основного объекта
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; записывает Z копирующего объекта
	JMP [ik8_return]

kind8_dvx_Y:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD DWORD PTR DS:[EAX+14h] ; загружает dvx из itr
	FISTP DWORD PTR DS:[EBX+70h] ; ставит кадр как в dvx
	
	FLD QWORD PTR DS:[EDI+60h] ; загружает Y основного объекта
	FSTP QWORD PTR DS:[EBX+60h] ; записывает Y копирующего объекта
	
	FLD QWORD PTR DS:[EDI+68h] ; загружает Z основного объекта
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; записывает Z копирующего объекта
	JMP [ik8_return]

kind8_X:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD QWORD PTR DS:[EDI+58h] ; загружает X основного объекта
	FSTP QWORD PTR DS:[EBX+58h] ; записывает Х копирующего объекта
	
	FLD QWORD PTR DS:[EDI+68h] ; загружает Z основного объекта
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; записывает Z копирующего объекта
	JMP [ik8_return]
	
kind8_X_Y:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD QWORD PTR DS:[EDI+58h] ; загружает X основного объекта
	FSTP QWORD PTR DS:[EBX+58h] ; записывает Х копирующего объекта
	
	FLD QWORD PTR DS:[EDI+60h] ; загружает Y основного объекта
	FSTP QWORD PTR DS:[EBX+60h] ; записывает Y копирующего объекта
	
	FLD QWORD PTR DS:[EDI+68h] ; загружает Z основного объекта
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; записывает Z копирующего объекта
	JMP [ik8_return]

kind8_Y:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD QWORD PTR DS:[EDI+60h] ; загружает Y основного объекта
	FSTP QWORD PTR DS:[EBX+60h] ; записывает Y копирующего объекта
	
	FLD QWORD PTR DS:[EDI+68h] ; загружает Z основного объекта
	FADD QWORD PTR DS:[447A08h]
	FSTP QWORD PTR DS:[EBX+68h] ; записывает Z копирующего объекта
	JMP [ik8_return]
	
kind8_dvx:
	MOV EAX,DWORD PTR SS:[ESP+0Ch]
	MOV EDX,DWORD PTR DS:[EAX+44h] ; gets HEAL from Injury tag of ITR
	ADD EDX,3E8h
	MOV DWORD PTR DS:[EDI+0E0h],EDX ; writes heal to curing function
	FLD DWORD PTR DS:[EAX+14h] ; загружает dvx из itr
	FISTP DWORD PTR DS:[EBX+70h] ; ставит кадр как в dvx
	JMP [ik8_return]

 
ik8_return:
	JMP [ik8_back2]
	
ik8_false:
	JMP [ik8_back1]
 
itr_kind8 endp








itr_kind8_types proc

	MOV ECX, DWORD PTR SS:[ESI+368h]
	
	CMP DWORD PTR DS:[EBX],8 ; проверка что это IK8
	JE kind80x_type0
	
	CMP DWORD PTR DS:[EBX],800 ; проверка что это IK800
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],801
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],802
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],803
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],804
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],805
	JE kind80x_type0
	CMP DWORD PTR DS:[EBX],806
	JE kind80x_type0
	
	CMP DWORD PTR DS:[EBX],810
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],811
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],812
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],813
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],814
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],815
	JE kind81x_type1
	CMP DWORD PTR DS:[EBX],816
	JE kind81x_type1
	
	CMP DWORD PTR DS:[EBX],820
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],821
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],822
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],823
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],824
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],825
	JE kind82x_type2
	CMP DWORD PTR DS:[EBX],826
	JE kind82x_type2
	
	CMP DWORD PTR DS:[EBX],830
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],831
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],832
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],833
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],834
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],835
	JE kind83x_type3
	CMP DWORD PTR DS:[EBX],836
	JE kind83x_type3
	
	CMP DWORD PTR DS:[EBX],840
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],841
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],842
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],843
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],844
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],845
	JE kind84x_type4
	CMP DWORD PTR DS:[EBX],846
	JE kind84x_type4
	
	CMP DWORD PTR DS:[EBX],850
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],851
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],852
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],853
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],854
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],855
	JE kind85x_type5
	CMP DWORD PTR DS:[EBX],856
	JE kind85x_type5
	
	CMP DWORD PTR DS:[EBX],860
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],861
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],862
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],863
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],864
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],865
	JE kind86x_type6
	CMP DWORD PTR DS:[EBX],866
	JE kind86x_type6
	
	CMP DWORD PTR DS:[EBX],870
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],871
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],872
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],873
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],874
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],875
	JE kind87x_type1_2_4_6
	CMP DWORD PTR DS:[EBX],876
	JE kind87x_type1_2_4_6
	
	JMP [ik8_fix1]


kind80x_type0:
	CMP DWORD PTR SS:[ECX+6F8h],0 ; Проверка на Type 0
	JNE [skip_kind] ; Иначе пропускаем обработку
	JMP [ik8_fix1] ; Если всё нормально - продолжаем
	
kind81x_type1:
	CMP DWORD PTR SS:[ECX+6F8h],1 ; Проверка на Type
	JNE [skip_kind] ; Иначе пропускаем обработку
	JMP [ik8_fix1] ; Если всё нормально - продолжаем
	
kind82x_type2:
	CMP DWORD PTR SS:[ECX+6F8h],2 ; Проверка на Type
	JNE [skip_kind] ; Иначе пропускаем обработку
	JMP [ik8_fix1] ; Если всё нормально - продолжаем
	
kind83x_type3:
	CMP DWORD PTR SS:[ECX+6F8h],3 ; Проверка на Type
	JNE [skip_kind] ; Иначе пропускаем обработку
	JMP [ik8_fix1] ; Если всё нормально - продолжаем	

kind84x_type4:
	CMP DWORD PTR SS:[ECX+6F8h],4 ; Проверка на Type
	JNE [skip_kind] ; Иначе пропускаем обработку
	JMP [ik8_fix1] ; Если всё нормально - продолжаем	
	
kind85x_type5:
	CMP DWORD PTR SS:[ECX+6F8h],5 ; Проверка на Type
	JNE [skip_kind] ; Иначе пропускаем обработку
	JMP [ik8_fix1] ; Если всё нормально - продолжаем	
	
kind86x_type6:
	CMP DWORD PTR SS:[ECX+6F8h],6 ; Проверка на Type
	JNE [skip_kind] ; Иначе пропускаем обработку
	JMP [ik8_fix1] ; Если всё нормально - продолжаем	

;===============================================================
kind87x_type1_2_4_6:
	CMP DWORD PTR SS:[ECX+6F8h],1 ; Проверка на Type
	JE [kind87x_type1_2_4_6_fix] ; Иначе пропускаем обработку
	CMP DWORD PTR SS:[ECX+6F8h],2 ; Проверка на Type
	JE [kind87x_type1_2_4_6_fix] ; Иначе пропускаем обработку
	CMP DWORD PTR SS:[ECX+6F8h],4 ; Проверка на Type
	JE [kind87x_type1_2_4_6_fix] ; Иначе пропускаем обработку
	CMP DWORD PTR SS:[ECX+6F8h],6 ; Проверка на Type
	JE [kind87x_type1_2_4_6_fix] ; Иначе пропускаем обработку
	JMP [skip_kind]
kind87x_type1_2_4_6_fix:
	JMP [ik8_fix1] ; Если всё нормально - продолжаем
;===============================================================

skip_kind:
	JMP [ik8_fix2]


itr_kind8_types endp








