commom_header = " * @version 1.0\n \
 * @date 26/06/24\n \
 *\n \
 * @copyright Copyright (c) 2024 Renilson Almeida\n \
 *\n \
 * Permission is hereby granted, free of charge, to any person obtaining a copy\n \
 * of this software and associated documentation files (the \"Software\"), to deal\n \
 * in the Software without restriction, including without limitation the rights\n \
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n \
 * copies of the Software, and to permit persons to whom the Software is\n \
 * furnished to do so, subject to the following conditions:\n \
 *\n \
 * The above copyright notice and this permission notice shall be included in all\n \
 * copies or substantial portions of the Software.\n \
 *\n \
 * THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n \
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n \
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n \
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n \
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n \
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n \
 * SOFTWARE.\n \
 */\n\n"

class CREATE_INCLUDE:
    def __init__(self):
        self.is_reactive = False
        self.have_retry_until_sucess = False
        self.have_reapeat = False
        self.have_keep_running_until_failured = False
        self.have_inverter = False
        self.have_force_success = False
        self.have_force_fail = False
        self.have_action_timeout = False

    def create_processor(self):
        text = "/**\n\
                 * @file btree_process.c\n\
                 * @author Renilson Almeida (renilson.123@hotmail.com)\n\
                 * @brief Behavior tree process.\n\
                 * @version 1.1\n"
        text += commom_header
        text += "#include \"btree_process.h\"\n\n"
        if ((self.have_retry_until_sucess) or (self.have_reapeat) or 
            (self.have_keep_running_until_failured) or (self.have_force_fail)):
            text += "/**\n\
                      * @brief Minimum quantity of attempts.\n\
                      *\n\
                      */\n\
                      #define BTREE_PROCESS_MIN_ATTEMPTS 0\n\n\
                     /**\n\
                      * @brief Check is target node is valid.\n\
                      *\n\
                      */\n\
                      #define BTREE_PROCESS_CHECK_TARGET(_tree_ptr, _index)  \n\                                           \\\n\
                          do                                                                                            \\\n\
                          {                                                                                             \\\n\
                              if ((_tree_ptr)->tree[index].decorator_node.target_index == BTREE_DEFINITION_TREE_UNRELATED) \\\n\
                              {                                                                                         \\\n\
                                  (_tree_ptr)->node_index = BTREE_DEFINITON_NODE_FIRST_INDEX;                              \\\n\
                                  return BTREE_DEFINITION_STATUS_ERROR;                                                    \\\n\
                              }                                                                                         \\\n\
                          } while (0)"

        if self.is_reactive:
            text += "btree_definition_status_t btree_process_node(btree_definition_tree_data_t *struct_tree,\n\
                                       btree_index_t index_status_key,\n\
                                       uint32_t index_status_position)\n\
                    {\n\
                        uint32_t value_status = 0;\n\
                        uint32_t mask = 0;\n\
                        btree_index_t key = 0;\n\
                        btree_index_t position = 0;\n\
                        uint32_t nodes_status = 0;\n\
                        uint32_t new_value = 0;\n\
                        btree_index_t clear_index = 0;\n"
        else:
            text += "btree_definition_status_t btree_process_node(btree_definition_tree_data_t *struct_tree)\n\
                    {\n"
        text += "btree_index_t index = struct_tree->node_index;\n\
                 btree_definition_status_t status = BTREE_DEFINITION_STATUS_RUNNING;\n\
                 const btree_definition_node_t *node_struct = &(struct_tree->tree[index]);\n\
                 btree_definition_node_type_t node_type = node_struct->node_type;\n\n\
                 if (struct_tree == NULL)\n\
                 {\n\
                    return BTREE_DEFINITION_STATUS_ERROR;\n\
                 }\n\
                 switch (node_type)\n\
                 {\n\
                 case BTREE_DEFINITION_NODE_ACTION:\n\
                 case BTREE_DEFINITION_NODE_CONDITION:\n"
        if self.is_reactive:
            text += "case BTREE_DEFINITION_NODE_REACTIVE_ACTION:\n\
                     case BTREE_DEFINITION_NODE_REACTIVE_CONDITION:\n"
        text += "{\n\
                    status = node_struct->interaction_node.function();\n\
                    if ((status == BTREE_DEFINITION_STATUS_RUNNING) || (status == BTREE_DEFINITION_STATUS_STAND_BY))\n\
                    {\n\
                        return BTREE_DEFINITION_STATUS_STAND_BY;\n\
                    }\n\
                    break;\n\
                }\n\n"
        if self.have_retry_until_sucess:
            text += "case BTREE_DEFINITION_NODE_RETRY_UNTIL_SUCCESS:\n"
            if self.is_reactive:
                text += "case BTREE_DEFINITION_NODE_REACTIVE_RETRY_UNTIL_SUCCESS:\n\
                    {\n\
                            BTREE_PROCESS_CHECK_TARGET(struct_tree, index);\n\n\
                    if ((struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RUNNING) ||\n\
                        (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RE_EXECUTE))\n\
                    {\n\
                        if (node_struct->decorator_node.ties_node.times <= 0)\n\
                        {\n\
                            status = BTREE_DEFINITION_STATUS_FAIL;\n\
                            break;\n\
                        }\n\n\
                        *node_struct->decorator_node.ties_node.local = node_struct->decorator_node.ties_node.times - 1;\n\n\
                        struct_tree->node_index = node_struct->decorator_node.target_index;\n\n\
                        struct_tree->last_node_state = BTREE_DEFINITION_STATUS_RUNNING;\n\
                        mask = (0b11 << (index_status_key));\n\
                        value_status = struct_tree->nodes_status[index_status_position] & (~mask);\n\
                        struct_tree->nodes_status[index_status_position] = (value_status) | (0b00 << (index_status_key));\n\n\
                        return BTREE_DEFINITION_STATUS_RUNNING;\n\
                    }\n\
                    else if ((struct_tree->last_node_state == BTREE_DEFINITION_STATUS_FAIL) &&\n\
                            (*node_struct->decorator_node.ties_node.local > BTREE_PROCESS_MIN_ATTEMPTS))\n\
                    {\n\
                        *node_struct->decorator_node.ties_node.local -= 1;\n\
                        struct_tree->node_index = node_struct->decorator_node.target_index;\n\
                        status = BTREE_DEFINITION_STATUS_RUNNING;\n\
                        clear_index = struct_tree->node_index;\n\n\
                        do\n\
                        {\n\
                            key = (clear_index % 16) * 2;\n\
                            position = clear_index / 16;\n\
                            nodes_status = struct_tree->nodes_status[position];\n\
                            mask = (0b11 << (key));\n\
                            new_value = (nodes_status & (~mask));\n\
                            struct_tree->nodes_status[position] = (new_value) | (0b11 << (key));\n\
                            clear_index += 1;\n\
                        } while (clear_index <= node_struct->decorator_node.ties_node.node_limit);\n\
                    }\n\
                    else\n\
                    {\n\
                        status = struct_tree->last_node_state;\n\
                        *node_struct->decorator_node.ties_node.local = BTREE_PROCESS_MIN_ATTEMPTS;\n\
                    }\n\n\
                    break;\n\
                }\n\n"
            else:
                text += "" #TODO: Realizar novos testes sendo não reativos
        if self.have_reapeat:
            text += "case BTREE_DEFINITION_NODE_REACTIVE_REPEAT:\n"
            if self.is_reactive:
                text += "{\n\
                            BTREE_PROCESS_CHECK_TARGET(struct_tree, index);\n\
                            if ((struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RUNNING) ||\n\
                                (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RE_EXECUTE))\n\
                            {\n\
                                if (node_struct->decorator_node.ties_node.times <= 0)\n\
                                {\n\
                                    status = BTREE_DEFINITION_STATUS_FAIL;\n\
                                    break;\n\
                                }\n\n\
                                *node_struct->decorator_node.ties_node.local = node_struct->decorator_node.ties_node.times - 1;\n\n\
                                struct_tree->node_index = node_struct->decorator_node.target_index;\n\n\
                                mask = (0b11 << (index_status_key));\n\
                                value_status = struct_tree->nodes_status[index_status_position] & (~mask);\n\
                                struct_tree->nodes_status[index_status_position] = (value_status) | (0b00 << (index_status_key));\n\
                                struct_tree->last_node_state = BTREE_DEFINITION_STATUS_RUNNING;\n\n\
                                return BTREE_DEFINITION_STATUS_RUNNING;\n\
                            }\n\
                            else if (*node_struct->decorator_node.ties_node.local > BTREE_PROCESS_MIN_ATTEMPTS)\n\
                            {\n\
                                *node_struct->decorator_node.ties_node.local -= 1;\n\
                                struct_tree->node_index = node_struct->decorator_node.target_index;\n\
                                status = BTREE_DEFINITION_STATUS_RUNNING;\n\n\
                                clear_index = struct_tree->node_index;\n\n\
                                do\n\
                                {\n\
                                    key = (clear_index % 16) * 2;\n\
                                    position = clear_index / 16;\n\
                                    nodes_status = struct_tree->nodes_status[position];\n\
                                    mask = (0b11 << (key));\n\
                                    new_value = (nodes_status & (~mask));\n\
                                    struct_tree->nodes_status[position] = (new_value) | (0b11 << (key));\n\
                                    clear_index += 1;\n\
                                } while (clear_index <= node_struct->decorator_node.ties_node.node_limit);\n\
                            }\n\
                            else\n\
                            {\n\
                                status = struct_tree->last_node_state;\n\
                                *node_struct->decorator_node.ties_node.local = BTREE_PROCESS_MIN_ATTEMPTS;\n\
                            }\n\n\
                            break;\n\
                        }\n\n"
            else:
                text += "" #TODO: realizar testes sem reativo
        if self.have_keep_running_until_failured:
            text += "case BTREE_DEFINITION_NODE_KEEP_RUNNING_UNTIL_FAILURE:\n"
            if self.is_reactive:
                text += "case BTREE_DEFINITION_NODE_REACTIVE_KEEP_RUNNING_UNTIL_FAILURE:\n\
                         {\n\
                             BTREE_PROCESS_CHECK_TARGET(struct_tree, index);\n\
                             if ((struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RUNNING) ||\n\
                                 (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_FAIL))\n\
                             {\n\n\
                                 struct_tree->node_index = node_struct->decorator_node.target_index;\n\n\
                                 mask = (0b11 << (index_status_key));\n\
                                 value_status = struct_tree->nodes_status[index_status_position] & (~mask);\n\
                                  struct_tree->nodes_status[index_status_position] = (value_status) | (0b00 << (index_status_key));\n\
                                 clear_index = struct_tree->node_index;\n\n\
                                 do\n\
                                 {\n\
                                     key = (clear_index % 16) * 2;\n\
                                     position = clear_index / 16;\n\
                                     nodes_status = struct_tree->nodes_status[position];\n\
                                     mask = (0b11 << (key));\n\
                                     new_value = (nodes_status & (~mask));\n\
                                     struct_tree->nodes_status[position] = (new_value) | (0b11 << (key));\n\
                                     clear_index += 1;\n\
                                 } while (clear_index < node_struct->decorator_node.ties_node.node_limit);\n\n\
                                 return BTREE_DEFINITION_STATUS_RUNNING;\n\
                             }\n\
                             else\n\
                             {\n\
                                 status = struct_tree->last_node_state;\n\
                             }\n\n\
                             break;\n\
                         }\n\n"
            else:
                text += "" #TODO: Testar sem nós reativos
        if self.have_inverter:
            text += "case BTREE_DEFINITION_NODE_INVERTER:\n"
            if self.is_reactive:
                text += "case BTREE_DEFINITION_NODE_REACTIVE_INVERTER:\n\
                        {\n\
                            BTREE_PROCESS_CHECK_TARGET(struct_tree, index);\n\n\
                            if (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_SUCCESS)\n\
                            {\n\
                                status = BTREE_DEFINITION_STATUS_FAIL;\n\
                            }\n\
                            else if (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_FAIL)\n\
                            {\n\
                                status = BTREE_DEFINITION_STATUS_SUCCESS;\n\
                            }\n\
                            else\n\
                            {\n\
                                struct_tree->node_index = node_struct->decorator_node.target_index;\n\
                                status = BTREE_DEFINITION_STATUS_RUNNING;\n\
                            }\n\
                            break;\n\
                        }\n\n"
            else:
                text += "" #TODO: Testar sem nós reativos
        if self.have_force_success:
            text += "case BTREE_DEFINITION_NODE_FORCE_SUCCESS:\n"
            if self.is_reactive:
                text += "case BTREE_DEFINITION_NODE_REACTIVE_FORCE_SUCCESS:\n\
                         {\n\
                             BTREE_PROCESS_CHECK_TARGET(struct_tree, index);\n\n\
                             if (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RUNNING)\n\
                             {\n\
                                 struct_tree->node_index = node_struct->decorator_node.target_index;\n\
                                 status = BTREE_DEFINITION_STATUS_RUNNING;\n\
                             }\n\
                             else if (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RE_EXECUTE)\n\
                             {\n\
                                 struct_tree->node_index = node_struct->decorator_node.target_index;\n\
                                 status = BTREE_DEFINITION_STATUS_RUNNING;\n\
                             }\n\
                             else\n\
                             {\n\
                                 status = BTREE_DEFINITION_STATUS_SUCCESS;\n\
                             }\n\
                             break;\n\
                         }\n\n"
            else:
                text += "" #TODO: Testar sem nós reativos
                
        if self.have_force_fail:
            text += "case BTREE_DEFINITION_NODE_FORCE_FAIL:\n"
            if self.is_reactive:
                text += "case BTREE_DEFINITION_NODE_REACTIVE_FORCE_FAIL:\n\
                         {\n\
                             BTREE_PROCESS_CHECK_TARGET(struct_tree, index);\n\n\
                             if (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RUNNING)\n\
                             {\n\
                                 struct_tree->node_index = node_struct->decorator_node.target_index;\n\
                                 status = BTREE_DEFINITION_STATUS_RUNNING;\n\
                             }\n\
                             else if (struct_tree->last_node_state == BTREE_DEFINITION_STATUS_RE_EXECUTE)\n\
                             {\n\
                                 struct_tree->node_index = node_struct->decorator_node.target_index;\n\
                                 status = BTREE_DEFINITION_STATUS_RUNNING;\n\
                             }\n\
                             else\n\
                             {\n\
                                 status = BTREE_DEFINITION_STATUS_FAIL;\n\
                             }\n\
                             break;\n\
                         }\n\n"
            else:
                text += "" #TODO: Testar sem nós reativos
                
        if self.have_action_timeout:
            text += "case BTREE_DEFINITION_NODE_ACTION_TIMEOUT:\n"
            if self.is_reactive:
                text += "case BTREE_DEFINITION_NODE_REACTIVE_ACTION_TIMEOUT:\n"
            text += "{\n\
                         status = btree_common_action_timeout(node_struct->decorator_node.timeout_ms);\n\
                         break;\n\
                     }\n\n"
        text += "default:\n\
                {\n\
                    return BTREE_DEFINITION_STATUS_ERROR;\n\
                }\n\
                }\n\n"
        
        if self.is_reactive:
            text += "mask = (0b11 << (index_status_key));\n\
                     value_status = struct_tree->nodes_status[index_status_position] & (~mask);\n\n"
        
        text += "if ((status == BTREE_DEFINITION_STATUS_SUCCESS))\n\
                {\n\
                    struct_tree->node_index = node_struct->st_index;\n"
        
        if ((self.is_reactive) and ((self.have_retry_until_sucess) or (self.have_reapeat) or 
                                    (self.have_keep_running_until_failured) or (self.have_force_fail))):
            text += "if ((node_type >= BTREE_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT) && (node_type <= BTREE_DEFINITION_NODE_REACTIVE_FORCE_FAIL))\n\
                    {\n\
                        struct_tree->nodes_status[index_status_position] = (value_status) | (0b11 << (index_status_key));\n\
                    }\n\
                    else\n\
                    {\n\
                        struct_tree->nodes_status[index_status_position] = (value_status) | (0b01 << (index_status_key));\n\
                    }\n\n"
        
        text += "}\n\
                else if ((status == BTREE_DEFINITION_STATUS_FAIL))\n\
                {\n\
                    struct_tree->node_index = node_struct->ft_index;\n"
        
        if ((self.is_reactive) and ((self.have_retry_until_sucess) or (self.have_reapeat) or 
                                    (self.have_keep_running_until_failured) or (self.have_force_fail))):
            text += "if ((node_type >= BTREE_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT) && (node_type <= BTREE_DEFINITION_NODE_REACTIVE_FORCE_FAIL))\n\
                    {\n\
                        struct_tree->nodes_status[index_status_position] = (value_status) | (0b11 << (index_status_key));\n\
                    }\n\
                    else\n\
                    {\n\
                        struct_tree->nodes_status[index_status_position] = (value_status) | (0b10 << (index_status_key));\n\
                    }\n\n"
            
        text += "}\n\
                else\n\
                {\n\
                    struct_tree->nodes_status[index_status_position] = (value_status) | (0b00 << (index_status_key));\n\
                }\n\n\
                struct_tree->last_node_state = BTREE_DEFINITION_STATUS_RUNNING;\n"
        
        if self.is_reactive:
            text += "if (index > struct_tree->node_index)\n\
                    {\n\
                        struct_tree->last_node_state = status;\n\
                        key = (struct_tree->node_index % 16) * 2;\n\
                        position = struct_tree->node_index / 16;\n\
                        nodes_status = struct_tree->nodes_status[position];\n\
                        mask = (0b11 << (key));\n\
                        new_value = (nodes_status & (~mask));\n\
                        if (status == BTREE_DEFINITION_STATUS_SUCCESS)\n\
                        {\n\
                            struct_tree->nodes_status[position] = (new_value) | (0b01 << (key));\n\
                        }\n\
                        else if (status == BTREE_DEFINITION_STATUS_FAIL)\n\
                        {\n\
                            struct_tree->nodes_status[position] = (new_value) | (0b10 << (key));\n\
                        }\n\
                    }\n\n"
        
        text += "return status;\n\
                 }\n"
        
    def create_manager(self):
        text = "/**\n\
                 * @file btree_process.c\n\
                 * @author Renilson Almeida (renilson.123@hotmail.com)\n\
                 * @brief Behavior tree process.\n\
                 * @version 1.1\n"
        text += commom_header
        text += "#include \"btree_manager.h\"\n\
                 #include \"test_btree_common.h\"\n\n"
        
        if self.is_reactive:
            text += "btree_definition_status_t btree_manager_simple_tick_tree(btree_definition_tree_data_t *struct_tree)\n\
                    {\n\
                        if (struct_tree == NULL)\n\
                        {\n\
                            return BTREE_DEFINITION_STATUS_ERROR;\n\
                        }\n\n\
                        btree_index_t node_index = struct_tree->node_index;\n\
                        btree_index_t index = struct_tree->node_index;\n\
                        btree_index_t index_status_key = 0;\n\
                        uint32_t index_status_position = 0;\n\
                        uint32_t mask = 0;\n\
                        uint32_t value_status = struct_tree->nodes_status[BTREE_DEFINITON_NODE_FIRST_INDEX];\n\n\
                        index = struct_tree->node_index;\n\
                        index_status_key = (struct_tree->node_index % 16) * 2;\n\
                        index_status_position = struct_tree->node_index / 16;\n\
                        value_status = struct_tree->nodes_status[index_status_position];\n\
                        mask = (0b11 << (index_status_key));\n\n\
                        return btree_process_node(struct_tree, index_status_key, index_status_position);\n\
                    }\n\n\
                    btree_definition_status_t btree_manager_tick_reactive_tree(btree_definition_tree_data_t *struct_tree)\n\
                    {\n\
                        uint8_t check_node = 0;\n\
                        btree_definition_status_t tree_status = BTREE_DEFINITION_STATUS_SUCCESS;\n\
                        btree_definition_node_type_t node_type = BTREE_DEFINITION_NODE_CONDITION;\n\
                        btree_index_t node_index = struct_tree->node_index;\n\
                        btree_index_t index = struct_tree->node_index;\n\
                        btree_index_t index_status_key = 0;\n\
                        uint32_t index_status_position = 0;\n\
                        uint32_t mask = 0;\n\
                        uint32_t value_updated = 0;\n\
                        uint32_t value_status = struct_tree->nodes_status[BTREE_DEFINITON_NODE_FIRST_INDEX];\n\n\
                        if (struct_tree == NULL)\n\
                        {\n\
                            return BTREE_DEFINITION_STATUS_ERROR;\n\
                        }\n\n\
                        struct_tree->node_index = 0;\n\n\
                        while (struct_tree->node_index < node_index)\n\
                        {\n\
                            node_type = struct_tree->tree[struct_tree->node_index].node_type;\n\
                            index = struct_tree->node_index;\n\
                            index_status_key = (struct_tree->node_index % 16) * 2;\n\
                            index_status_position = struct_tree->node_index / 16;\n\
                            value_status = struct_tree->nodes_status[index_status_position];\n\
                            mask = (0b11 << (index_status_key));\n\
                            check_node = (value_status & mask) >> index_status_key;\n\n\
                            if ((node_type & BTREE_DEFINITION_NODE_REACTIVE_NODES) && (check_node != BTREE_DEFINITION_STATUS_RUNNING))\n\
                            {\n\
                                if (((node_type >= BTREE_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT) && (node_type <= BTREE_DEFINITION_NODE_REACTIVE_FORCE_FAIL)) || ((node_type >= BTREE_DEFINITION_NODE_DECORATOR_TIMEOUT) && (node_type <= BTREE_DEFINITION_NODE_FORCE_FAIL)))\n\
                                {\n\
                                    struct_tree->last_node_state = check_node;\n\
                                }\n\n\
                                tree_status = btree_process_node(struct_tree, index_status_key, index_status_position);\n\
                                if (tree_status == BTREE_DEFINITION_STATUS_STAND_BY)\n\
                                {\n\
                                    return BTREE_DEFINITION_STATUS_STAND_BY;\n\
                                }\n\
                                continue;\n\
                            }\n\n\
                            index_status_key = (struct_tree->node_index % 16) * 2;\n\
                            index_status_position = struct_tree->node_index / 16;\n\
                            value_status = struct_tree->nodes_status[index_status_position];\n\
                            mask = (0b11 << (index_status_key));\n\
                            check_node = (value_status & mask) >> index_status_key;\n\n\
                            if ((struct_tree->node_index < node_index) && (check_node != BTREE_DEFINITION_STATUS_RE_EXECUTE))\n\
                            {\n\
                                if (check_node == BTREE_DEFINITION_STATUS_SUCCESS)\n\
                                {\n\
                                    struct_tree->node_index = struct_tree->tree[struct_tree->node_index].st_index;\n\
                                }\n\
                                else if ((check_node == BTREE_DEFINITION_STATUS_RUNNING) || (check_node == BTREE_DEFINITION_STATUS_RE_EXECUTE))\n\
                                {\n\
                                    struct_tree->node_index = struct_tree->tree[struct_tree->node_index].decorator_node.target_index;\n\
                                }\n\
                                else if (check_node == BTREE_DEFINITION_STATUS_FAIL)\n\
                                {\n\
                                    struct_tree->node_index = struct_tree->tree[struct_tree->node_index].ft_index;\n\
                                }\n\n\
                                if (index > struct_tree->node_index)\n\
                                {\n\
                                    struct_tree->last_node_state = check_node;\n\
                                    index_status_key = (struct_tree->node_index % 16) * 2;\n\
                                    index_status_position = struct_tree->node_index / 16;\n\
                                    value_status = struct_tree->nodes_status[index_status_position];\n\
                                    mask = (0b11 << (index_status_key));\n\
                                    value_updated = (value_status & (~mask));\n\
                                    if (check_node == BTREE_DEFINITION_STATUS_SUCCESS)\n\
                                    {\n\
                                        struct_tree->nodes_status[index_status_position] = (value_updated) | (0b01 << (index_status_key));\n\
                                    }\n\
                                    else if (check_node == BTREE_DEFINITION_STATUS_FAIL)\n\
                                    {\n\
                                        struct_tree->nodes_status[index_status_position] = (value_updated) | (0b10 << (index_status_key));\n\
                                    }\n\
                                }\n\
                            }\n\
                        }\n\n\
                        node_type = struct_tree->tree[struct_tree->node_index].node_type;\n\
                        index_status_key = (struct_tree->node_index % 16) * 2;\n\
                        index_status_position = struct_tree->node_index / 16;\n\
                        value_status = struct_tree->nodes_status[index_status_position];\n\
                        mask = (0b11 << (index_status_key));\n\
                        check_node = (value_status & mask) >> index_status_key;\n\n\
                        if (((node_type >= BTREE_DEFINITION_NODE_REACTIVE_DECORATOR_TIMEOUT) && (node_type <= BTREE_DEFINITION_NODE_REACTIVE_FORCE_FAIL)) || ((node_type >= BTREE_DEFINITION_NODE_DECORATOR_TIMEOUT) && (node_type <= BTREE_DEFINITION_NODE_FORCE_FAIL)))\n\
                        {\n\
                            struct_tree->last_node_state = check_node;\n\
                        }\n\n\
                        tree_status = btree_process_node(struct_tree, index_status_key, index_status_position);\n\n\
                        return tree_status;\n\
                    }\n\n"
        text += "btree_definition_status_t btree_manager_reset_tree(btree_definition_tree_data_t *struct_tree)\n\
                 {\n\
                     if (struct_tree == NULL)\n\
                     {\n\
                         return BTREE_DEFINITION_STATUS_ERROR;\n\
                     }\n\n\
                     struct_tree->last_node_state = BTREE_DEFINITION_STATUS_RUNNING;\n\
                     struct_tree->node_index = BTREE_DEFINITON_NODE_FIRST_INDEX;\n\n\
                     return BTREE_DEFINITION_STATUS_SUCCESS;\n\
                  }\n"
        if self.is_reactive:
            text += "btree_definition_status_t btree_manager_clear_nodes(btree_definition_tree_data_t *struct_tree)\n\
                     {\n\
                         if (struct_tree == NULL)\n\
                         {\n\
                             return BTREE_DEFINITION_STATUS_ERROR;\n\
                         }\n\n\
                         memset();\n\n\
                         return BTREE_DEFINITION_STATUS_SUCCESS;\n\
                     }\n"
        