/**
 * @file btree_process.c
 * @author Renilson Almeida (renilson.123@hotmail.com)
 * @brief Header of behavior tree common.
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

#ifndef BTREE_COMMON_H_
#define BTREE_COMMON_H_

#include "../../bt/include/btree_definition.h"
#include "stdbool.h"

/**
 * @brief Divisor value for milliseconds.
 *
 */
#define BTREE_COMMON_MILLISECONDS_DIVISOR 1000

/**
 * @brief Divisor value for seconds.
 *
 */
#define BTREE_COMMON_SECONDS_DIVISOR 60

/**
 * @brief Divisor value for minutes.
 *
 */
#define BTREE_COMMON_MINUTES_DIVISOR 60

/**
 * @brief Function for delay within the behavior tree.
 *
 * @param timeout_ms Wait timeout value in milliseconds.
 * @retval BTREE_DEFINITION_STATUS_SUCCESS if successful
 * @retval BTREE_DEFINITION_STATUS_RUNNING if delay initiated.
 * @retval BTREE_DEFINITION_STATUS_FAIL if fail something.
 */
btree_definition_status_t btree_common_action_timeout(uint32_t timeout_ms);

#endif /* BTREE_COMMON_H_ */
