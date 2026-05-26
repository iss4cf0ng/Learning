//TestException3.cpp
int main() {
	__asm {
		push Handler
		push FS:[0]
		push FSl[0],ESP
	}

	*(int*)0 = 0;

	__asm {
	Handler:
		INT 3
	}
}
