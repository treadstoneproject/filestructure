#ifndef PE__HPP
#define PE__HPP

/*
 * Copyrigth(c) 2007. Victor M. Alvarez  [plusvic@gmail.com].
 * Apache license
 */

#include <stdint.h>
#include <stdlib.h>

#define FILE_DESCRIPTOR  int

typedef uint8_t 	BYTE;
typedef uint16_t	WORD;
typedef uint32_t	DWORD;
typedef	int32_t		LONG;
typedef uint32_t	ULONG;


#define FIELD_OFFSET(type, field)    ((size_t)&(((type *)0)->field))

#ifndef _MAC

#pragma pack(push,4)                   // 4 byte packing is the default

#define IMAGE_DOS_SIGNATURE                 0x5A4D      // MZ
#define IMAGE_OS2_SIGNATURE                 0x454E      // NE
#define IMAGE_OS2_SIGNATURE_LE              0x454C      // LE
#define IMAGE_VXD_SIGNATURE                 0x454C      // LE
#define IMAGE_NT_SIGNATURE                  0x00004550  // PE00

#pragma pack(push,2)                   // 16 bit headers are 2 byte packed

#else

#pragma pack(push,1)

#define IMAGE_DOS_SIGNATURE                 0x4D5A      // MZ
#define IMAGE_OS2_SIGNATURE                 0x4E45      // NE
#define IMAGE_OS2_SIGNATURE_LE              0x4C45      // LE
#define IMAGE_NT_SIGNATURE                  0x50450000  // PE00

#endif


struct IMAGE_DOS_HEADER {      // DOS .EXE header
    WORD   e_magic;                     // Magic number
    WORD   e_cblp;                      // Bytes on last page of file
    WORD   e_cp;                        // Pages in file
    WORD   e_crlc;                      // Relocations
    WORD   e_cparhdr;                   // Size of header in paragraphs
    WORD   e_minalloc;                  // Minimum extra paragraphs needed
    WORD   e_maxalloc;                  // Maximum extra paragraphs needed
    WORD   e_ss;                        // Initial (relative) SS value
    WORD   e_sp;                        // Initial SP value
    WORD   e_csum;                      // Checksum
    WORD   e_ip;                        // Initial IP value
    WORD   e_cs;                        // Initial (relative) CS value
    WORD   e_lfarlc;                    // File address of relocation table
    WORD   e_ovno;                      // Overlay number
    WORD   e_res[4];                    // Reserved words
    WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    WORD   e_oeminfo;                   // OEM information; e_oemid specific
    WORD   e_res2[10];                  // Reserved words
    LONG   e_lfanew;                    // File address of new exe header
};

typedef struct IMAGE_DOS_HEADER *PIMAGE_DOS_HEADER;

#ifndef _MAC
#pragma pack(pop)             	        // Back to 4 byte packing
#endif

//
// File header format.
//

struct IMAGE_FILE_HEADER {
    WORD    Machine;
    WORD    NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    WORD    SizeOfOptionalHeader;
    WORD    Characteristics;
};

typedef struct IMAGE_FILE_HEADER *PIMAGE_FILE_HEADER;

#define IMAGE_SIZEOF_FILE_HEADER             20


#define IMAGE_FILE_RELOCS_STRIPPED           0x0001  // Relocation info stripped from file.
#define IMAGE_FILE_EXECUTABLE_IMAGE          0x0002  // File is executable  (i.e. no unresolved externel references).
#define IMAGE_FILE_LINE_NUMS_STRIPPED        0x0004  // Line nunbers stripped from file.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED       0x0008  // Local symbols stripped from file.
#define IMAGE_FILE_AGGRESIVE_WS_TRIM         0x0010  // Agressively trim working set
#define IMAGE_FILE_LARGE_ADDRESS_AWARE       0x0020  // App can handle >2gb addresses
#define IMAGE_FILE_BYTES_REVERSED_LO         0x0080  // Bytes of machine word are reversed.
#define IMAGE_FILE_32BIT_MACHINE             0x0100  // 32 bit word machine.
#define IMAGE_FILE_DEBUG_STRIPPED            0x0200  // Debugging info stripped from file in .DBG file
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP   0x0400  // If Image is on removable media, copy and run from the swap file.
#define IMAGE_FILE_NET_RUN_FROM_SWAP         0x0800  // If Image is on Net, copy and run from the swap file.
#define IMAGE_FILE_SYSTEM                    0x1000  // System File.
#define IMAGE_FILE_DLL                       0x2000  // File is a DLL.
#define IMAGE_FILE_UP_SYSTEM_ONLY            0x4000  // File should only be run on a UP machine
#define IMAGE_FILE_BYTES_REVERSED_HI         0x8000  // Bytes of machine word are reversed.


#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.

//
// Directory format.
//

struct IMAGE_DATA_DIRECTORY {
    DWORD   VirtualAddress;
    DWORD   Size;
};

typedef struct IMAGE_DATA_DIRECTORY *PIMAGE_DATA_DIRECTORY;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

//
// Optional header format.
//

