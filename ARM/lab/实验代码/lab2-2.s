		PRESERVE8
		IMPORT TC1
		AREA HUIC,CODE ,READONLY
		ENTRY
		LDR SP,=0X40000400    	;???????
		MOV R0,#1
		MOV R1,#2
		MOV R2,#3
		MOV R3,#4
		STR LR, [SP, #-4]!
		MOV R4,#6            
		STR R4, [SP, #-4]!  	;??6??
		MOV R4,#5
		STR R4, [SP, #-4]!  	;??5??
		BL TC1               	;??C?????
		ADD SP,SP,#8        	;??????,????LR???????
		LDR PC, [SP], #4   ;???LR?????????,?0x0??????
	
		END
