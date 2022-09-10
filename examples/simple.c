/*
 * file: examples/simple.c
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

#include "simple.h"
#include "simple_jcon_gen.c"

int main
(
  void
)
{
  jcon_example_simple_1 simple1 =
  {
    .j_int = 4,
    .j_float = 43.24f,
    .j_double = 423.932433434f
  };
  char *simple1_json = jcon_jcon_example_simple_1_to_json(&simple1);
  printf("%s\n", simple1_json);

  jcon_example_simple_2 simple2 =
  {
    .j_str = "hello",
    .j_bool = true,
    .j_arr_int = {1, 2, 3},
    .j_arr_float = {1.2f, 2.43f, 3.22f},
    .j_arr_double = {1.24343f, 2.2434234f, 3.3433},
    .j_arr_str = {"hello", "today", "I'll", "do", "something"}
  };
  char *simple2_json = jcon_jcon_example_simple_2_to_json(&simple2);
  printf("%s\n", simple2_json);

  return 0;
}
