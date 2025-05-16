/**
 * @file btree_subtree_common.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header of interface of the common variables of the subtree.
 * @version 1.0
 * @date 12/05/2025
 *
 */

#ifndef BTREE_SUBTREE_COMMON_H_
#define BTREE_SUBTREE_COMMON_H_

#include "btree_definition.h"

/**
 * @brief Size of array nodes status.
 *
 */
#define BTREE_SUBTREE_COMMON_STATUS_NODES_SIZE (btree_index_t) 1

/**
 * @brief Number of fields needed in the worst case scenario of tree subtree attempted fields.
 *
 */
#define BTREE_SUBTREE_COMMON_ATTEMPTS_SIZE 3

/**
 * @brief Externalize array of tree subtree attemps.
 *
 */
extern uint32_t btree_subtree_status_nodes[BTREE_SUBTREE_COMMON_STATUS_NODES_SIZE];

/**
 * @brief Externalize array of tree subtree attemps.
 *
 */
extern uint32_t btree_subtree_common_attempts[BTREE_SUBTREE_COMMON_ATTEMPTS_SIZE];

#endif /* BTREE_SUBTREE_COMMON_H_ */
