//
//  DispatchAfter.c
//  HyRecencyList
//
//  Created by Hamidreza Vakilian on 8/17/24.
//

#include "./DispatchAfter.h"
#include <stdio.h>
#include <stdlib.h>

typedef void (*dispatch_after_callback_fn)(void *arg);

typedef struct _DispatchAfterContext {
    struct event *ev;
    dispatch_after_callback_fn callback;
    void *cb_arg;
} DispatchAfterContext;


void
dispatch_cancel(void *handle) {
    DispatchAfterContext *ctx = (DispatchAfterContext *)handle;
    if (ctx) {
        if (ctx->ev) {
            event_del(ctx->ev);
            event_free(ctx->ev);
            ctx->ev = NULL;
        }
        free(ctx);
    }
}

void
dispatch_after_callback(evutil_socket_t fd, short event, void *arg) {
    DispatchAfterContext *ctx = (DispatchAfterContext *)arg;

    if (ctx) {
        // keep the callback and callback's argument
        dispatch_after_callback_fn cb = ctx->callback;
        void *cb_arg = ctx->cb_arg;

        // cleanup dispatch resources
        dispatch_cancel(ctx);

        // invoke user callback
        if (cb) {
            cb(cb_arg);
        }
    }
}

void*
dispatch_after(struct event_base *evbase, int seconds, void (*callback)(void*), void *arg) {
    if (!evbase || !callback || seconds < 0) {
        return NULL; // Handle invalid arguments
    }

    DispatchAfterContext *context = malloc(sizeof(DispatchAfterContext));
    if (!context) {
        return NULL; // Handle memory allocation failure
    }

    context->ev = event_new(evbase, -1, EV_TIMEOUT, dispatch_after_callback, context);
    if (!context->ev) {
        free(context); // Handle event creation failure
        return NULL;
    }

    context->callback = callback;
    context->cb_arg = arg;

    struct timeval interval = {seconds, 0};
    event_add(context->ev, &interval);

    return context;
}
