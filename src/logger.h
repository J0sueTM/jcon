/*
 * file: src/logger.h
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

#ifndef LOGGER_H
#define LOGGER_H

#include "core.h"

#define JCON_INFO    "INFO"
#define JCON_WARNING "WARNING"
#define JCON_ERROR   "ERROR"

void jcon_log
(
  char *_type,
  char *_msg
);

#endif
