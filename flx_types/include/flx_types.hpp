#ifndef FLX_TYPES_HPP
#define FLX_TYPES_HPP

#ifdef FLX_ALL_MEMBERS_ARE_PUBLIC
	#define flx_public public
	#define flx_protected public
	#define flx_private public
#else
	#define flx_public public
	#define flx_protected protected
	#define flx_private private
#endif // FLX_ALL_MEMBERS_ARE_PUBLIC

namespace flx
{
	using u0	=			void;
	using u00	=			void;

	using b8	=			bool;
	using b08	=			bool;

	using i8	= 			char;
	using i08	=			char;
	using i16	=			short;
	using i32	=			int;
	using i64	=			long long;

	using u8	= unsigned	char;
	using u08	= unsigned	char;
	using u16	= unsigned	short;
	using u32	= unsigned	int;
	using u64	= unsigned	long long;

	using f32	=			float;
	using f64	=			double;
	using f80	=			long double;

	//constexpr flx::u16 operator ""_u16(flx::u64 value) noexcept;

	// made so users can "using" only types
	namespace types
	{
		using u0	=			void;
		using u00	=			void;

		using b8	=			bool;
		using b08	=			bool;

		using i8	=			char;
		using i08	=			char;
		using i16	=			short;
		using i32	=			int;
		using i64	=			long long;

		using u8	= unsigned	char;
		using u08	= unsigned	char;
		using u16	= unsigned	short;
		using u32	= unsigned	int;
		using u64	= unsigned	long long;

		using f32	=			float;
		using f64	=			double;
		using f80	=			long double;
	} // namespace types
} // namespace flx

#endif // !FLX_TYPES_HPP