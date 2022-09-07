/*
 * file: src/main.h
 * author: Josue Teodoro Moreira <teodoro.josue@protonmail.ch>
 * date: 04 September 2022
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

#include "core.h"
#include "logger.h"
#include "args.h"
#include "parser.h"
#include "generator.h"

int main
(
  int    _argc,
  char **_argv
)
{
  jcon_args args;
  bool are_args_ok = jcon_parse_args(_argc, _argv, &args);
  if (!are_args_ok)
  {
    jcon_log(JCON_ERROR, "Could not parse args");

    return 1;
  }
  if (args.needs_helper)
    jcon_help();

  jcon_parser *cur_parser;
  jcon_generator *cur_gen;
  for (int i = 0; i < args.in_file_count; ++i)
  {
    cur_parser = jcon_parse_file(args.in_files[i]);
    if (!cur_parser)
    {
      char warning[255];
      sprintf(warning, "Could not parse input file %s", args.in_files[i]);
      jcon_log(JCON_WARNING, warning);

      goto skip_file;
    }

    cur_gen = jcon_generate_files(cur_parser, args.in_files[i], args.out_folder);
    if (!cur_gen)
    {
      char err[255];
      sprintf(err, "Could not generate output from file %s", args.in_files[i]);
      jcon_log(JCON_ERROR, err);

      goto skip_file;
    }

    /*
    for (int i = 0; i < cur_parser->obj_count; ++i)
    {
      int prop_i = 0;
      jcon_parser_obj *cur_obj = &cur_parser->objs[i];
      printf("%s -> %d\n", cur_obj->name, cur_obj->token_count);
      for (int j = 0; j < cur_obj->token_count; ++j)
      {
        if (cur_obj->tokens[j] == JCON_TOKEN_PROP)
        {
          printf("\"%s\":\n", cur_obj->props[prop_i]);
          ++prop_i;
        }
        else
          printf("%s\n", jcon_token_to_str(cur_obj->tokens[j]));
      }
      printf("\n");
    }
    */

  skip_file:
    free(cur_parser);
  }

  return 0;
}
