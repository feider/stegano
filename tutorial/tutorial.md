# Steganography Tutorial

A small tutorial on how to hide information in bitmap images.

An image normally consists of x times y times 3 bytes.
Classically, the bytes represent the red, green and blue values of the pixel at the x and y coordinate.
Small differences in pixel values can only hardly be seen by the human eye - so it should be easy to hide information there.
The idea of this steganographic file, is to hide a string - a series of bytes - in the lowest bits of the pixels of an image.

I'll walk you step by step through the creation of a software capable of that.

## Prerequisites

First we need to set up our directory structure and install extra libraries.
Set up the directory structure:

```
mkdir stegano
cd stegano
mkdir src
```

We then create a 3rdparty subdirectoy where we put our bmp loading and saving library.

```
cd src
mkdir 3rdparty
cd 3rdparty
git submodule add https://github.com/aburgh/EasyBMP.git
```

Perfect! On to the programming!

We go back to our src folder and create a `stegano.bmp` and a `stegano.h` file.
Inside the `stegano.h` we put

```
#ifndef STEGANO
#define STEGANO

#include "3rdparty/EasyBMP/EasyBMP.h"

bool encrypt(BMP &bmp, const char * src);
std::string decrypt(BMP & bmp);

#endif
```

## Hiding the data

So, on to the fun part: Implementing the hiding. How will it work?
One character consists of 1 byte = 8 bits. We can split up the byte in 4 parts of 2 bits. Then we will use two pixels for one character - red and green contain 2 parts of the byte in the 2 lowest bits, blue contains a 0 in the lowest bit to inform us, that there still is encrypted text. To mark the end of our hidden data data, second blue pixel of the last character will contain a 1 in the lowest bit.

Now we'll create a `stegano.cpp` in the `src` folder:

```
#include "stegano.h"
#include "string.h"

#define CLEAR 0b11111100
#define GOING 0b11111110
#define END   0b00000001

#define MASK_1 0b11000000
#define MASK_2 0b00110000
#define MASK_3 0b00001100
#define MASK_4 0b00000011

namespace stegano {

bool hide(BMP & bmp, const char * text)
{
    int free_chars = bmp.TellWidth() * bmp.TellHeight();
    free_chars /= 2; // two pixels are needed for one char
    unsigned int sx = bmp.TellWidth();
    if(free_chars < strlen(text))
    {
        return false;
    }

    for(int i = 0; text[i]!='\0'; i++)
    {
    }
    return true;
}

std::string sfind(BMP & bmp)
{
    return "";
}

}

```

