/*
 *  include/linux/nfs4.h
 *
 *  NFSv4 protocol definitions.
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *  Andy Adamson   <andros@umich.edu>
 */

#ifndef _LINUX_NFS4_H
#define _LINUX_NFS4_H

#include <linux/types.h>
#include <linux/list.h>

#define NFS4_VERIFIER_SIZE	8
#define NFS4_FHSIZE		128
#define NFS4_MAXPATHLEN		PATH_MAX
#define NFS4_MAXNAMLEN		NAME_MAX

#define NFS4_ACCESS_READ        0x0001
#define NFS4_ACCESS_LOOKUP      0x0002
#define NFS4_ACCESS_MODIFY      0x0004
#define NFS4_ACCESS_EXTEND      0x0008
#define NFS4_ACCESS_DELETE      0x0010
#define NFS4_ACCESS_EXECUTE     0x0020

#define NFS4_FH_PERISTENT		0x0000
#define NFS4_FH_NOEXPIRE_WITH_OPEN	0x0001
#define NFS4_FH_VOLATILE_ANY		0x0002
#define NFS4_FH_VOL_MIGRATION		0x0004
#define NFS4_FH_VOL_RENAME		0x0008

#define NFS4_OPEN_RESULT_CONFIRM 0x0002

#define NFS4_SHARE_ACCESS_READ	0x0001
#define NFS4_SHARE_ACCESS_WRITE	0x0002
#define NFS4_SHARE_ACCESS_BOTH	0x0003
#define NFS4_SHARE_DENY_READ	0x0001
#define NFS4_SHARE_DENY_WRITE	0x0002
#define NFS4_SHARE_DENY_BOTH	0x0003

#define NFS4_SET_TO_SERVER_TIME	0
#define NFS4_SET_TO_CLIENT_TIME	1

#define NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE 0
#define NFS4_ACE_ACCESS_DENIED_ACE_TYPE  1
#define NFS4_ACE_SYSTEM_AUDIT_ACE_TYPE   2
#define NFS4_ACE_SYSTEM_ALARM_ACE_TYPE   3

#define ACL4_SUPPORT_ALLOW_ACL 0x01
#define ACL4_SUPPORT_DENY_ACL  0x02
#define ACL4_SUPPORT_AUDIT_ACL 0x04
#define ACL4_SUPPORT_ALARM_ACL 0x08

#define NFS4_ACE_FILE_INHERIT_ACE             0x00000001
#define NFS4_ACE_DIRECTORY_INHERIT_ACE        0x00000002
#define NFS4_ACE_NO_PROPAGATE_INHERIT_ACE     0x00000004
#define NFS4_ACE_INHERIT_ONLY_ACE             0x00000008
#define NFS4_ACE_SUCCESSFUL_ACCESS_ACE_FLAG   0x00000010
#define NFS4_ACE_FAILED_ACCESS_ACE_FLAG       0x00000020
#define NFS4_ACE_IDENTIFIER_GROUP             0x00000040
#define NFS4_ACE_OWNER                        0x00000080
#define NFS4_ACE_GROUP                        0x00000100
#define NFS4_ACE_EVERYONE                     0x00000200

#define NFS4_ACE_READ_DATA                    0x00000001
#define NFS4_ACE_LIST_DIRECTORY               0x00000001
#define NFS4_ACE_WRITE_DATA                   0x00000002
#define NFS4_ACE_ADD_FILE                     0x00000002
#define NFS4_ACE_APPEND_DATA                  0x00000004
#define NFS4_ACE_ADD_SUBDIRECTORY             0x00000004
#define NFS4_ACE_READ_NAMED_ATTRS             0x00000008
#define NFS4_ACE_WRITE_NAMED_ATTRS            0x00000010
#define NFS4_ACE_EXECUTE                      0x00000020
#define NFS4_ACE_DELETE_CHILD                 0x00000040
#define NFS4_ACE_READ_ATTRIBUTES              0x00000080
#define NFS4_ACE_WRITE_ATTRIBUTES             0x00000100
#define NFS4_ACE_DELETE                       0x00010000
#define NFS4_ACE_READ_ACL                     0x00020000
#define NFS4_ACE_WRITE_ACL                    0x00040000
#define NFS4_ACE_WRITE_OWNER                  0x00080000
#define NFS4_ACE_SYNCHRONIZE                  0x00100000
#define NFS4_ACE_GENERIC_READ                 0x00120081
#define NFS4_ACE_GENERIC_WRITE                0x00160106
#define NFS4_ACE_GENERIC_EXECUTE              0x001200A0
#define NFS4_ACE_MASK_ALL                     0x001F01FF

enum nfs4_acl_whotype {
	NFS4_ACL_WHO_NAMED = 0,
	NFS4_ACL_WHO_OWNER,
	NFS4_ACL_WHO_GROUP,
	NFS4_ACL_WHO_EVERYONE,
};

