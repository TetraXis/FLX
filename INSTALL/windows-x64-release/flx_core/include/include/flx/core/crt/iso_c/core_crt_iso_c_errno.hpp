#ifndef FLX_INC_CORE_CRT_ISO_C_ERRNO_HPP
#define FLX_INC_CORE_CRT_ISO_C_ERRNO_HPP

// This is a part of a compatibility layer between FLX and CRT.
// It is needed since Windows' CRT does not follow POSIX.

// To Dev: when linking to new CRT functions, do not forget to add both variants.

#include "flx/core.hpp"

extern "C"
{
	using namespace flx::types;

	// ===== WIN CRT ===== //
#if FLX_ENV_CRT == FLX_ENV_CRT_MSVCRT || FLX_ENV_CRT == FLX_ENV_CRT_UCRT

	i32* __cdecl _errno(void);



	// ===== POSIX CRT ===== //
#else

	i32* __errno_location(void);



#endif
} // extern "C"

namespace flx::crt
{
    inline i32& errno() noexcept
    {
		#if FLX_ENV_CRT == FLX_ENV_CRT_MSVCRT || FLX_ENV_CRT == FLX_ENV_CRT_UCRT
		        return *_errno();
		#else
		        return *__errno_location();
		#endif
    }

	// Win and POSIX have different error codes

		// ===== MSVCRT/UCRT ===== //
	#if FLX_ENV_CRT == FLX_ENV_CRT_MSVCRT || FLX_ENV_CRT == FLX_ENV_CRT_UCRT

		constexpr i32 EPERM				= 1;
		constexpr i32 ENOENT			= 2;
		constexpr i32 ESRCH				= 3;
		constexpr i32 EINTR				= 4;
		constexpr i32 EIO				= 5;
		constexpr i32 ENXIO				= 6;
		constexpr i32 E2BIG				= 7;
		constexpr i32 ENOEXEC			= 8;
		constexpr i32 EBADF				= 9;
		constexpr i32 ECHILD			= 10;
		constexpr i32 EAGAIN			= 11;
		constexpr i32 ENOMEM			= 12;
		constexpr i32 EACCES			= 13;
		constexpr i32 EFAULT			= 14;
		constexpr i32 EBUSY				= 16;
		constexpr i32 EEXIST			= 17;
		constexpr i32 EXDEV				= 18;
		constexpr i32 ENODEV			= 19;
		constexpr i32 ENOTDIR			= 20;
		constexpr i32 EISDIR			= 21;
		constexpr i32 EINVAL			= 22;
		constexpr i32 ENFILE			= 23;
		constexpr i32 EMFILE			= 24;
		constexpr i32 ENOTTY			= 25;
		constexpr i32 EFBIG				= 27;
		constexpr i32 ENOSPC			= 28;
		constexpr i32 ESPIPE			= 29;
		constexpr i32 EROFS				= 30;
		constexpr i32 EMLINK			= 31;
		constexpr i32 EPIPE				= 32;
		constexpr i32 EDOM				= 33;
		constexpr i32 ERANGE			= 34;
		constexpr i32 EDEADLK			= 36;
		constexpr i32 EDEADLOCK			= 36;
		constexpr i32 ENAMETOOLONG		= 38;
		constexpr i32 ENOLCK			= 39;
		constexpr i32 ENOSYS			= 40;
		constexpr i32 ENOTEMPTY			= 41;
		constexpr i32 EILSEQ			= 42;
		constexpr i32 STRUNCATE			= 80;

