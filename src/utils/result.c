#include "include/result.h"
#include <error.h>
#include <stddef.h>

Result result_ok(void *data) {
  Result result;
  result.is_ok = true;
  result.data = data;
  return result;
};
Result result_error(Error *error) {
  Result result;
  result.is_ok = false;
  result.error = error;
  return result;
};
void *result_unwrap(Result *result) {
  if (result->is_ok) {
    return result->data;
  } else {
    return NULL;
  }
};
Error *result_unwrap_error(Result *result) {
  if (!result->is_ok) {
    return result->error;
  } else {
    return NULL;
  }
};
bool result_is_ok(Result *result) { return result->is_ok; };
bool result_is_error(Result *result) { return !result->is_ok; };
