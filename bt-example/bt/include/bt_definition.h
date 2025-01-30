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
    BT_DEFINITION_STATUS_RUNNING = 0, /**< Status running in node or tree. */
    BT_DEFINITION_STATUS_SUCCESS,     /**< Status success in node or tree. */
    BT_DEFINITION_STATUS_FAIL,        /**< Status failed in node or tree. */
    BT_DEFINITION_STATUS_RE_EXECUTE,   /**< Status of new re-execution in node or tree. */
    BT_DEFINITION_STATUS_ERROR,       /**< Status error in node or tree. */
    __BT_DEFINITION_STATUS_AMOUNT,    /**< Status amount in lib. */
} bt_definition_status_t;

/**
 * @brief Enumerates the types of nodes in the tree.
 *
 */
typedef enum
{
    BT_DEFINITION_NODE_CONDITION = 0,     /**< Type of interaction condition node. */
    BT_DEFINITION_NODE_ACTION,            /**< Type of interaction action node. */
    BT_DEFINITION_NODE_ACTION_TIMEOUT,    /**< Type of interaction action timeout node. */
    BT_DEFINITION_NODE_DECORATOR_TIMEOUT,
    BT_DEFINITION_NODE_RETRY_UNTIL_SUCCESS,
    BT_DEFINITION_NODE_REPEAT,
    BT_DEFINITION_NODE_KEEP_RUNNING_UNTIL_FAILURE,
    BT_DEFINITION_NODE_INVERTER,
    BT_DEFINITION_NODE_FORCE_SUCCESS,
    BT_DEFINITION_NODE_FORCE_FAIL,
    BT_DEFINITION_NODE_REACTIVE_NODES = 0x10,
    BT_DEFINITION_NODE_REACTIVE_CONDITION,/**< Type of reactive interaction condition node. */
    BT_DEFINITION_NODE_REACTIVE_ACTION,   /**< Type of reactive interaction action node. */
    BT_DEFINITION_NODE_REACTIVE_ACTION_TIMEOUT,    /**< Type of reactive interaction action timeout node. */
    BT_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT,
    BT_DEFINITION_NODE_REACTIVE_RETRY_UNTIL_SUCCESS,
    BT_DEFINITION_NODE_REACTIVE_REPEAT,
    BT_DEFINITION_NODE_REACTIVE_KEEP_RUNNING_UNTIL_FAILURE,
    BT_DEFINITION_NODE_REACTIVE_INVERTER,
    BT_DEFINITION_NODE_REACTIVE_FORCE_SUCCESS,
    BT_DEFINITION_NODE_REACTIVE_FORCE_FAIL,
    __BT_DEFINITION_NODE_AMOUNT,          /**< Amount of nodes. */
} bt_definition_node_type_t;

typedef struct bt_definition_node_decorator
{
    bt_index_t target_index;
    union
    {
        struct
        {
            bt_index_t node_limit;
            uint32_t times;
            uint32_t *local;
        } ties_node;
        uint32_t timeout_ms;
    };
} bt_definition_node_decorator_t;

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
        bt_definition_node_decorator_t decorator_node; /**< Decorator type node. */
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
#define BT_DEFINITION_CREATE_NODE_CONDITION(_success_target, _fail_target, _function) \
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
#define BT_DEFINITION_CREATE_NODE_ACTION(_success_target, _fail_target, _function) \
    {                                                                              \
        .node_type = BT_DEFINITION_NODE_ACTION,                                    \
        .st_index = _success_target,                                               \
        .ft_index = _fail_target,                                                  \
        .interaction_node.function = _function,                                    \
    }

