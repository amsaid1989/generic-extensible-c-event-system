# Generic and extensible C event system using macros

This version defines 4 macro functions (defined [here](./EventSystem.h)):

1. `DECLARE_EVENT(TYPE)` -> to be used in a `*.h` file to declare the necessary functions for the provided data type.
2. `DEFINE_EVENT(TYPE)` -> to be used in a `*.c` file to define the functions for the provided data type.
3. `add_event_listener(TYPE)` -> helper macro that calls the type-specific `add_event_listener` function.
4. `emit_event(TYPE)` -> helper macro that calls the type-specific `emit_event` function.

Here are examples of how to use all of them.

First, in a header file (say, `events.h`), add the following:

```c
#ifndef EVENTS_H
#define EVENTS_H

#include "EventSystem.h"

typedef struct {
  int score;
} ScoreUpdated;

DECLARE_EVENT(ScoreUpdated);

#endif // !EVENTS_H
```

Next, in a source file (say, `events.c`), add the following:

```c
#include "events.h"
#include "EventSystem.h"

DEFINE_EVENT(ScoreUpdated);
```

Lastly, in your main file, add the following:

```c
#include "EventSystem.h"
#include "events.h"

void score_updated_listener(ScoreUpdated event) {
  printf("SCORE: %d\n", event.score);
}

int main(int argc, char *argv[]) {
  EventManager manager = {};

  // 1) ADDING AN EVENT LISTENER

  // FUNCTION FORMAT
  add_event_listener_ScoreUpdated(&manager, score_updated_listener);

  // HELPER MACRO FORMAT
  // add_event_listener(ScoreUpdated)(&manager, score_updated_listener);


  // 2) EMITTING AN EVENT

  // FUNCTION FORMAT
  emit_event_ScoreUpdated(&manager, (ScoreUpdated){.score = 50});

  // HELPER MACRO FORMAT
  // emit_event(ScoreUpdated)(&manager, (ScoreUpdated){.score = 50});


  return 0;
}
```
