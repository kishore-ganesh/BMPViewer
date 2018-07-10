INP=decoder.cpp
linker=-lSDL2
all: $(INP)
	g++ $(INP) $(linker) 

