
class CTest1
{
private:	//default for class is private
protected:
public:
	DWORD	id1;
	char*	id2;

	CTest1();
	~CTest1();
};

typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;

typedef struct  _DCB_cd_entry { /* */
        PVOID   DCB_cd_io_address;      // addr of request routine
        ULONG   DCB_cd_flags;           // demand bits - as defined below
        ULONG   DCB_cd_ddb;             // driver's DDB pointer
        ULONG   DCB_cd_next;            // pointer to next cd entry
        USHORT  DCB_cd_expan_off;       // offset of expansion area
        UCHAR   DCB_cd_layer_flags;     // flags for layer's use
        UCHAR   DCB_cd_lgn;             // load group number
} DCB_cd_entry, *pDCB_cd_entry;

/*
** union fields follow
*/



/*
** fields common to physical and logical disk DCB's
*/

typedef struct  _DCB_COMMON { /* */

        ULONG   DCB_physical_dcb;       /* DCB for physical device */
        ULONG   DCB_expansion_length;   /* total length of IOP extension filled */
                                        /* in by IOS (excludes IOP size) */
        /*
         * Link fields follow
         */

        PVOID   DCB_ptr_cd;             /* pointer to calldown list */
        ULONG   DCB_next_dcb;           /* link to next DCB */
        ULONG   DCB_next_logical_dcb;   /* pointer to next logical dcb */
                                        /* for physical device */

        BYTE    DCB_drive_lttr_equiv;   /* drive number (A: = 0, etc.) */
                                        /* set up by iosserv during logical */
                                        /* device associate processing. */

        BYTE    DCB_unit_number;        /* either physical drive number */
                                        /* (sequential drive number or'd */
                                        /* with 80h) or unit number within */
                                        /* tsd. set up by iosbid for disk */
                                        /* physical dcb's. set up by tsdpart*/
                                        /* for disk logical dcb's. set up by*/
                                        /* tsdaer for cdrom physical dcb's. */

        USHORT  DCB_TSD_Flags;          /* Flags for TSD */

        /*
         * Volume Tracking fields follow
         */

        ULONG   DCB_vrp_ptr;            /* pointer to VRP for this DCB */

        ULONG   DCB_dmd_flags;          /* demand bits of the topmost layer */

        ULONG   DCB_device_flags;       /* was BDD_Flags */
        ULONG   DCB_device_flags2;      /* second set of general purpose flags*/

        ULONG   DCB_Partition_Start;    /* partition start sector */

        ULONG   DCB_track_table_ptr;    /* pointer for the track table buffer */
                                        /* for ioctls */

        ULONG   DCB_bds_ptr;            /* DOS BDS corresp. to this DCB */
                                        /* (logical DCB's only) */
        ULONG   DCB_Reserved1;          /* reserved - MBZ */
        //ULONG   DCB_Reserved2;          /* reserved - MBZ */
        ULONG   DCB_pEid;               /* IDE ID block */

        BYTE    DCB_apparent_blk_shift; /* log of apparent_blk_size */
        BYTE    DCB_partition_type;     /* partition type */
        USHORT  DCB_sig;                /* padding and signature */
        BYTE    DCB_device_type;        /* Device Type */
        ULONG   DCB_Exclusive_VM;       /* handle for exclusive access to this device */
        UCHAR   DCB_disk_bpb_flags;     /* bpb flags see defines below */
        UCHAR   DCB_cAssoc;             /* count of logical drives */
                                        /* associated with this logical DCB */
        UCHAR   DCB_Sstor_Host;         /* This field indicates a sstor host volume */

        USHORT DCB_user_drvlet;         /* contains the userdriveletter settings else ff*/
        USHORT DCB_Reserved3;           /* reserved - MBZ */

        //#ifndef OnNow
        //ULONG   DCB_Reserved4;          /* reserved - MBZ */
        //#else OnNow
        BYTE    DCB_fACPI;              /* Are we on ACPI subtree ? */
        BYTE    DCB_fSpinDownIssued;    /* Has a spindown issued ? */
        BYTE    DCB_bPowerState;
        BYTE    DCB_bEidLength;
        //#endif


} DCB_COMMON, *PDCB_COMMON;

/*
** RMM uses DCB_Reserved2 field. This should be mutually exclusive to
** Pmode IDE driver controlled DCB which should never be controlled by RMM.
*/

#define DCB_Reserved2 DCB_pEid


/*
** blockdev compatible fields in physical disk DCB's
*/

