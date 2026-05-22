#ifndef FLX_INC_CORE_CRT_HPP
#define FLX_INC_CORE_CRT_HPP

// This is a compatibility layer between FLX and CRT.
// It is needed since Windows' CRT does not follow POSIX.
// FLX will link against the C Standard Library and POSIX, where UCRT is missing, FLX will do its best to substitute with its implementations.



// ===== ISO C Headers ===== //
// https://cppreference.com/c/header

#include "flx/core/crt/iso_c/core_crt_iso_c_assert.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_complex.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_ctype.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_errno.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_fenv.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_float.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_inttypes.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_iso646.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_limits.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_locale.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_math.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_setjmp.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_signal.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdalign.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdarg.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdatomic.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdbit.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdbool.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdckdint.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stddef.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdint.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdio.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdlib.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_stdnoreturn.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_string.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_tgmath.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_threads.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_time.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_uchar.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_wchar.hpp"
#include "flx/core/crt/iso_c/core_crt_iso_c_wctype.hpp"



// ===== POSIX Headers ===== //
// https://pubs.opengroup.org/onlinepubs/9699919799/idx/head.html
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/crt-alphabetical-function-reference?view=msvc-170

#include "flx/core/crt/posix/core_crt_posix_aio.hpp"
#include "flx/core/crt/posix/core_crt_posix_arpa_inet.hpp"
#include "flx/core/crt/posix/core_crt_posix_cpio.hpp"
#include "flx/core/crt/posix/core_crt_posix_dirent.hpp"
#include "flx/core/crt/posix/core_crt_posix_dlfcn.hpp"
#include "flx/core/crt/posix/core_crt_posix_endian.hpp"
#include "flx/core/crt/posix/core_crt_posix_fcntl.hpp"
#include "flx/core/crt/posix/core_crt_posix_fmtmsg.hpp"
#include "flx/core/crt/posix/core_crt_posix_fnmatch.hpp"
#include "flx/core/crt/posix/core_crt_posix_ftw.hpp"
#include "flx/core/crt/posix/core_crt_posix_glob.hpp"
#include "flx/core/crt/posix/core_crt_posix_grp.hpp"
#include "flx/core/crt/posix/core_crt_posix_iconv.hpp"
#include "flx/core/crt/posix/core_crt_posix_langinfo.hpp"
#include "flx/core/crt/posix/core_crt_posix_libgen.hpp"
#include "flx/core/crt/posix/core_crt_posix_libintl.hpp"
#include "flx/core/crt/posix/core_crt_posix_monetary.hpp"
#include "flx/core/crt/posix/core_crt_posix_mqueue.hpp"
#include "flx/core/crt/posix/core_crt_posix_ndbm.hpp"
#include "flx/core/crt/posix/core_crt_posix_net_if.hpp"
#include "flx/core/crt/posix/core_crt_posix_netdb.hpp"
#include "flx/core/crt/posix/core_crt_posix_netinet_in.hpp"
#include "flx/core/crt/posix/core_crt_posix_netinet_tcp.hpp"
#include "flx/core/crt/posix/core_crt_posix_nl_types.hpp"
#include "flx/core/crt/posix/core_crt_posix_poll.hpp"
#include "flx/core/crt/posix/core_crt_posix_pthread.hpp"
#include "flx/core/crt/posix/core_crt_posix_pwd.hpp"
#include "flx/core/crt/posix/core_crt_posix_regex.hpp"
#include "flx/core/crt/posix/core_crt_posix_sched.hpp"
#include "flx/core/crt/posix/core_crt_posix_search.hpp"
#include "flx/core/crt/posix/core_crt_posix_semaphore.hpp"
#include "flx/core/crt/posix/core_crt_posix_spawn.hpp"
#include "flx/core/crt/posix/core_crt_posix_strings.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_ipc.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_mman.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_msg.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_resource.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_select.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_sem.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_shm.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_socket.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_stat.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_statvfs.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_time.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_times.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_types.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_uio.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_un.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_utsname.hpp"
#include "flx/core/crt/posix/core_crt_posix_sys_wait.hpp"
#include "flx/core/crt/posix/core_crt_posix_syslog.hpp"
#include "flx/core/crt/posix/core_crt_posix_tar.hpp"
#include "flx/core/crt/posix/core_crt_posix_termios.hpp"
#include "flx/core/crt/posix/core_crt_posix_time.hpp"
#include "flx/core/crt/posix/core_crt_posix_unistd.hpp"
#include "flx/core/crt/posix/core_crt_posix_utmpx.hpp"
#include "flx/core/crt/posix/core_crt_posix_wordexp.hpp"



#endif //FLX_INC_CORE_CRT_HPP