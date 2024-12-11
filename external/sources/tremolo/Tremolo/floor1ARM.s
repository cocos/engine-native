	.text
	
	.global	render_lineARM
	
render_lineARM:
	@ r0 = n
	@ r1 = d
	@ r2 = floor
	@ r3 = base
	@ <> = err
	@ <> = adx
	@ <> = ady
	MOV	r12,r13
	STMFD	r13!,{r4-r6,r11,r14}
	LDMFD	r12,{r11,r12,r14}	@ r11 = err
					@ r12 = adx
					@ r14 = ady
rl_loop:
	LDR	r4,[r1]			@ r4 = *d
	LDR	r5,[r2],r3,LSL #2	@ r5 = *floor    r2 = floor+base
	SUBS	r11,r11,r14		@ err -= ady
	ADDLT	r11,r11,r12		@ if (err < 0) err+=adx
	SMULL	r6, r5, r4, r5		@ (r6,r5) = *d * *floor
	ADDLT	r2, r2, #4		@              floor+=1
	MOVS	r6, r6, LSR #15
	ADC	r5, r6, r5, LSL #17	@ r5 = MULT31_SHIFT15
	STR	r5,[r1],#4
	SUBS	r0, r0, #1
	BGT	rl_loop

	LDMFD	r13!,{r4-r6,r11,PC}
