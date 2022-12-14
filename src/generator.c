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

  gen->in_f = _file;
  gen->parser = _parser;
  int folder_len = strlen(_folder);
  if (_folder[folder_len - 1] == '/')
    _folder[folder_len - 1] = '\0';

  char *in_fbase = basename(_file);
  int in_fbase_len = strlen(in_fbase);
  in_fbase[in_fbase_len - 2] = '\0';
  gen->in_fbase = in_fbase;

  char out_fname[258];
  sprintf(out_fname, "%s/%s_jcon_gen.c", _folder, in_fbase);

  char msg[310];
  sprintf(msg, "Generating file %s", out_fname);
  jcon_log(JCON_INFO, msg);
  
  gen->out_f = fopen(out_fname, "w");
  if (!gen->out_f)
  {
    jcon_log(JCON_ERROR, "Could not open file to write");

    free(gen);
    return NULL;
  }

  jcon_generate_header(gen);
  jcon_generate_to_json(gen);
  fprintf(gen->out_f, "\n#endif\n");

  fclose(gen->out_f);

  return gen;
}

void jcon_generate_header
(
  jcon_generator *_gen
)
{
  fprintf(_gen->out_f, "/*\n * WARNING: This is a generated file\n *\n");
  fprintf(_gen->out_f, " * Generated by jcon | Josue Teodoro Moreira | GPL3\n");
  fprintf(_gen->out_f, " * More info: https://github.com/J0sueTM/jcon\n");
  fprintf(_gen->out_f, " */\n\n");

  /* Programmer's job to include source files' folder on compiler args when compiling */
  fprintf(_gen->out_f, "#ifndef JCON_%s_GENERATED\n#define JCON_%s_GENERATED\n\n", _gen->in_fbase, _gen->in_fbase);
  fprintf(_gen->out_f, "#include \"%s.h\"\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\n", _gen->in_fbase);
  fprintf(_gen->out_f, "static char out_json[10000];\n");
  fprintf(_gen->out_f, "\n#define JSON_POS out_json + strlen(out_json)\n\n");
}

void jcon_generate_to_json
(
  jcon_generator *_gen
)
{
  jcon_parser *parser = _gen->parser;
  for (int i = 0; i < parser->obj_count; ++i)
  {
    fprintf(_gen->out_f, "char *jcon_%s_to_json\n(\n  %s *_obj\n)\n{\n", parser->objs[i].name, parser->objs[i].name);

    fprintf(_gen->out_f, "  memset(out_json, '\\0', 10000 * sizeof(char));\n");
    int prop_i = 0;
    jcon_parser_obj *cur_obj = &parser->objs[i];
    for (int j = 0; j < cur_obj->token_count; ++j)
    {
      if (cur_obj->tokens[j] == JCON_TOKEN_PROP)
      {
        char *prop = cur_obj->props[prop_i];
        fprintf(_gen->out_f, "  sprintf(JSON_POS, \"\\\"%s\\\": \");\n", prop);
        ++prop_i;
      }
      else if (cur_obj->tokens[j] < JCON_TOKEN_INT)
      {
        char *tok_str = jcon_token_to_str(cur_obj->tokens[j]);
        fprintf(_gen->out_f, "  sprintf(JSON_POS, \"%s\");\n", tok_str);

        char *prop = cur_obj->props[prop_i - 1];
        switch (cur_obj->tokens[j])
        {
          case JCON_TOKEN_OBJ_MAIN_BEGIN:
            fprintf(_gen->out_f, "  sprintf(JSON_POS, \"\\n\");\n");
   
            break;
          case JCON_TOKEN_ARR_END:
            fprintf(_gen->out_f, "  sprintf(JSON_POS, \",\\n\");\n");

            break;
          default:
            if (cur_obj->tokens[j] >= JCON_TOKEN_ARR_BEGIN_INT &&
                cur_obj->tokens[j] <= JCON_TOKEN_ARR_BEGIN_OBJ)
            {
              fprintf(_gen->out_f, "  sprintf(JSON_POS, \"\\n\");\n");
              fprintf(_gen->out_f, "  for (int i = 0; i < (int)(sizeof(_obj->%s) / sizeof(_obj->%s[0])); ++i)\n  {\n", prop, prop);
              switch (cur_obj->tokens[j])
              {
              case JCON_TOKEN_ARR_BEGIN_INT:
                fprintf(_gen->out_f, "    sprintf(JSON_POS, \"%%d,\\n\", _obj->%s[i]);\n", prop);

                break;
              case JCON_TOKEN_ARR_BEGIN_FLOAT:
                fprintf(_gen->out_f, "    sprintf(JSON_POS, \"%%f,\\n\", _obj->%s[i]);\n", prop);

                break;
              case JCON_TOKEN_ARR_BEGIN_DOUBLE:
                fprintf(_gen->out_f, "    sprintf(JSON_POS, \"%%lf,\\n\", _obj->%s[i]);\n", prop);

                break;
              case JCON_TOKEN_ARR_BEGIN_STR:
                fprintf(_gen->out_f, "    sprintf(JSON_POS, \"\\\"%%s\\\",\\n\", _obj->%s[i]);\n", prop);

                break;
              case JCON_TOKEN_ARR_BEGIN_BOOL:
                fprintf(_gen->out_f, "    sprintf(JSON_POS, \"%%s,\\n\", _obj->%s[i]);\n", prop);

                break;
              case JCON_TOKEN_ARR_BEGIN_OBJ:
                /* TODO */

                break;
              default:
                fprintf(_gen->out_f, "    sprintf(JSON_POS, \"%%d,\\n\", _obj->%s[i]);\n", prop);

                break;
              }
              fprintf(_gen->out_f, "  }\n");
            }
            else
            {
              fprintf(_gen->out_f, "\n");
            }
            
            break;
        }
      }
      else
      {
        char *prop = cur_obj->props[prop_i - 1];
        switch (cur_obj->tokens[j])
        {
          case JCON_TOKEN_INT:
            fprintf(_gen->out_f, "  sprintf(JSON_POS, \"%%d\", _obj->%s);\n", prop);
            
            break;
          case JCON_TOKEN_FLOAT:
            fprintf(_gen->out_f, "  sprintf(JSON_POS, \"%%f\", _obj->%s);\n", prop);
            
            break;
          case JCON_TOKEN_DOUBLE:
            fprintf(_gen->out_f, "  sprintf(JSON_POS, \"%%lf\", _obj->%s);\n", prop);

            break;
          case JCON_TOKEN_STR:
            fprintf(_gen->out_f, "  sprintf(JSON_POS, \"\\\"%%s\\\"\", _obj->%s);\n", prop);
            
            break;
          case JCON_TOKEN_BOOL:
            fprintf(_gen->out_f, "  sprintf(JSON_POS, \"%%s\", (_obj->%s) ? \"true\" : \"false\");\n", prop);
            
            break;
          default:
            fprintf(_gen->out_f, "  sprintf(JSON_POS, \"undefined\");\n");
            
            break;
        }
        
        fprintf(_gen->out_f, "  sprintf(JSON_POS, \",\\n\");\n");
      }
    }
    
    fprintf(_gen->out_f, "  return out_json;\n}\n");
    if (i < parser->obj_count - 1)
      fprintf(_gen->out_f, "\n");
  }
}
