/*
 * file: src/parser.c
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

#include "parser.h"

jcon_parser *jcon_parse_file
(
  char *_file
)
{
  char msg[255];
  sprintf(msg, "Parsing file %s", _file);

  jcon_parser *parser = malloc(sizeof(jcon_parser));
  parser->file = fopen(_file, "r");
  if (parser->file == NULL)
  {
    jcon_log(JCON_ERROR, "Could not open file to read");

    free(parser);
    return NULL;
  }

  fseek(parser->file, 0, SEEK_END);
  parser->file_s = ftell(parser->file);
  fseek(parser->file, 0, SEEK_SET);
  parser->buf = malloc(parser->file_s + 1);
  fread(parser->buf, parser->file_s, 1, parser->file);
  parser->buf_len = strlen(parser->buf);
  fclose(parser->file);

  jcon_parse_objs(parser);

  free(parser->buf);

  return parser;
}

void jcon_parse_objs
(
  jcon_parser *_parser
)
{
  _parser->obj_count = 0;
  char *buf = _parser->buf;

  char comment_b[6];
  int cur_word_b = 0;
  int cur_word_e = 0;
  int cur_word_len = 0;
  char cur_word[255];
  for (int i = 0; i < _parser->buf_len; ++i)
  {
    if (*(buf + i) != '/' || *(buf + i + 1) != '*')
      continue;

    i += 3;
    strncpy(comment_b, (buf + i), 5);
    if (strcmp(comment_b, "@jcon"))
      continue;

    i += 6;
    cur_word_b = i;
    for (; *(buf + i) != ':'; ++i)
      cur_word_e = i;
    cur_word_len = (cur_word_e - cur_word_b + 1);
    strncpy(cur_word, (buf + cur_word_b), cur_word_len);

    int token = jcon_str_to_token(cur_word);
    
    memset(cur_word, '\0', sizeof(cur_word));
    i += 2;
    cur_word_b = i;
    for (; *(buf + i) != '"'; ++i)
      cur_word_e = i;
    cur_word_len = (cur_word_e - cur_word_b + 1);
    strncpy(cur_word, (buf + cur_word_b), cur_word_len);

    jcon_parser_obj *cur_obj = &_parser->objs[_parser->obj_count];
    if (token == JCON_TOKEN_OBJ_MAIN_BEGIN)
    {
      cur_obj->tokens[0] = JCON_TOKEN_OBJ_MAIN_BEGIN;
      cur_obj->token_count = 1;
      sprintf(cur_obj->name, "%s", cur_word);

      if (_parser->obj_count > 0)
      {
        (cur_obj - 1)->tokens[(cur_obj - 1)->token_count] = JCON_TOKEN_OBJ_MAIN_END;
        ++(cur_obj - 1)->token_count;
      }

      cur_obj->prop_count = 0;

      ++_parser->obj_count;
    }
    else
    {
      --cur_obj;
      cur_obj->tokens[cur_obj->token_count] = JCON_TOKEN_PROP;
      sprintf(cur_obj->props[cur_obj->prop_count], "%s", cur_word);

      ++cur_obj->token_count;
      ++cur_obj->prop_count;

      cur_obj->tokens[cur_obj->token_count] = token;
      ++cur_obj->token_count;

      if (token == JCON_TOKEN_ARR_BEGIN)
      {
        cur_obj->tokens[cur_obj->token_count] = JCON_TOKEN_ARR_END;
        ++cur_obj->token_count;
      }
    }

    memset(cur_word, '\0', sizeof(cur_word));
  }

  jcon_parser_obj *lst_obj = &_parser->objs[_parser->obj_count - 1];
  lst_obj->tokens[lst_obj->token_count] = JCON_TOKEN_OBJ_MAIN_END;
  ++lst_obj->token_count;
}

int jcon_str_to_token
(
  char *_type
)
{
  if (!strcmp(_type, "obj_"))
    return JCON_TOKEN_OBJ_MAIN_BEGIN;
  if (!strcmp(_type, "obj"))
    return JCON_TOKEN_OBJ_BEGIN;
  if (!strncmp(_type, "arr", 3))
    return JCON_TOKEN_ARR_BEGIN;
  if (!strcmp(_type, "int"))
    return JCON_TOKEN_INT;
  if (!strcmp(_type, "float"))
    return JCON_TOKEN_FLOAT;
  if (!strcmp(_type, "double"))
    return JCON_TOKEN_DOUBLE;
  if (!strcmp(_type, "str"))
    return JCON_TOKEN_STR;
  if (!strcmp(_type, "bool"))
    return JCON_TOKEN_BOOL;
  
  return JCON_TOKEN_UNDEF;
}

char *jcon_token_to_str
(
  int _token
)
{
  switch (_token)
  {
    case JCON_TOKEN_UNDEF:
      return "undefined";

      break;
    case JCON_TOKEN_NULL:
      return "null";

      break;
    case JCON_TOKEN_OBJ_MAIN_BEGIN:
      return "{";

      break;
    case JCON_TOKEN_OBJ_MAIN_END:
      return "}";

      break;
    case JCON_TOKEN_OBJ_BEGIN:
      return "{";

      break;
    case JCON_TOKEN_OBJ_END:
      return "}";
      
      break;
    case JCON_TOKEN_PROP:
      return "\"prop\"";
      
      break;
    case JCON_TOKEN_ARR_BEGIN:
      return "[";

      break;
    case JCON_TOKEN_ARR_END:
      return "]";

      break;
    case JCON_TOKEN_INT:
      return "0";
   
      break;
    case JCON_TOKEN_FLOAT:
      return "0.0";
   
      break;
    case JCON_TOKEN_DOUBLE:
      return "0.000000";
   
      break;
    case JCON_TOKEN_STR:
      return "\"string\"";
   
      break;
    case JCON_TOKEN_BOOL:
      return "true";
   
      break;
    default:
      return NULL;
      
      break;
  }
}
