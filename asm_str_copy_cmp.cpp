#include <iostream>

using namespace std;

void __declspec (naked) asmCopy(char[], char[], int)
{
	__asm
	{
		pushad
		pushfd
		mov ebp, esp

		mov edi, [ebp+40]
 		mov esi, [ebp+44]
		mov ecx, [ebp+48]
		cld

		rep movsb

		mov esp, ebp
		popfd
		popad
		ret
	}
}

bool __declspec (naked) asmCompare(char[], char[], int)
{
	__asm
	{
		push ecx
		push esi
		push edi
		pushfd
		mov ebp, esp

		mov ecx, [ebp+28]
		mov esi, [ebp+24]
		mov edi, [ebp+20]
		sub eax, eax

		cld

		repe cmpsb

		jne DONE
		inc eax
DONE:
		mov esp, ebp
		popfd
		pop edi
		pop esi
		pop ecx
		ret

	}
}

int main()
{
	char asdf[] = "Testing";
	char asdf2[20];


	asmCopy(asdf2, asdf, 7);

	for(int i = 0; i < 7; i++)
		cout << asdf2[i] << "\t";
	cout << endl;

	bool test = asmCompare(asdf2, asdf, 7);
	if(test)
		cout << "true" << endl;
		
	cin.get();cin.get();cin.get();cin.get();
	return 0;
}