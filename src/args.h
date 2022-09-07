/*
 * file: src/args.h
 * author: Josue Teodoro Moreira <teodoro.josue@protonmail.ch>
 * date: 07 September 2022
 *
 * Copyright (C) 2022 Josue Teodoro Moreira
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef JCON_ARGS_H
#define JCON_ARGS_H

#include "core.h"

#define JCON_ARG_OPTS "hi:o:"
#define JCON_MAX_INPUT_FILES 500

typedef struct jcon_args
{
  int in_file_count;
  char *in_files[JCON_MAX_INPUT_FILES];
  char *out_folder;
  bool needs_helper;
} jcon_args;

void jcon_help
(
  void
);

bool jcon_parse_args
(
  int    _argc,
  char **_argv,
  jcon_args *_args
);

#endif
