
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

SRCS             = main.cpp

OBJS             = $(SRCS:.cpp=.o)
LOBJS            = $(addprefix $(LOBJ_PATH)/,$(OBJS))
WOBJS            = $(addprefix $(WOBJ_PATH)/,$(OBJS))

CFLAGS           = -O2 -pipe -march=native -I$(INC)

LDFLAGS          = -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
LLDFLAGS         = $(LDFLAGS) -Llib/linux
WLDFLAGS         = $(LDFLAGS) -Llib/windows -static-libgcc -static-libstdc++

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

all: windows linux

$(LBIN): $(LOBJS)
	@$(MKDIR) $$(echo "$@" | sed 's/\/[^\/]*$$//')
	$(CXX) -o $(LBIN) $(LLDFLAGS) $(LOBJS)

$(WBIN): $(WOBJS)
	@$(MKDIR) $$(echo "$@" | sed 's/\/[^\/]*$$//')
	$(WINCXX) -o $(WBIN) $(WLDFLAGS) $(WOBJS)

$(LOBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC)
	@$(MKDIR) $$(echo "$@" | sed 's/\/[^\/]*$$//')
	$(CXX) -o $@ $(CXXFLAGS) -c $<

$(WOBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC)
	@$(MKDIR)
	$(WINCXX) -o $@ $(CXXFLAGS) -c $<

clean:
	$(RM) obj

fclean: clean
	$(RM) bin

.PHONY: all default linux windows clean fclean
