/**
 * @file btree_test_array.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header of interface of array tree.
 * @version 1.0
 * @date 27/04/2025
 *
 */

#ifndef BTREE_TEST_ARRAY_H_
#define BTREE_TEST_ARRAY_H_

#include "btree_test_blackboard.h"

/**
 * @brief test tree size.
 *
 */
#define BTREE_TEST_ARRAY_SIZE 43

/**
 * @brief Array containing the nodes of the test tree.
 *
 */
extern const btree_definition_node_t btree_test_array[BTREE_TEST_ARRAY_SIZE];

/**
 * @brief Externalizes test tree control structure.
 *
 */
extern btree_definition_tree_data_t btree_test_control;

#endif /* BTREE_TEST_ARRAY_H_ */
