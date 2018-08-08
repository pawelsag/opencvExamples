
CC = g++ 

INC_PATHS = \
-I/usr/local/include 

LIB_PATHS = \
-L/usr/local/lib/ \
-L/usr/lib/

LIB_FLAGS = -lstdc++ -lopencv_highgui -lopencv_core  -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_video -lopencv_videostab

all:
	$(CC) example2.cpp $(LIB_FLAGS) $(INC_PATHS) $(LIB_PATHS) -o example2