struct nfs4_ace {
	uint32_t	type;
	uint32_t	flag;
	uint32_t	access_mask;
	int		whotype;
	uid_t		who;
	struct list_head l_ace;
};

struct nfs4_acl {
	uint32_t	naces;
	struct list_head ace_head;
};

typedef struct { char data[NFS4_VERIFIER_SIZE]; } nfs4_verifier;
typedef struct { char data[16]; } nfs4_stateid;

enum nfs_opnum4 {
	OP_ACCESS = 3,
	OP_CLOSE = 4,
	OP_COMMIT = 5,
	OP_CREATE = 6,
	OP_DELEGPURGE = 7,
	OP_DELEGRETURN = 8,
	OP_GETATTR = 9,
	OP_GETFH = 10,
	OP_LINK = 11,
	OP_LOCK = 12,
	OP_LOCKT = 13,
	OP_LOCKU = 14,
	OP_LOOKUP = 15,
	OP_LOOKUPP = 16,
	OP_NVERIFY = 17,
	OP_OPEN = 18,
	OP_OPENATTR = 19,
	OP_OPEN_CONFIRM = 20,
	OP_OPEN_DOWNGRADE = 21,
	OP_PUTFH = 22,
	OP_PUTPUBFH = 23,
	OP_PUTROOTFH = 24,
	OP_READ = 25,
	OP_READDIR = 26,
	OP_READLINK = 27,
	OP_REMOVE = 28,
	OP_RENAME = 29,
	OP_RENEW = 30,
	OP_RESTOREFH = 31,
	OP_SAVEFH = 32,
	OP_SECINFO = 33,
	OP_SETATTR = 34,
	OP_SETCLIENTID = 35,
	OP_SETCLIENTID_CONFIRM = 36,
	OP_VERIFY = 37,
	OP_WRITE = 38,
	OP_RELEASE_LOCKOWNER = 39,
	OP_ILLEGAL = 10044,
};

enum nfsstat4 {
	NFS4_OK = 0,
	NFS4ERR_PERM = 1,
	NFS4ERR_NOENT = 2,
	NFS4ERR_IO = 5,
	NFS4ERR_NXIO = 6,
	NFS4ERR_ACCESS = 13,
	NFS4ERR_EXIST = 17,
	NFS4ERR_XDEV = 18,
	/* Unused/reserved 19 */
	NFS4ERR_NOTDIR = 20,
	NFS4ERR_ISDIR = 21,
	NFS4ERR_INVAL = 22,
	NFS4ERR_FBIG = 27,
	NFS4ERR_NOSPC = 28,
	NFS4ERR_ROFS = 30,
	NFS4ERR_MLINK = 31,
	NFS4ERR_NAMETOOLONG = 63,
	NFS4ERR_NOTEMPTY = 66,
	NFS4ERR_DQUOT = 69,
	NFS4ERR_STALE = 70,
	NFS4ERR_BADHANDLE = 10001,
	NFS4ERR_BAD_COOKIE = 10003,
	NFS4ERR_NOTSUPP = 10004,
	NFS4ERR_TOOSMALL = 10005,
	NFS4ERR_SERVERFAULT = 10006,
	NFS4ERR_BADTYPE = 10007,
	NFS4ERR_DELAY = 10008,
	NFS4ERR_SAME = 10009,
	NFS4ERR_DENIED = 10010,
	NFS4ERR_EXPIRED = 10011,
	NFS4ERR_LOCKED = 10012,
	NFS4ERR_GRACE = 10013,
	NFS4ERR_FHEXPIRED = 10014,
	NFS4ERR_SHARE_DENIED = 10015,
	NFS4ERR_WRONGSEC = 10016,
	NFS4ERR_CLID_INUSE = 10017,
	NFS4ERR_RESOURCE = 10018,
	NFS4ERR_MOVED = 10019,
	NFS4ERR_NOFILEHANDLE = 10020,
	NFS4ERR_MINOR_VERS_MISMATCH = 10021,
	NFS4ERR_STALE_CLIENTID = 10022,
	NFS4ERR_STALE_STATEID = 10023,
	NFS4ERR_OLD_STATEID = 10024,
	NFS4ERR_BAD_STATEID = 10025,
	NFS4ERR_BAD_SEQID = 10026,
	NFS4ERR_NOT_SAME = 10027,
	NFS4ERR_LOCK_RANGE = 10028,
	NFS4ERR_SYMLINK = 10029,
	NFS4ERR_RESTOREFH = 10030,
	NFS4ERR_LEASE_MOVED = 10031,
	NFS4ERR_ATTRNOTSUPP = 10032,
	NFS4ERR_NO_GRACE = 10033,
	NFS4ERR_RECLAIM_BAD = 10034,
	NFS4ERR_RECLAIM_CONFLICT = 10035,
	NFS4ERR_BADXDR = 10036,
	NFS4ERR_LOCKS_HELD = 10037,
	NFS4ERR_OPENMODE = 10038,
	NFS4ERR_BADOWNER = 10039,
	NFS4ERR_BADCHAR = 10040,
	NFS4ERR_BADNAME = 10041,
	NFS4ERR_BAD_RANGE = 10042,
	NFS4ERR_LOCK_NOTSUPP = 10043,
	NFS4ERR_OP_ILLEGAL = 10044,
	NFS4ERR_DEADLOCK = 10045,
	NFS4ERR_FILE_OPEN = 10046,
	NFS4ERR_ADMIN_REVOKED = 10047,
	NFS4ERR_CB_PATH_DOWN = 10048
};

