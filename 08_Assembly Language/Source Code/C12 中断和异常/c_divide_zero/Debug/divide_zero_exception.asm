; Listing generated by Microsoft (R) Optimizing Compiler Version 19.22.27905.0 

	TITLE	C:\新书示例\C12 中断和异常\c_divide_zero\divide_zero_exception.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

msvcjmc	SEGMENT
__F66CEB67_corecrt_stdio_config@h DB 01H
__101834BA_corecrt_wstdio@h DB 01H
__AD6A91B7_stdio@h DB 01H
__F9CA266B_divide_zero_exception@cpp DB 01H
msvcjmc	ENDS
PUBLIC	___local_stdio_printf_options
PUBLIC	__vfprintf_l
PUBLIC	_printf
PUBLIC	?divide@@YANABN0@Z				; divide
PUBLIC	_main
PUBLIC	__JustMyCode_Default
PUBLIC	?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA ; `__local_stdio_printf_options'::`2'::_OptionsStorage
PUBLIC	__TI2PAD
PUBLIC	__CTA2PAD
PUBLIC	??_R0PAD@8					; char * `RTTI Type Descriptor'
PUBLIC	__CT??_R0PAD@84
PUBLIC	??_R0PAX@8					; void * `RTTI Type Descriptor'
PUBLIC	__CT??_R0PAX@84
PUBLIC	??_C@_0L@IHEJLGJP@?$LD?$PN?J?$PN?N?$KK?50?$KD?$KB@ ; `string'
PUBLIC	??_C@_03OFAPEBGM@?$CFs?6@			; `string'
PUBLIC	??_C@_06LADKOPEH@error?6@			; `string'
PUBLIC	??_C@_05ILDKDEIO@?$CF?42f?6@			; `string'
PUBLIC	__real@0000000000000000
PUBLIC	__real@4024000000000000
PUBLIC	__real@bff0000000000000
EXTRN	__imp____acrt_iob_func:PROC
EXTRN	__imp____stdio_common_vfprintf:PROC
EXTRN	@_RTC_CheckStackVars@8:PROC
EXTRN	@__CheckForDebuggerJustMyCode@4:PROC
EXTRN	@__security_check_cookie@4:PROC
EXTRN	__CxxThrowException@8:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_InitBase:PROC
EXTRN	__RTC_Shutdown:PROC
EXTRN	___CxxFrameHandler3:PROC
EXTRN	??_7type_info@@6B@:QWORD			; type_info::`vftable'
EXTRN	___security_cookie:DWORD
EXTRN	__fltused:DWORD
;	COMDAT ?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA
_BSS	SEGMENT
?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA DQ 01H DUP (?) ; `__local_stdio_printf_options'::`2'::_OptionsStorage
_BSS	ENDS
;	COMDAT __real@bff0000000000000
CONST	SEGMENT
__real@bff0000000000000 DQ 0bff0000000000000r	; -1
CONST	ENDS
;	COMDAT __real@4024000000000000
CONST	SEGMENT
__real@4024000000000000 DQ 04024000000000000r	; 10
CONST	ENDS
;	COMDAT __real@0000000000000000
CONST	SEGMENT
__real@0000000000000000 DQ 00000000000000000r	; 0
CONST	ENDS
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
;	COMDAT ??_C@_05ILDKDEIO@?$CF?42f?6@
CONST	SEGMENT
??_C@_05ILDKDEIO@?$CF?42f?6@ DB '%.2f', 0aH, 00H	; `string'
CONST	ENDS
;	COMDAT ??_C@_06LADKOPEH@error?6@
CONST	SEGMENT
??_C@_06LADKOPEH@error?6@ DB 'error', 0aH, 00H		; `string'
CONST	ENDS
;	COMDAT ??_C@_03OFAPEBGM@?$CFs?6@
CONST	SEGMENT
??_C@_03OFAPEBGM@?$CFs?6@ DB '%s', 0aH, 00H		; `string'
CONST	ENDS
;	COMDAT ??_C@_0L@IHEJLGJP@?$LD?$PN?J?$PN?N?$KK?50?$KD?$KB@
CONST	SEGMENT
??_C@_0L@IHEJLGJP@?$LD?$PN?J?$PN?N?$KK?50?$KD?$KB@ DB 0b3H, 0fdH, 0caH, 0fdH
	DB	0ceH, 0aaH, ' 0', 0a3H, 0a1H, 00H		; `string'
CONST	ENDS
;	COMDAT __CT??_R0PAX@84
xdata$x	SEGMENT
__CT??_R0PAX@84 DD 01H
	DD	FLAT:??_R0PAX@8
	DD	00H
	DD	0ffffffffH
	ORG $+4
	DD	04H
	DD	00H
