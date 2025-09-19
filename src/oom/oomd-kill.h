#include "_sd-common.h"

struct sd_oom_kill_state {
        int refs;    // use standard SD macros, etc.
        int pending; // specifically # of *pending* prekill calls. If this is zero, the action is done (can be treated as a boolean).

        // TODO: include everything needed to effect an action (do_kill).
        cgroup_t cgroup;                // could be a reference to rule, cgroup, etc.
        int (*killer)(cgroup_t cgroup); // kill_by_pgscan, kill_byswap, etc.

};

typedef struct sd_oom_kill_state sd_oom_kill_state;

sd_oomd_kill_state* sd_oomd_kill_state_ref(sd_oomd_kill_state *kill);
int sd_oomd_kill_state_new(sd_oomd_kill_state **kill);
void sd_oomd_kill_state_unref(sd_oomd_kill_state *kill);

// Specifically for the pending prekill calls.
void sd_oomd_kill_state_inc_pending(sd_oomd_kill_state *kill);
void sd_oomd_kill_state_dec_pending(sd_oomd_kill_state *kill);

_SD_DEFINE_POINTER_CLEANUP_FUNC(sd_oom_kill_state, sd_oom_kill_state_unref);
