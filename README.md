# Systems Programming Exercises

This repository is a collection of exercises and solutions developed to prepare for the Systems Programming examinations. 

## About the Course
Systems programming involves developing software that interacts with other programs or "systems" rather than human users. These systems—such as operating systems, database engines, and networked architectures—require rigid interaction formats and have non-trivial architectures where performance is critical.

The primary focus of this course was a practice-oriented introduction to the C programming language and, to a limited extent, C++. Beyond writing code, the goal was to understand the underlying execution model in depth, including:
* Memory management, pointer arithmetic, and manual allocation/deallocation.
* The build process: compilation units, symbols, linking, and using `make` for dependency management.
* System interfaces: network primitives, asynchronous I/O, and signals.
* Practical debugging using symbolic debuggers and `valgrind` to detect memory leaks.

I thoroughly enjoyed learning C and C++ during this course, specifically gaining a deeper appreciation for how high-level logic maps to low-level hardware execution.

## Repository Structure

The repository is organized into three sections based on the source and complexity of the problems:

### 1. Starting Exercises
Foundational exercises focused on the basic and advanced features of C, including pointer arithmetic, string processing, and dynamic memory allocation.
* **Source:** [Antonio Carzaniga - Systems Programming Exercises](https://www.inf.usi.ch/carzaniga/edu/sysprog_exercises/index.html)
* **Key Topics:** Basic types, control structures, `wordcount`, `sortstrings`, and memory model basics.

### 2. Lab Exercises
Practical tasks solved during university laboratory sessions to reinforce course concepts.
* **Key Topics:** Multi-file projects, pre-processor usage, custom data structures (structures/unions), and symbolic debugging.

### 3. Exam Exercises
The most challenging material, consisting of complex problems from past examination papers that require a synthesis of all course topics.
* **Source:** [Systems Programming Exam Exercises (PDF)](https://www.inf.usi.ch/carzaniga/edu/sysprog_exams/exercises.pdf)
* **Key Topics:** Advanced execution models, network primitives, and performance-critical C/C++ implementations.

## Technical Environment
The solutions in this repository are designed to be compiled with `gcc` or `g++` and managed via `make`. Memory safety was verified using `valgrind`.