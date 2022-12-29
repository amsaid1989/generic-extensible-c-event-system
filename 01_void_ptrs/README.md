# Generic and extensible C event system using void pointers

This version declares 3 functions: `register_event`, `add_event_listener` and `emit_event`.

The first just returns an `EventID` that will be used to identify the event by the `EventManager`.

This ID will be needed for the other two functions.

Here is a quick example for how to use all of them:

```c
typedef struct {
  int32_t score;
} ScoreUpdatedEventData;

void score_updated_listener(void *event_data) {
  ScoreUpdatedEventData *ev = (ScoreUpdatedEventData *)event_data;

  printf("%d\n", ev->score);
}

int main(int argc, char *argv[]) {
  EventManager manager = {};

  EventID ScoreUpdatedEvent = register_event(&manager);

  add_event_listener(&manager, ScoreUpdatedEvent, score_updated_listener);

  ScoreUpdatedEventData ev1 = {.score = 200};

  emit_event(&manager, ScoreUpdatedEvent, (void *)&ev1);

  return 0;
}
```