		// Additional POSIX compatibility constants
		constexpr i32 EADDRINUSE		= 100;
		constexpr i32 EADDRNOTAVAIL		= 101;
		constexpr i32 EAFNOSUPPORT		= 102;
		constexpr i32 EALREADY			= 103;
		constexpr i32 EBADMSG			= 104;
		constexpr i32 ECANCELED			= 105;
		constexpr i32 ECONNABORTED		= 106;
		constexpr i32 ECONNREFUSED		= 107;
		constexpr i32 ECONNRESET		= 108;
		constexpr i32 EDESTADDRREQ		= 109;
		constexpr i32 EHOSTUNREACH		= 110;
		constexpr i32 EIDRM				= 111;
		constexpr i32 EINPROGRESS		= 112;
		constexpr i32 EISCONN			= 113;
		constexpr i32 ELOOP				= 114;
		constexpr i32 EMSGSIZE			= 115;
		constexpr i32 ENETDOWN			= 116;
		constexpr i32 ENETRESET			= 117;
		constexpr i32 ENETUNREACH		= 118;
		constexpr i32 ENOBUFS			= 119;
		constexpr i32 ENODATA			= 120;
		constexpr i32 ENOLINK			= 121;
		constexpr i32 ENOMSG			= 122;
		constexpr i32 ENOPROTOOPT		= 123;
		constexpr i32 ENOSR				= 124;
		constexpr i32 ENOSTR			= 125;
		constexpr i32 ENOTCONN			= 126;
		constexpr i32 ENOTRECOVERABLE	= 127;
		constexpr i32 ENOTSOCK			= 128;
		constexpr i32 ENOTSUP			= 129;
		constexpr i32 EOPNOTSUPP		= 130;
		constexpr i32 EOTHER			= 131;
		constexpr i32 EOVERFLOW			= 132;
		constexpr i32 EOWNERDEAD		= 133;
		constexpr i32 EPROTO			= 134;
		constexpr i32 EPROTONOSUPPORT	= 135;
		constexpr i32 EPROTOTYPE		= 136;
		constexpr i32 ETIME				= 137;
		constexpr i32 ETIMEDOUT			= 138;
		constexpr i32 ETXTBSY			= 139;
		constexpr i32 EWOULDBLOCK		= 140;

		// POSIX error codes missing from Windows
		constexpr i32 ENOTBLK			= 1000;
		constexpr i32 ECHRNG			= 1001;
		constexpr i32 EL2NSYNC			= 1002;
		constexpr i32 EL3HLT			= 1003;
		constexpr i32 EL3RST			= 1004;
		constexpr i32 ELNRNG			= 1005;
		constexpr i32 EUNATCH			= 1006;
		constexpr i32 ENOCSI			= 1007;
		constexpr i32 EL2HLT			= 1008;
		constexpr i32 EBADE				= 1009;
		constexpr i32 EBADR				= 1010;
		constexpr i32 EXFULL			= 1011;
		constexpr i32 ENOANO			= 1012;
		constexpr i32 EBADRQC			= 1013;
		constexpr i32 EBADSLT			= 1014;
		constexpr i32 EBFONT			= 1015;
		constexpr i32 ENONET			= 1016;
		constexpr i32 ENOPKG			= 1017;
		constexpr i32 EREMOTE			= 1018;
		constexpr i32 EADV				= 1019;
		constexpr i32 ESRMNT			= 1020;
		constexpr i32 ECOMM				= 1021;
		constexpr i32 EMULTIHOP			= 1022;
		constexpr i32 EDOTDOT			= 1023;
		constexpr i32 ENOTUNIQ			= 1024;
		constexpr i32 EBADFD			= 1025;
		constexpr i32 EREMCHG			= 1026;
		constexpr i32 ELIBACC			= 1027;
		constexpr i32 ELIBBAD			= 1028;
		constexpr i32 ELIBSCN			= 1029;
		constexpr i32 ELIBMAX			= 1030;
		constexpr i32 ELIBEXEC			= 1031;
		constexpr i32 ERESTART			= 1032;
		constexpr i32 ESTRPIPE			= 1033;
		constexpr i32 EUSERS			= 1034;
		constexpr i32 ESOCKTNOSUPPORT	= 1035;
		constexpr i32 EPFNOSUPPORT		= 1036;
		constexpr i32 ESHUTDOWN			= 1037;
		constexpr i32 ETOOMANYREFS		= 1038;
		constexpr i32 EHOSTDOWN			= 1039;
		constexpr i32 ESTALE			= 1040;
		constexpr i32 EUCLEAN			= 1041;
		constexpr i32 ENOTNAM			= 1042;
		constexpr i32 ENAVAIL			= 1043;
		constexpr i32 EISNAM			= 1044;
		constexpr i32 EREMOTEIO			= 1045;
		constexpr i32 EDQUOT			= 1046;
		constexpr i32 ENOMEDIUM			= 1047;
		constexpr i32 EMEDIUMTYPE		= 1048;
		constexpr i32 ENOKEY			= 1049;
		constexpr i32 EKEYEXPIRED		= 1050;
		constexpr i32 EKEYREVOKED		= 1051;
		constexpr i32 EKEYREJECTED		= 1052;

