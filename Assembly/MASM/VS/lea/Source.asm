.386
.MODEL flat, stdcall
ExitProcess PROTO NEAR32 stdcall,
dwExitCode:DWORD
.STACK 4096
.DATA
Number dword 12345678h
.CODE
main proc
	lea eax, [Number]
	INVOKE ExitProcess, 0
main endp
end main