int main()
{
00007FF717C211C5  mov         ebx,14h  
00007FF717C211CA  mov         rdx,qword ptr [rsp+38h]  
00007FF717C211CF  nop  
	{
		a.emplace_back();
00007FF717C211D0  cmp         rdx,rax  
00007FF717C211D3  je          main+4Bh (07FF717C211EBh)  
00007FF717C211D5  mov         dword ptr [rdx],0Ah  
00007FF717C211DB  mov         rdx,qword ptr [rsp+38h]  
00007FF717C211E0  add         rdx,4  
00007FF717C211E4  mov         qword ptr [rsp+38h],rdx  
00007FF717C211E9  jmp         main+5Ah (07FF717C211FAh)  
00007FF717C211EB  lea         rcx,[a]  
00007FF717C211F0  call        std::vector<test_str,std::allocator<test_str> >::_Emplace_reallocate<> (07FF717C21300h)  
00007FF717C211F5  mov         rdx,qword ptr [rsp+38h]  

	for (size_t i = 0; i < 20; i++)
00007FF717C211FA  sub         rbx,1  
00007FF717C211FE  je          main+67h (07FF717C21207h)  
00007FF717C21200  mov         rax,qword ptr [rsp+40h]  
00007FF717C21205  jmp         main+30h (07FF717C211D0h)  
	}

	std::cout << a[19].a;
00007FF717C21207  mov         rdx,qword ptr [a]  
00007FF717C2120C  mov         edx,dword ptr [rdx+4Ch]  
00007FF717C2120F  mov         rcx,qword ptr [__imp_std::cout (07FF717C23088h)]  
00007FF717C21216  call        qword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (07FF717C23080h)]  
00007FF717C2121C  nop  
}
00007FF717C2121D  mov         rcx,qword ptr [a]  
00007FF717C21222  test        rcx,rcx  
00007FF717C21225  je          main+0D3h (07FF717C21273h)  
00007FF717C21227  mov         rdx,qword ptr [rsp+40h]  
00007FF717C2122C  sub         rdx,rcx  
00007FF717C2122F  and         rdx,0FFFFFFFFFFFFFFFCh  
00007FF717C21233  mov         rax,rcx  
00007FF717C21236  cmp         rdx,1000h  
00007FF717C2123D  jb          main+0CEh (07FF717C2126Eh)  
00007FF717C2123F  add         rdx,27h  
00007FF717C21243  mov         rcx,qword ptr [rcx-8]  
00007FF717C21247  sub         rax,rcx  
00007FF717C2124A  sub         rax,8  
00007FF717C2124E  cmp         rax,1Fh  
00007FF717C21252  jbe         main+0CEh (07FF717C2126Eh)  
00007FF717C21254  mov         qword ptr [rsp+20h],0  
00007FF717C2125D  xor         r9d,r9d  
00007FF717C21260  xor         r8d,r8d  
00007FF717C21263  xor         edx,edx  
00007FF717C21265  xor         ecx,ecx  
00007FF717C21267  call        qword ptr [__imp__invoke_watson (07FF717C231A8h)]  
00007FF717C2126D  int         3  
00007FF717C2126E  call        operator delete (07FF717C21574h)  
00007FF717C21273  xor         eax,eax  
00007FF717C21275  mov         rcx,qword ptr [rsp+48h]  
00007FF717C2127A  xor         rcx,rsp  
00007FF717C2127D  call        __security_check_cookie (07FF717C21510h)  
00007FF717C21282  add         rsp,50h  
00007FF717C21286  pop         rbx  
00007FF717C21287  ret  