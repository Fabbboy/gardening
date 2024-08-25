#include "include/error.h"
#include <stdlib.h>

Error *error_create(const char *message) {
  Error *error = malloc(sizeof(Error));
  error->message = message;
  return error;
};
void error_destroy(Error *error) { free(error); };
