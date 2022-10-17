SOURCES=SillyBalls.c
RFILES=SillyBalls.r Size.r
EXECUTABLE=SillyBalls
CREATOR='SILB'

LDFLAGS=-w -c $(CREATOR) -t APPL \
	-sn STDIO=Main -sn INTENV=Main -sn %A5Init=Main

LIBRARIES={Libraries}Stubs.o \
	{Libraries}MacRuntime.o \
	{Libraries}IntEnv.o \
	{Libraries}Interface.o \
	{Libraries}ToolLibs.o \
	{CLibraries}StdCLib.o

TOOLBOXFLAGS=-d OLDROUTINENAMES=1 -typecheck relaxed

OBJECTS=$(SOURCES:%.c=build/obj/%.o)

all: prepass build/$(EXECUTABLE)

prepass:
	mkdir -p build build/obj

build/$(EXECUTABLE): $(OBJECTS)
	mpw link $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@
	mpw rez -rd $(RFILES) -o $@ -i "{RINCLUDES}" -append

build/obj/%.o : %.c
	mpw sc $(TOOLBOXFLAGS) $< -o $@

clean:
	rm -rf build/obj build
