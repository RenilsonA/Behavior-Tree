/**
 * @file bt_example.h
 * @author Renilson Almeida (renilson.123@hotmail.com)
 * @brief Header of one example of behavior tree.
 * @version 1.0
 * @date 02/12/24
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

#ifndef BT_EXAMPLE_H_
#define BT_EXAMPLE_H_

#include <stdint.h>
#include "bt_definition.h"
#include "bt_functions.h"

/**
 * @brief Size of tree example.
 * 
 */
#define BT_EXAMPLE_SIZE 8

/**
 * @brief Example of tree.
 * 
 */
const bt_definition_node_t bt_example[BT_EXAMPLE_SIZE] = {
    [0] = BT_DEFINITION_CREATE_NODE_CONDITION(&condition1, 1, 5, 5),
    [1] = BT_DEFINITION_CREATE_NODE_ACTION(&action1, 2, 5),
    [2] = BT_DEFINITION_CREATE_NODE_CONDITION(&condition2, 5, 3, 5),
    [3] = BT_DEFINITION_CREATE_NODE_ACTION(&action2, 4, 5),
    [4] = BT_DEFINITION_CREATE_NODE_ACTION(&action3, 5, 5),
    [5] = BT_DEFINITION_CREATE_NODE_CONDITION(&condition3, BT_DEFINITION_TREE_UNRELATED, 6, BT_DEFINITION_TREE_UNRELATED),
    [6] = BT_DEFINITION_CREATE_NODE_ACTION(&action4, BT_DEFINITION_TREE_UNRELATED, 7),
    [7] = BT_DEFINITION_CREATE_NODE_ACTION(&action5, BT_DEFINITION_TREE_UNRELATED, BT_DEFINITION_TREE_UNRELATED),
};

#endif /* BT_EXAMPLE_H_ */
