int main()
{
00007FF68BDC11A0  sub         rsp,68h  
00007FF68BDC11A4  mov         rax,qword ptr [__security_cookie (07FF68BDC5040h)]  
00007FF68BDC11AB  xor         rax,rsp  
00007FF68BDC11AE  mov         qword ptr [rsp+50h],rax  
00007FF68BDC11B3  xor         eax,eax  
00007FF68BDC11B5  xorps       xmm1,xmm1  
	std::vector<i32> d;
00007FF68BDC11B8  movdqu      xmmword ptr [d],xmm1  
00007FF68BDC11BE  mov         qword ptr [rsp+48h],rax  
	
	d.emplace_back(1);
00007FF68BDC11C3  mov         dword ptr [rsp+30h],1  
00007FF68BDC11CB  lea         r8,[rsp+30h]  
00007FF68BDC11D0  xor         edx,edx  
00007FF68BDC11D2  lea         rcx,[d]  
00007FF68BDC11D7  call        std::vector<int,std::allocator<int> >::_Emplace_reallocate<int> (07FF68BDC12C0h)  
00007FF68BDC11DC  nop  

	return 0;
00007FF68BDC11DD  mov         rcx,qword ptr [d]  
00007FF68BDC11E2  test        rcx,rcx  
00007FF68BDC11E5  je          main+93h (07FF68BDC1233h)  
00007FF68BDC11E7  mov         rdx,qword ptr [rsp+48h]  
00007FF68BDC11EC  sub         rdx,rcx  
00007FF68BDC11EF  and         rdx,0FFFFFFFFFFFFFFFCh  
00007FF68BDC11F3  mov         rax,rcx  
00007FF68BDC11F6  cmp         rdx,1000h  
00007FF68BDC11FD  jb          main+8Eh (07FF68BDC122Eh)  
00007FF68BDC11FF  add         rdx,27h  
00007FF68BDC1203  mov         rcx,qword ptr [rcx-8]  
00007FF68BDC1207  sub         rax,rcx  
00007FF68BDC120A  sub         rax,8  
00007FF68BDC120E  cmp         rax,1Fh  
00007FF68BDC1212  jbe         main+8Eh (07FF68BDC122Eh)  
00007FF68BDC1214  mov         qword ptr [rsp+20h],0  
00007FF68BDC121D  xor         r9d,r9d  
00007FF68BDC1220  xor         r8d,r8d  
00007FF68BDC1223  xor         edx,edx  
00007FF68BDC1225  xor         ecx,ecx  
00007FF68BDC1227  call        qword ptr [__imp__invoke_watson (07FF68BDC3170h)]  
00007FF68BDC122D  int         3  
00007FF68BDC122E  call        operator delete (07FF68BDC1774h)  
00007FF68BDC1233  xor         eax,eax  
}
00007FF68BDC1235  mov         rcx,qword ptr [rsp+50h]  
00007FF68BDC123A  xor         rcx,rsp  
00007FF68BDC123D  call        __security_check_cookie (07FF68BDC1710h)  
00007FF68BDC1242  add         rsp,68h  
00007FF68BDC1246  ret  