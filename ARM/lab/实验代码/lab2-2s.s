		PRESERVE8
		IMPORT TC1
		AREA HUIC,CODE ,READONLY
		ENTRY
		LDR SP,=0X40000400    	;��ʼ����ջָ��
		MOV R0,#20
		MOV R1,#5
		MOV R2,#4
		MOV R3,#3
		STR LR, [SP, #-4]!
		MOV R4,#2           
		STR R4, [SP, #-4]!  	 ;����6��ջ
		MOV R4,#1       
		STR R4, [SP, #-4]!  	;����5��ջ
		BL TC1               	;����c����
		ADD SP,SP,#8        	;�޸Ķ�ջָ�룬ʹ��ָ��LRѹջ�Ĵ洢��Ԫ
		LDR PC, [SP], #4      ;����LRִ�еĳ����ִַ��
	
		END