/*
 * Note: NF4BAD is not actually part of the protocol; it is just used
 * internally by nfsd.
 */
enum nfs_ftype4 {
	NF4BAD		= 0,
        NF4REG          = 1,    /* Regular File */
        NF4DIR          = 2,    /* Directory */
        NF4BLK          = 3,    /* Special File - block device */
        NF4CHR          = 4,    /* Special File - character device */
        NF4LNK          = 5,    /* Symbolic Link */
        NF4SOCK         = 6,    /* Special File - socket */
        NF4FIFO         = 7,    /* Special File - fifo */
        NF4ATTRDIR      = 8,    /* Attribute Directory */
        NF4NAMEDATTR    = 9     /* Named Attribute */
};

enum open_claim_type4 {
	NFS4_OPEN_CLAIM_NULL = 0,
	NFS4_OPEN_CLAIM_PREVIOUS = 1,
	NFS4_OPEN_CLAIM_DELEGATE_CUR = 2,
	NFS4_OPEN_CLAIM_DELEGATE_PREV = 3
};

enum opentype4 {
	NFS4_OPEN_NOCREATE = 0,
	NFS4_OPEN_CREATE = 1
};

enum createmode4 {
	NFS4_CREATE_UNCHECKED = 0,
	NFS4_CREATE_GUARDED = 1,
	NFS4_CREATE_EXCLUSIVE = 2
};

enum limit_by4 {
	NFS4_LIMIT_SIZE = 1,
	NFS4_LIMIT_BLOCKS = 2
};

enum open_delegation_type4 {
	NFS4_OPEN_DELEGATE_NONE = 0,
	NFS4_OPEN_DELEGATE_READ = 1,
	NFS4_OPEN_DELEGATE_WRITE = 2
};

enum lock_type4 {
	NFS4_UNLOCK_LT = 0,
	NFS4_READ_LT = 1,
	NFS4_WRITE_LT = 2,
	NFS4_READW_LT = 3,
	NFS4_WRITEW_LT = 4
};


/* Mandatory Attributes */
#define FATTR4_WORD0_SUPPORTED_ATTRS    (1UL << 0)
#define FATTR4_WORD0_TYPE               (1UL << 1)
#define FATTR4_WORD0_FH_EXPIRE_TYPE     (1UL << 2)
#define FATTR4_WORD0_CHANGE             (1UL << 3)
#define FATTR4_WORD0_SIZE               (1UL << 4)
#define FATTR4_WORD0_LINK_SUPPORT       (1UL << 5)
#define FATTR4_WORD0_SYMLINK_SUPPORT    (1UL << 6)
#define FATTR4_WORD0_NAMED_ATTR         (1UL << 7)
#define FATTR4_WORD0_FSID               (1UL << 8)
#define FATTR4_WORD0_UNIQUE_HANDLES     (1UL << 9)
#define FATTR4_WORD0_LEASE_TIME         (1UL << 10)
#define FATTR4_WORD0_RDATTR_ERROR       (1UL << 11)

