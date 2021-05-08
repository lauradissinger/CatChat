CC     = g++
CFLAGS = -std=c++11

CatChat: catchat.cpp
	${CC} ${CFLAGS} $^ -o $@
