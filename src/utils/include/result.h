#pragma once

#include "error.h"
#include <error.h>
#include <stdbool.h>

typedef struct Result Result;
struct Result {
  bool is_ok;
  union {
    void *data;
    unsigned int uidata;
    int idata;
    Error *error;
  };
};

Result result_ok(void *data);
Result result_error(Error *error);
void *result_unwrap(Result *result);
Error *result_unwrap_error(Result *result);
bool result_is_ok(Result *result);
bool result_is_error(Result *result);

#define OK (result_ok(NULL))