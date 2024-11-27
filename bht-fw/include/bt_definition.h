/**
 * @file bt_definition.h
 * @author Renilson Almeida (renilson.123@hotmail.com)
 * @brief Header of behavior tree definitions.
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

#ifndef BT_DEFINITION_H_
#define BT_DEFINITION_H_

/**
 * @brief Non-existing item.
 * Last ID of 32-bit value.
 *
 */
#define BT_DEFINITION_TREE_UNRELATED 0xFFFFFFFF

/**
 * @brief Error checking a function of type bt_definition_status_t.
 *
 */
#define BT_DEFINITION_TREE_STATUS(_err)       \
    do                                        \
    {                                         \
        if (_err)                             \
        {                                     \
            return BT_DEFINITION_STATUS_FAIL; \
        }                                     \
        return BT_DEFINITION_STATUS_SUCCESS;  \
    } while (0)

/**
 * @brief Enumerates the types of tree returns.
 *
 */
typedef enum
{
    BT_DEFINITION_STATUS_SUCCESS = 0, /**< Status success in node or tree. */
    BT_DEFINITION_STATUS_FAIL,        /**< Status failed in node or tree. */
    BT_DEFINITION_STATUS_RUNNING,     /**< Status running in node or tree. */
    BT_DEFINITION_STATUS_ERROR,       /**< Status error in node or tree. */
    _BT_DEFINITION_STATUS_AMOUNT,     /**< Status amount in lib. */
} bt_definition_status_t;

/**
 * @brief Enumerates the types of nodes in the tree.
 *
 */
typedef enum
{
} bt_definition_node_type_t;

/**
 * @brief Structure of a tree node.
 *
 */
typedef struct bt_definition
{
    bt_definition_node_type_t node_type; /**< Node type. */
} bt_definition_t;

#endif /* INCLUDE_BT_DEFINITION_H_ */
