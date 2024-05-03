.data

oneNOP			db 90h
doubleNOP       	dw 9090h
FourNOP			dd 90909090h
EightNOP	 		dq 9090909090909090h
F4_patch	 		db 02h
MakeByte1	 	db 80h
MakeByte2	 	db 88h
random			dq 00417170h
keyByte0	 		dd 66h
cleaner		 	dd 00
TimeStopTime 		dd 459E00h
JNEtoJMP		byte 0EBh
numbersFix	 	byte 81h
; jne 00412C74
