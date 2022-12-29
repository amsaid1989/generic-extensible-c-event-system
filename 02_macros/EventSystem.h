#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_EVENTS 1000
#define MAX_LISTENERS 30

typedef void (*EventListener)();

typedef struct {
  char name[512];
  EventListener listeners[MAX_LISTENERS];
  int32_t count;
} Event;

typedef struct {
  Event events[MAX_EVENTS];
  int32_t count;
} EventManager;

#define add_event_listener(TYPE) add_event_listener_##TYPE
#define emit_event(TYPE) emit_event_##TYPE

#define DECLARE_EVENT(TYPE)                                                    \
  void add_event_listener_##TYPE(EventManager *manager,                        \
                                 EventListener listener);                      \
                                                                               \
  void emit_event_##TYPE(const EventManager *manager, TYPE event_data);

#define DEFINE_EVENT(TYPE)                                                     \
  void add_event_listener_##TYPE(EventManager *manager,                        \
                                 EventListener listener) {                     \
    Event *ev = NULL;                                                          \
    const char *name = #TYPE;                                                  \
                                                                               \
    for (size_t i = 0; i < manager->count; ++i) {                              \
      if (strcmp(name, manager->events[i].name) == 0) {                        \
        ev = &(manager->events[i]);                                            \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
                                                                               \
    if (!ev) {                                                                 \
      ev = &(manager->events[(manager->count)++]);                             \
      strcpy(ev->name, name);                                                  \
      ev->count = 0;                                                           \
    }                                                                          \
                                                                               \
    ev->listeners[(ev->count)++] = listener;                                   \
  }                                                                            \
                                                                               \
  void emit_event_##TYPE(const EventManager *manager, TYPE event_data) {       \
    const Event *ev = NULL;                                                    \
    const char *name = #TYPE;                                                  \
                                                                               \
    for (size_t i = 0; i < manager->count; ++i) {                              \
      if (strcmp(name, manager->events[i].name) == 0) {                        \
        ev = &(manager->events[i]);                                            \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
                                                                               \
    if (ev) {                                                                  \
      for (size_t i = 0; i < ev->count; ++i) {                                 \
        EventListener listener = ev->listeners[i];                             \
                                                                               \
        listener(event_data);                                                  \
      }                                                                        \
    }                                                                          \
  }

#endif // !EVENT_SYSTEM_H