		// ===== POSIX ===== //
	#else

		constexpr i32 EPERM				= 1;
		constexpr i32 ENOENT			= 2;
		constexpr i32 ESRCH				= 3;
		constexpr i32 EINTR				= 4;
		constexpr i32 EIO				= 5;
		constexpr i32 ENXIO				= 6;
		constexpr i32 E2BIG				= 7;
		constexpr i32 ENOEXEC			= 8;
		constexpr i32 EBADF				= 9;
		constexpr i32 ECHILD			= 10;
		constexpr i32 EAGAIN			= 11;
		constexpr i32 ENOMEM			= 12;
		constexpr i32 EACCES			= 13;
		constexpr i32 EFAULT			= 14;
		constexpr i32 ENOTBLK			= 15;
		constexpr i32 EBUSY				= 16;
		constexpr i32 EEXIST			= 17;
		constexpr i32 EXDEV				= 18;
		constexpr i32 ENODEV			= 19;
		constexpr i32 ENOTDIR			= 20;
		constexpr i32 EISDIR			= 21;
		constexpr i32 EINVAL			= 22;
		constexpr i32 ENFILE			= 23;
		constexpr i32 EMFILE			= 24;
		constexpr i32 ENOTTY			= 25;
		constexpr i32 ETXTBSY			= 26;
		constexpr i32 EFBIG				= 27;
		constexpr i32 ENOSPC			= 28;
		constexpr i32 ESPIPE			= 29;
		constexpr i32 EROFS				= 30;
		constexpr i32 EMLINK			= 31;
		constexpr i32 EPIPE				= 32;
		constexpr i32 EDOM				= 33;
		constexpr i32 ERANGE			= 34;
		constexpr i32 EDEADLK			= 35;
		constexpr i32 ENAMETOOLONG		= 36;
		constexpr i32 ENOLCK			= 37;
		constexpr i32 ENOSYS			= 38;
		constexpr i32 ENOTEMPTY			= 39;
		constexpr i32 ELOOP				= 40;
		constexpr i32 EWOULDBLOCK		= EAGAIN;
		constexpr i32 ENOMSG			= 42;
		constexpr i32 EIDRM				= 43;
		constexpr i32 ECHRNG			= 44;
		constexpr i32 EL2NSYNC			= 45;
		constexpr i32 EL3HLT			= 46;
		constexpr i32 EL3RST			= 47;
		constexpr i32 ELNRNG			= 48;
		constexpr i32 EUNATCH			= 49;
		constexpr i32 ENOCSI			= 50;
		constexpr i32 EL2HLT			= 51;
		constexpr i32 EBADE				= 52;
		constexpr i32 EBADR				= 53;
		constexpr i32 EXFULL			= 54;
		constexpr i32 ENOANO			= 55;
		constexpr i32 EBADRQC			= 56;
		constexpr i32 EBADSLT			= 57;
		constexpr i32 EDEADLOCK			= EDEADLK;
		constexpr i32 EBFONT			= 59;
		constexpr i32 ENOSTR			= 60;
		constexpr i32 ENODATA			= 61;
		constexpr i32 ETIME				= 62;
		constexpr i32 ENOSR				= 63;
		constexpr i32 ENONET			= 64;
		constexpr i32 ENOPKG			= 65;
		constexpr i32 EREMOTE			= 66;
		constexpr i32 ENOLINK			= 67;
		constexpr i32 EADV				= 68;
		constexpr i32 ESRMNT			= 69;
		constexpr i32 ECOMM				= 70;
		constexpr i32 EPROTO			= 71;
		constexpr i32 EMULTIHOP			= 72;
		constexpr i32 EDOTDOT			= 73;
		constexpr i32 EBADMSG			= 74;
		constexpr i32 EOVERFLOW			= 75;
		constexpr i32 ENOTUNIQ			= 76;
		constexpr i32 EBADFD			= 77;
		constexpr i32 EREMCHG			= 78;
		constexpr i32 ELIBACC			= 79;
		constexpr i32 ELIBBAD			= 80;
		constexpr i32 ELIBSCN			= 81;
		constexpr i32 ELIBMAX			= 82;
		constexpr i32 ELIBEXEC			= 83;
		constexpr i32 EILSEQ			= 84;
		constexpr i32 ERESTART			= 85;
		constexpr i32 ESTRPIPE			= 86;
		constexpr i32 EUSERS			= 87;
		constexpr i32 ENOTSOCK			= 88;
		constexpr i32 EDESTADDRREQ		= 89;
		constexpr i32 EMSGSIZE			= 90;
		constexpr i32 EPROTOTYPE		= 91;
		constexpr i32 ENOPROTOOPT		= 92;
		constexpr i32 EPROTONOSUPPORT	= 93;
		constexpr i32 ESOCKTNOSUPPORT	= 94;
		constexpr i32 EOPNOTSUPP		= 95;
		constexpr i32 EPFNOSUPPORT		= 96;
		constexpr i32 EAFNOSUPPORT		= 97;
		constexpr i32 EADDRINUSE		= 98;
		constexpr i32 EADDRNOTAVAIL		= 99;
		constexpr i32 ENETDOWN			= 100;
		constexpr i32 ENETUNREACH		= 101;
		constexpr i32 ENETRESET			= 102;
		constexpr i32 ECONNABORTED		= 103;
		constexpr i32 ECONNRESET		= 104;
		constexpr i32 ENOBUFS			= 105;
		constexpr i32 EISCONN			= 106;
		constexpr i32 ENOTCONN			= 107;
		constexpr i32 ESHUTDOWN			= 108;
		constexpr i32 ETOOMANYREFS		= 109;
		constexpr i32 ETIMEDOUT			= 110;
		constexpr i32 ECONNREFUSED		= 111;
		constexpr i32 EHOSTDOWN			= 112;
		constexpr i32 EHOSTUNREACH		= 113;
		constexpr i32 EALREADY			= 114;
		constexpr i32 EINPROGRESS		= 115;
		constexpr i32 ESTALE			= 116;
		constexpr i32 EUCLEAN			= 117;
		constexpr i32 ENOTNAM			= 118;
		constexpr i32 ENAVAIL			= 119;
		constexpr i32 EISNAM			= 120;
		constexpr i32 EREMOTEIO			= 121;
		constexpr i32 EDQUOT			= 122;
		constexpr i32 ENOMEDIUM			= 123;
		constexpr i32 EMEDIUMTYPE		= 124;
		constexpr i32 ECANCELED			= 125;
		constexpr i32 ENOKEY			= 126;
		constexpr i32 EKEYEXPIRED		= 127;
		constexpr i32 EKEYREVOKED		= 128;
		constexpr i32 EKEYREJECTED		= 129;
		constexpr i32 EOWNERDEAD		= 130;
		constexpr i32 ENOTRECOVERABLE	= 131;

		// Windows error codes missing from POSIX
		constexpr i32 STRUNCATE			= 2000;
		constexpr i32 EDEADLOCK_WIN		= 2001;

	#endif
} // namespace flx::crt

#endif //FLX_INC_CORE_CRT_ISO_C_ERRNO_HPP
