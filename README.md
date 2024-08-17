# DispatchAfter

A simple implementation of a `dispatch_after` mechanism using 
[libevent](https://libevent.org/).

## Overview

This library provides a `dispatch_after` function that schedules a 
callback to be executed after a specified delay. It also provides a 
`dispatch_cancel` function to cancel a scheduled task before it executes.

## Usage

```c
#include "DispatchAfter.h"
#include <event2/event.h>

int main() {
    struct event_base *base = event_base_new();
    if (!base) {
        fprintf(stderr, "Could not initialize libevent!\n");
        return 1;
    }

    DispatchAfterHandle handle = dispatch_after(base, 5, 
my_callback_function, my_argument);

    // To cancel the task before it executes:
    // dispatch_cancel(handle);

    event_base_dispatch(base);
    event_base_free(base);

    return 0;
}

