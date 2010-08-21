/*******************************************************************************
*  This is a part of aIm SUITE.Internet                                        *
*                                                                              *
*  Kernel Services public include file with communicaction protocol definitions*
*                                                                              *
*  Do not copy, view or modify this code unless your a member of               *
*  aIm SUITe development team                                                  *
*                                                                              *
*  For licensing information see license.txt in the program root directory     *
*                                                                              *
*  Created 06.01.2003 Maxim A. Orlovsky (maxim_orlovsky@yahoo.com)             *
*                                                                              *
*******************************************************************************/

#ifndef __KSPACKET_INCLUDE_DEFINITIONS__
#define __KSPACKET_INCLUDE_DEFINITIONS__

extern udword kstp_errno;

typedef udword error_t;

struct errordef_st {
	error_t		type;
	char		message[128];
};

extern struct errordef_st kserr_messages[];

#define	KSCMD_HELLO		0x00000000
#define	KSCMD_BYE		0x00000001
#define	KSCMD_LOAD		0x00000002
#define	KSCMD_EXTRACT		0x00000003
#define	KSCMD_LINK		0x00000004
#define	KSCMD_UNLINK		0x00000005
#define	KSCMD_CREATE		0x00000006
#define	KSCMD_DELETE		0x00000007
#define	KSCMD_OPEN		0x00000008
#define	KSCMD_TEMP		0x00000009
#define	KSCMD_CLOSE		0x0000000A
#define	KSCMD_SAVE		0x0000000B


#define	KSERRT_LOGENTRY		0x00000000
#define	KSERRT_WARNING		0x10000000
#define	KSERRT_ERROR		0x20000000
#define	KSERRT_CRITICAL		0x40000000
#define	KSERRT_PANIC		0x80000000

#define	KSERR_STARTED		0x00000001
#define	KSERR_COULDNTSTART	0x80000008
#define	KSERR_SUCCESS		0x00000000
#define	KSERR_NOACCESS		0x20000000
#define	KSERR_SHARECONFLICT	0x20000001
#define	KSERR_NOTHOBJ		0x20000002
#define	KSERR_NOTEXISTS		0x20000003
#define	KSERR_OPENED		0x10000004
#define	KSERR_SOCKET		0x20000005
#define	KSERR_BIND		0x20000006
#define	KSERR_LISTEN		0x20000007
#define	KSERR_OBJOPENED		0x00000009
#define	KSERR_WAITFORCLIENT	0x0000000A
#define	KSERR_CLIENTCONNECTED	0x0000000B
#define	KSERR_CLIENTDISCONN	0x0000000C
#define	KSERR_ACCEPTSOCKET	0x2000000D
#define	KSERR_SOCKRECV		0x2000000E
#define	KSERR_SOCKRECVDATA	0x2000000F
#define	KSERR_ARGCOUNT		0x20000010
#define	KSERR_ARGTYPE		0x20000011
#define	KSERR_NULLPTR		0x20000012
#define	KSERR_NEWCLIENT		0x00000013
#define	KSERR_BYECLIENT		0x00000014
#define	KSERR_UNKNOWNCMD	0x20000015
#define	KSERR_SOCKRECVFMT	0x2000001B
#define	KSERR_SRCFILEOPEN	0x2000001C
#define	KSERR_OBJFILEOPEN	0x2000001D
#define	KSERR_NOTIMPLEMENTED	0x2000001E
#define	KSERR_WRONGSRCPATH	0x20000020
#define	KSERR_WRONGSRCFILE	0x20000021
#define	KSERR_UNKNOWNDOBJF	0x20000022
#define	KSERR_UNKNOWNDOBJT	0x20000023
#define	KSERR_OBJDBINIT		0x20000024
#define	KSERR_OBJDBCONN		0x20000025
#define	KSERR_MAXCLIENTS	0x20000026
#define	KSERR_SQL		0x20000027
#define	KSERR_OPFAILED		0x20000028
#define	KSERR_OBJEXISTS		0x2000002D
#define	KSERR_OBJHASPARENTS	0x2000002E
#define	KSERR_OBJNOTPARENT	0x2000002F
#define	KSERR_QUOT		0x20000030

#define	KSERR_NOCLIENT		0x2000002E
#define	KSERR_QUOTAEXC		0x2000002D
#define	KSERR_NOTOWNER		0x20000019
#define	KSERR_CLIENTKEY		0x2000002F

#define	KSERR_OUTOFMEM		0x40000017
#define	KSERR_NOTKSMEM		0x40000018
#define	KSERR_MEMINT		0x4000001A
#define	KSERR_MEMTAILNOTNULL	0x40000029
#define	KSERR_MEMZEROSIZE	0x1000002A
#define	KSERR_MEMSTAMP1		0x4000002B
#define	KSERR_MEMSTAMP2		0x4000002C


#define	KSTPERR_SOCKRECV	0x2000000E
#define	KSTPERR_SOCKRECVDATA	0x2000000F
#define	KSTPERR_ARGCOUNT	0x20000010
#define	KSTPERR_ARGTYPE		0x20000011
#define	KSTPERR_NULLPTR		0x20000012
#define	KSTPERR_OUTOFMEM	0x20000017
#define	KSTPERR_SOCKRECVFMT	0x2000001B

struct packet_st;
typedef struct packet_st packet;

struct packet_st {
	ubyte		key[64];
	udword		cmd;
	uvar32_64	argc;
	ubyte*		argt;
	void**		argv;
};

bool	kstp_allocate (packet* data, uvar32_64 argno);
void	kstp_release (packet* data);
bool	kstp_send (SOCKET s, packet* data);
bool	kstp_recv (SOCKET s, packet* data);
bool	kstp_get_string (packet* data, uvar32_64 argno, string* val);
bool	kstp_get_int (packet* data, uvar32_64 argno, sdword* val);
bool	kstp_get_real (packet* data, uvar32_64 argno, rtbyte* val);
bool	kstp_set_string (packet* data, uvar32_64 argno, string val);
bool	kstp_set_int (packet* data, uvar32_64 argno, sdword val);
bool	kstp_set_real (packet* data, uvar32_64 argno, rtbyte val);
char*	kstp_msg (error_t err);

#endif /* __KSPACKET_INCLUDE_DEFINITIONS__ */