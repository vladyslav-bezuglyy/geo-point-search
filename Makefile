.PHONY: build

CC = g++
CFLAGS = -std=c++11 -Wall
CFLAGS_SHARED = -shared -fPIC 

NAME = sample
BINARY_NAME = $(NAME)
LIBRARY_NAME = lib$(NAME).so

SRC_MAIN = Sample.cpp

SRC_SHARED = EarthGrid.cpp \
             RandomPointGenerator.cpp \
             GeoObjects.cpp

SRC = $(SRC_SHARED) $(SRC_MAIN)

build:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(BINARY_NAME)

shared:
	$(CC) $(SRC_SHARED) $(CFLAGS) $(CFLAGS_SHARED) $(LDFLAGS) -o $(LIBRARY_NAME)

shared_binary: shared
	$(CC) $(SRC_MAIN) $(LDFLAGS) -L. -l$(NAME) -o $(BINARY_NAME)

clean:
	rm -rf $(BINARY_NAME)
	rm -rf $(LIBRARY_NAME)

