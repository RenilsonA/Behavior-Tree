/**
 * @file test_bt_array.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface da behavior tree array.
 * @version 1.0
 * @date 03/01/2025
 *
 */

#include "test_bt_array.h"
#include "test_bt_example.h"

/**
 * @brief Array contendo os nós da árvore test.
 *
 */
const bt_definition_node_t test_bt_array[TEST_BT_ARRAY_SIZE] = 
{
         [0] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition1, 5, 1), \
         [1] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action1, 2, BT_DEFINITION_TREE_UNRELATED), \
         [2] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition2, 5, 3), \
         [3] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action2, 5, 4), \
         [4] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action3, 5, BT_DEFINITION_TREE_UNRELATED), \
         [5] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition4, 7, 6), \
         [6] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action9, 7, BT_DEFINITION_TREE_UNRELATED), \
         [7] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition5, 8, BT_DEFINITION_TREE_UNRELATED), \
         [8] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action10, 9, BT_DEFINITION_TREE_UNRELATED), \
         [9] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition6, BT_DEFINITION_TREE_UNRELATED, 10), \
         [10] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition7, BT_DEFINITION_TREE_UNRELATED, 11), \
         [11] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action11, BT_DEFINITION_TREE_UNRELATED, 12), \
         [12] = BT_DEFINITION_CREATE_NODE_CONDITION(&test_bt_example_condition8, BT_DEFINITION_TREE_UNRELATED, 13), \
         [13] = BT_DEFINITION_CREATE_NODE_ACTION(&test_bt_example_action12, BT_DEFINITION_TREE_UNRELATED, BT_DEFINITION_TREE_UNRELATED), \
};

/**
 * @brief Estrutura de controle da árvore test.
 *
 */
bt_definition_tree_data_t test_bt_control = {
    .last_node_state = BT_DEFINITION_STATUS_RUNNING,
    .node_index      = BT_DEFINITON_NODE_FIRST_INDEX,
    .tree_size       = TEST_BT_ARRAY_SIZE,
    .tree            = test_bt_array,
};

