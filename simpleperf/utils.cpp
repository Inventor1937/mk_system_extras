/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utils.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#include <base/logging.h>

void PrintIndented(size_t indent, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  printf("%*s", static_cast<int>(indent), "");
  vprintf(fmt, ap);
  va_end(ap);
}

bool ReadNBytesFromFile(int fd, void* buf, size_t nbytes) {
  char* p = reinterpret_cast<char*>(buf);
  size_t bytes_left = nbytes;
  while (bytes_left > 0) {
    ssize_t nread = TEMP_FAILURE_RETRY(read(fd, p, bytes_left));
    if (nread <= 0) {
      return false;
    } else {
      p += nread;
      bytes_left -= nread;
    }
  }
  return true;
}