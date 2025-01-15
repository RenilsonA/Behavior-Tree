/**
 * @file test_bt_blackboard.h
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Header da interface da blackboard.
 * @version 1.0
 * @date 14/01/2025
 *
 *
 */

#ifndef TEST_BT_BLACKBOARD_H_
#define TEST_BT_BLACKBOARD_H_

#include "test_bt_common.h"

/**
 * @brief Estrutura dos dados usado na árvore test.
 * 
 */
struct test_bt_blackboard
{

};

/**
 * @brief Estrutura com dados pertinentes da blackboard da árvore test.
 * 
 */
extern struct test_bt_blackboard test_bt_data;

/**
 * @brief Limpa todos dados da blackboard test.
 * 
 */
void test_bt_reset_blackboard(void);

#endif /* TEST_BT_BLACKBOARD_H_ */
