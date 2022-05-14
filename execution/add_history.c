#include "minishell1.h"

int size = 100;


struct History {
  char** lines;
  int max_size;
  int begin;
};

void initialize_history(struct History* history, int size) {
  history->max_size = size;
  history->lines = malloc(size * sizeof(char*));
  int i;
  for (i = 0; i < size; ++i) {
    history->lines[i] = NULL;
  }
}

void add_to_history(struct History* history, char* commandline) {
  if (history->lines[history->begin] != NULL) {
    free(history->lines[history->begin]);
  }
  history->lines[history->begin] = commandline;
  history->begin = (history->begin + 1) % history->max_size;
}

void print_history(struct History* history) {
  int i;
  int begin = history->begin;
  for (i = 0; i < size; ++i) {
    if (history->lines[begin] != NULL) {
      printf("%s\n", history->lines[begin]);
    }
    ++begin;
    if (begin >= history->max_size) {
      begin = 0;
    }
  }
}
void free_history(struct History* history) {
  int i;
  for (i = 0; i < size; ++i) {
    if (history->lines[i] != NULL) {
      free(history->lines[i]);
    }
  }
  free(history->lines);
}

