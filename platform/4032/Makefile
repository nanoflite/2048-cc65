SOURCES = ../../main.c ../../utils.c ../../game.c ../../grid.c ../../tile.c ../../array.c ../../introscreen_data.c screen.c numbers.c header_data.c
ASOURCES =
CC65_TARGET = pet
PROGRAM = 2048.prg

CC      = $(CC65_HOME)/bin/cl65
CFLAGS  = -t $(CC65_TARGET) -g -I../..
LDFLAGS = -t $(CC65_TARGET) -m $(PROGRAM).map -Ln $(PROGRAM).lbl -I../..

.PHONY: all clean assets
all: assets $(PROGRAM)

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

run: all
	xpet -model 4032 $(PROGRAM)

assets:
	python ../../json_to_c.py pet header ./assets/header.json > header_data.c
	python ../../json_to_c.py pet introscreen ../../assets/introscreen.json > ../../introscreen_data.c
