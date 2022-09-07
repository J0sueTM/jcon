# file: Makefile
# author: Josue Teodoro Moreira <teodoro.josue@protonmail.ch>
# date: 04 September 2022
#
# Copyright (C) 2022 Josue Teodoro Moreira
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.

CC=gcc
CC_FLAGS=-c -Wall -Werror -O3

DIR_BIN=bin
DIR_OBJ=obj
DIR_SRC=src

NAME=jcon
BIN=${DIR_BIN}/${NAME}
SRC=$(shell find ${DIR_SRC} -type f -name "*.c")
OBJ=$(patsubst ${DIR_SRC}/%.c, ${DIR_OBJ}/%.o, ${SRC})

.PHONY: all build setup dirs clean

all: setup ${BIN}

build: setup ${BIN}

setup: dirs
	$(info -- Compiling objects)

${BIN}: ${OBJ}
	$(info -- Building binary)
	${CC} $^ -o $@

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@ mkdir -p $(dir $@)
	${CC} ${CC_FLAGS} $< -o $@

dirs:
	$(info -- Creating dirs)
	mkdir -p ${DIR_BIN}
	mkdir -p ${DIR_OBJ}

clean:
	$(info -- Cleaning)
	@ find ${DIR_BIN} -type f -exec rm -fv {} \;
	@ find ${DIR_OBJ} -type f -exec rm -fv {} \;
