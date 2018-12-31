gcodesrc = $(wildcard ./gcode/*.c)
modulesrc = $(wildcard ./module/*.c)
gcoderel = $(patsubst %.c,build/%.rel,$(gcodesrc))
modulerel = $(patsubst %.c,build/%.rel,$(modulesrc))

all: marlin.bin

marlin.bin: build/marlin.ihx

build/marlin.ihx: $(gcoderel) $(modulerel)

build/%.rel: %.c
	sdcc -o $(dir $@) -c $<

clean:
	rm -rf build
	mkdir build
	mkdir build/gcode
	mkdir build/module
