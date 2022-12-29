#ifndef EVENTS_H
#define EVENTS_H

#include "EventSystem.h"
#include <stdint.h>

typedef struct {
  int32_t score;
} ScoreUpdated;

typedef struct {
  char name[512];
} NameChanged;

DECLARE_EVENT(ScoreUpdated);
DECLARE_EVENT(NameChanged);

#endif // !EVENTS_H
