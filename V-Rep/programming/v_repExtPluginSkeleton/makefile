CFLAGS = -I../include -Wall -fPIC -static

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	CFLAGS += -D__linux
	EXT = so
else
	CFLAGS += -D__APPLE__
	EXT = dylib
endif

all: 
	@rm -f lib/*.$(EXT)
	@rm -f *.o 
	g++ $(CFLAGS) -c v_repExtPluginSkeleton.cpp -o v_repExtPluginSkeleton.o
	g++ $(CFLAGS) -c ../common/luaFunctionData.cpp -o luaFunctionData.o
	g++ $(CFLAGS) -c ../common/luaFunctionDataItem.cpp -o luaFunctionDataItem.o
	g++ $(CFLAGS) -c ../common/v_repLib.cpp -o v_repLib.o
	@mkdir -p lib
	g++ luaFunctionData.o luaFunctionDataItem.o v_repExtPluginSkeleton.o v_repLib.o -o lib/libv_repExtPluginSkeleton.$(EXT) -lpthread -ldl -shared 

