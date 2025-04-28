/**
 * @file btree_common.c
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

#include "btree_common.h"

btree_definition_status_t btree_common_action_timeout(uint32_t timeout_ms)
{
    uint8_t hours = 0;
    uint8_t minutes = 0;
    uint8_t seconds = 0;
    uint16_t milliseconds = timeout_ms;

    hours = timeout_ms / (BTREE_COMMON_MILLISECONDS_DIVISOR * BTREE_COMMON_SECONDS_DIVISOR * BTREE_COMMON_MINUTES_DIVISOR);
    milliseconds %= (BTREE_COMMON_MILLISECONDS_DIVISOR * BTREE_COMMON_SECONDS_DIVISOR * BTREE_COMMON_MINUTES_DIVISOR);

    minutes = milliseconds / (BTREE_COMMON_MILLISECONDS_DIVISOR * BTREE_COMMON_SECONDS_DIVISOR);
    milliseconds %= (BTREE_COMMON_MILLISECONDS_DIVISOR * BTREE_COMMON_SECONDS_DIVISOR);

    seconds = milliseconds / (BTREE_COMMON_MILLISECONDS_DIVISOR);
    milliseconds %= (BTREE_COMMON_MILLISECONDS_DIVISOR);

    SEGGER_RTT_printf(0, "%d ", timeout_ms);
    // Input here delay funcion

    return BTREE_DEFINITION_STATUS_SUCCESS;
}
