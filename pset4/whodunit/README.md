# Questions

## What's `stdint.h`?

a header file with int types of exact widths

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

to use an int of the exact width you need

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

424d, 3810

## What's the difference between `bfSize` and `biSize`?

biSize is the size in bytes of the BITMAPINFOHEADER, bfSize is the size in bytes of the bitmap file.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The file being opened doesn't exist, or couldn't be created.

## Why is the third argument to `fread` always `1` in our code?

The code only reads the size of RGBTRIPLE one at a time

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

move the cursor

## What is `SEEK_CUR`?

The curent position of the cursor
