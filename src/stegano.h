#ifndef STEGANO_H
#define STEGANO_H

#include <string>

namespace stegano {
bool embed(unsigned char * image, int length, const char * src);
std::string extract(const unsigned char * image, int length);
}

#endif
