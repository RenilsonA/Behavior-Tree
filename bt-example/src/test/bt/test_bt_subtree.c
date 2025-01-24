/**
 * @file test_bt_subtree.c
 * @author Renilson Almeida (joserenilson.silva@edge.ufal.br)
 * @brief Interface da behavior tree subtree.
 * @version 1.0
 * @date 20/01/2025
 *
 */

#include "test_bt_subtree.h"

int a1 = 0;
int a2 = 0;
int a3 = 0;
int a4 = 0;
int a5 = 0;
int a6 = 0;
int a7 = 0;
int a8 = 0;

bt_definition_status_t test_bt_subtree_condition20(void)
{
  SEGGER_RTT_printf(0, "condition20 ");
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_subtree_action21(void)
{
  SEGGER_RTT_printf(0, "test_bt_subtree_action21 ");
  if(a1++ > 3)
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_subtree_action22(void)
{
  SEGGER_RTT_printf(0, "action22 ");
  if(a2++ > 5) //inverte aqui
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

bt_definition_status_t test_bt_subtree_condition21(void)
{
  SEGGER_RTT_printf(0, "condition21 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_subtree_action23(void)
{
  SEGGER_RTT_printf(0, "action23 ");
  return BT_DEFINITION_STATUS_SUCCESS;
}

bt_definition_status_t test_bt_subtree_action24(void)
{
  SEGGER_RTT_printf(0, "action24 ");
  if(a3++ > 5) //inverte aqui
    return BT_DEFINITION_STATUS_SUCCESS;
  return BT_DEFINITION_STATUS_FAIL;
}

