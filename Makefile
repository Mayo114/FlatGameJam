
NAME             = Skiving

WNAME            = $(NAME).exe

BIN              = ./bin
LBIN             = $(BIN)/linux/$(NAME)
WBIN             = $(BIN)/windows/$(WNAME)

OBJ_PATH         = ./obj
LOBJ_PATH        = $(OBJ_PATH)/linux
WOBJ_PATH        = $(OBJ_PATH)/windows

SRC_PATH         = ./src

INC              = ./include

SRCS             = main.cpp          \
				   GraphicCore.cpp   \
				   GameCore.cpp      \
				   Timeline.cpp      \
				   Modules/Text.cpp  \
				   BasicExcel.cpp

OBJS             = $(SRCS:.cpp=.o)
LOBJS            = $(addprefix $(LOBJ_PATH)/,$(OBJS))
WOBJS            = $(addprefix $(WOBJ_PATH)/,$(OBJS))

CXXFLAGS         = $(FLAGS) -std=c++0x -O2 -pipe -march=native -I$(INC)
LCXXFLAGS        = $(CXXFLAGS) -I$(INC)/linux
WCXXFLAGS        = $(CXXFLAGS) -I$(INC)/windows

LDFLAGS          =
LLDFLAGS         = $(LDFLAGS) -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -Llib/linux
WLDFLAGS         = $(LDFLAGS) -lsfml-audio-2 -lsfml-graphics-2 -lsfml-system-2 -lsfml-window-2 -Llib/windows -static-libgcc -static-libstdc++

ifeq ($(OS),Windows_NT)
	FixPath      = $(subst /,\,$1)
	RM           = del /Q
	DEFAULT      = windows

	# TODO: complete vars here
	MKDIR        =
	CXX          =
	WINCXX       =
else
	ifeq ($(shell uname), Linux)
		FixPath  = $1
		RM       = rm -rf
		MKDIR    = mkdir -p $$(echo "$@" | sed 's/\/[^\/]*$$//')
		DEFAULT  = linux
		WINCXX   = i686-w64-mingw32-c++
		CXX      = g++
	endif
endif

default: $(DEFAULT)

linux: $(LBIN)

windows: $(WBIN)

all: linux windows

$(LBIN): $(LOBJS)
	@$(MKDIR) $$(echo "$@" | sed 's/\/[^\/]*$$//')
	$(CXX) -o $(LBIN) $(LLDFLAGS) $(LOBJS)

$(WBIN): $(WOBJS)
	@$(MKDIR) $$(echo "$@" | sed 's/\/[^\/]*$$//')
	$(WINCXX) -o $(WBIN) $(WLDFLAGS) $(WOBJS)

$(LOBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@$(MKDIR) $$(echo "$@" | sed 's/\/[^\/]*$$//')
	$(CXX) -o $@ $(LCXXFLAGS) -c $<

$(WOBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@$(MKDIR)
	$(WINCXX) -o $@ $(WCXXFLAGS) -c $<

clean:
	$(RM) obj

fclean: clean
	$(RM) $(LBIN)
	$(RM) $(WBIN)

.PHONY: all default linux windows clean fclean
