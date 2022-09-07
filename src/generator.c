/*
 * file: src/generator.c
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

#include "generator.h"

jcon_generator *jcon_generate_files
(
  jcon_parser *_parser,
  char        *_file,
  char        *_folder
)
{
  jcon_generator *gen = malloc(sizeof(jcon_generator));
  if (!gen)
    return NULL;

  gen->parser = _parser;
  int folder_len = strlen(_folder);
  if (_folder[folder_len - 1] == '/')
    _folder[folder_len - 1] = '\0';

  char in_fbase[255];
  char *in_fbase_ext = basename(_file);
  int in_fbase_len = strlen(basename(_file)) - 2;
  strncpy(in_fbase, in_fbase_ext, in_fbase_len);

  char out_fname[258];
  sprintf(out_fname, "%s/%s.c", _folder, in_fbase);

  char msg[310];
  memset(msg, '\0', sizeof(msg));
  sprintf(msg, "Generating file %s", out_fname);
  jcon_log(JCON_INFO, msg);
  
  gen->out_f = fopen(out_fname, "w");
  if (!gen->out_f)
  {
    jcon_log(JCON_ERROR, "Could not open file to write");

    free(gen);
    return NULL;
  }

  fclose(gen->out_f);

  return gen;
}
