/*
 * file: src/parser.h
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

#ifndef JCON_PARSER_H
#define JCON_PARSER_H

#include "core.h"
#include "logger.h"

#define JCON_TOKEN_UNDEF            0
#define JCON_TOKEN_NULL             1
#define JCON_TOKEN_OBJ_MAIN_BEGIN   2
#define JCON_TOKEN_OBJ_MAIN_END     3
#define JCON_TOKEN_OBJ_BEGIN        4
#define JCON_TOKEN_OBJ_END          5
#define JCON_TOKEN_PROP             6
#define JCON_TOKEN_ARR_BEGIN_INT    7
#define JCON_TOKEN_ARR_BEGIN_FLOAT  8
#define JCON_TOKEN_ARR_BEGIN_DOUBLE 9
#define JCON_TOKEN_ARR_BEGIN_STR    10
#define JCON_TOKEN_ARR_BEGIN_BOOL   11
#define JCON_TOKEN_ARR_BEGIN_OBJ    12
#define JCON_TOKEN_ARR_END          13
#define JCON_TOKEN_INT              14
#define JCON_TOKEN_FLOAT            15
#define JCON_TOKEN_DOUBLE           16
#define JCON_TOKEN_STR              17
#define JCON_TOKEN_BOOL             18

#define JCON_MAX_TOKENS 5000
#define JCON_MAX_OBJS   50
#define JCON_MAX_PROPS  500
#define JCON_MAX_PROP_S 255

typedef struct jcon_parser_obj
{
  char name[255];
  int token_count;
  int tokens[JCON_MAX_TOKENS];
  int prop_count;
  char props[JCON_MAX_PROPS][JCON_MAX_PROP_S];
} jcon_parser_obj;

typedef struct jcon_parser
{
  FILE *file;
  long file_s;
  int buf_len;
  char *buf;

  int obj_count;
  jcon_parser_obj objs[JCON_MAX_OBJS];
} jcon_parser;

jcon_parser *jcon_parse_file
(
  char *_file
);

void jcon_parse_objs
(
  jcon_parser *_parser
);

int jcon_str_to_token
(
  char *_str
);

char *jcon_token_to_str
(
  int _token
);

#endif
