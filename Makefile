
all: stegano_embed stegano_extract

stegano_embed: src/embed.cpp src/stegano.cpp
	g++ src/embed.cpp src/stegano.cpp  -o stegano_embed

stegano_extract: src/extract.cpp src/stegano.cpp
	g++ src/extract.cpp src/stegano.cpp  -o stegano_extract
