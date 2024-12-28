/**
 * @file test_bt_array.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface da behavior tree array.
 * @version 1.0
 * @date 28/12/2024
 *
 */

#include "test_bt_array.h"
#include "test_bt_example.h"
#include "test_bt_subtree.h"

/**
 * @brief Array contendo os nós da árvore test.
 *
 */
const bt_definition_node_t test_bt_array[TEST_BT_ARRAY_SIZE] = 
{
         [0] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition1, 1, 9), \
         [1] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action1, 2, 9), \
         [2] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action2, 4, 3), \
         [3] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action3, 4, 9), \
         [4] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action4, 5, 9), \
         [5] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_subtree_condition3, 8, 6), \
         [6] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_subtree_action7, 8, 7), \
         [7] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_subtree_action8, 8, 9), \
         [8] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action5, BT_DEFINITION_TREE_UNRELATED, 9), \
         [9] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition2, BT_DEFINITION_TREE_UNRELATED, 10), \
         [10] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action6, BT_DEFINITION_TREE_UNRELATED, BT_DEFINITION_TREE_UNRELATED), \
};

/**
 * @brief Estrutura de controle da árvore test.
 *
 */
bt_definition_tree_data_t test_bt_struct = {
    .last_node_state = BT_DEFINITION_STATUS_RUNNING,
    .node_index      = BT_DEFINITON_NODE_FIRST_INDEX,
    .condition_index = 0,
    .tree_size       = TEST_BT_ARRAY_SIZE,
    .tree            = test_bt_array,
};

