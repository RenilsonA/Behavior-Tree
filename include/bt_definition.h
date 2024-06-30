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

#ifndef INCLUDE_BT_DEFINITION_H_
#define INCLUDE_BT_DEFINITION_H_

#include <stdint.h>

/**
 * @brief Non-existing item.
 *
 */
#define BT_DEFINITION_TREE_UNRELATED 255

/**
 * @brief Error checking a function of type bt_definition_status_t.
 *
 */
#define BT_DEFINITION_TREE_STATUS(_err)         \
    do {                                        \
        if (_err) {                             \
            return BT_DEFINITION_STATUS_FAIL;   \
        }                                       \
        return BT_DEFINITION_STATUS_SUCCESS;    \
    } while (0)

/**
 * @brief Enumerates the types of tree returns.
 *
 */
typedef enum
{
    BT_DEFINITION_STATUS_SUCCESS = 0,     /**< Sucess status node or tree. */
    BT_DEFINITION_STATUS_RUNNING,         /**< Running status node or tree. */
    BT_DEFINITION_STATUS_FAIL,            /**< Failed status node or tree. */
    BT_DEFINITION_STATUS_ERROR,           /**< Error status node or tree. */            
    BT_DEFINITION_STATUS_LEAVE_TREE,      /**< Leave Tree status on root node. */
} bt_definition_status_t;

/**
 * @brief Enumerates the types of nodes in the tree.
 *
 */
typedef enum
{
    BT_DEFINITION_NODE_ROOT = 0,            /**< Type of root node. */
    BT_DEFINITION_NODE_SEQUENCE,            /**< Type of composite sequence node. */
    BT_DEFINITION_NODE_FALLBACK,            /**< Type of composite fallback node. */
} bt_definition_node_type_t;

/**
 * @brief Data loaded into a root node.
 *
 */
typedef struct bt_root_node
{
    uint8_t children_index;    /**< Index to the first child node. */
    uint8_t tree_index;        /**< Index of where the tree that called it is located. */
    uint8_t parent_tree_index; /**< Index of where the tree that called it stopped is. */
} bt_definition_root_node_t;

/**
 * @brief Data loaded into a composition type node.
 *
 */
typedef struct bt_definition_composite_node
{
      uint8_t children_index;    /**< Index to first child structure. */
} bt_definition_composite_node_t;

/**
 * @brief Data loaded into a tree leaf node.
 *
 */
typedef struct bt_definition_node
{
      uint8_t sibling_index;                                    /**< Index to the leaf's sister structure. */
      uint8_t parent_index;                                     /**< Index to the parent structure. */
      union
      {
            bt_definition_composite_node_t composite_node;   /**< Data for composite type node. */
      };
} bt_definition_node_t;

/**
 * @brief Structure of a tree node.
 *
 */
typedef struct __attribute__((__packed__)) bt_definition
{
    bt_definition_node_type_t node_type;          /**< Node type. */
    union {
          bt_definition_root_node_t root_node;    /**< Node type root. */
          bt_definition_node_t node;           /**< Node type leaf. */
      };
} bt_definition_t;

/**
 * @brief Macro that creates a root node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_ROOT(_children, _parent_tree, _parent_index)             \
                                      {                                                       \
                                         .node_type = BT_DEFINITION_NODE_ROOT,             \
                                         .root_node.children_index = _children,               \
                                         .root_node.tree_index = _parent_tree,                \
                                         .root_node.parent_tree_index = _parent_index,        \
                                      }

#endif /* INCLUDE_BT_DEFINITION_H_ */
