/**
 * @file btree_main_common.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header of interface of the common variables of the main.
 * @version 1.0
 * @date 18/05/2025
 *
 */

#ifndef BTREE_MAIN_COMMON_H_
#define BTREE_MAIN_COMMON_H_

#include "btree_definition.h"

/**
 * @brief Size of array nodes status.
 *
 */
#define BTREE_MAIN_COMMON_STATUS_NODES_SIZE (btree_index_t) 15

/**
 * @brief Number of fields needed in the worst case scenario of tree main attempted fields.
 *
 */
#define BTREE_MAIN_COMMON_ATTEMPTS_SIZE 0

/**
 * @brief Externalize array of tree main attemps.
 *
 */
extern uint32_t btree_main_status_nodes[BTREE_MAIN_COMMON_STATUS_NODES_SIZE];

/**
 * @brief Externalize array of tree main attemps.
 *
 */
extern uint32_t btree_main_common_attempts[BTREE_MAIN_COMMON_ATTEMPTS_SIZE];

#endif /* BTREE_MAIN_COMMON_H_ */