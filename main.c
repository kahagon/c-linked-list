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

void destroy_state_storage(state_storage* storage) {
    state_element* current_element = storage->first;
    while (current_element) {
        printf("current:%s\n", current_element->state);
        state_element* next = current_element->next;
        free(current_element);
        current_element = next;
    }
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

    store_state_to_first(storage, "3");
    store_state_to_first(storage, "2");
    store_state_to_first(storage, "1");

    destroy_state_storage(storage);
    return 0;
}
