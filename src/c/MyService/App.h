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

#ifndef _APP_H_
#define _APP_H_

typedef void (*Activity)(void*, long);
typedef void * Context;

extern void
App_help(char *appname);

extern void
App_arguments(int argc, char **argv, long* sleep_time, long* count);

extern void
App_sleep(long count);

extern void
App_loop(long sleep_time, long count,
        Activity activity, Context context);

#endif /* APP_H_ */