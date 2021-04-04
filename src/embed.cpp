#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "3rdparty/stb/stb_image_write.h"
#include "stegano.h"
#include <iostream>
#include <iterator>
#include <string>

int main(int argc, char ** argv) {

    if (argc < 3) {
        std::cout<<"Usage: stegano_embed input.bmp output.bmp"<<std::endl;
        return -1;
    }

    std::istreambuf_iterator<char> begin(std::cin), end;
    std::string data(begin, end);

    int w, h, channels;

    unsigned char * imdata = stbi_load(argv[1], &w, &h, &channels, 0);

    if(!stegano::embed(imdata, w*h*3, data.c_str()))
    {
        std::cout<<"image to small for data!"<<std::endl;
        return -1;
    }

    stbi_write_bmp(argv[2], w, h, channels, imdata);

    return 0;
}
