#pragma once

//#ifdef __cplusplus
//extern "C" {
//#endif
//
#ifdef _WIN32

#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
//#define inet_ntop InetNtop
#include "heact.h"

#include <windows.h>

#pragma comment(lib,"ws2_32.lib")
#define IPV4_ADDR_ARGS(in6p) (in6p).u.Byte[12], (in6p).u.Byte[13], (in6p).u.Byte[14], (in6p).u.Byte[15]
#define IPV4_ADDR_SET(in6p,val) {(in6p).u.Byte[11]=(in6p).u.Byte[10]=0xff;(in6p).u.Byte[15]=(val)>>24;(in6p).u.Byte[14]=(((val)>>16)&0xff);(in6p).u.Byte[13]=(((val)>>8)&0xff);(in6p).u.Byte[12]=((val)&0xff);}
#pragma comment(lib,"mariadbclient.lib")
#pragma comment(lib,"zlibstatic.lib")
#pragma comment(lib,"Shlwapi.lib")
#ifdef _MSC_VER
extern FILE *_iob;
static inline FILE * __cdecl __iob_func(void)
{
	return _iob;
}
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)

#ifdef __cplusplus

#define VERSIONHELPERAPI inline bool

#else  // __cplusplus

#define VERSIONHELPERAPI FORCEINLINE BOOL

#endif // __cplusplus

	VERSIONHELPERAPI
		IsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)
	{
		OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0,{ 0 }, 0, 0 };
		DWORDLONG        const dwlConditionMask = VerSetConditionMask(
			VerSetConditionMask(
				VerSetConditionMask(
					0, VER_MAJORVERSION, VER_GREATER_EQUAL),
				VER_MINORVERSION, VER_GREATER_EQUAL),
			VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

		osvi.dwMajorVersion = wMajorVersion;
		osvi.dwMinorVersion = wMinorVersion;
		osvi.wServicePackMajor = wServicePackMajor;

		return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
	}

	VERSIONHELPERAPI
		IsWindowsXPOrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0);
	}

	VERSIONHELPERAPI
		IsWindowsXPSP1OrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 1);
	}

	VERSIONHELPERAPI
		IsWindowsXPSP2OrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 2);
	}

	VERSIONHELPERAPI
		IsWindowsXPSP3OrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 3);
	}

	VERSIONHELPERAPI
		IsWindowsVistaOrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0);
	}

	VERSIONHELPERAPI
		IsWindowsVistaSP1OrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 1);
	}

	VERSIONHELPERAPI
		IsWindowsVistaSP2OrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 2);
	}

	VERSIONHELPERAPI
		IsWindows7OrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0);
	}

	VERSIONHELPERAPI
		IsWindows7SP1OrGreater()
	{
		return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 1);
	}


	VERSIONHELPERAPI
		IsWindowsServer()
	{
		OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0,{ 0 }, 0, 0, 0, VER_NT_WORKSTATION };
		DWORDLONG        const dwlConditionMask = VerSetConditionMask(0, VER_PRODUCT_TYPE, VER_EQUAL);

		return !VerifyVersionInfoW(&osvi, VER_PRODUCT_TYPE, dwlConditionMask);
	}

#endif // NTDDI_VERSION

#else

#define IPV4_ADDR_ARGS(in6p) (in6p).s6_addr[12], (in6p).s6_addr[13], (in6p).s6_addr[14], (in6p).s6_addr[15]

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <signal.h>
#include <sys/epoll.h>
#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#include <arpa/inet.h>
	typedef struct sockaddr_in6 SOCKADDR_IN6;
	typedef struct in6_addr IN6_ADDR, *PIN6_ADDR, in_addr6;
	typedef struct sockaddr SOCKADDR;
	inline static void
		IN6_SET_ADDR_UNSPECIFIED(PIN6_ADDR a)
	{
		//
		// We can't use the in6addr_any variable, since that would
		// require existing callers to link with a specific library.
		//
		memset(a->s6_addr, 0, sizeof(IN6_ADDR));
	}

#endif

void he_socket_startup();
void he_socket_cleanup();

SOCKET he_socket_udp_create();
int he_socket_error();
SOCKET he_socket_udp_select(SOCKET socket, long sec, long usec);
int he_socket_udp_listen(SOCKET sockServer, unsigned long ip, unsigned short port);

SOCKET he_socket_tcp_create();
#define  he_socket_tcp_select he_socket_udp_select
int he_socket_tcp_listen(SOCKET sockServer, unsigned long ip, unsigned short port);

//#ifdef __cplusplus
//}
//#endif
