.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.

 
SPACE   .FILL x0020
NEW_LINE        .FILL x000A
CHAR_RETURN     .FILL x000D
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.

LOOP	IN						;
		JSR IS_BALANCED			;
		BR LOOP



IS_BALANCED
        ST R1, SaveR1      		;save R1
		ADD R1, R0, #-10		;
		BRz COMPLETE			;
		ADD R1, R1, #-16		;
		ADD R1, R1, #-6			;
		BRz SPC_DET				;
		ADD	R1, R1, #-8			;
		BRz PUSH				;
		LD R1, STACK_TOP		;
		ADD R1, R1, #1			;
		LDR R1, R1, #0			;
		ADD R1, R1, #-15		;
		ADD R1, R1, #-15		;
		ADD R1, R1, #-10		;
		BRz POP					;
		AND R5, R5, #0			;
		ADD R5, R5, #-1			;
		HALT					;


SPC_DET	RET						;

COMPLETE
		LD R3, STACK_START		;
		LD R4, STACK_TOP		;
		AND R5, R5, #0			;
		ADD R5, R5, #-1			;
		NOT R3, R3				;
		ADD R3, R3, #1			;
		ADD R3, R3, R4			;
		BRnp DONE				;
		ADD R5, R5, #2			;
DONE	HALT					;
		

NEG_OPEN .FILL xFFD8
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
        ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
        AND R5, R5, #0          ;
        LD R3, STACK_END        ;
        LD R4, STACK_TOP        ;
        ADD R3, R3, #-1         ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;
OVERFLOW
        ADD R5, R5, #1          ;
DONE_PUSH
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4      ;
        LD R1, SaveR1   	    ;
        RET


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        LD R1, SaveR1   	    ;
        RET


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;

KBSRPtr			.FILL xFE00		;
KBDRPtr			.FILL xFE02		;
SaveR1     		.BLKW #1        ;


.END

