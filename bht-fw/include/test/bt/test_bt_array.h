/**
 * @file test_bt_array.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header da interface da behavior tree array.
 * @version 1.0
 * @date 27/12/2024
 *
 */

#ifndef TEST_BT_ARRAY_H_
#define TEST_BT_ARRAY_H_

#include "test_bt_blackboard.h"

/**
 * @brief Tamanho da árvore test_.
 *
 */
#define TEST_BT_ARRAY_SIZE 11

/**
 * @brief Array contendo os nós da árvore test.
 *
 */
extern const bt_definition_node_t test_bt_array[TEST_BT_ARRAY_SIZE];

/**
 * @brief Externaliza estrutura de controle da árvore test, caso precise.
 *
 */
extern bt_definition_tree_data_t test_bt_struct;

#endif /* TEST_BT_ARRAY_H_ */