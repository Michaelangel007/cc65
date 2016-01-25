/*

= A2 Utilities =

a2_make_zero_dsk         - Creates a .DSK image with 143,360 bytes of zeroes
a2_make_empty_doss33_dsk - Creates a non-bootable blank DSK image in DOS 3.3 format
a2_make_empty_prodos_dsk - Creates a non-bootable blank DSK image in ProDOS format
a2_data_dos33_dsk        - Create a non-bootable blank DSK image in DOS 3.3 format
                           Tracks 1 and 2 are free (normally DOS 3.3 would use them)
a2_make_boot_dsk         - Create image of custom boot disk with binary program
a2_raw2dsk               - Write binary file "as-is" plus padding to a .DSK

Example:

   a2_raw2dsk -v -dos33 barebones.boot

*/

// Inc
    #include <stdio.h>
    #include <string.h>

// Macros
    #define VERBOSE if( gbVerbose )

// Types
    typedef unsigned char u8; // so we don't need <stdint.h>

// Consts
    const size_t DSK_SIZE = 35 * 16 * 256;
    const size_t NAME_LEN = 256;

// Globals
    bool gbVerbose = 0;
    bool gbError   = 0;

    size_t gnInputName = 0;
    size_t gnHeader    = 0; // assume we don't have a 4-byte DOS 3.3 header
    size_t gnInputSize = 0;

    char *gpInputName  = NULL;
    char  gaOutputName [ NAME_LEN ];

    u8    gaInputImage [ DSK_SIZE + 4 ]; // +4 if we have 4-byte DOS 3.3 header
    u8    gaOutputImage[ DSK_SIZE ];

// returns pointer to extension 
// returns NULL if couldn't find extension before path seperator '/'
const char* FileNameGetExtension( const size_t len, const char *haystack )
{
    /*
        char  *p  = haystack + len;
        while (p >= haystack)
        {
            if (*p == needle)
                return p;
            p--;
        }
    */
    const char needle = '.';
    for( const char *p = haystack + len - 1; p >= haystack; --p )
        if (*p == needle)
            return p;
        else
            if (*p == '/')
                return NULL;

    return NULL;
}

void init( const char *pFileName )
{
    gpInputName = (char*) pFileName;
    gnInputName = strlen( pFileName );
    memset( gaOutputName , 0, NAME_LEN );

    memset( gaInputImage , 0, DSK_SIZE + 4 );
    memset( gaOutputImage, 0, DSK_SIZE + 0 );
}

void make_ext()
{
    const char *pName = gpInputName;
    size_t      nLen  = gnInputName;
    const char *pExt  = FileNameGetExtension( nLen, pName );

    size_t nPrefix = pExt ? (pExt - pName) : nLen;
    if( pExt )
    {
        VERBOSE printf( "File Name: %s\n", pName );
        VERBOSE printf( "           %*s^ @ %d\n", (int)nPrefix, "", (int)nPrefix );
    }

    strncpy( gaOutputName, pName, nPrefix );
    sprintf( gaOutputName + nPrefix, ".dsk" );
    VERBOSE printf( "Output File Name: %s\n", gaOutputName );
}

void read_input()
{
    FILE * pFile = fopen( gpInputName, "rb" );
    if( !pFile )
    {
        gbError = printf( "ERROR: Couldn't open binary file for reading: %s\n", gpInputName );
        return;
    }

    fseek( pFile, 0, SEEK_END );
    gnInputSize = ftell( pFile );
    fseek( pFile, 0, SEEK_SET );
    VERBOSE printf( "Input Size: %d\n", (int) gnInputSize );
    size_t nMax = DSK_SIZE + gnHeader;
    if (gnInputSize > nMax)
    {
        fclose( pFile );
        gbError = printf( "ERROR: Input binary file is larger then %d bytes\n", (int) nMax );
        return;
    }

    gnInputSize -= gnHeader;
    VERBOSE printf( "Data Size: %d\n", (int) gnInputSize );
    fread( (void*) gaInputImage, 1, gnInputSize, pFile );
    fclose( pFile );
}

void make_output()
{
    memcpy( gaOutputImage, gaInputImage, gnInputSize );
}

void save_output()
{
    FILE *pFile = fopen( gaOutputName, "w+b" );
    if( !pFile )
    {
        gbError = printf( "ERROR: Couldn't open binary file for writing: %s\n", gaOutputName );
        return;
    }

    fwrite( gaOutputImage, 1, DSK_SIZE, pFile );
    fclose( pFile );

    VERBOSE printf( "Saved: %s\n", gaOutputName );
}

int main( const int nArg, const char *aArg[] )
{
    int iArg = 1;

    if (nArg <= 1)
        gbError = 1;
    else
    {
        for( int i = 1; i < nArg; i++ )
        {
            if (aArg[ i ][0] != '-')
                break;

            if (strcmp( aArg[ iArg ], "-dos33") == 0)
            {
                VERBOSE printf( "Skipping 4-byte DOS3.3 header ...\n" );
                iArg++;
                gnHeader = 4; // skip this many bytes
                if (nArg < 2)
                    gbError = 1;
            }
            if (strcmp( aArg[ iArg ], "-v") == 0)
            {
                iArg++;
                gbVerbose = true;
            }
        }
    }

    if( gbError )
        return printf( "Usage: [-dos33] file.bin\nERROR: need a binary file to read from\n" );

    const char *pFileName = aArg[ iArg ];
    init( pFileName );
    make_ext   ();  if( gbError ) return gbError;
    read_input ();  if( gbError ) return gbError;
    make_output();  if( gbError ) return gbError;
    save_output();

    return 0;
}

