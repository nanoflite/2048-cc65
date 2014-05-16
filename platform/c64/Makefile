SOURCES = ../../main.c ../../utils.c ../../game.c ../../grid.c ../../tile.c ../../array.c ../../introscreen_data.c screen.c map.c map_data.c tiles_data.c chars_data.c attribs_data.c
ASOURCES = characters.s data.s
CC65_TARGET = c64
PROGRAM = 2048.prg

CC      = $(CC65_HOME)/bin/cl65
CFLAGS  = -t $(CC65_TARGET) -g -I../..
LDFLAGS = -t $(CC65_TARGET) -m $(PROGRAM).map -C c64.cfg -Ln $(PROGRAM).lbl -I../..

.PHONY: all clean
all: $(PROGRAM)

ifneq ($(MAKECMDGOALS),clean)
-include $(SOURCES:.c=.d)
endif

%.o: %.s
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(PROGRAM): $(SOURCES:.c=.o) $(ASOURCES:.s=.o)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(ASOURCES:.s=.o) $(SOURCES:.c=.o) $(SOURCES:.c=.d) $(PROGRAM) $(PROGRAM).map $(PROGRAM).lbl

run: $(PROGRAM)
	x64 $(PROGRAM)

assets: 
	xxd -i -c8 assets/attribs.raw >attribs_data.c
	xxd -i -c8 assets/chars.raw >chars_data.c
	xxd -i -c8 assets/map.raw >map_data.c
	xxd -i -c5 assets/tiles.raw >tiles_data.c
	perl -pi -e 's/_raw//g' *_data.c
	./gen_tile_screen_addr > data.s
	python ../../json_to_c.py ../../introscreen.json > ../../introscreen_data.c