typedef struct  _DCB_BLOCKDEV { /* */

        /* The initial set of fields below should not be re-ordered or modified in
         * anyway as the offset and the size of fileds have to match those
         * in BLOCKDEV.H for COMPATIBITLITY!!!
         */

        ULONG   DCB_BDD_Next;
        BYTE    DCB_BDD_BD_Major_Version;       /* INIT <BDD_BD_Major_Ver>                        */
        BYTE    DCB_BDD_BD_Minor_Version;       /* INIT <BDD_BD_Minor_Ver>                        */
        BYTE  DCB_BDD_Device_SubType;
        BYTE  DCB_BDD_Int_13h_Number;
        ULONG DCB_BDD_flags;                                    /* was BDD_Flags                                                  */
        ULONG DCB_BDD_Name_Ptr;
        ULONG   DCB_apparent_sector_cnt[2];/* num. of secs as seen by tsd and above */
        ULONG   DCB_apparent_blk_size;  /* blk size of dev. as seen by tsd and above */
        ULONG   DCB_apparent_head_cnt;  /* num. of heads as seen by tsd and above */
        ULONG DCB_apparent_cyl_cnt;     /* num. of cyls as seen by tsd and above */
        ULONG   DCB_apparent_spt;       /* num. of secs/trk as seen by tsd and above */
        ULONG DCB_BDD_Sync_Cmd_Proc;
        ULONG DCB_BDD_Command_Proc;
        ULONG DCB_BDD_Hw_Int_Proc;              /* INIT <0> */
        ULONG   DCB_BDP_Cmd_Queue_Ascending;
        ULONG   DCB_BDP_Cmd_Queue_Descending;
        ULONG   DCB_BDP_Current_Flags;
        ULONG   DCB_BDP_Int13_Param_Ptr;
        ULONG   DCB_BDP_Current_Command;
        ULONG   DCB_BDP_Current_Position[2];
        ULONG   DCB_BDP_Reserved[5];
        ULONG   DCB_fastdisk_bdd;         /* set for DCBs created when a fastdisk regs */
                                                                             /* with the blockdev BDD for it else 0 */

        /*
         *  End BlockDev compatibility
         */

} DCB_BLOCKDEV, *PDCB_BLOCKDEV;

/*
** define the device control block (dcb) for physical devices (i.e., disks)
*/

typedef struct  _DCB { /* */

        DCB_COMMON      DCB_cmn;

        ULONG   DCB_max_xfer_len;       /* maximum transfer length */

        /*
         *      Actual geometry data follows
         */

        ULONG   DCB_actual_sector_cnt[2];/* number of sectors as seen below  */
                                        /* the tsd.                         */
        ULONG   DCB_actual_blk_size;    /* actual block size of the device  */
                                        /* as seen below the tsd.           */
        ULONG   DCB_actual_head_cnt;    /* number of heads as seen below    */
                                        /* the tsd.                         */
        ULONG   DCB_actual_cyl_cnt;     /* number of cylinders as seen      */
                                        /* below the tsd.                   */
        ULONG     DCB_actual_spt;         /* number of sectors per track as   */
                                        /* seen below the tsd.              */

        PVOID   DCB_next_ddb_dcb;                 /* link to next DCB on DDB chain */

        PVOID     DCB_dev_node;                   /* pointer to dev node for this device */
        BYTE    DCB_bus_type;           /* Type of BUS, see below           */

        BYTE    DCB_bus_number;           /* channel (cable) within adapter   */
        UCHAR   DCB_queue_freeze;  /* queue freeze depth counter */

        UCHAR   DCB_max_sg_elements;    /* max # s/g elements.  set initially */
                                          /* by port, but may be MORE RESTRICTIVELY */
                                                                                           /* updated by other layers */
        UCHAR   DCB_io_pend_count; /* indicates number of requests pending */
                                   /* for this DCB (VOLUME TRACKING LAYER USE ONLY) */
        UCHAR   DCB_lock_count;    /* depth counter for LOCK MEDIA commands */
                                   /* (VOLUME TRACKING LAYER USE ONLY) */
        /*
         * SCSI fields follow
         */

        USHORT  DCB_SCSI_VSD_FLAGS;     /* Flags for SRB builder            */

        BYTE    DCB_scsi_target_id;              /* SCSI target ID */
        BYTE    DCB_scsi_lun;                                           /* SCSI logical unit number         */
        BYTE    DCB_scsi_hba;                    /* adapter number relative to port driver */
        BYTE    DCB_max_sense_data_len; /* Maximum sense Length             */
        USHORT  DCB_srb_ext_size;         /* miniport srb extension length    */

        BYTE    DCB_inquiry_flags[8];   /* Device Inquiry Flags             */
        BYTE    DCB_vendor_id[8];       /* Vendor ID string                 */

        BYTE    DCB_product_id[16];     /* Product ID string                */

        BYTE    DCB_rev_level[4];       /* Product revision level           */

        BYTE    DCB_port_name[8];

        UCHAR   DCB_current_unit;       /* used to emulate multiple logical devices */
                                        /* with a single physical device */
        ULONG   DCB_blocked_iop;        /* pointer to requests for an inactive */
                                          /* volume (VOLUME TRACKING LAYER USE ONLY) */
        ULONG   DCB_vol_unlock_timer;   /* unlock timer handle */
        UCHAR   DCB_access_timer;       /* used to measure time between accesses */
        UCHAR   DCB_Vol_Flags;          /* Flags for Volume Tracking          */
                                        /* volume tracking use only */
        BYTE    DCB_q_algo;             /* queuing algorithm index - see    */
                                        /* values below.                    */

        BYTE    DCB_unit_on_ctl;        /* relative device number on ctlr (0-based) */
        ULONG   DCB_Port_Specific;      /* bytes for PORT DRIVER use        */

        ULONG   DCB_spindown_timer;      /* timer for drive spin down      */

        DCB_BLOCKDEV    DCB_bdd;

} DCB, *PDCB;