xdata$x	ENDS
;	COMDAT ??_R0PAX@8
data$r	SEGMENT
??_R0PAX@8 DD	FLAT:??_7type_info@@6B@			; void * `RTTI Type Descriptor'
	DD	00H
	DB	'.PAX', 00H
data$r	ENDS
;	COMDAT __CT??_R0PAD@84
xdata$x	SEGMENT
__CT??_R0PAD@84 DD 01H
	DD	FLAT:??_R0PAD@8
	DD	00H
	DD	0ffffffffH
	ORG $+4
	DD	04H
	DD	00H
xdata$x	ENDS
;	COMDAT ??_R0PAD@8
data$r	SEGMENT
??_R0PAD@8 DD	FLAT:??_7type_info@@6B@			; char * `RTTI Type Descriptor'
	DD	00H
	DB	'.PAD', 00H
data$r	ENDS
;	COMDAT __CTA2PAD
xdata$x	SEGMENT
__CTA2PAD DD	02H
	DD	FLAT:__CT??_R0PAD@84
	DD	FLAT:__CT??_R0PAX@84
xdata$x	ENDS
;	COMDAT __TI2PAD
xdata$x	SEGMENT
__TI2PAD DD	00H
	DD	00H
	DD	00H
	DD	FLAT:__CTA2PAD
xdata$x	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
__unwindtable$_main DD 0ffffffffH
	DD	00H
	DD	0ffffffffH
	DD	00H
__tryblocktable$_main DD 00H
	DD	00H
	DD	01H
	DD	02H
	DD	FLAT:__catchsym$_main$3
__catchsym$_main$3 DD 01H
	DD	FLAT:??_R0PAD@8
	DD	0ffffffb4H
	DD	FLAT:__catch$_main$0
	DD	040H
	DD	00H
	DD	00H
	DD	FLAT:__catch$_main$1
__ehfuncinfo$_main DD 019930522H
	DD	02H
	DD	FLAT:__unwindtable$_main
	DD	01H
	DD	FLAT:__tryblocktable$_main
	DD	2 DUP(00H)
	DD	00H
	DD	01H
xdata$x	ENDS
; Function compile flags: /Odt
;	COMDAT __JustMyCode_Default
_TEXT	SEGMENT
__JustMyCode_Default PROC				; COMDAT
	push	ebp
	mov	ebp, esp
	pop	ebp
	ret	0
__JustMyCode_Default ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File C:\新书示例\C12 中断和异常\c_divide_zero\divide_zero_exception.cpp
;	COMDAT _main
_TEXT	SEGMENT
tv75 = -280						; size = 8
_msg$2 = -76						; size = 4
_result$ = -64						; size = 8
_num2$ = -48						; size = 8
_num1$ = -32						; size = 8
__$ArrayPad$ = -20					; size = 4
__$EHRec$ = -16						; size = 16
_main	PROC						; COMDAT

; 15   : int main() {

	push	ebp
	mov	ebp, esp
	push	-1
	push	__ehhandler$_main
	mov	eax, DWORD PTR fs:0
	push	eax
	push	ecx
	sub	esp, 264				; 00000108H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-280]
	mov	ecx, 66					; 00000042H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	push	eax
	lea	eax, DWORD PTR __$EHRec$[ebp+4]
	mov	DWORD PTR fs:0, eax
	mov	DWORD PTR __$EHRec$[ebp], esp
	mov	ecx, OFFSET __F9CA266B_divide_zero_exception@cpp
	call	@__CheckForDebuggerJustMyCode@4

; 16   : 
; 17   : 	double num1 = 10, num2 = 0;

	movsd	xmm0, QWORD PTR __real@4024000000000000
	movsd	QWORD PTR _num1$[ebp], xmm0
	xorps	xmm0, xmm0
	movsd	QWORD PTR _num2$[ebp], xmm0

; 18   : 	double result = -1;

	movsd	xmm0, QWORD PTR __real@bff0000000000000
	movsd	QWORD PTR _result$[ebp], xmm0

; 19   : 	try {

	mov	DWORD PTR __$EHRec$[ebp+12], 0

; 20   : 		result = divide(num1, num2);

	lea	eax, DWORD PTR _num2$[ebp]
	push	eax
	lea	ecx, DWORD PTR _num1$[ebp]
	push	ecx
	call	?divide@@YANABN0@Z			; divide
	add	esp, 8
	fstp	QWORD PTR tv75[ebp]
	movsd	xmm0, QWORD PTR tv75[ebp]
	movsd	QWORD PTR _result$[ebp], xmm0

; 21   : 	//	throw 1;
; 22   : 	}

	jmp	SHORT $LN4@main
