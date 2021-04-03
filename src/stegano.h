#ifndef STEGANO
#define STEGANO

#include <string>

namespace stegano {
bool hide(unsigned char * image, int length, const char * src);
std::string find(const unsigned char * image, int length);
}

#endif
