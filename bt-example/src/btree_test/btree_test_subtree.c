/**
 * @file btree_test_subtree.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface of subtree tree.
 * @version 1.0
 * @date 27/04/2025
 *
 */

#include "btree_test_subtree.h"

int a1 = 0;
int a2 = 0;
int a3 = 0;
int a4 = 0;
int a5 = 0;
int a6 = 0;
int a7 = 0;
int a8 = 0;

btree_definition_status_t btree_test_subtree_condition21(void)
{
  SEGGER_RTT_printf(0, "c21 ");
  return BTREE_DEFINITION_STATUS_SUCCESS;
}

btree_definition_status_t btree_test_subtree_action24(void)
{
  SEGGER_RTT_printf(0, "a24 ");
//  if(a6++ > 20){
//      a6 = 0;
//      return BTREE_DEFINITION_STATUS_RUNNING;
//  }
  return BTREE_DEFINITION_STATUS_FAIL;
}

btree_definition_status_t btree_test_subtree_action23(void)
{
  SEGGER_RTT_printf(0, "a23 ");
  return BTREE_DEFINITION_STATUS_SUCCESS;
}

btree_definition_status_t btree_test_subtree_condition20(void)
{
  SEGGER_RTT_printf(0, "c20 ");
  if(a7++ > 30)
    return BTREE_DEFINITION_STATUS_SUCCESS;
  return BTREE_DEFINITION_STATUS_FAIL;
}

btree_definition_status_t btree_test_subtree_action21(void)
{
  SEGGER_RTT_printf(0, "a21 ");
  if(a1++ > 3)
    return BTREE_DEFINITION_STATUS_SUCCESS;
  return BTREE_DEFINITION_STATUS_FAIL;
}

btree_definition_status_t btree_test_subtree_action25(void)
{
  SEGGER_RTT_printf(0, "a25 ");
  if(a8++ > 10)
    return BTREE_DEFINITION_STATUS_SUCCESS;
//  return BTREE_DEFINITION_STATUS_RUNNING;
  return BTREE_DEFINITION_STATUS_FAIL;
}

