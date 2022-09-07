/*
 * file: src/logger.c
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

#include "logger.h"

void jcon_log
(
  char *_type,
  char *_msg
)
{
  printf("[%s]: %s.\n", _type, _msg);
}
