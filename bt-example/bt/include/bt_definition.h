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

#include "stdint.h"
#include "stddef.h"

/**
 * @brief Define type of indexes.
 * Type index of 32-bit, 16-bit 8-bit value, respectively.
 *
 */
#if BT_SIZE == 32
typedef uint32_t bt_index_t;
#elif BT_SIZE == 16
typedef uint16_t bt_index_t;
#else
typedef uint8_t bt_index_t;
#endif

/**
 * @brief Non-existing item.
 * Last ID of 32-bit, 16-bit 8-bit value, respectively.
 *
 */
#if BT_SIZE == 32
#define BT_DEFINITION_TREE_UNRELATED 0xFFFFFFFF
#elif BT_SIZE == 16
#define BT_DEFINITION_TREE_UNRELATED 0xFFFF
#else
#define BT_DEFINITION_TREE_UNRELATED 0xFF
#endif

/**
 * @brief Index of first node.
 *
 */
#define BT_DEFINITON_NODE_FIRST_INDEX 0

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
    __BT_DEFINITION_STATUS_AMOUNT,    /**< Status amount in lib. */
} bt_definition_status_t;

/**
 * @brief Enumerates the types of nodes in the tree.
 *
 */
typedef enum
{
    BT_DEFINITION_NODE_SEQUENCE = 0,      /**< Type of control sequence node. */
    BT_DEFINITION_NODE_FALLBACK,          /**< Type of control fallback node. */
    BT_DEFINITION_NODE_CONDITION,         /**< Type of interaction condition node. */
    BT_DEFINITION_NODE_ACTION,            /**< Type of interaction action node. */
    BT_DEFINITION_NODE_REACTIVE_CONDITION,/**< Type of interaction condition node. */
    BT_DEFINITION_NODE_REACTIVE_ACTION,   /**< Type of interaction action node. */
    BT_DEFINITION_NODE_ACTION_TIMEOUT,    /**< Type of interaction action timeout node. */
    __BT_DEFINITION_NODE_AMOUNT,          /**< Amount of nodes. */
} bt_definition_node_type_t;

/**
 * @brief Data loaded into interaction node.
 *
 */
typedef struct bt_definition_node_interaction
{
    union
    {
        bt_definition_status_t (*function)(void); /**< Pointer to interaction function. */
        bt_index_t timeout_ms; /**< Delay timeout value for interaction action node delay. */
    };
} bt_definition_node_interaction_t;

/**
 * @brief Structure of a tree node.
 *
 */
typedef struct bt_definition_node
{
    bt_definition_node_type_t node_type; /**< Node type. */
    bt_index_t st_index;                 /**< Index to next node struture if have success. */
    bt_index_t ft_index;                 /**< Index to next node struture if have fail. */
    union
    {
        bt_definition_node_interaction_t interaction_node; /**< interaction type node. */
    };
} bt_definition_node_t;

/**
 * @brief Estrutura de itens pertinentes de uma árvore.
 *
 */
typedef struct bt_definition_tree_data
{
    bt_definition_status_t last_node_state; /**< State of tree execution. */
    bt_index_t node_index;                  /**< Node to be executed. */
    bt_index_t tree_size;                   /**< Size of tree. */
    bt_index_t ignored_node_index;          /**< Ignored node index. */
    uint32_t *nodes_status;                 /**< Pointer to status of nodes. */
    const bt_definition_node_t *tree;       /**< Pointer to tree. */
} bt_definition_tree_data_t;

/**
 * @brief Macro that creates condition node condition.
 *
 */
#define BT_DEFINITION_CREATE_NODE_CONDITION(_function, _success_target, _fail_target) \
    {                                                                                 \
        .node_type = BT_DEFINITION_NODE_CONDITION,                                    \
        .st_index = _success_target,                                                  \
        .ft_index = _fail_target,                                                     \
        .interaction_node.function = _function,                                       \
    }

/**
 * @brief Macro that creates action node common.
 *
 */
#define BT_DEFINITION_CREATE_NODE_ACTION(_function, _success_target, _fail_target) \
    {                                                                              \
        .node_type = BT_DEFINITION_NODE_ACTION,                                    \
        .st_index = _success_target,                                               \
        .ft_index = _fail_target,                                                  \
        .interaction_node.function = _function,                                    \
    }

/**
 * @brief Macro that creates condition node condition.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(_function, _success_target, _fail_target) \
    {                                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_CONDITION,                                    \
        .st_index = _success_target,                                                           \
        .ft_index = _fail_target,                                                              \
        .interaction_node.function = _function,                                                \
    }

/**
 * @brief Macro that creates action node common.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(_function, _success_target, _fail_target) \
    {                                                                                       \
        .node_type = BT_DEFINITION_NODE_REACTIVE_ACTION,                                    \
        .st_index = _success_target,                                                        \
        .ft_index = _fail_target,                                                           \
        .interaction_node.function = _function,                                             \
    }

/**
 * @brief Macro that creates delay action node with delay.
 *
 */
#define BT_DEFINITION_CREATE_NODE_ACTION_DELAY(_timeout_ms, _sibling, _parent) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_ACTION,                                \
        .interaction_node.st_index = _sibling,                                 \
        .interaction_node.ft_index = _parent,                                  \
        .interaction_node.interaction.timeout_ms = _timeout_ms,                \
    }

#endif /* BT_DEFINITION_H_ */