/* ASM

;; changing the DCB size will break all precompiled utilities.

.errnz SIZE DCB NE 299

*/


/*
** define the device control block (dcb) for logical disk devices
*/

typedef struct  _LOG_DCB { /* */

        DCB_COMMON      DCB_cmn;

} LOG_DCB, *PLOG_DCB;

/*
** define the device control block (dcb) for disk and cd-rom device types
*/

//
//  NOTE: Any changes in this structure must also be reflected in cfr.h
//

// shk BUGBUG Note that this same structure is used for floppies too...
// see iosbid.asm in inquiry_type_table.
typedef struct  _DCB_disk { /* */

        DCB     DCB_filler_1;           /* standard dcb header              */

        USHORT  DCB_write_precomp;      /* Write Precompensation            */

   ULONG   DCB_disk_tsd_private;   /* private area for tsd.  used to  */
                                                                                                         /* store b: BDS ptr for single flp */
} DCB_disk, *pDCB_disk;

//
// To support Japanese 3mode floppy driver this is defined to add an extra
// field to the end of DCB_disk.
//
//

typedef struct  _DCB_floppy { /* */

        DCB_disk  DCB_filler_3;         /* standard dcb header */

        USHORT  DCB_3mode_Flags;        /* 3mode floppy flag */

} DCB_floppy, *pDCB_floppy;

#define DCB_IS_3MODE_DRIVE      0x0001  /* floppy drive supports 3mode access */
#define DCB_SET_RPM_ON_ACCESS   0x0002  /* set spindle speed on every access */

/*
** DCB_disk_geometry structure access into either the actual or apparent
** DCB geometry fields
*/

typedef struct _DCB_disk_geometry { /* */
        ULONG   sector_cnt[2];/* number of sectors */
        ULONG   blk_size;       /* actual block size of the device  */
                                        /* as seen below the tsd.           */
        ULONG   head_cnt;       /* number of heads as seen below    */
                                        /* the tsd.                         */
        ULONG   cyl_cnt;        /* number of cylinders as seen      */
                                        /* below the tsd.                   */
        ULONG   spt;            /* number of sectors per track as   */
                                        /* seen below the tsd.              */
} DCB_disk_geometry, *pDCB_disk_geometry;

/* ASM

.errnz DCB_apparent_sector_cnt - DCB_apparent_sector_cnt[0] - sector_cnt[0]
.errnz DCB_apparent_blk_size - DCB_apparent_sector_cnt[0] - blk_size
.errnz DCB_apparent_head_cnt - DCB_apparent_sector_cnt[0] - head_cnt
.errnz DCB_apparent_cyl_cnt - DCB_apparent_sector_cnt[0] - cyl_cnt
.errnz DCB_apparent_spt - DCB_apparent_sector_cnt[0] - spt

.errnz DCB_actual_sector_cnt - DCB_actual_sector_cnt[0] - sector_cnt[0]
.errnz DCB_actual_blk_size - DCB_actual_sector_cnt[0] - blk_size
.errnz DCB_actual_head_cnt - DCB_actual_sector_cnt[0] - head_cnt
.errnz DCB_actual_cyl_cnt - DCB_actual_sector_cnt[0] - cyl_cnt
.errnz DCB_actual_spt - DCB_actual_sector_cnt[0] - spt

*/

