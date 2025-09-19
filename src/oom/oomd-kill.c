/* SPDX-License-Identifier: LGPL-2.1-or-later */

#include "oomd-kill.h"

static void sd_oomd_kill_state_free(sd_oomd_kill_state *kill)
{
        assert(kill->refs == 0);
        assert(kill->pending == 0);
        free(kill);
}

int sd_oomd_kill_state_new(sd_oomd_kill_state **kill)
{
        sd_oomd_kill_state *k = new0(sd_oomd_kill_state, 1);
        if (k == NULL) {
                return -ENOMEM;
        }
        *kill = k;
        return 0;
}

void sd_oomd_kill_state_unref(sd_oomd_kill_state *kill)
{
        assert(ctx->refs > 0);
        ctx->refs--;
        if (ctx->refs == 0) {
                sd_oomd_kill_state_free(kill);
        }
}

void sd_oomd_kill_state_inc_pending(sd_oomd_kill_state_t *kill)
{
        kill->pending++;
}

void sd_oomd_kill_state_dec_pending(sd_oomd_kill_state_t *kill)
{
        assert(kill->pending > 0);
        kill->pending--;
        if (kill->pending == 0) {
                // Perform the actual kill.
                kill->killer(kill->cgroup);
        }
}
