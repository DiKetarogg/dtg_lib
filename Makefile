#* ************************************************************************** *#
#*                                                                            *#
#*                                    :::::::         :::          :::::::    *#
#*   Makefile                       :+:    :+:       :+:         :+:    :+:   *#
#*                                 +:+      +:+     +:+         +:+           *#
#*                                +#+       +#+  +#+#+#+       +#+            *#
#*                               +#+       +#+    +#+         +#+   #+#+#+    *#
#*   dtg_lib                    #+#      #+#     #+#    #+    #+#     +#+     *#
#*                             ##########         ######       ########       *#
#*                                                                            *#
#* ************************************************************************** *#
#*
all: $(TARGET)
#*
#* ************************************************************************** *#
#*                             Executable name                                *#
#* ************************************************************************** *#
#*
TARGET_NAME		=test_lib
DEBUG_TARGET_NAME	=deb_test_lib
#*
#* ************************************************************************** *#
#*                             Directories                                    *#
#* ************************************************************************** *#
#*
OBJS_DIR	=Objects
SRCS_DIR	=Sources
TARGET_DIR	=bin
INCLUDE_DIR	=Includes
DEBUG_DIR	=bin
#*
#* ************************************************************************** *#
#*                             Compilation variables                          *#
#* ************************************************************************** *#
#*
SRCS_EXT	=.cpp
OBJS_EXT	=.o
HEADER_EXT	=.hpp
CC		=g++ --std=c++14
CFLAGS		=-Wextra -Wall -Werror -Wno-parentheses #-Wno-error=parentheses
DEBUG_FLAGS	=-g3
DEBUG_PROGRAM	=gdb
#*
#* ************************************************************************** *#
#*                              Additional commands                           *#
#* ************************************************************************** *#
#*
ADDPHONY=
#*
#* ************************************************************************** *#
#*                             Do not edit below                              *#
#* ************************************************************************** *#
#*

SRCS = $(shell find $(SRCS_DIR) -type f -name *$(SRCS_EXT))
OBJS = $(patsubst $(SRCS_DIR)/%,$(OBJS_DIR)/%,$(SRCS:$(SRCS_EXT)=$(OBJS_EXT)))
DIRS = $(SRCS_DIR) $(TARGET_DIR) #$(OBJS_DIR)

INCLUDES	= $(addprefix -I,$(sort $(dir $(shell find $(SRCS_DIR) -type f -name *$(HEADER_EXT)))))\
			-I$(INCLUDE_DIR)

TARGET		= $(TARGET_DIR)/$(TARGET_NAME)

DEBUG_TARGET	= $(DEBUG_DIR)/$(DEBUG_TARGET_NAME)

DIRS = $(OBJS_DIR) $(SRCS_DIR) $(TARGET_DIR) $(INCLUDE_DIR)


debug: $(DEBUG_TARGET)

de: debug

drun: debug
	$(DEBUG_PROGRAM) $(DEBUG_DIR)/$(DEBUG_TARGET_NAME)

$(TARGET): $(DIRS) ${OBJS}
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)
$(DEBUG_TARGET): $(DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDES) $(SRCS) -o $(DEBUG_TARGET)
	
$(OBJS_DIR)/%$(OBJS_EXT): $(SRCS_DIR)/%$(SRCS_EXT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

clean:
	rm -f ${OBJS}

clear_console:
	clear
	clear

cl: clear_console all

fclean: clean
	rm -f ${NAME}
re: fclean all

remake: re

run: ${TARGET}
	./$(TARGET)
rerun: re run
test:
	@echo '	SRCS: $(SRCS)'
	@echo '	OBJS: $(OBJS)'
	@echo '	INCLUDES: $(INCLUDES)'
.PHONY: all clean cl clear_console fclean re remake debug de drun rerun run $(ADDPHONY)
