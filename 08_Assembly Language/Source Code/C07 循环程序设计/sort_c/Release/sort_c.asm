; Listing generated by Microsoft (R) Optimizing Compiler Version 19.22.27905.0 

	TITLE	c:\???????\c07 ??????????\sort_c\sort_c.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

PUBLIC	??_C@_0M@KKMMFNCK@x?$DN?$CFd?5y?$DN?$CFd?5?6@	; `string'
PUBLIC	??_C@_03JDANDILB@?$CFd?5@			; `string'
EXTRN	__imp____stdio_common_vfprintf:PROC
EXTRN	__imp____acrt_iob_func:PROC
EXTRN	@__security_check_cookie@4:PROC
;	COMDAT ??_C@_03JDANDILB@?$CFd?5@
CONST	SEGMENT
??_C@_03JDANDILB@?$CFd?5@ DB '%d ', 00H			; `string'
CONST	ENDS
;	COMDAT ??_C@_0M@KKMMFNCK@x?$DN?$CFd?5y?$DN?$CFd?5?6@
CONST	SEGMENT
??_C@_0M@KKMMFNCK@x?$DN?$CFd?5y?$DN?$CFd?5?6@ DB 'x=%d y=%d ', 0aH, 00H ; `string'
CONST	ENDS
PUBLIC	_main
PUBLIC	_printf
PUBLIC	__vfprintf_l
PUBLIC	___local_stdio_printf_options
PUBLIC	__xmm@ffffff9c0000001e00000014fffffff6
COMM	?_OptionsStorage@?1??__local_stdio_printf_options@@9@9:QWORD							; `__local_stdio_printf_options'::`2'::_OptionsStorage
_DATA	ENDS
;	COMDAT __xmm@ffffff9c0000001e00000014fffffff6
CONST	SEGMENT
__xmm@ffffff9c0000001e00000014fffffff6 DB 0f6H, 0ffH, 0ffH, 0ffH, 014H, 00H
	DB	00H, 00H, 01eH, 00H, 00H, 00H, 09cH, 0ffH, 0ffH, 0ffH
CONST	ENDS
; Function compile flags: /Ogtp
; File C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\corecrt_stdio_config.h
;	COMDAT ___local_stdio_printf_options
_TEXT	SEGMENT
___local_stdio_printf_options PROC			; COMDAT

; 87   :         static unsigned __int64 _OptionsStorage;
; 88   :         return &_OptionsStorage;

	mov	eax, OFFSET ?_OptionsStorage@?1??__local_stdio_printf_options@@9@9 ; `__local_stdio_printf_options'::`2'::_OptionsStorage

; 89   :     }

	ret	0
___local_stdio_printf_options ENDP
_TEXT	ENDS
; Function compile flags: /Ogtp
; File C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h
;	COMDAT __vfprintf_l
_TEXT	SEGMENT
__Locale$dead$ = 8					; size = 4
__ArgList$ = 12						; size = 4
__vfprintf_l PROC					; COMDAT
; __Stream$ = ecx
; __Format$ = edx

; 642  :     {

	push	ebp
	mov	ebp, esp

; 643  :         return __stdio_common_vfprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, _Stream, _Format, _Locale, _ArgList);

	push	DWORD PTR __ArgList$[ebp]
	push	0
	push	edx
	push	ecx
	call	___local_stdio_printf_options
	push	DWORD PTR [eax+4]
	push	DWORD PTR [eax]
	call	DWORD PTR __imp____stdio_common_vfprintf
	add	esp, 24					; 00000018H

; 644  :     }

	pop	ebp
	ret	0
__vfprintf_l ENDP
_TEXT	ENDS
; Function compile flags: /Ogtp
; File C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt\stdio.h
;	COMDAT _printf
_TEXT	SEGMENT
__Format$ = 8						; size = 4
_printf	PROC						; COMDAT

