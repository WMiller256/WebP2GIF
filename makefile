# Name of program
MAIN     = webp-gif

ABS      = ./
BIN      = ~/bin
BUILD    = ./build
RM       = /bin/rm -f
MV       = /bin/mv -f
CFLAGS   = -I /usr/lib/boost -I /usr/local/lib/webp -Wno-deprecated-declarations -g -O3 `Magick++-config --cppflags --cxxflags` -std=c++17
CC       = /usr/bin/c++ $(CFLAGS)

LIBS     = -lboost_program_options -lwebp -lwebpdemux -lwebpmux `Magick++-config --libs` -lstdc++fs

LFLAGS   = -Wl,-rpath,/usr/local/lib `Magick++-config --ldflags` -Wno-sign-compare
LIBDIRS  = $(LFLAGS) -L/usr/local/lib -L/usr/lib/boost

# Output coloring
GREEN   = \033[1;32m
CYAN    = \033[36m
BLUE    = \033[1;34m
BRIGHT  = \033[1;37m
WHITE   = \033[0;m
MAGENTA = \033[35m
YELLOW  = \033[33m
RED     = \033[91m

# Source files
OBJS  = $(BUILD)/webp-gif.o

all:
	@printf "[      $(YELLOW)Building $(MAIN)$(WHITE)       ]\n"
	@printf "[$(BLUE)Building$(WHITE)] $(BRIGHT)$(MAIN)$(WHITE) - $(MAGENTA)Program$(WHITE)\n"
	make -f makefile main
	@printf "[$(GREEN) Built  $(WHITE)] $(BRIGHT)$(MAIN)$(WHITE) - $(MAGENTA)Program$(WHITE)\n"
	@printf "[        $(GREEN)Build Complete$(WHITE)        ]\n"
	
$(BUILD)/%.o: %.c++
	@printf "[$(CYAN)Building$(WHITE)]   $(BRIGHT)$<$(WHITE) - $(MAGENTA)Object$(WHITE)\n"
	cd $(ABS); $(CC) -c -o $@ $<
	@printf "[$(GREEN) Built  $(WHITE)]   $(BRIGHT)$<$(WHITE) - $(MAGENTA)Object$(WHITE)\n"

$(MAIN).o:
	@printf "[$(CYAN)Building$(WHITE)]   $(BRIGHT)$<$(WHITE) - $(MAGENTA)Object$(WHITE)\n"
	cd $(ABS); $(CC) -c $(MAIN).c++ -o $(MAIN).o
	@printf "[$(GREEN) Built  $(WHITE)]   $(BRIGHT)$<$(WHITE) - $(MAGENTA)Object$(WHITE)\n"

main: $(OBJS)
	@printf "[$(CYAN)Linking $(WHITE)]   $(BRIGHT)$(MAIN)$(WHITE) - $(MAGENTA)Binary$(WHITE)\n"
	cd $(ABS); $(CC) $(OBJS) $(LIBDIRS) -o $(BIN)/$(MAIN) $(LIBS)
	@printf "[$(GREEN) Linked $(WHITE)]   $(BRIGHT)$(MAIN)$(WHITE) - $(MAGENTA)Binary$(WHITE)\n"

clean:
	$(RM) *.core $(BUILD)/*.o *.d *.stackdump

# Disable command echoing, reenabled with make verbose=1
ifndef verbose
.SILENT:
endif
