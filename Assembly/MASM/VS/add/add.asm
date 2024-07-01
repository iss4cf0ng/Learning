.386
.MODEL flat, stdcall
ExitProcess PROTO NEAR32 stdcall,
dwExitCode:DWORD
.STACK 4096
.CODE
main proc
	mov eax, 5
	add eax, 2
	INVOKE ExitProcess, 0
main endp
end main