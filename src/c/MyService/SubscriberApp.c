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

#include "Databus.h"
#include "App.h"

#include "Subscriber.h"
#include "Readers.h"

int
subscriber_app(long sleep_time, long count) {

    struct Databus *databus = NULL;

    assert((databus = Databus_create(My_If_SUB))
            != NULL
    );
    Databus_initialize(databus, READER_INFOS, NULL);

    assert(Databus_enable(databus)
            == DDS_RETCODE_OK
    );

    App_sleep(count);

done:
    Databus_finalize(databus);
    Databus_delete(databus);

    return 0;
}

int
main(int argc, char **argv) {
    long sleep_time = 1000;
    long count = 0;
    App_arguments(argc, argv, &sleep_time, &count);
    return subscriber_app(sleep_time, count);
}
