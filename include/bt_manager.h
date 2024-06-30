/**
 * @file bt_manager.h
 * @author Renilson Almeida (renilson.123@hotmail.com)
 * @brief Header of behavior tree manager.
 * @version 1.0
 * @date 26/06/24
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

#ifndef INCLUDE_BT_MANAGER_H_
#define INCLUDE_BT_MANAGER_H_

#include "bt_process.h"

/**
 * @brief Tree root address.
 *
 */
#define BT_MANAGER_ROOT_INDEX 0

/**
 * @brief Function that manages and performs a step in the tree.
 *
 * @return behavior_tree_status_t
 * BT_DEFINITION_STATUS_SUCCESS for successfully executed tree;
 * BT_DEFINITION_STATUS_FAIL for failed tree;
 * BT_DEFINITION_STATUS_RUNNING for running tree;
 * BT_DEFINITION_STATUS_ERROR for irregular tree;
 */
bt_definition_status_t bt_manager_tick_tree();

/**
 * @brief Function to init behavior tree.
 * 
 * @return int 0 for success, other case fail.
 */
int tc_bt_manager_init();

#endif /* INCLUDE_BT_MANAGER_H_ */
