#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_EVENTS 1000
#define MAX_LISTENERS 30
#define INVALID_ID -1

typedef int32_t EventID;

typedef void (*EventListener)(void *event_data);

typedef struct {
  EventListener listeners[MAX_LISTENERS];
  uint32_t count;
} Event;

typedef struct {
  Event events[MAX_EVENTS];
  uint32_t count;
} EventManager;

EventID register_event(EventManager *manager) {
  return manager->count < MAX_EVENTS - 1 ? (manager->count)++ : INVALID_ID;
}

void add_event_listener(EventManager *manager, EventID event_id,
                        EventListener listener) {
  if (event_id < 0 || event_id > MAX_EVENTS || event_id == INVALID_ID) {
    return;
  }

  Event *ev = &(manager->events[event_id]);

  if (ev->count == MAX_LISTENERS) {
    return;
  }

  ev->listeners[(ev->count)++] = listener;
}

void emit_event(const EventManager *manager, EventID event_id,
                void *event_data) {
  if (event_id < 0 || event_id > MAX_EVENTS || event_id == INVALID_ID) {
    return;
  }

  const Event *ev = &(manager->events[event_id]);

  for (size_t i = 0; i < ev->count; ++i) {
    const EventListener listener = ev->listeners[i];

    listener(event_data);
  }
}

typedef struct {
  int32_t score;
} ScoreUpdatedEventData;

typedef struct {
  char name[512];
} NameChangedEventData;

void score_updated_listener(void *event_data) {
  ScoreUpdatedEventData *ev = (ScoreUpdatedEventData *)event_data;

  printf("%d\n", ev->score);
}

void name_changed_listener(void *event_data) {
  NameChangedEventData *ev = (NameChangedEventData *)event_data;

  printf("%s\n", ev->name);
}

int main(int argc, char *argv[]) {
  EventManager manager = {};

  EventID ScoreUpdatedEvent = register_event(&manager);
  EventID NameChangedEvent = register_event(&manager);

  add_event_listener(&manager, ScoreUpdatedEvent, score_updated_listener);
  add_event_listener(&manager, NameChangedEvent, name_changed_listener);

  ScoreUpdatedEventData ev1 = {.score = 200};

  emit_event(&manager, ScoreUpdatedEvent, (void *)&ev1);

  NameChangedEventData ev2 = {};
  strcpy(ev2.name, "Abdelrahman");

  emit_event(&manager, NameChangedEvent, (void *)&ev2);

  return 0;
}
