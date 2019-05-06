/******************************************************************************
#   Copyright 2019 Rajive Joshi, Real-Time Innovations Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "osapi/osapi_thread.h"

void
App_help(char *appname) {
    printf("%s [options]\n", appname);
    printf("options:\n");
    printf("-h                 - This text\n");
    printf("-count <count>     - count (default: 0 i.e. forever)\n");
    printf("-sleep <ms>        - sleep between sends (default 1s)\n");
    printf("\n");
}

void
App_arguments(int argc, char **argv, long* sleep_time, long* count) {
    assert(sleep_time != 0 && count != 0);

    /* Uncomment to increase verbosity level:
       OSAPI_Log_set_verbosity(OSAPI_LOG_VERBOSITY_WARNING);
     */

    *sleep_time = 1000;
    *count = 0;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-sleep")) {
            ++i;
            if (i == argc) {
                printf("-sleep <sleep_time>\n");
                return;
            }
            *sleep_time = strtol(argv[i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-count")) {
            ++i;
            if (i == argc) {
                printf("-count <count>\n");
                return;
            }
            *count = strtol(argv[i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-h")) {
            App_help(argv[0]);
            return;
        }
        else {
            printf("unknown option: %s\n", argv[i]);
            return;
        }
    }
}

/**
 * Sleep for count seconds
 *
 * count - number of seconds to sleep; values <=0 are interpreted as 24 hours
 */
void
App_sleep(long count) {

    if (count > 0) {
        printf("Sleeping for %ld seconds, press Ctrl-C to exit\n", count);
        OSAPI_Thread_sleep(count * 1000);
    }
    else {
        printf("Sleeping for 24 hours, press Ctrl-C to exit\n");
        int sleep_loop_count =  (24 * 60 * 60) / 2000;
        int sleep_loop_left = (24 * 60 * 60) % 2000;
        while (sleep_loop_count) {
            OSAPI_Thread_sleep(2000  * 1000); /* sleep is in ms */
            --sleep_loop_count;
        }
        OSAPI_Thread_sleep(sleep_loop_left * 1000);
    }
}

/**
 * 'do_somnething' periodically in a loop
 *
 * sleep_time - number of seconds to sleep
 * count - number of times to run the loop; values <=0 are interpreted as forever
 * do_something - the function to execute periodically
 * context - the context in which to execute do_something
 */
void
App_loop(long sleep_time, long count, void (*do_something)(void*, long), void* context) {
    for (int i=0; (count == 0) || (i < count); ++i) {
        do_something(context, i);
        OSAPI_Thread_sleep(sleep_time);
    }
}
