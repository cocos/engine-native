	.text

	.global stmiaTest
	.global strTest
	.global smullTest

stmiaTest:
	STMFD	r13!,{r4-r12,r14}

	@ r0 = start
	@ r1 = size
	@ r2 = loops
stmiaTestLoop2:
	MOV	r3,r0
	MOV	r4,r1
stmiaTestLoop:
	STMIA	r3!,{r6,r7,r8,r9,r10,r11,r12,r14}
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0

	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0

	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0

	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0

	SUBS	r4,r4,#8*4
	BGT	stmiaTestLoop

	SUBS	r2,r2,#1
	BGT	stmiaTestLoop2


	LDMFD	r13!,{r4-r12,PC}

strTest:
	STMFD	r13!,{r4-r12,r14}

	@ r0 = start
	@ r1 = size
	@ r2 = loops
strTestLoop2:
	MOV	r3,r0
	MOV	r4,r1
strTestLoop:
	STR	r6,[r3],#4
	STR	r7,[r3],#4
	STR	r8,[r3],#4
	STR	r9,[r3],#4
	STR	r10,[r3],#4
	STR	r11,[r3],#4
	STR	r12,[r3],#4
	STR	r14,[r3],#4
	@STMIA	r3!,{r6,r7,r8,r9,r10,r11,r12,r14}
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0

	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0

	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0

	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0
	MOV	r6,#0

	SUBS	r4,r4,#8*4
	BGT	strTestLoop

	SUBS	r2,r2,#1
	BGT	strTestLoop2

	LDMFD	r13!,{r4-r12,PC}

smullTest:
	STMFD	r13!,{r4-r12,r14}

	@ r0 = start
	@ r1 = size
	@ r2 = loops
smullTestLoop2:
	MVN	r7,#0xAA000000
	MVN	r8,#0xAA000000
	MOV	r3,r0
	MOV	r4,r1
smullTestLoop:
	SMULL	r14,r12,r7,r8
	MOV	r6,#0
	SMLAL	r14,r12,r7,r8
	MOV	r6,#0
	SMULL	r14,r11,r7,r8
	MOV	r6,#0
	SMLAL	r14,r11,r7,r8

	SUBS	r4,r4,#8*4
	BGT	smullTestLoop

	SUBS	r2,r2,#1
	BGT	smullTestLoop2

	LDMFD	r13!,{r4-r12,PC}
