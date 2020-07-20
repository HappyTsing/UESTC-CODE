		PRESERVE8
		IMPORT TC1
		AREA HUIC,CODE ,READONLY
		ENTRY
		LDR SP,=0X40000400    	;初始化堆栈指针
		MOV R0,#20
		MOV R1,#5
		MOV R2,#4
		MOV R3,#3
		STR LR, [SP, #-4]!
		MOV R4,#2           
		STR R4, [SP, #-4]!  	 ;参数6入栈
		MOV R4,#1       
		STR R4, [SP, #-4]!  	;参数5入栈
		BL TC1               	;调用c程序
		ADD SP,SP,#8        	;修改堆栈指针，使其指向LR压栈的存储单元
		LDR PC, [SP], #4      ;跳到LR执行的程序地址执行
	
		END
