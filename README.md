# Exploring ideas for a generic and extensible event system in C

These are two different ideas for implementing a generic and extensible event system using the C programming language.

The [first version](./01_void_ptrs) is the simplest of the two. It relies on using void pointers. This makes the implementation very simple, but it also makes it less type safe, as it relies on the user to make sure to pass the correct types and to cast them properly.

The [second version](./02_macros) is a little bit more complicated as it relies on macros that declare and define different versions of the `add_event_listener` and `emit_event` functions for each desired event type. The user can then call these functions either directly using the function name (e.g. for type `int`, the names would be `add_event_listener_int` and `emit_event_int`) or using the macro functions which would be converted to the correct function names using the C preprocessor. Although it is a bit more complicated than the first version, this added complexity comes also with more type safety, which makes this version less prone to user errors (At least, as long as the user isn't going out of their way to pass an object of the wrong type to the functions).

> Please note that none of these two systems are intended for production use. They are just personal explorations meant for me to increase my familiarity with the C programming language. However, they could still be useful for anyone, like me, who is still relatively new to C.
