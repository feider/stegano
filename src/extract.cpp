#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb/stb_image.h"
#include "stegano.h"
#include <iostream>
#include <string>

int main(int argc, char ** argv) {

    if (argc < 2) {
        std::cout<<"Usage: stegano_extract input.bmp"<<std::endl;
        return -1;
    }
    
    int w, h, channels;
    unsigned char * imdata = stbi_load(argv[1], &w, &h, &channels, 0);

    std::cout<<stegano::extract(imdata, w*h*channels);
    std::cout.flush();


    return 0;
}
