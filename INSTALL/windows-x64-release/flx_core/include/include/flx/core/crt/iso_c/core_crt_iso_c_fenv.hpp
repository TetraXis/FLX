#ifndef FLX_INC_CORE_CRT_ISO_C_FENV_HPP
#define FLX_INC_CORE_CRT_ISO_C_FENV_HPP

// This is a part of a compatibility layer between FLX and CRT.
// It is needed since Windows' CRT does not follow POSIX.

// To Dev: when linking to new CRT functions, do not forget to add both variants.

// This header can not be linked fully, since fenv_t and fexcept_t are implementation specific, thus their size is unknown.

#include "flx/core.hpp"

// TODO: here

// extern "C"
// {
// 	struct fexcept_t;
// 	struct femode_t;
// 	struct fenv_t;
// 
// 	using namespace flx::types;
// 	using namespace flx::crt;
// 
// 	i32 feclearexcept		(i32 excepts);
// 	i32 fegetexceptflag		(fexcept_t* flagp, i32 excepts);
// 	i32 feraiseexcept		(i32 excepts);
// 	i32 fesetexcept			(i32 excepts);
// 	i32 fesetexceptflag		(const fexcept_t* flagp, i32 excepts);
// 	i32 fetestexceptflag	(const fexcept_t* flagp, i32 excepts);
// 	i32 fetestexcept		(i32 excepts);
// 	i32 fegetmode			(femode_t* modep);
// 	i32 fegetround			(void);
// 	i32 fesetmode			(const femode_t* modep);
// 	i32 fesetround			(i32 rnd);
// 	i32 fegetenv			(fenv_t* envp);
// 	i32 feholdexcept		(fenv_t* envp);
// 	i32 fesetenv			(const fenv_t* envp);
// 	i32 feupdateenv			(const fenv_t* envp);
// } // extern "C"
// 
// namespace flx::crt
// {
// 	inline i32 feclearexcept		(i32 excepts)							noexcept { return feclearexcept		(excepts);							}
// 	inline i32 fegetexceptflag		(fexcept_t* flagp, i32 excepts)			noexcept { return fegetexceptflag	(flagp, excepts);					}	
// 	inline i32 feraiseexcept		(i32 excepts)							noexcept { return feraiseexcept		(excepts);							}
// 	inline i32 fesetexcept			(i32 excepts)							noexcept { return fesetexcept		(excepts);							}	
// 	inline i32 fesetexceptflag		(const fexcept_t* flagp, i32 excepts)	noexcept { return fesetexceptflag	(const fexcept_t* flagp, excepts);	}	
// 	inline i32 fetestexceptflag		(const fexcept_t* flagp, i32 excepts)	noexcept { return fetestexceptflag	(const fexcept_t* flagp, excepts);	}		
// 	inline i32 fetestexcept			(i32 excepts)							noexcept { return fetestexcept		(i32 excepts);						}	
// 	inline i32 fegetmode			(femode_t* modep)						noexcept { return fegetmode			(modep);							}
// 	inline i32 fegetround			()										noexcept { return fegetround		();									}
// 	inline i32 fesetmode			(const femode_t* modep)					noexcept { return fesetmode			(modep);							}
// 	inline i32 fesetround			(i32 rnd)								noexcept { return fesetround		(rnd);								}
// 	inline i32 fegetenv				(fenv_t* envp)							noexcept { return fegetenv			(envp);								}	
// 	inline i32 feholdexcept			(fenv_t* envp)							noexcept { return feholdexcept		(envp);								}	
// 	inline i32 fesetenv				(const fenv_t* envp)					noexcept { return fesetenv			(envp);								}	
// 	inline i32 feupdateenv			(const fenv_t* envp)					noexcept { return feupdateenv		(envp);								}	
// 
// 	constexpr int FE_INVALID	= 0x01;
// 	constexpr int FE_DENORMAL	= 0x02;
// 	constexpr int FE_DIVBYZERO	= 0x04;
// 	constexpr int FE_OVERFLOW	= 0x08;
// 	constexpr int FE_UNDERFLOW	= 0x10;
// 	constexpr int FE_INEXACT	= 0x20;
// 	constexpr int FE_ALL_EXCEPT	= FE_INVALID | FE_DENORMAL | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT;
// 
// 	constexpr int FE_TONEAREST	= 0x00;
// 	constexpr int FE_DOWNWARD	= 0x400;
// 	constexpr int FE_UPWARD		= 0x800;
// 	constexpr int FE_TOWARDZERO	= 0xC00;
// 
// 		// TODO: Check if this works for all supported platforms
// 		// ===== UCRT/MSVCRT ===== //
// 	#if FLX_ENV_CRT == FLX_ENV_CRT_MSVCRT || FLX_ENV_CRT == FLX_ENV_CRT_UCRT
// 
// 		struct fexcept_t
// 		{
// 
// 		};
// 
// 		// ===== POSIX ===== //
// 	#elif
// 
// 
// 
// 	#endif
// } // namespace flx::crt



#endif //FLX_INC_CORE_CRT_ISO_C_FENV_HPP
