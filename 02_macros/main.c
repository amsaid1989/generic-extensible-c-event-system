#include "EventSystem.h"
#include "events.h"

void score_updated_listener(ScoreUpdated event) {
  printf("SCORE: %d\n", event.score);
}

void name_changed_listener(NameChanged event) {
  printf("NAME: %s\n", event.name);
}

int main(int argc, char *argv[]) {
  EventManager manager = {};

  add_event_listener_ScoreUpdated(&manager, score_updated_listener);
  add_event_listener_NameChanged(&manager, name_changed_listener);
  // The above could also be called using the macro format:
  // add_event_listener(ScoreUpdated)(&manager, score_updated_listener);
  // add_event_listener(NameChanged)(&manager, name_changed_listener);

  emit_event_ScoreUpdated(&manager, (ScoreUpdated){.score = 50});
  emit_event_NameChanged(&manager, (NameChanged){.name = "Abdelrahman"});
  // The above could also be called using the macro format:
  // emit_event(ScoreUpdated)(&manager, (ScoreUpdated){.score = 50});
  // emit_event(NameChanged)(&manager, (NameChanged){.name = "Abdelrahman"});

  return 0;
}
