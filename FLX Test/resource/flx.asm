int main()
{
00007FF658C11000  sub         rsp,48h  
	dynamic_array<i32> d;
00007FF658C11004  lea         rcx,[d]  
00007FF658C11009  call        flx::dynamic_array<int,unsigned __int64>::dynamic_array<int,unsigned __int64> (07FF658C11050h)  
	
	d.emplace_back(1);
00007FF658C1100E  mov         rax,qword ptr [rsp+28h]  
00007FF658C11013  mov         rdx,qword ptr [rsp+30h]  
00007FF658C11018  cmp         rax,rdx  
00007FF658C1101B  jb          main+2Fh (07FF658C1102Fh)  
00007FF658C1101D  inc         rdx  
00007FF658C11020  lea         rcx,[d]  
00007FF658C11025  call        flx::dynamic_array<int,unsigned __int64>::reallocate (07FF658C110A0h)  
00007FF658C1102A  mov         rax,qword ptr [rsp+28h]  
00007FF658C1102F  mov         rcx,qword ptr [d]  
00007FF658C11034  lea         rdx,[rcx+rax*4]  
00007FF658C11038  test        rdx,rdx  
00007FF658C1103B  je          main+43h (07FF658C11043h)  
00007FF658C1103D  mov         dword ptr [rdx],1  

	return 0;
00007FF658C11043  call        operator delete (07FF658C1142Ch)  
00007FF658C11048  xor         eax,eax  
}
00007FF658C1104A  add         rsp,48h  
00007FF658C1104E  ret  
--- No source file -------------------------------------------------------------
00007FF658C1104F  int         3  
--- D:\C++\Visual Studio Projects\FLX\shared\Win64\MaxOptimizations\flx\dynamic_array.hpp 

flx_public:
	constexpr dynamic_array() noexcept
00007FF658C11050  mov         qword ptr [rsp+10h],rbx  
00007FF658C11055  mov         qword ptr [rsp+8],rcx  
00007FF658C1105A  push        rdi  
00007FF658C1105B  sub         rsp,20h  
00007FF658C1105F  mov         rbx,rcx  