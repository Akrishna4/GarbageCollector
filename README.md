
# GarbageCollector

A minimal **mark-and-sweep garbage collector** implemented in C.  
This project demonstrates the basic concepts of garbage collection and memory management using a simple virtual machine (VM) with integers and pairs.

---

## **Overview**

Garbage collection is a technique to automatically manage memory in programming languages. This project implements a simple **mark-and-sweep** garbage collector:

1. **Mark phase**: Traverse all reachable objects and mark them.  
2. **Sweep phase**: Free all unmarked (unreachable) objects.  

The VM has a stack to store active variables and a linked list of all allocated objects to track memory usage.

---

## **Features**

- Supports two object types: `int` and `pair` (linked structures).  
- Handles cyclic references without crashing.  
- Dynamic threshold to trigger garbage collection.  
- Minimal implementation suitable for learning and experimentation.

---

## **Project Structure**

```

GarbageCollector/
├── main.c       # Full GC implementation + demo tests
├── Makefile     # Build & run helper
├── README.md    # Project description (this file)
├── LICENSE      # MIT license
└── .gitignore   # Ignore compiled files and VS Code configs

````

---

## **Build & Run**

### **Using GCC directly**
```bash
gcc main.c -o gc
./gc
````

### **Using Makefile**

```bash
make        # Build
make run    # Build and run
make clean  # Remove executable
```

---

## **Demo Tests**

The `main.c` file includes 4 demo tests:

| Test   | Description                     |
| ------ | ------------------------------- |
| Test 1 | Objects on stack are preserved  |
| Test 2 | Unreached objects are collected |
| Test 3 | Nested objects are preserved    |
| Test 4 | Handles cycles without crashing |

**Sample output:**

```
Test 1: Objects on stack are preserved.
Collected 0 objects, 2 remaining.
Test 2: Unreached objects are collected.
Collected 2 objects, 0 remaining.
Test 3: Reach nested objects.
Collected 0 objects, 3 remaining.
Test 4: Handle cycles.
Collected 0 objects, 4 remaining.
```

---

## **License**

This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.

---

## **Learn More**

* Mark-and-sweep GC concept: [Wikipedia](https://en.wikipedia.org/wiki/Tracing_garbage_collection#Mark-and-sweep)
* Memory management in C: [C Programming](https://www.learn-c.org/)

````

---

### ✅ How to Add This to Your Repo

1. Save this content in your repo folder as `README.md`  
2. Stage, commit, and push:

```bash
cd /Users/ayushkrishna/Desktop/GarbageCollector
git add README.md
git commit -m "Add polished README with overview and usage"
git push
````

---

