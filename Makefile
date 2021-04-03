
all: shide sfind

shide: src/hide.cpp src/stegano.cpp
	g++ src/hide.cpp src/stegano.cpp  -o shide

sfind: src/find.cpp src/stegano.cpp
	g++ src/find.cpp src/stegano.cpp  -o sfind
