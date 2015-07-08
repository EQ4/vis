
#ifndef VIS_SCRIPT_HEADER_INCLUDED_
#define VIS_SCRIPT_HEADER_INCLUDED_ 1

#include "drawer.h"
#include <stdint.h>

struct flist;

typedef struct script_cb {
    struct script* owner;
    char* fn_name;
    char* fn_code;
} *script_cb_t;

typedef struct script* script_t;

enum script_debug_id {
    SCRIPT_DEBUG_PARTICLES_EMITTED,
    SCRIPT_DEBUG_TIME_NOW,
    SCRIPT_DEBUG_FRAMES_EMITTED,
    SCRIPT_DEBUG_NUM_MUTATES
};

typedef struct script_debug {
    uint32_t particles_emitted;
    uint32_t time_now;
    uint32_t frames_emitted;
    uint32_t num_mutates;
} *script_debug_t;

typedef unsigned int script_cfg_t;
static const script_cfg_t SCRIPT_ALLOW_ALL = 0; /* allow all features */
static const script_cfg_t SCRIPT_NO_CB = 1; /* disable callbacks */

script_t script_new(script_cfg_t cfg);
void script_free(script_t s);
void script_callback_free(script_cb_t cb);

/* number of errors returned to the script API, 0 for success */
int script_get_status(script_t s);

void script_set_debug(script_t s, enum script_debug_id what, uint32_t n);
void script_get_debug(script_t s, /*out*/ script_debug_t dbg);

struct flist* script_run(script_t script, const char* filename);
void script_run_string(script_t script, const char* torun);
void script_run_cb(script_t state, script_cb_t func, void* args);
void script_set_drawer(script_t script, drawer_t drawer);

void script_mousemove(script_t script, int x, int y);
void script_mousedown(script_t script, int x, int y);
void script_mouseup(script_t script, int x, int y);
void script_keydown(script_t script, const char* keyname, BOOL shift);
void script_keyup(script_t script, const char* keyname, BOOL shift);
void script_on_quit(script_t script);

#endif

