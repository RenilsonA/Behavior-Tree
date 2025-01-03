/**
 * @file bt_process.h
 * @author Renilson Almeida (renilson.123@hotmail.com)
 * @brief Header of behavior tree process.
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

#ifndef BT_PROCESS_H_
#define BT_PROCESS_H_

#include "bt_common.h"
#include "stddef.h"

/**
 * @brief Executes nodes. Each function call is a tick.
 *
 * @param data_tree[in] Data struct of tree.
 * @retval BT_DEFINITION_STATUS_SUCCESS if successfully executed node;
 * @retval BT_DEFINITION_STATUS_FAIL if failed node;
 * @retval BT_DEFINITION_STATUS_RUNNING if running node;
 * @retval BT_DEFINITION_STATUS_ERROR if irregular node;
 */
bt_definition_status_t bt_process_node(bt_definition_tree_data_t *struct_tree);

#endif /* BT_PROCESS_H_ */
