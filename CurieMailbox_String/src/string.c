/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <zephyr.h>
#include <ipm.h>
#include <ipm/ipm_quark_se.h>
#include "arduino101_services/arduino101_services.h"

#define SLEEP_TIME 100

/* Sending messages on channel 0 */
QUARK_SE_IPM_DEFINE(ipm_send, 0, QUARK_SE_IPM_OUTBOUND);

const char data[] = "Hello from x86";

void main (void)
{
    struct device *ipm = device_get_binding("ipm_send");

    while (1) {
        task_sleep(SLEEP_TIME);
        ipm_send(ipm, 1, 0, data, 16);
        task_yield();
    }
}
