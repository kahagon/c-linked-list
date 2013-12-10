#include <stdio.h>
#include <stdlib.h>

typedef struct _state_element state_element;
typedef struct _state_storage state_storage;

struct _state_element {
    char* state;
    state_element* next;
};

struct _state_storage {
    state_element* first;
};

state_storage* init_state_storage() {
    state_storage* storage = (state_storage*)malloc(sizeof (state_storage));
    storage->first = NULL;

    return storage;
}

void destroy_state_element(state_element* element) {
    if (!element) return;

    printf("destroying:%s\n", element->state);
    destroy_state_element(element->next);
    free(element);
}

void destroy_state_storage(state_storage* storage) {
    destroy_state_element(storage->first);
    free(storage);
}

void store_state(state_storage* storage, char* state) {
    state_element* last_element;
    state_element* element 
        = (state_element*)malloc(sizeof (state_element));
    element->state = state;

    element->next = (void*)0;
    if(storage->first) {
        for (last_element = storage->first; last_element->next; last_element = last_element->next) 
            ;
        last_element->next = element;
    } else {
        storage->first = element;
    }
}

void store_state_to_first(state_storage* storage, char* state) {
    state_element* element 
        = (state_element*)malloc(sizeof (state_element));
    element->state = state;
    element->next = storage->first;
    storage->first = element;
}

int main (int argc, char* argv[]) {
    state_storage* storage = init_state_storage();
    state_element* current_element;

    store_state(storage, "1");
    store_state(storage, "2");
    store_state(storage, "3");

    for (current_element = storage->first; current_element; current_element = current_element->next) {
        printf("current:%s\n", current_element->state);
    }

    destroy_state_storage(storage);
    return 0;
}
