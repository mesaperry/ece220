; This code was modified by Mesa Perry to print a histogram to the
; screen of a string written in memory locations starting with x4000.
; This code contains two parts. The first part, which I did not create,
; takes the string and generates the data for the histogram. The data
; is stored in memory. The second part, which I did create, takes this
; data and prints it to the screen with comprehensive labels. The
; string has to be manually written to memory.



;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA			; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop


; table of register use in this part of the code
;    R0 contains what will be printed (single digit)
;    R1 is the digit counter
;    R2 is the bit counter
;    R3 contains the value to be printed
;    R4 holds a pointer to the histogram (x3F00), then increases
;	 as the values of the histogram are printed
;    R5 counts down from 27, representing the 27 values to be printed
;    R6 holds the hex data which character is being counted/printed
;

PRINT_HIST
	LD 		R4,HIST_ADDR  	; point R4 to the start of the histogram
	LD		R6, atCharacter	; loads R6 with the hex for the first character
	AND		R5, R5, #0		; clear R5
	ADD		R5, R5, #15		; init R5 to 27
	ADD		R5, R5, #12		; init R5 to 27

LinePrintLoop
	LDR		R3, R4, #0		; load R3 with the value to be printed
	ADD		R0, R6, #0		; puts the current character in R0 to be printed, from R6
	TRAP	x21				; print the current character
	LD		R0, spaceChar	; load the spaceChar code into R0 to be printed
	TRAP	x21				; print a space
	AND		R1, R1, #0		; init digit counter
digitLoop
	ADD		R1, R1, #-4		; check R1 against 4
	BRz		end				; have 4 digits have been printed?
	ADD		R1, R1, #4		; put R1 back to original number
	AND		R0, R0, #0		; init digit
	AND		R2, R2, #0		; init bit counter
bitLoop	
	ADD		R2, R2, #-4		; check R2 against 4
	BRz		printSeq		; have 4 bits been counted from R3?
	ADD		R2, R2, #4		; restore R2 to original number
	ADD		R0, R0, R0		; left shift R0
	ADD		R3, R3, #0		; set cc for R3
	BRzp	addedZero		; is the MSB of R3 a one or zero?
	ADD		R0, R0, #1		; it's a one
addedZero
	ADD		R3, R3, R3		; left shift R3
	ADD		R2, R2, #1		; increment bit counter
	BR		bitLoop			; go back to cycle through another bit
printSeq
	ADD		R0, R0, #-9		; check R0 against 9
	BRnz	itsANumber		; is the digit a number or letter?
	ADD		R0, R0, #7		; give R0 the 7 difference for letters
itsANumber
	ADD		R0, R0, #15		; add 57 to make it value of the ascii
	ADD		R0, R0, #15		; splitting up the addition
	ADD		R0, R0, #15		; splitting up the addition
	ADD		R0, R0, #12		; splitting up the addition
	TRAP	x21				; print
	ADD		R1, R1, #1		; increment digit counter
	BR		digitLoop		; go back to cycle through another digit
end
	LD		R0, NEXT_LINE	; load next line data into R0 to be printed
	TRAP	x21				; print next line
	ADD		R4, R4, #1		; increment R4 to the location of the next value
	ADD		R6, R6, #1		; increment R6 to the next counted character being printed
	ADD		R5, R5, #-1		; decrement R5, representing one less value to print
	BRz		DONE			; finish if gone through 27 print loops
	BRnzp	LinePrintLoop	; loop back to start a new line

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE
	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address

NEXT_LINE   .FILL x000A ; next line ascii data
atCharacter	.FILL x0040 ; @ character ascii data
spaceChar	.FILL x0020 ; space character ascii data

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