__catch$_main$0:

; 23   : 	// 捕获相应类型的异常
; 24   : 	catch (const char* msg) {
; 25   : 		printf("%s\n", msg);

	mov	eax, DWORD PTR _msg$2[ebp]
	push	eax
	push	OFFSET ??_C@_03OFAPEBGM@?$CFs?6@
	call	_printf
	add	esp, 8

; 26   : 	}

	mov	eax, $LN8@main
	ret	0
__catch$_main$1:

; 27   : 	// 能处理任何类型的异常
; 28   : 	catch (...) {
; 29   : 		printf("error\n");

	push	OFFSET ??_C@_06LADKOPEH@error?6@
	call	_printf
	add	esp, 4

; 30   : 	}

	mov	eax, $LN10@main
	ret	0
$LN4@main:
	mov	DWORD PTR __$EHRec$[ebp+12], -1
	jmp	SHORT $LN9@main
$LN10@main:
	mov	DWORD PTR __$EHRec$[ebp+12], -1
	jmp	SHORT $LN7@main
$LN9@main:
	jmp	SHORT $LN7@main
$LN8@main:
	mov	DWORD PTR __$EHRec$[ebp+12], -1
$LN7@main:

; 31   : 	printf("%.2f\n", result);

	sub	esp, 8
	movsd	xmm0, QWORD PTR _result$[ebp]
	movsd	QWORD PTR [esp], xmm0
	push	OFFSET ??_C@_05ILDKDEIO@?$CF?42f?6@
	call	_printf
	add	esp, 12					; 0000000cH

; 32   : 
; 33   : 	return 0;

	xor	eax, eax

; 34   : 
; 35   : }

	push	edx
	mov	ecx, ebp
	push	eax
	lea	edx, DWORD PTR $LN16@main
	call	@_RTC_CheckStackVars@8
	pop	eax
	pop	edx
	mov	ecx, DWORD PTR __$EHRec$[ebp+4]
	mov	DWORD PTR fs:0, ecx
	pop	ecx
	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	add	esp, 280				; 00000118H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
	npad	1
$LN16@main:
	DD	3
	DD	$LN15@main
$LN15@main:
	DD	-32					; ffffffe0H
	DD	8
	DD	$LN11@main
	DD	-48					; ffffffd0H
	DD	8
	DD	$LN12@main
	DD	-76					; ffffffb4H
	DD	4
	DD	$LN13@main
$LN13@main:
	DB	109					; 0000006dH
	DB	115					; 00000073H
	DB	103					; 00000067H
	DB	0
$LN12@main:
	DB	110					; 0000006eH
	DB	117					; 00000075H
	DB	109					; 0000006dH
	DB	50					; 00000032H
	DB	0
$LN11@main:
	DB	110					; 0000006eH
	DB	117					; 00000075H
	DB	109					; 0000006dH
	DB	49					; 00000031H
	DB	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
__ehhandler$_main:
	mov	edx, DWORD PTR [esp+8]
	lea	eax, DWORD PTR [edx+12]
	mov	ecx, DWORD PTR [edx-284]
	xor	ecx, eax
	call	@__security_check_cookie@4
	mov	ecx, DWORD PTR [edx-8]
	xor	ecx, eax
	call	@__security_check_cookie@4
	mov	eax, OFFSET __ehfuncinfo$_main
	jmp	___CxxFrameHandler3
text$x	ENDS
_main	ENDP
; Function compile flags: /Odtp /RTCsu /ZI
; File C:\新书示例\C12 中断和异常\c_divide_zero\divide_zero_exception.cpp
;	COMDAT ?divide@@YANABN0@Z
_TEXT	SEGMENT
tv78 = -212						; size = 8
$T1 = -200						; size = 4
_dividend$ = 8						; size = 4
_divisor$ = 12						; size = 4
?divide@@YANABN0@Z PROC					; divide, COMDAT

; 8    : double divide(const double& dividend, const double& divisor) {

	push	ebp
	mov	ebp, esp
	sub	esp, 212				; 000000d4H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-212]
	mov	ecx, 53					; 00000035H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __F9CA266B_divide_zero_exception@cpp
	call	@__CheckForDebuggerJustMyCode@4

