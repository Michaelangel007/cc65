/*

Problem:

Getting a binary image onto a .DSK image requires

- A bootable DOS 3.3 .DSK image
- some third party utility to copy the binary onto the DOS 3.3 .DSK image

The problem is that legally you aren't allowed to distribute
this bootable DOS 3.3 .DSK image.

The solution is to provide our own bootable disk that doesn't use DOS 3.3
but instead has a small custom boot loader that is able to our binary
stored on disk into memory.

   $8FC: binary start address low  byte
   $8FD: binary start address high byte
   $8FE: binary length low  byte
   $8FF: binary length high byte

```assembly
    .org $800
    .byte $01  ; one sector to load

```

.3 but is able to load "x" pages
off the disk starting at T1,S0

Instead, we make bootable disk with out DOS that directly
load the binary file into memory utilizing a small boot loader.

= Utilities =

a2_make_zero_dsk         - Creates a .DSK image with 143,360 bytes of zeroes
a2_make_empty_doss33_dsk - Creates a non-bootable blank DSK image in DOS 3.3 format
a2_make_empty_prodos_dsk - Creates a non-bootable blank DSK image in ProDOS format
a2_data_dos33_dsk        - Create a non-bootable blank DSK image in DOS 3.3 format
                           Tracks 1 and 2 are free (normally DOS 3.3 would use them)
a2_make_boot_dsk         - Create image of custom boot disk with binary program
a2_raw2dsk               - Write binary file "as-is" plus padding to a .DSK

make_binary_dsk
make_custom_dsk
make_dos33_dsk

*/

int main()
{
}
