/**
 * @file test_bt_blackboard.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface do blackboard.
 * @version 1.0
 * @date 05/01/2025
 *
 *
 */

#include "test_bt_blackboard.h"

/**
 * @brief Estrutura com dados pertinentes da blackboard da árvore TEST_.
 * 
 */
struct test_bt_blackboard test_bt_data = 
{

};

bt_definition_status_t test_bt_reset_blackboard(void)
{
     memset(&test_bt_data, 0, sizeof(test_bt_data));
}