/*
** DCB_disk_bpb_flags definitions follow
*/

#define DCBF_DISK_BPB_USEFAKE   0x00000001

/*
** maximum size of a Table of Contents for a CDROM
*/

#define CDROM_MAX_TOC 804

/*
** maximum size of a mode sense buffer for CDROM
*/
#define CDROM_MAX_MODE_BUF 20

typedef struct  _DCB_cdrom { /* */

        DCB     DCB_filler_2;           /* standard dcb header                */

        ULONG   DCB_cdrom_Partition_Start;    /* partition start sector      */
        ULONG   DCB_cdrom_Partition_End;      /* partition end sector         */
    UCHAR       DCB_cd_ls_ft;           /* first track number in the last sess*/

        ULONG   DCB_TOC[202];	//[CDROM_MAX_TOC / 4 + 1]; /* cdrom toc buffer           */

/* ASM
        .errnz  (DCB_TOC / 4) * 4 - DCB_TOC
*/

        ULONG   DCB_cd_mode_sense_buf[6];	//[CDROM_MAX_MODE_BUF /4 + 1]; /* cdrom mode */

    UCHAR   DCB_cd_first_session;       /* index number of first session      */
        UCHAR   DCB_cd_last_session;    /* index of last session on disc      */

        ULONG   DCB_play_resume_start;  /* re-start address when paused(LBA)  */
        ULONG   DCB_play_resume_stop;   /* end of re-started play (LBA)       */
        ULONG   DCB_play_status;        /* last command play status           */
        ULONG   DCB_cd_device_flags;    /* flags indicating the audio support
                                          capabilities of the device          */

        UCHAR   DCB_cd_fs_lt;           /* last track in the first session    */
        UCHAR DCB_cd_bobbit_pt; /* indicates the track where a CDPLUS disc is */
                                                                   /* chopped off to prevent data tracks from showing */
                                                                        /* up in the table of contents                              */

        ULONG   DCB_cd_fs_lo;           /* lead out address of first session  */
        ULONG   DCB_cd_last_session_start  ; /* LBA start address of data area in
                                  the last session on a multi-session disc    */

   ULONG   DCB_cd_current_block_size;  /* current block size selected by the
                                                   mode command               */

        UCHAR   DCB_cd_vol_map[8];              /* current volume / channel mapping */
        ULONG   DCB_cd_current_command; /* current command                    */

        ULONG   DCB_cd_queue_head;      /* head of current command queue      */

    UCHAR   DCB_cd_grp1_time[2];    /* group 1 command timeouts        */
    UCHAR   DCB_cd_grp2_time[2];    /* group 2 command timeouts        */

	ULONG	DCB_cd_dvd_copy_flags;  /* dvd copy protection bytes */

} DCB_cdrom, *PDCB_cdrom;

typedef struct type_sdeffsd_req_usage { /* */
   USHORT _IOR_ioctl_drive;
   USHORT _IOR_ioctl_function ;
   ULONG _IOR_ioctl_control_param ;
   ULONG _IOR_ioctl_buffer_ptr;
   ULONG _IOR_ioctl_client_params;
   ULONG _IOR_ioctl_return;
} _type_sdeffsd_req_usage;

typedef union urequestor_usage { /* */
   ULONG  _IOR_requestor_usage[5];

   type_sdeffsd_req_usage sdeffsd_req_usage;
} _urequestor_usage;

typedef  void (* CMDCPLT)(void);

