//###############################################
//# ###                                     ### #
//# ### Epics SNL Routines for              ### #
//# ### MDrive Motor Status                 ### #
//# ###                                     ### #
//# ### author: D. Hampai - M. Montis       ### #
//# ###                                     ### #
//# ### Ref 2.0; 2026-10-21                 ### #
//###############################################
//#
#include <stdio.h>
#include "motor_status.h"

/* ════════════════════════════════════════════════
 *  API MDriveStatus
 * ════════════════════════════════════════════════ */

int parse_mdrive_status(int error_code, int drive_en, int moving, MDriveStatus *ms)
{
    if (!ms) return -1;
    ms->error_code   = error_code;
    ms->drive_enable = drive_en;
    ms->in_motion    = moving;
    ms->limit_right  = (error_code == MDRIVE_ERR_LIMIT_PLUS);
    ms->limit_left   = (error_code == MDRIVE_ERR_LIMIT_MINUS);
    ms->stall        = (error_code == MDRIVE_ERR_STALL);
    return 0;
}

int mdrive_status_ok(MDriveStatus *ms)
{
    if (!ms) return 0;
    return (ms->drive_enable && ms->error_code == MDRIVE_ERR_NONE);
}

int mdrive_is_ready(MDriveStatus *ms)
{
    if (!ms) return 0;
    return (ms->drive_enable &&
            !ms->in_motion   &&
            ms->error_code == MDRIVE_ERR_NONE);
}

void print_mdrive_status(const char *label, MDriveStatus *ms)
{
    if (!ms) return;
    printf("=== MDrive Status [%s] ===\n", label ? label : "?");
    printf("  Error code   : %d\n", ms->error_code);
    printf("  Drive enable : %s\n", ms->drive_enable ? "ON"      : "OFF");
    printf("  In motion    : %s\n", ms->in_motion    ? "YES"     : "NO");
    printf("  Limit right  : %s\n", ms->limit_right  ? "TRIPPED" : "OK");
    printf("  Limit left   : %s\n", ms->limit_left   ? "TRIPPED" : "OK");
    printf("  Stall        : %s\n", ms->stall        ? "YES"     : "NO");
    printf("==========================\n");
}

/* ════════════════════════════════════════════════
 *  API TotalStatus
 * ════════════════════════════════════════════════ */

int parse_total_status(MDriveStatus *ms, TotalStatus *ts)
{
    if (!ms || !ts) return -1;
    ts->drive_enable = ms->drive_enable;
    ts->in_motion    = ms->in_motion;
    ts->limit_right  = ms->limit_right;
    ts->limit_left   = ms->limit_left;
    ts->stall        = ms->stall;
    return 0;
}

void print_total_status(MDriveStatus *ms)
{
    if (!ms) return;
    printf("=== Total Status ===\n");
    printf("  Drive enable : %s\n", ms->drive_enable ? "ON"      : "OFF");
    printf("  In motion    : %s\n", ms->in_motion    ? "YES"     : "NO");
    printf("  Limit right  : %s\n", ms->limit_right  ? "TRIPPED" : "OK");
    printf("  Limit left   : %s\n", ms->limit_left   ? "TRIPPED" : "OK");
    printf("  Stall        : %s\n", ms->stall        ? "YES"     : "NO");
    printf("====================\n");
}

