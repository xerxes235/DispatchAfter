//
//  DispatchAfter.h
//  HyRecencyList
//
//  Created by Hamidreza Vakilian on 8/17/24.
//

#ifndef DispatchAfter_h
#define DispatchAfter_h

#include <stdio.h>
#include <event2/event.h>

/**
 * @typedef DispatchAfterHandle
 * @brief A handle to the dispatch_after context, used for managing and canceling the scheduled task.
 */
typedef void* DispatchAfterHandle;

/**
 * @brief Schedules a callback to be executed after a specified delay.
 *
 * @param evbase The event base that manages the event loop.
 * @param seconds The delay in seconds after which the callback should be executed.
 * @param callback The function to be called when the timer expires. It takes a single void* argument.
 * @param arg A pointer to be passed to the callback function when it is called.
 *
 * @return A handle to the scheduled task, which can be used to cancel the task before it is executed.
 * @retval NULL If memory allocation fails or if the event could not be created.
 */
DispatchAfterHandle
dispatch_after(struct event_base *evbase, int seconds, void (*callback)(void*), void *arg);

/**
 * @brief Cancels a scheduled task.
 *
 * @param handle The handle to the scheduled task, as returned by dispatch_after().
 *
 * @note This function will remove the event from the event loop if it has not yet been triggered,
 *       and will free all associated resources. If the event has already fired, this function has no effect.
 */
void
dispatch_cancel(void *handle);

#endif /* DispatchAfter_h */