/* Recommended Attributes */
#define FATTR4_WORD0_ACL                (1UL << 12)
#define FATTR4_WORD0_ACLSUPPORT         (1UL << 13)
#define FATTR4_WORD0_ARCHIVE            (1UL << 14)
#define FATTR4_WORD0_CANSETTIME         (1UL << 15)
#define FATTR4_WORD0_CASE_INSENSITIVE   (1UL << 16)
#define FATTR4_WORD0_CASE_PRESERVING    (1UL << 17)
#define FATTR4_WORD0_CHOWN_RESTRICTED   (1UL << 18)
#define FATTR4_WORD0_FILEHANDLE         (1UL << 19)
#define FATTR4_WORD0_FILEID             (1UL << 20)
#define FATTR4_WORD0_FILES_AVAIL        (1UL << 21)
#define FATTR4_WORD0_FILES_FREE         (1UL << 22)
#define FATTR4_WORD0_FILES_TOTAL        (1UL << 23)
#define FATTR4_WORD0_FS_LOCATIONS       (1UL << 24)
#define FATTR4_WORD0_HIDDEN             (1UL << 25)
#define FATTR4_WORD0_HOMOGENEOUS        (1UL << 26)
#define FATTR4_WORD0_MAXFILESIZE        (1UL << 27)
#define FATTR4_WORD0_MAXLINK            (1UL << 28)
#define FATTR4_WORD0_MAXNAME            (1UL << 29)
#define FATTR4_WORD0_MAXREAD            (1UL << 30)
#define FATTR4_WORD0_MAXWRITE           (1UL << 31)
#define FATTR4_WORD1_MIMETYPE           (1UL << 0)
#define FATTR4_WORD1_MODE               (1UL << 1)
#define FATTR4_WORD1_NO_TRUNC           (1UL << 2)
#define FATTR4_WORD1_NUMLINKS           (1UL << 3)
#define FATTR4_WORD1_OWNER              (1UL << 4)
#define FATTR4_WORD1_OWNER_GROUP        (1UL << 5)
#define FATTR4_WORD1_QUOTA_HARD         (1UL << 6)
#define FATTR4_WORD1_QUOTA_SOFT         (1UL << 7)
#define FATTR4_WORD1_QUOTA_USED         (1UL << 8)
#define FATTR4_WORD1_RAWDEV             (1UL << 9)
#define FATTR4_WORD1_SPACE_AVAIL        (1UL << 10)
#define FATTR4_WORD1_SPACE_FREE         (1UL << 11)
#define FATTR4_WORD1_SPACE_TOTAL        (1UL << 12)
#define FATTR4_WORD1_SPACE_USED         (1UL << 13)
#define FATTR4_WORD1_SYSTEM             (1UL << 14)
#define FATTR4_WORD1_TIME_ACCESS        (1UL << 15)
#define FATTR4_WORD1_TIME_ACCESS_SET    (1UL << 16)
#define FATTR4_WORD1_TIME_BACKUP        (1UL << 17)
#define FATTR4_WORD1_TIME_CREATE        (1UL << 18)
#define FATTR4_WORD1_TIME_DELTA         (1UL << 19)
#define FATTR4_WORD1_TIME_METADATA      (1UL << 20)
#define FATTR4_WORD1_TIME_MODIFY        (1UL << 21)
#define FATTR4_WORD1_TIME_MODIFY_SET    (1UL << 22)
#define FATTR4_WORD1_MOUNTED_ON_FILEID  (1UL << 23)

#define NFSPROC4_NULL 0
#define NFSPROC4_COMPOUND 1
#define NFS4_MINOR_VERSION 0
#define NFS4_DEBUG 1

#ifdef __KERNEL__

/* Index of predefined Linux client operations */

enum {
	NFSPROC4_CLNT_NULL = 0,		/* Unused */
	NFSPROC4_CLNT_READ,
	NFSPROC4_CLNT_WRITE,
	NFSPROC4_CLNT_COMMIT,
	NFSPROC4_CLNT_OPEN,
	NFSPROC4_CLNT_OPEN_CONFIRM,
	NFSPROC4_CLNT_OPEN_NOATTR,
	NFSPROC4_CLNT_OPEN_DOWNGRADE,
	NFSPROC4_CLNT_CLOSE,
	NFSPROC4_CLNT_SETATTR,
	NFSPROC4_CLNT_FSINFO,
	NFSPROC4_CLNT_RENEW,
	NFSPROC4_CLNT_SETCLIENTID,
	NFSPROC4_CLNT_SETCLIENTID_CONFIRM,
	NFSPROC4_CLNT_LOCK,
	NFSPROC4_CLNT_LOCKT,
	NFSPROC4_CLNT_LOCKU,
	NFSPROC4_CLNT_ACCESS,
	NFSPROC4_CLNT_GETATTR,
	NFSPROC4_CLNT_LOOKUP,
	NFSPROC4_CLNT_LOOKUP_ROOT,
	NFSPROC4_CLNT_REMOVE,
	NFSPROC4_CLNT_RENAME,
	NFSPROC4_CLNT_LINK,
	NFSPROC4_CLNT_SYMLINK,
	NFSPROC4_CLNT_CREATE,
	NFSPROC4_CLNT_PATHCONF,
	NFSPROC4_CLNT_STATFS,
	NFSPROC4_CLNT_READLINK,
	NFSPROC4_CLNT_READDIR,
	NFSPROC4_CLNT_SERVER_CAPS,
	NFSPROC4_CLNT_DELEGRETURN,
};

#endif
#endif

/*
 * Local variables:
 *  c-basic-offset: 8
 * End:
 */
