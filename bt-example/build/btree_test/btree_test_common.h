/**
 * @file btree_test_common.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header of interface of the common variables of the test.
 * @version 1.0
 * @date 27/04/2025
 *
 */

#ifndef BTREE_TEST_COMMON_H_
#define BTREE_TEST_COMMON_H_

#include "btree_definition.h"

/**
 * @brief Size of array nodes status.
 *
 */
#define BTREE_TEST_COMMON_STATUS_NODES_SIZE (btree_index_t) 3

/**
 * @brief Number of fields needed in the worst case scenario of tree test attempted fields.
 *
 */
#define BTREE_TEST_COMMON_ATTEMPTS_SIZE 2

/**
 * @brief Externalize array of tree test attemps.
 *
 */
extern uint32_t btree_test_status_nodes[BTREE_TEST_COMMON_STATUS_NODES_SIZE];

/**
 * @brief Externalize array of tree test attemps.
 *
 */
extern uint32_t btree_test_common_attempts[BTREE_TEST_COMMON_ATTEMPTS_SIZE];

#endif /* BTREE_TEST_COMMON_H_ */
