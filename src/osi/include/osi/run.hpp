#ifndef RUN_INCLUDE
#define RUN_INCLUDE

namespace osi
{

/**
 * Initializes environment which communicates directly with the operating system.
 */
void start();

/**
 * Runs the application loop, in which input and output events are registered and generated respectively.
 * @exception Throws runtime_error if glad fails to load.
 */
void run();

/**
 * Terminates the program and frees all the resources reserved in the `start()` function.
 */
void finish();

} // namespace osi

#endif