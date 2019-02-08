;This code was created by Mesa Perry. This program evaluates postfix expressions by
;utilizing a stack. The program will print the result in hex if properly executed,
;otherwise will return an error.

.ORIG x3000
	
;your code goes here

TAKEINPUT
	IN					;
	ADD R0, R0, #-16	;
	ADD R0, R0, #-16	;
	ADD R0, R0, #-16	;
	ADD R0, R0, #-13	;
	BRnp CHK_CHAR		;check for =
	LD R1, STACK_TOP	;
	LD R2, STACK_START	;
	ADD R2, R2, #-2		;
	NOT R2, R2			;
	ADD R2, R2, R1		;
	BRz LOADRESULT		;
	BR INVALID			;

LOADRESULT
	JSR POP				;
	ADD R5, R0, #0		;
	ADD R3, R5, #0		;
	JSR PRINT_HEX		;
	HALT				;


CHK_CHAR
	AND R2, R2, #0		;
	ADD R0, R0, #15		;
	ADD R0, R0, #14		;
	BRz TAKEINPUT		;SPACE
	ADD R2, R2, #1		;
	ADD R0, R0, #-10	;
	BRz OPERATION		;MUL
	ADD R2, R2, #1		;
	ADD R0, R0, #-1		;
	BRz OPERATION		;ADD
	ADD R2, R2, #1		;
	ADD R0, R0, #-2		;
	BRz OPERATION		;SUB
	ADD R2, R2, #1		;
	ADD R0, R0, #-2		;
	BRz OPERATION		;DIV
	ADD R2, R2, #1		;
	ADD R0, R0, #-15	;
	ADD R0, R0, #-15	;
	ADD R0, R0, #-15	;
	ADD R0, R0, #-2		;
	BRz OPERATION		;EXP
	ADD R0, R0, #15		;
	ADD R0, R0, #15		;
	ADD R0, R0, #15		;
	ADD R0, R0, #2		;
	BRn INVALID			;
	ADD R0, R0, #-10	;
	BRp INVALID			;
	ADD R0, R0, #9		;
	JSR PUSH			;
	BR TAKEINPUT		;

INVALID
	LEA R0, INV_STR		;
	PUTS				;
	HALT				;

OPERATION
	JSR POP				;
	ADD R4, R0, #0		;
	JSR POP				;
	ADD R3, R0, #0		;
	ADD R5, R5, #0		;
	BRp INVALID			;
	ADD R2, R2, #-1		;
	BRz	MULB			;
	ADD R2, R2, #-1		;
	BRz ADDB			;
	ADD R2, R2, #-1		;
	BRz SUBB			;
	ADD R2, R2, #-1		;
	BRz DIVB			;
	ADD R2, R2, #-1		;
	BRz EXPB			;

MULB
	JSR MUL				;
	JSR PUSH			;
	BR TAKEINPUT		;

ADDB
	JSR PLUS			;
	JSR PUSH			;
	BR TAKEINPUT		;
SUBB
	JSR MIN				;
	JSR PUSH			;
	BR TAKEINPUT		;
DIVB
	JSR DIV				;
	JSR PUSH			;
	BR TAKEINPUT		;
EXPB
	JSR EXP				;
	JSR PUSH			;
	BR TAKEINPUT		;


INV_STR	.STRINGZ "Invalid Expression"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	ST R7, PRINT_SaveR7	;save R7
	AND R1, R1, #0		;init digit counter
	ADD R1, R1, #4		;
MainLoop
	AND R0, R0, #0		;init digit
	AND R2, R2, #0		;init bit counter
	ADD R2, R2, #4		;
BitLoop
	ADD R0, R0, R0		;
	ADD R3, R3, #0		;
	BRzp HexSkip		;
	ADD R0, R0, #1		;
HexSkip
	ADD R3, R3, R3		;
	ADD R2, R2, #-1		;
	BRp BitLoop			;
	ADD R0, R0, #-9		;
	BRnz HexSkip2		;
	ADD R0, R0, #7		;
HexSkip2
	ADD R0, R0, #7		;
	ADD R0, R0, #10		;
	ADD R0, R0, #10		;
	ADD R0, R0, #10		;
	ADD R0, R0, #10		;
	ADD R0, R0, #10		;
	OUT					;
	ADD R1, R1, #-1		;
	BRp MainLoop		;
	LD R7, PRINT_SaveR7	;
	RET					;

PRINT_SaveR7	.BLKW #1	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ADD R0, R3, R4		;
	RET					;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	NOT R0, R4			;
	ADD R0, R0, #1		;
	ADD R0, R0, R3		;
	RET					;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ST R3, MUL_SaveR3	;
	AND R0, R0, #0		;
MULLOOP
	ADD R0, R0, R4		;
	ADD R3, R3, #-1		;
	BRp MULLOOP			;
	LD R3, MUL_SaveR3	;
	RET					;

MUL_SaveR3	.BLKW #1	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	ST R3, DIV_SaveR3	;
	ST R4, DIV_SaveR4	;
	AND R0, R0, #0		;
	NOT R4, R4			;
	ADD R4, R4, #1		;
DIVLOOP
	ADD R0, R0, #1		;
	ADD R3, R3, R4		;
	BRp DIVLOOP			;	
	BRz DIVSKIP			;
	ADD R0, R0, #-1		;
DIVSKIP
	LD R3, DIV_SaveR3	;
	LD R4, DIV_SaveR4	;
	RET					;

DIV_SaveR3 .BLKW #1		;
DIV_SaveR4 .BLKW #1		;	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ST R4, EXP_SaveR4	;
	ST R5, EXP_SaveR5	;
	ADD R5, R4, #0		;
	ADD R5, R5, #-1		;
	ADD R4, R3, #0		;
EXPLOOP
	
	ST R3, MULE_SaveR3	;
	AND R0, R0, #0		;
MULLOOPE
	ADD R0, R0, R4		;
	ADD R3, R3, #-1		;
	BRp MULLOOPE		;
	LD R3, MULE_SaveR3	;

	ADD R4, R0, #0		;
	ADD R5, R5, #-1		;
	BRp EXPLOOP			;
	LD R4, EXP_SaveR4	;
	LD R5, EXP_SaveR5	;
	RET					;

MULE_SaveR3	.BLKW #1	;

EXP_SaveR4 .BLKW #1		;
EXP_SaveR5 .BLKW #1		;
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
