#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 8

typedef enum {
    OBJ_INT,
    OBJ_PAIR
} ObjectType;

typedef struct sObject {
    unsigned char marked;
    ObjectType type;

    struct sObject* next; // Linked list of allocated objects

    union {
        int value; // OBJ_INT
        struct {   // OBJ_PAIR
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;

typedef struct {
    Object* stack[STACK_MAX];
    int stackSize;

    Object* firstObject;

    int numObjects;
    int maxObjects;
} VM;

/* --- VM Functions --- */
VM* newVM() {
    VM* vm = malloc(sizeof(VM));
    vm->stackSize = 0;
    vm->firstObject = NULL;
    vm->numObjects = 0;
    vm->maxObjects = INITIAL_GC_THRESHOLD;
    return vm;
}

void push(VM* vm, Object* value) {
    assert(vm->stackSize < STACK_MAX && "Stack overflow!");
    vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm) {
    assert(vm->stackSize > 0 && "Stack underflow!");
    return vm->stack[--vm->stackSize];
}

/* --- GC Functions --- */
void mark(Object* object) {
    if (object->marked) return;

    object->marked = 1;

    if (object->type == OBJ_PAIR) {
        if (object->head) mark(object->head);
        if (object->tail) mark(object->tail);
    }
}

void markAll(VM* vm) {
    for (int i = 0; i < vm->stackSize; i++) {
        mark(vm->stack[i]);
    }
}

void sweep(VM* vm) {
    Object** object = &vm->firstObject;
    while (*object) {
        if (!(*object)->marked) {
            Object* unreached = *object;
            *object = unreached->next;
            free(unreached);
            vm->numObjects--;
        } else {
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void gc(VM* vm) {
    int numObjects = vm->numObjects;
    markAll(vm);
    sweep(vm);
    vm->maxObjects = vm->numObjects * 2;

    printf("Collected %d objects, %d remaining.\n",
           numObjects - vm->numObjects, vm->numObjects);
}

/* --- Object Creation --- */
Object* newObject(VM* vm, ObjectType type) {
    if (vm->numObjects == vm->maxObjects) gc(vm);

    Object* object = malloc(sizeof(Object));
    object->type = type;
    object->marked = 0;

    object->next = vm->firstObject;
    vm->firstObject = object;

    vm->numObjects++;
    return object;
}

void pushInt(VM* vm, int value) {
    Object* object = newObject(vm, OBJ_INT);
    object->value = value;
    push(vm, object);
}

Object* pushPair(VM* vm) {
    Object* object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);
    push(vm, object);
    return object;
}

/* --- Demo --- */
void test1() {
    printf("Test 1: Objects on stack are preserved.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    gc(vm); // should keep both ints
}

void test2() {
    printf("Test 2: Unreached objects are collected.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    pop(vm);
    pop(vm);
    gc(vm); // should collect both
}

void test3() {
    printf("Test 3: Reach nested objects.\n");
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    pushPair(vm);  // pair(1,2)
    gc(vm);        // should keep everything
}

void test4() {
    printf("Test 4: Handle cycles.\n");
    VM* vm = newVM();

    pushInt(vm, 1);
    pushInt(vm, 2);
    Object* a = pushPair(vm); // pair(1,2)

    pushInt(vm, 3);
    pushInt(vm, 4);
    Object* b = pushPair(vm); // pair(3,4)

    // Create cycle
    a->tail = b;
    b->tail = a;

    gc(vm); // should not crash
}

int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}