struct IMAGE_OPTIONAL_HEADER {
    //
    // Standard fields.
    //

    WORD    Magic;
    BYTE    MajorLinkerVersion;
    BYTE    MinorLinkerVersion;
    DWORD   SizeOfCode;
    DWORD   SizeOfInitializedData;
    DWORD   SizeOfUninitializedData;
    DWORD   AddressOfEntryPoint;
    DWORD   BaseOfCode;
    DWORD   BaseOfData;

    //
    // NT additional fields.
    //

    DWORD   ImageBase;
    DWORD   SectionAlignment;
    DWORD   FileAlignment;
    WORD    MajorOperatingSystemVersion;
    WORD    MinorOperatingSystemVersion;
    WORD    MajorImageVersion;
    WORD    MinorImageVersion;
    WORD    MajorSubsystemVersion;
    WORD    MinorSubsystemVersion;
    DWORD   Win32VersionValue;
    DWORD   SizeOfImage;
    DWORD   SizeOfHeaders;
    DWORD   CheckSum;
    WORD    Subsystem;
    WORD    DllCharacteristics;
    DWORD   SizeOfStackReserve;
    DWORD   SizeOfStackCommit;
    DWORD   SizeOfHeapReserve;
    DWORD   SizeOfHeapCommit;
    DWORD   LoaderFlags;
    DWORD   NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
};

typedef struct IMAGE_OPTIONAL_HEADER *PIMAGE_OPTIONAL_HEADER;

#define IMAGE_NT_OPTIONAL_HDR32_MAGIC      0x10b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC      0x20b



struct IMAGE_NT_HEADERS {
    DWORD Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER OptionalHeader;
};

typedef struct IMAGE_NT_HEADERS *PIMAGE_NT_HEADERS;


// IMAGE_FIRST_SECTION doesn't need 32/64 versions since the file header is the same either way.

#define IMAGE_FIRST_SECTION( ntheader ) ((PIMAGE_SECTION_HEADER)        \
    ((BYTE*)ntheader +                                              \
     FIELD_OFFSET( IMAGE_NT_HEADERS, OptionalHeader ) +                 \
     ((PIMAGE_NT_HEADERS)(ntheader))->FileHeader.SizeOfOptionalHeader   \
    ))

// Subsystem Values

#define IMAGE_SUBSYSTEM_UNKNOWN              0   // Unknown subsystem.
#define IMAGE_SUBSYSTEM_NATIVE               1   // Image doesn't require a subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_GUI          2   // Image runs in the Windows GUI subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_CUI          3   // Image runs in the Windows character subsystem.
#define IMAGE_SUBSYSTEM_OS2_CUI              5   // image runs in the OS/2 character subsystem.
#define IMAGE_SUBSYSTEM_POSIX_CUI            7   // image runs in the Posix character subsystem.
#define IMAGE_SUBSYSTEM_NATIVE_WINDOWS       8   // image is a native Win9x driver.

//
// Section header format.
//

#define IMAGE_SIZEOF_SHORT_NAME              8

struct IMAGE_SECTION_HEADER {
    BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
    union {
        DWORD   PhysicalAddress;
        DWORD   VirtualSize;
    } Misc;
    DWORD   VirtualAddress;
    DWORD   SizeOfRawData;
    DWORD   PointerToRawData;
    DWORD   PointerToRelocations;
    DWORD   PointerToLinenumbers;
    WORD    NumberOfRelocations;
    WORD    NumberOfLinenumbers;
    DWORD   Characteristics;
};

typedef struct IMAGE_SECTION_HEADER *PIMAGE_SECTION_HEADER;
#define IMAGE_SIZEOF_SECTION_HEADER          40

#pragma pack(pop)


#include "boost/scoped_array.hpp"

struct MAPPED_FILE_PE {
    FILE_DESCRIPTOR   file;
    size_t            size;
    uint8_t 					*data;
    //unsigned char     *file_name;
    std::string file_name;
    //If scan found infected file.
    std::string file_sig;

    //Support TBB Scanning (Layout of PE file)
    //Position of data. start position of  file.
    uint64_t          start_point;
    //Position of data. end position of file.
    uint64_t					end_point;

    //Pre scanning check layout incorrect or not.
    bool             pass_pre_scanning;
    //Post scanning check binary hex has infected or not.
    bool             pass_post_scanning;
    //Summary status
    uint8_t          status;
    //MD5 of file.
    uint64_t         file_map_md5;
};

struct MAMORY_BLOCK_PE {
    unsigned char *data;
    size_t				 	size;
    size_t					base;
};


//PE Header
struct IMAGE_NT_HEADERS_EXT {
    uint64_t      offset;
    size_t        size;
    uint8_t       *data_offset;
    //contain type
    uint64_t          rva_block;
    size_t            size_block;
    //Section Virtual Address, PointerToRawData.
    DWORD section_rva;
    DWORD section_offset;
};


/** @file */
/** Header for this PE file
  \group_pe */
