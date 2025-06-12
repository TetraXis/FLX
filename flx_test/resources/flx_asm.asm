int main()
{
00007FF7BA2B1000  mov         qword ptr [rsp+8],rbx  
00007FF7BA2B1005  mov         qword ptr [rsp+10h],rbp  
00007FF7BA2B100A  mov         qword ptr [rsp+18h],rsi  
00007FF7BA2B100F  push        rdi  
00007FF7BA2B1010  push        r14  
00007FF7BA2B1012  push        r15  
00007FF7BA2B1014  sub         rsp,40h  
	test_t a;
00007FF7BA2B1018  mov         ecx,10h  
00007FF7BA2B101D  call        operator new (07FF7BA2B1170h)  
00007FF7BA2B1022  mov         rsi,rax  
00007FF7BA2B1025  mov         qword ptr [a],rax  
00007FF7BA2B102A  xor         edi,edi  
00007FF7BA2B102C  mov         qword ptr [rsp+28h],rdi  
00007FF7BA2B1031  mov         r15d,4  
00007FF7BA2B1037  mov         qword ptr [rsp+30h],r15  
00007FF7BA2B103C  mov         ebp,14h  
	{
		a.emplace_back();
00007FF7BA2B1041  cmp         rdi,r15  
00007FF7BA2B1044  jne         main+0E0h (07FF7BA2B10E0h)  
00007FF7BA2B104A  add         r15,r15  
00007FF7BA2B104D  mov         qword ptr [rsp+30h],r15  
00007FF7BA2B1052  lea         rcx,[r15*4]  
00007FF7BA2B105A  call        operator new (07FF7BA2B1170h)  
00007FF7BA2B105F  mov         r14,rax  
00007FF7BA2B1062  xor         ebx,ebx  
00007FF7BA2B1064  test        rdi,rdi  
00007FF7BA2B1067  je          main+0D0h (07FF7BA2B10D0h)  
00007FF7BA2B1069  cmp         rdi,4  
00007FF7BA2B106D  jb          main+0A8h (07FF7BA2B10A8h)  
00007FF7BA2B106F  lea         rax,[rdi-1]  
00007FF7BA2B1073  lea         rax,[r14+rax*4]  
00007FF7BA2B1077  lea         rcx,[rdi-1]  
00007FF7BA2B107B  lea         rcx,[rsi+rcx*4]  
00007FF7BA2B107F  cmp         r14,rcx  
00007FF7BA2B1082  ja          main+89h (07FF7BA2B1089h)  
00007FF7BA2B1084  cmp         rax,rsi  
00007FF7BA2B1087  jae         main+0A8h (07FF7BA2B10A8h)  
00007FF7BA2B1089  lea         r8,[rdi*4]  
00007FF7BA2B1091  mov         rdx,rsi  
00007FF7BA2B1094  mov         rcx,r14  
00007FF7BA2B1097  call        memcpy (07FF7BA2B20F2h)  
00007FF7BA2B109C  nop         dword ptr [rax]  
00007FF7BA2B10A0  inc         rbx  
00007FF7BA2B10A3  cmp         rbx,rdi  
00007FF7BA2B10A6  jb          main+0A0h (07FF7BA2B10A0h)  
00007FF7BA2B10A8  cmp         rbx,rdi  
00007FF7BA2B10AB  jae         main+0D0h (07FF7BA2B10D0h)  
00007FF7BA2B10AD  lea         rcx,[r14+rbx*4]  
00007FF7BA2B10B1  mov         r8,rsi  
00007FF7BA2B10B4  sub         r8,r14  
00007FF7BA2B10B7  mov         rdx,rdi  
00007FF7BA2B10BA  sub         rdx,rbx  
00007FF7BA2B10BD  nop         dword ptr [rax]  
00007FF7BA2B10C0  mov         eax,dword ptr [r8+rcx]  
00007FF7BA2B10C4  mov         dword ptr [rcx],eax  
00007FF7BA2B10C6  lea         rcx,[rcx+4]  
00007FF7BA2B10CA  sub         rdx,1  
00007FF7BA2B10CE  jne         main+0C0h (07FF7BA2B10C0h)  
00007FF7BA2B10D0  mov         rcx,rsi  
00007FF7BA2B10D3  call        operator delete (07FF7BA2B11ACh)  
00007FF7BA2B10D8  mov         rsi,r14  
00007FF7BA2B10DB  mov         qword ptr [a],r14  
00007FF7BA2B10E0  mov         dword ptr [rsi+rdi*4],0Ah  
00007FF7BA2B10E7  inc         rdi  
00007FF7BA2B10EA  mov         qword ptr [rsp+28h],rdi  

	for (size_t i = 0; i < 20; i++)
00007FF7BA2B10EF  sub         rbp,1  
00007FF7BA2B10F3  jne         main+41h (07FF7BA2B1041h)  
	}

	std::cout << a[19].a;
00007FF7BA2B10F9  mov         edx,dword ptr [rsi+4Ch]  
00007FF7BA2B10FC  mov         rcx,qword ptr [__imp_std::cout (07FF7BA2B3080h)]  
00007FF7BA2B1103  call        qword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (07FF7BA2B3088h)]  
00007FF7BA2B1109  nop  
}
00007FF7BA2B110A  mov         rcx,rsi  
00007FF7BA2B110D  call        operator delete (07FF7BA2B11ACh)  
00007FF7BA2B1112  xor         eax,eax  
00007FF7BA2B1114  mov         rbx,qword ptr [rsp+60h]  
00007FF7BA2B1119  mov         rbp,qword ptr [rsp+68h]  
00007FF7BA2B111E  mov         rsi,qword ptr [rsp+70h]  
00007FF7BA2B1123  add         rsp,40h  
00007FF7BA2B1127  pop         r15  
00007FF7BA2B1129  pop         r14  
00007FF7BA2B112B  pop    