/**
 * @file bt_common.c
 * @author Renilson Almeida (renilson.123@hotmail.com)
 * @brief Behavior tree common.
 * @version 1.0
 * @date 30/06/24
 * 
 * @copyright Copyright (c) 2024 Renilson Almeida
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "bt_common.h"

bt_definition_status_t bt_common_action_timeout(uint32_t timeout_ms)
{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t milliseconds;

    hours = timeout_ms / (BT_COMMON_MILLISECONDS_DIVISOR * BT_COMMON_SECONDS_DIVISOR * BT_COMMON_MINUTES_DIVISOR);
    milliseconds %= (BT_COMMON_MILLISECONDS_DIVISOR * BT_COMMON_SECONDS_DIVISOR * BT_COMMON_MINUTES_DIVISOR);

    minutes = milliseconds / (BT_COMMON_MILLISECONDS_DIVISOR * BT_COMMON_SECONDS_DIVISOR);
    milliseconds %= (BT_COMMON_MILLISECONDS_DIVISOR * BT_COMMON_SECONDS_DIVISOR);

    seconds = milliseconds / (BT_COMMON_MILLISECONDS_DIVISOR);
    milliseconds %= (BT_COMMON_MILLISECONDS_DIVISOR);

    //Input here delay funcion

    return BT_DEFINITION_STATUS_SUCCESS;
}
