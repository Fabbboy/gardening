#pragma once

typedef struct Error Error;
struct Error {
  const char *message;
};

Error* error_create(const char *message);
void error_destroy(Error *error);
