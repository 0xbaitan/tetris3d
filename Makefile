########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS = -lGL -lGLU -lGLEW -lglut -lglfw3 -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lassimp


# Makefile settings - Can be customized.
APPNAME = main
EXT = .cc
SRCDIR = src
OBJDIR = obj
DEPDIR = dependencies

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(DEPDIR)/%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
$(DEPDIR)/%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)
