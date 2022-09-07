/*
 * file: src/args.c
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

#include "args.h"

void jcon_help
(
  void
)
{
  printf("  jcon brings reflection (not really) to C, with json\n\n");
  printf("  This is how you should call jcon:\n");
  printf("  jcon -h\n");
  printf("    outputs this helper\n");
  printf("  jcon -i input_file1.c input_file2.c -o output_folder/\n");
  printf("    jcon will lookup for notations and parse json transformers to\n");
  printf("    a new file, which can be imported afterwards in your project.\n");
}

bool jcon_parse_args
(
  int    _argc,
  char **_argv,
  jcon_args *_args
)
{
  _args->needs_helper = false;
  _args->in_file_count = 0;
  int opt;
  while ((opt = getopt(_argc, _argv, JCON_ARG_OPTS)) != -1)
  {
    switch (opt)
    {
      case 'h': {
        _args->needs_helper = true;
      } break;
      case 'i': {
        --optind;
        for (; optind < _argc && *_argv[optind] != '-'; ++optind)
        {
          int filename_s = strlen(_argv[optind]);
          _args->in_files[_args->in_file_count] = malloc(filename_s * sizeof(char));
          strcpy(_args->in_files[_args->in_file_count], _argv[optind]);

          ++_args->in_file_count;
        }
      } break;
      case 'o': {
        int foldername_s = strlen(optarg);
        _args->out_folder = malloc(foldername_s * sizeof(char));
        strcpy(_args->out_folder, optarg);
      } break;
      case '?': {
        _args->needs_helper = true;
       
        return false;
      } break;
      default: {
        _args->needs_helper = true;
       
        return false;
      } break;
    }
  }

  return true;
}
