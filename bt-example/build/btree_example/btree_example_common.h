/**
 * @file btree_example_common.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header of interface of the common variables of the example.
 * @version 1.0
 * @date 12/05/2025
 *
 */

#ifndef BTREE_EXAMPLE_COMMON_H_
#define BTREE_EXAMPLE_COMMON_H_

#include "btree_definition.h"

/**
 * @brief Size of array nodes status.
 *
 */
#define BTREE_EXAMPLE_COMMON_STATUS_NODES_SIZE (btree_index_t) 2

/**
 * @brief Number of fields needed in the worst case scenario of tree example attempted fields.
 *
 */
#define BTREE_EXAMPLE_COMMON_ATTEMPTS_SIZE 0

/**
 * @brief Externalize array of tree example attemps.
 *
 */
extern uint32_t btree_example_status_nodes[BTREE_EXAMPLE_COMMON_STATUS_NODES_SIZE];

/**
 * @brief Externalize array of tree example attemps.
 *
 */
extern uint32_t btree_example_common_attempts[BTREE_EXAMPLE_COMMON_ATTEMPTS_SIZE];

#endif /* BTREE_EXAMPLE_COMMON_H_ */