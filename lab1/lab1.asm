; R0 contains what will be printed (single digit)
; R1 is the digit counter
; R2 is the bit counter
; R3 contains the value to be printed



			.ORIG x3000
			AND		R1, R1, #0			; init digit counter
digitLoop	ADD		R1, R1, #-4			; check R1 against 4
			BRz		end					; have 4 digits have been printed?
			ADD		R1, R1, #4			; put R1 back to original number
			AND		R0, R0, #0			; init digit
			AND		R2, R2, #0			; init bit counter
bitLoop		ADD		R2, R2, #-4			; check R2 against 4
			BRz		printSeq			; have 4 bits been counted from R3?
			ADD		R2, R2, #4			; restore R2 to original number
			ADD		R0, R0, R0			; left shift R0
			ADD		R3, R3, #0			; set cc for R3
			BRzp		addedZero			; is the MSB of R3 a one or zero?
			ADD		R0, R0, #1			; it's a one
addedZero	ADD		R3, R3, R3			; left shift R3
			ADD		R2, R2, #1			; increment bit counter
			BR		bitLoop				; go back to cycle through another bit

printSeq	ADD		R0, R0, #-9			; check R0 against 9
			BRnz	itsANumber			; is the digit a number or letter?
			ADD		R0, R0, #7			; give R0 the 7 difference for letters
itsANumber	ADD		R0, R0, #15			; add 57 to make it value of the ascii
			ADD		R0, R0, #15			; splitting up the addition
			ADD		R0, R0, #15			; splitting up the addition
			ADD		R0, R0, #12			; splitting up the addition
			TRAP	x21					; print
			ADD		R1, R1, #1			; increment digit counter
			BR		digitLoop			; go back to cycle through another digit
end			TRAP	x25					; halt
			.END