; 9    : 	if (divisor == 0) {

	mov	eax, DWORD PTR _divisor$[ebp]
	movsd	xmm0, QWORD PTR [eax]
	ucomisd	xmm0, QWORD PTR __real@0000000000000000
	lahf
	test	ah, 68					; 00000044H
	jp	SHORT $LN2@divide

; 10   : 		throw "除数为 0！";

	mov	DWORD PTR $T1[ebp], OFFSET ??_C@_0L@IHEJLGJP@?$LD?$PN?J?$PN?N?$KK?50?$KD?$KB@
	push	OFFSET __TI2PAD
	lea	eax, DWORD PTR $T1[ebp]
	push	eax
	call	__CxxThrowException@8
$LN2@divide:

; 11   : 	}
; 12   : 	return dividend / divisor;

	mov	eax, DWORD PTR _dividend$[ebp]
	mov	ecx, DWORD PTR _divisor$[ebp]
	movsd	xmm0, QWORD PTR [eax]
	divsd	xmm0, QWORD PTR [ecx]
	movsd	QWORD PTR tv78[ebp], xmm0
	fld	QWORD PTR tv78[ebp]
$LN1@divide:

; 13   : }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 212				; 000000d4H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?divide@@YANABN0@Z ENDP					; divide
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h
;	COMDAT _printf
_TEXT	SEGMENT
__ArgList$ = -20					; size = 4
__Result$ = -8						; size = 4
__Format$ = 8						; size = 4
_printf	PROC						; COMDAT

; 954  :     {

	push	ebp
	mov	ebp, esp
	sub	esp, 228				; 000000e4H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-228]
	mov	ecx, 57					; 00000039H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __AD6A91B7_stdio@h
	call	@__CheckForDebuggerJustMyCode@4

; 955  :         int _Result;
; 956  :         va_list _ArgList;
; 957  :         __crt_va_start(_ArgList, _Format);

	lea	eax, DWORD PTR __Format$[ebp+4]
	mov	DWORD PTR __ArgList$[ebp], eax

; 958  :         _Result = _vfprintf_l(stdout, _Format, NULL, _ArgList);

	mov	eax, DWORD PTR __ArgList$[ebp]
	push	eax
	push	0
	mov	ecx, DWORD PTR __Format$[ebp]
	push	ecx
	mov	esi, esp
	push	1
	call	DWORD PTR __imp____acrt_iob_func
	add	esp, 4
	cmp	esi, esp
	call	__RTC_CheckEsp
	push	eax
	call	__vfprintf_l
	add	esp, 16					; 00000010H
	mov	DWORD PTR __Result$[ebp], eax

; 959  :         __crt_va_end(_ArgList);

	mov	DWORD PTR __ArgList$[ebp], 0

; 960  :         return _Result;

	mov	eax, DWORD PTR __Result$[ebp]

; 961  :     }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 228				; 000000e4H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
_printf	ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h
;	COMDAT __vfprintf_l
_TEXT	SEGMENT
__Stream$ = 8						; size = 4
__Format$ = 12						; size = 4
__Locale$ = 16						; size = 4
__ArgList$ = 20						; size = 4
__vfprintf_l PROC					; COMDAT

; 642  :     {

	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __AD6A91B7_stdio@h
	call	@__CheckForDebuggerJustMyCode@4

; 643  :         return __stdio_common_vfprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, _Stream, _Format, _Locale, _ArgList);

	mov	esi, esp
	mov	eax, DWORD PTR __ArgList$[ebp]
	push	eax
	mov	ecx, DWORD PTR __Locale$[ebp]
	push	ecx
	mov	edx, DWORD PTR __Format$[ebp]
	push	edx
	mov	eax, DWORD PTR __Stream$[ebp]
	push	eax
	call	___local_stdio_printf_options
	mov	ecx, DWORD PTR [eax+4]
	push	ecx
	mov	edx, DWORD PTR [eax]
	push	edx
	call	DWORD PTR __imp____stdio_common_vfprintf
	add	esp, 24					; 00000018H
	cmp	esi, esp
	call	__RTC_CheckEsp

; 644  :     }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
__vfprintf_l ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\corecrt_stdio_config.h
;	COMDAT ___local_stdio_printf_options
_TEXT	SEGMENT
___local_stdio_printf_options PROC			; COMDAT

; 86   :     {

	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __F66CEB67_corecrt_stdio_config@h
	call	@__CheckForDebuggerJustMyCode@4

; 87   :         static unsigned __int64 _OptionsStorage;
; 88   :         return &_OptionsStorage;

	mov	eax, OFFSET ?_OptionsStorage@?1??__local_stdio_printf_options@@9@4_KA ; `__local_stdio_printf_options'::`2'::_OptionsStorage

; 89   :     }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
___local_stdio_printf_options ENDP
_TEXT	ENDS
END
