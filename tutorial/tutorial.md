# Steganography Tutorial

A small tutorial on how to hide information in bitmap images.

An image normally consists of x times y times 3 bytes.
Classically, the bytes represent the red, green and blue values of the pixel at the x and y coordinate.
Small differences in pixel values can only hardly be seen by the human eye - so it should be easy to hide information there.
The idea of this steganographic file, is to hide a string - a series of bytes - in the lowest bits of the pixels of an image.

I'll walk you step by step through the creation of a software capable of that.

## Prerequisites

First we need to set up our directory structure and install extra libraries.
Set up the directory structure (git init is optional):

```
mkdir stegano
cd stegano
git init
mkdir src
```

We then create a 3rdparty subdirectoy where we put our bmp loading and saving library (if you did not init a new git repo, git clone stb instead).

```
cd src
mkdir 3rdparty
cd 3rdparty
git submodule add https://github.com/nothings/stb.git
```

Perfect! On to the programming!

We go back to our src folder and create a `stegano.cpp` and a `stegano.h` file.
Inside the `stegano.h` we put


```
#ifndef STEGANO_H
#define STEGANO_H

#include <string>

namespace stegano {
bool hide(unsigned char * image, int length, const char * src);
std::string find(const unsigned char * image, int length);
}

#endif
```

We define it as our header file and define our stegano namespace.
In the first step we declare our hiding and finding functions.
`hide` takes the image as an unsigned char array with it's length and the text to embed as another char array and returns a bood that tells us if we were successful.
`find` takes the image as an unsigned char array and it's lenght and returns the embedded message as a C++ string.


## Hiding the data

So, on to the fun part: Implementing the hiding. How will it work?
One character consists of 1 byte = 8 bits. We can split up the byte in 4 parts of 2 bits.
Then we will use four bytes for one character and replace their lowest two bits with the 2 bits of the respective character part.
Once a 0-value-character is embedded, our embedded information is over.

Now we'll create a `stegano.cpp` in the `src` folder:

```
#include "stegano.h"
#include "string.h"
#include <string>

#define CLEAR 0b11111100


#define MASK_1 0b11000000
#define MASK_2 0b00110000
#define MASK_3 0b00001100
#define MASK_4 0b00000011

#define MASK_CONTENT 0b00000011

namespace stegano {
```

We include the necessary string functions as well as our header file.
Next come some definitions:

* `CLEAR` is a bit mask which marks the bits that should be kept int he color as 1, the bits to discard as 0.
* `MASK_1` to `MASK_4` are bit masks that are used to split our char into different parts.
* `MASK_CONTENT` is the oppisite of clear, to access the content.

Then we define our namespace and write our embedding function

```
bool embed(unsigned char * image, int length, const char * text)
{
    int free_chars = length/4;

    int textlen = strlen(text);
    if(free_chars < textlen)
    {
        return false;
    }

    int x, y, pos;
    unsigned char data[4];
    for(int i = 0; i<=textlen; i++)
    {
        data[0] = ( text[i] & MASK_1 ) >> 6;
        data[1] = ( text[i] & MASK_2 ) >> 4;
        data[2] = ( text[i] & MASK_3 ) >> 2;
        data[3] = ( text[i] & MASK_4 );

        for(int off = 0; off < 4; off++)
        {
            pos = off+(i*4);
            image[pos] &= CLEAR;
            image[pos] += data[off];
        }
    }
    return true;
}
```

First we calculate the number of characters we embed.
We need 4 bytes for each character, that means 1 1/3 pixels.
In the next step, we iterate over the characters in the text, and split it into 4 different parts.
We do this by using a logical `and` with the masks we previously defined, and then bit-shift the results.
Once we have our character split up nicely, we embed it in the next 4 bytes. We first calculate our offset from the beginning of the image (number of the character times 4).
Then we clear the lowest two bits of the bytes to 0 with our `CLEAR` mask and add our character parts.

Voila! it's encoded!

## Extracting the Data

Now we have hidden our data - but how do we get it back?
Below you find the extraction function:

```
std::string extract(const unsigned char * image, int length)
{
    std::string returnstring = "";
    unsigned char c;
    int cursor = 0;
    do
    {
        c = '\0';
        c += (image[cursor+0] & MASK_CONTENT) << 6;
        c += (image[cursor+1] & MASK_CONTENT) << 4;
        c += (image[cursor+2] & MASK_CONTENT) << 2;
        c += (image[cursor+3] & MASK_CONTENT);
        if(c != '\0') returnstring.push_back(c);
        cursor+=4;
    }
    while(c != '\0' && cursor < length-4);
    return returnstring;
}
```

We define our string which we want to return (and name it returnstring, how creative) and then iterate through the image bytes.
To get the embedded content of the bytes, we use the `MASK_CONTENT` masks we defined in the beginning - the opposite of the `CLEAR` masks, do you remember?
Then we reverse the bit shift we did when embedding the data and add our different parts back together. If we hit a 0-value-character or the end of the image we stop the traversing and return our returnstring.

## Calling the Functions