struct pe_image_file_hdr {
    uint32_t Magic;  /**< PE magic header: PE\\0\\0 */
    uint16_t Machine;/**< CPU this executable runs on, see libclamav/pe.c for possible values */
    uint16_t NumberOfSections;/**< Number of sections in this executable */
    uint32_t TimeDateStamp;   /**< Unreliable */
    uint32_t PointerToSymbolTable;	    /**< debug */
    uint32_t NumberOfSymbols;		    /**< debug */
    uint16_t SizeOfOptionalHeader;	    /**< == 224 */
    uint16_t Characteristics;
};

/** PE data directory header
  \group_pe */
struct pe_image_data_dir {
    uint32_t VirtualAddress;
    uint32_t Size;
};

/** 32-bit PE optional header
  \group_pe */
struct pe_image_optional_hdr32 {
    uint16_t Magic;
    uint8_t  MajorLinkerVersion;		    /**< unreliable */
    uint8_t  MinorLinkerVersion;		    /**< unreliable */
    uint32_t SizeOfCode;			    /**< unreliable */
    uint32_t SizeOfInitializedData;		    /**< unreliable */
    uint32_t SizeOfUninitializedData;		    /**< unreliable */
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint32_t BaseOfData;
    uint32_t ImageBase;				    /**< multiple of 64 KB */
    uint32_t SectionAlignment;			    /**< usually 32 or 4096 */
    uint32_t FileAlignment;			    /**< usually 32 or 512 */
    uint16_t MajorOperatingSystemVersion;	    /**< not used */
    uint16_t MinorOperatingSystemVersion;	    /**< not used */
    uint16_t MajorImageVersion;			    /**< unreliable */
    uint16_t MinorImageVersion;			    /**< unreliable */
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;			    /*< ? */
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;				    /**< NT drivers only */
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint32_t SizeOfStackReserve;
    uint32_t SizeOfStackCommit;
    uint32_t SizeOfHeapReserve;
    uint32_t SizeOfHeapCommit;
    uint32_t LoaderFlags;			    /*< ? */
    uint32_t NumberOfRvaAndSizes;		    /**< unreliable */
    struct pe_image_data_dir DataDirectory[16];
};

/** PE 64-bit optional header
  \group_pe */
struct pe_image_optional_hdr64 {
    uint16_t Magic;
    uint8_t  MajorLinkerVersion;		    /**< unreliable */
    uint8_t  MinorLinkerVersion;		    /**< unreliable */
    uint32_t SizeOfCode;			    /**< unreliable */
    uint32_t SizeOfInitializedData;		    /**< unreliable */
    uint32_t SizeOfUninitializedData;		    /**< unreliable */
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint64_t ImageBase;				    /**< multiple of 64 KB */
    uint32_t SectionAlignment;			    /**< usually 32 or 4096 */
    uint32_t FileAlignment;			    /**< usually 32 or 512 */
    uint16_t MajorOperatingSystemVersion;	    /**< not used */
    uint16_t MinorOperatingSystemVersion;	    /**< not used */
    uint16_t MajorImageVersion;			    /**< unreliable */
    uint16_t MinorImageVersion;			    /**< unreliable */
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;			    /* ? */
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;				    /**< NT drivers only */
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint64_t SizeOfStackReserve;
    uint64_t SizeOfStackCommit;
    uint64_t SizeOfHeapReserve;
    uint64_t SizeOfHeapCommit;
    uint32_t LoaderFlags;			    /* ? */
    uint32_t NumberOfRvaAndSizes;		    /**< unreliable */
    struct pe_image_data_dir DataDirectory[16];
};

/** PE section header
  \group_pe */
struct pe_image_section_hdr {
    uint8_t Name[8];			    /**< may not end with NULL */
    /*
    union {
    uint32_t PhysicalAddress;
    uint32_t VirtualSize;
    } AddrSize;
    */
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;		    /**< multiple of FileAlignment */
    uint32_t PointerToRawData;		    /**< offset to the section's data */
    uint32_t PointerToRelocations;	    /**< object files only */
    uint32_t PointerToLinenumbers;	    /**< object files only */
    uint16_t NumberOfRelocations;	    /**< object files only */
    uint16_t NumberOfLinenumbers;	    /**< object files only */
    uint32_t Characteristics;
};

/** Data for the bytecode PE hook
  \group_pe */
struct cli_pe_hook_data {
    uint32_t offset;
    uint32_t ep; /**< EntryPoint as file offset */
    uint16_t nsections;/**< Number of sections */
    uint16_t dummy; /* align */
    struct pe_image_file_hdr file_hdr;/**< Header for this PE file */
    struct pe_image_optional_hdr32 opt32; /**< 32-bit PE optional header */
    uint32_t dummy2; /* align */
    struct pe_image_optional_hdr64 opt64;/**< 64-bit PE optional header */
    struct pe_image_data_dir dirs[16]; /**< PE data directory header */
    uint32_t e_lfanew;/**< address of new exe header */
    uint32_t overlays;/**< number of overlays */
    int32_t overlays_sz;/**< size of overlays */
    uint32_t hdr_size;/**< internally needed by rawaddr */
};





#endif
