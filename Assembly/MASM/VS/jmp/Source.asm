.386
.MODEL flat, stdcall
ExitProcess PROTO NEAR32 stdcall,
dwExitCode:DWORD
.STACK 4096
.CODE
main proc
	jmp Android
Apple:
	mov eax, 5
	jmp Quit
Android:
	mov eax, 6
	jmp Apple
Quit:
	INVOKE ExitProcess, 0

main endp
end main