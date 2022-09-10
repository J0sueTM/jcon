/*
 * file: examples/simple.h
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

#ifndef JCON_EXAMPLES_SIMPLE_H
#define JCON_EXAMPLES_SIMPLE_H

#include <stdbool.h>

/* @jcon obj_:"jcon_example_simple_1" */
typedef struct jcon_example_simple_1
{
  /* @jcon int:"j_int" */
  int j_int;
  /* @jcon float:"j_float" */
  float j_float;
  /* @jcon double:"j_double" */
  double j_double;
} jcon_example_simple_1;

/* @jcon obj_:"jcon_example_simple_2" */
typedef struct jcon_example_simple_2
{
  /* @jcon str:"j_str" */
  char *j_str;
  /* @jcon bool:"j_bool" */
  bool j_bool;
  /* @jcon arr/int:"j_arr_int" */
  int j_arr_int[3];
  /* @jcon arr/float:"j_arr_float" */
  float j_arr_float[3];
  /* @jcon arr/double:"j_arr_double" */
  double j_arr_double[3];
  /* @jcon arr/str:"j_arr_str" */
  char *j_arr_str[5];
} jcon_example_simple_2;

#endif
