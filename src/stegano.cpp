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

}
