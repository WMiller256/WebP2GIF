# Name of program
MAIN     = webp2gif

ABS      = ./
BIN      = ~/bin
BUILD    = ./build
RM       = /bin/rm -f
MV       = /bin/mv -f
CFLAGS   = -isystem /usr/include/opencv4/ -I /usr/lib/boost -I /usr/local/lib/webp -Wno-deprecated-declarations -g -O3 `Magick++-config --cppflags --cxxflags` -std=c++17
CC       = /usr/bin/c++ $(CFLAGS)

LIBS     = -lboost_program_options -lwebp -lwebpdemux -lwebpmux `Magick++-config --ldflags --libs` -lstdc++fs \
           -lopencv_stitching -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired                  \
           -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dpm -lopencv_face                       \
           -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash            \
           -lopencv_line_descriptor -lopencv_quality -lopencv_reg -lopencv_rgbd -lopencv_saliency  \
           -lopencv_stereo -lopencv_structured_light -lopencv_superres                             \
           -lopencv_surface_matching -lopencv_tracking -lopencv_videostab                          \
           -lopencv_xobjdetect -lopencv_xphoto -lopencv_shape -lopencv_datasets -lopencv_plot      \
           -lopencv_text -lopencv_dnn -lopencv_highgui -lopencv_ml -lopencv_phase_unwrapping       \
           -lopencv_optflow -lopencv_ximgproc -lopencv_video -lopencv_videoio -lopencv_imgcodecs   \
           -lopencv_objdetect -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_photo   \
           -lopencv_imgproc -lopencv_core -lavutil -lavcodec -lavformat -lavdevice -lavfilter      \
           -lswscale -lncurses

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
OBJS  = $(BUILD)/webp2gif.o

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