/**
 * @brief Macro that creates retry until success node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_RETRY_UNTIL_SUCCESS(_success_target, _fail_target, _target, _attempts, _local, _node_limit) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_RETRY_UNTIL_SUCCESS,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
        .decorator_node.ties_node.node_limit = _node_limit, \
        .decorator_node.ties_node.times = _attempts,     \
        .decorator_node.ties_node.local = _local,     \
    }

/**
 * @brief Macro that creates repeat node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REPEAT(_success_target, _fail_target, _target, _times, _local, _node_limit) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_REPEAT,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
        .decorator_node.ties_node.node_limit = _node_limit, \
        .decorator_node.ties_node.times = _times,     \
        .decorator_node.ties_node.local = _local,     \
    }

/**
 * @brief Macro that creates keep running until failure node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_KEEP_RUNNING_UNTIL_FAILURE(_success_target, _fail_target, _target, _node_limit) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_KEEP_RUNNING_UNTIL_FAILURE,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
        .decorator_node.ties_node.node_limit = _node_limit, \
    }

/**
 * @brief Macro that creates inverter node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_INVERTER(_success_target, _fail_target, _target) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_INVERTER,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
    }

/**
 * @brief Macro that creates force success node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_FORCE_SUCCESS(_success_target, _fail_target, _target) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_FORCE_SUCCESS,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
    }

/**
 * @brief Macro that creates force fail node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_FORCE_FAIL(_success_target, _fail_target, _target) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_FORCE_FAIL,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
    }

/**
 * @brief Macro that creates decorator timeout node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_DECORATOR_TIMEOUT(_success_target, _fail_target, _target, _timeout_ms) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_DECORATOR_TIMEOUT,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
        .decorator_node.timeout_ms = _timeout_ms, \
    }

/**
 * @brief Macro that creates condition reactive node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_CONDITION(_success_target, _fail_target, _function) \
    {                                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_CONDITION,                                    \
        .st_index = _success_target,                                                           \
        .ft_index = _fail_target,                                                              \
        .interaction_node.function = _function,                                                \
    }

/**
 * @brief Macro that creates action reactive node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_ACTION(_success_target, _fail_target, _function) \
    {                                                                                       \
        .node_type = BT_DEFINITION_NODE_REACTIVE_ACTION,                                    \
        .st_index = _success_target,                                                        \
        .ft_index = _fail_target,                                                           \
        .interaction_node.function = _function,                                             \
    }

/**
 * @brief Macro that creates retry until success reactive node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_RETRY_UNTIL_SUCCESS(_success_target, _fail_target, _target, _attempts, _local, _node_limit) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_RETRY_UNTIL_SUCCESS,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
        .decorator_node.ties_node.node_limit = _node_limit, \
        .decorator_node.ties_node.times = _attempts,     \
        .decorator_node.ties_node.local = _local,     \
    }

/**
 * @brief Macro that creates repeat reactive node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_REPEAT(_success_target, _fail_target, _target, _times, _local, _node_limit) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_REPEAT,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
        .decorator_node.ties_node.node_limit = _node_limit, \
        .decorator_node.ties_node.times = _times,     \
        .decorator_node.ties_node.local = _local,     \
    }

/**
 * @brief Macro that creates keep running until failure reactive node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_KEEP_RUNNING_UNTIL_FAILURE(_success_target, _fail_target, _target, _node_limit) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_KEEP_RUNNING_UNTIL_FAILURE,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
        .decorator_node.ties_node.node_limit = _node_limit, \
    }

/**
 * @brief Macro that creates decorator timeout reactive node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_DECORATOR_TIMEOUT(_success_target, _fail_target, _target, _timeout_ms) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
        .decorator_node.timeout_ms = _timeout_ms, \
    }

/**
 * @brief Macro that creates inverter node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_INVERTER(_success_target, _fail_target, _target) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_INVERTER,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
    }

/**
 * @brief Macro that creates force success node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_FORCE_SUCCESS(_success_target, _fail_target, _target) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_FORCE_SUCCESS,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
    }

/**
 * @brief Macro that creates force fail node.
 *
 */
#define BT_DEFINITION_CREATE_NODE_REACTIVE_FORCE_FAIL(_success_target, _fail_target, _target) \
    {                                                                          \
        .node_type = BT_DEFINITION_NODE_REACTIVE_FORCE_FAIL,                   \
        .st_index = _success_target,                                 \
        .ft_index = _fail_target,                                  \
        .decorator_node.target_index = _target, \
    }

#endif /* BT_DEFINITION_H_ */