typedef struct _IOR { /* */

      ULONG    IOR_next;	     		/* client link for BCB's 					*/
												/* (MBZ for IORF_VERSION_002) 			*/

      USHORT   IOR_func;	    		/* function to be performed - see   	*/
				       						/* defines below.		   					*/

      USHORT   IOR_status;				/* request status - see defines	   	*/
				       						/* below.			   						*/
      ULONG    IOR_flags;	     		/* request control flags - see	   	*/
				       						/* defines below.		   					*/
      CMDCPLT  IOR_callback;	  		/* address to call request back to if 	*/
												/* IORF_SYNC_COMMAND is not set. 		*/

      ULONG    IOR_start_addr[2];	/* volume relative starting addr 		*/
												/* if IORF_LOGICAL_START_SECTOR is set.*/
												/* physical if not set.						*/

      ULONG    IOR_xfer_count;		/* number of sectors to process if 		*/
												/* IORF_CHAR_COMMAND is not set, or # 	*/
												/* of bytes if it is set.             	*/
												/* MUST be set to zero if no data xfer */

      ULONG    IOR_buffer_ptr;		/* BlockDev client buffer pointer. 		*/
												/* Contains pointer to data buffer 		*/
												/* or to null terminated list of sgd's */
												/* depending on IORF_SCATTER_GATHER 	*/
												/* Undefined if no data transfer     	*/

      ULONG    IOR_private_client;	/* BlockDev/IOS client reserved	  		*/

      ULONG    IOR_private_IOS;    	/* reserved space for IOS	   			*/

      ULONG    IOR_private_port;		/* private area for port driver			*/

      union    urequestor_usage _ureq;
												/* requestor usage area, also used for	*/
												/* IOCTL's										*/

      ULONG    IOR_req_req_handle;	/* requestor provided request	   		*/
				       						/* handle. often is a pointer to    	*/
				       						/* to this ior or its containing    	*/
				       						/* iop. pushed on the stack by IOS   	*/
				       						/* before IOR_callback is called			*/

      ULONG    IOR_req_vol_handle; 	/* requestor provided media handle  	*/
				       						/* designating the media to perform 	*/
				       						/* the function on (VRP).					*/

      ULONG    IOR_sgd_lin_phys; 	/* pointer to first physical sgd, as   */
												/*	contrasted with IOR_buffer_ptr,		*/
												/*	which points to the logical sgds.	*/
				       						/* this is either a linear or phys  	*/
				       						/* address, depending on the needs  	*/
				       						/* of the drivers, as indicated	   	*/
				       						/* via the DCB demand bits.		   	*/

      UCHAR    IOR_num_sgds;	    	/* number of phys sgd's pointed to by  */
												/* IOR_sgd_lin_phys							*/
      UCHAR    IOR_vol_designtr; 	/* numeric representation of the    	*/
				       						/* drive letter designating the	   	*/
				       						/* volume to perform the function   	*/
				       						/* on (c: = 2).				   			*/

      USHORT   IOR_ios_private_1;	/* reserved by IOS to force alignment 	*/

      ULONG    IOR_reserved_2[2];  	/* reserved for internal use 				*/

} IOR, *PIOR;

struct IOP_callback_entry { /* */

	ULONG	IOP_CB_address; 	/* call back address		        */
	ULONG	IOP_CB_ref_data;	/* pointer to callback ref data */

} ;

#define IOP_CALLBACK_TABLE_DEPTH 6
/*
** i/o request packet - offset 0
*/
typedef struct _IOP { /* */

	ULONG	IOP_physical;		/* physical address of IOP.	    */
	ULONG	IOP_physical_dcb;	/* pointer to physical dcb.	    */
	ULONG	IOP_original_dcb;	/* ptr to dcb designated by ior.    */
/*
** offset 20 (hex)
*/
	USHORT	IOP_timer;		/* rcb current timeout value.	    */
	USHORT	IOP_timer_orig;		/* rcb original timeout value.	    */

	ULONG	IOP_calldown_ptr;	/* ptr to next calldown routine.    */
	ULONG	IOP_callback_ptr;	/* ptr to current callback address. */
/*
** offset 30 (hex)
*/
	ULONG	IOP_voltrk_private; /* for use by volume tracking.  BUGBUG BGP- I */
									  /* only need one byte of this, but to maintain */
                             /* alignment it's a dword.							*/


	ULONG	IOP_Thread_Handle;	/* contains the handle of the thread in whose*/
										/* context this IO originated. This is inited*/
										/* in IOS_SendCommand.								*/

	ULONG	IOP_srb;				   /* used by SCSI'izers to pass SRB pointer to */
										/* next layer											*/

	ULONG	IOP_reserved[2];		/* reserved for future use - must be zero */

/*
** offset 44 (hex)
*/
	IOP_callback_entry IOP_callback_table[6];//IOP_CALLBACK_TABLE_DEPTH];	       // RCB_CallBackTable
/*
** offset 74 (hex)
*/

	 BYTE   IOP_format_head;	/* fields for low level format */
	 BYTE   IOP_format_xfer_rate;	
	 USHORT IOP_format_track;
	 ULONG  IOP_format_num_sectors;

	IOR	IOP_ior;			/* i/o request descriptor	    */

} IOP, *pIOP;