; 954  :     {

	push	ebp
	mov	ebp, esp
	push	esi

; 955  :         int _Result;
; 956  :         va_list _ArgList;
; 957  :         __crt_va_start(_ArgList, _Format);
; 958  :         _Result = _vfprintf_l(stdout, _Format, NULL, _ArgList);

	mov	esi, DWORD PTR __Format$[ebp]
	push	1
	call	DWORD PTR __imp____acrt_iob_func
	add	esp, 4

; 643  :         return __stdio_common_vfprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, _Stream, _Format, _Locale, _ArgList);

	lea	ecx, DWORD PTR __Format$[ebp+4]
	push	ecx
	push	0
	push	esi
	push	eax
	call	___local_stdio_printf_options
	push	DWORD PTR [eax+4]
	push	DWORD PTR [eax]
	call	DWORD PTR __imp____stdio_common_vfprintf
	add	esp, 24					; 00000018H

; 959  :         __crt_va_end(_ArgList);
; 960  :         return _Result;

	pop	esi

; 961  :     }

	pop	ebp
	ret	0
_printf	ENDP
_TEXT	ENDS
; Function compile flags: /Ogtp
; File C:\????????\C07 ????????????\sort_c\sort_c.c
;	COMDAT _main
_TEXT	SEGMENT
_buf$ = -24						; size = 24
_argc$ = 8						; size = 4
_argv$ = 12						; size = 4
_main	PROC						; COMDAT

; 4    : {

	push	ebp
	mov	ebp, esp
	sub	esp, 24					; 00000018H

; 5    : 	int buf[N] = { -10, 20, 30, -100, 25, 60 };

	movaps	xmm0, XMMWORD PTR __xmm@ffffff9c0000001e00000014fffffff6
	push	ebx
	push	esi
	push	edi

; 6    : 	int  i;
; 7    : 	int  j;
; 8    : 	int  x = 20;
; 9    : 	int  y = 30;
; 10   : 
; 11   : 	printf("x=%d y=%d \n", x, y);

	push	30					; 0000001eH
	push	20					; 00000014H
	push	OFFSET ??_C@_0M@KKMMFNCK@x?$DN?$CFd?5y?$DN?$CFd?5?6@
	movups	XMMWORD PTR _buf$[ebp], xmm0
	mov	DWORD PTR _buf$[ebp+16], 25		; 00000019H
	mov	DWORD PTR _buf$[ebp+20], 60		; 0000003cH
	call	_printf
	mov	edi, 1
	lea	ecx, DWORD PTR _buf$[ebp]
	add	esp, 12					; 0000000cH
	lea	ebx, DWORD PTR [edi+4]
	npad	2
$LL4@main:

; 13   : 	   for (j = i + 1; j < N;j++)

	mov	eax, edi
	cmp	edi, 6
	jge	SHORT $LN2@main
$LL7@main:

; 14   : 	      if (buf[i] > buf[j]) {

	mov	edx, DWORD PTR _buf$[ebp+eax*4]
	mov	esi, DWORD PTR [ecx]
	cmp	esi, edx
	jle	SHORT $LN5@main

; 15   : 		     x = buf[i];
; 16   : 		     buf[i] = buf[j];

	mov	DWORD PTR [ecx], edx

; 17   : 		     buf[j] = x;

	mov	DWORD PTR _buf$[ebp+eax*4], esi
$LN5@main:

; 13   : 	   for (j = i + 1; j < N;j++)

	inc	eax
	cmp	eax, 6
	jl	SHORT $LL7@main
$LN2@main:

; 12   : 	for (i = 0; i < N - 1; i++) {

	inc	edi
	add	ecx, 4
	sub	ebx, 1
	jne	SHORT $LL4@main

; 18   : 	     }
; 19   : 	}
; 20   : 	for (i = 0; i < N;i++)

	xor	esi, esi
	npad	8
$LL10@main:

; 21   : 	   printf("%d ", buf[i]);

	push	DWORD PTR _buf$[ebp+esi*4]
	push	OFFSET ??_C@_03JDANDILB@?$CFd?5@
	call	_printf
	inc	esi
	add	esp, 8
	cmp	esi, 6
	jl	SHORT $LL10@main

; 22   : 	return 0;

	pop	edi
	pop	esi
	xor	eax, eax
	pop	ebx

; 23   : }

	mov	esp, ebp
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
END
