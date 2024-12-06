import os
from datetime import date

class ARCHIVE_CREATOR:
    def __init__(self):
        self.text = ""
        self.name = ""
        self.email = ""
        self.version = ""
        self.copyrights = ""
        self.project = ""
        self.project_id = ""

    def get_project_id(self):
        return self.project_id

    def get_output_folder(self):
        return self.output_folder

    def set_text(self, project_id = None, name = None, email = None, version = None, copyrights = None, project = None):
        self.project_id = project_id if project_id != None else input("Put your Project ID:")
        self.name = name if name != None else input("Put your name:")
        self.email = email if email != None else input("Put your email:")
        self.version = version if version != None else input("Put your project version:")
        self.copyrights = copyrights if copyrights != None else input("Put your copyrights:")
        self.project = project if project != None else input("Put your project ID:")

    def archive_header(self, archive, src_file = None):
        today          = date.today()
        init           = "/**\n"
        file_name      = f" * @file {self.project.lower()}_bht_{(archive.lower())}." 
        file_name     += "h\n" if src_file == None else "c\n"
        author         = f" * @author {self.name} " if self.name != None else ""
        author        += f"({self.email.lower()})" if self.email != None else ""
        author        += "\n"
        value          = f"das variáveis comuns do {self.project.lower()}.\n" if archive == "common" else f"da behavior tree {archive.lower()}.\n"
        brief          = f" * @brief Header da interface " if src_file == None else " * @brief Interface "
        brief         += value
        version        = f" * @version {self.version}\n" if (self.version != None) else ""
        date_generated = f' * @date {today.strftime("%d/%m/%Y")}\n'
        copyright      = f" *\n * @copyright Copyright © {today.year} {self.copyrights}. Todos os direitos reservados.\n" if self.copyrights != None else ""
        end            = " *\n */\n\n"
        self.text      = init + file_name + author + brief + version + date_generated + copyright + end

    def archive_top(self, archive, src_file = False, includes = None):
        if src_file == False:
            self.text    += f"#ifndef {self.project.upper()}_BHT_{archive.upper()}_H_\n"
            self.text    += f"#define {self.project.upper()}_BHT_{archive.upper()}_H_\n\n"
            if archive == 'common':
                self.text    += f'#include "bht_definition.h"\n'
            else:
                self.text    += f'#include "{self.project.lower()}_bht_blackboard.h"\n'
        else:
            self.text    += f"#include \"{self.project.lower()}_bht_{archive.lower()}.h\"\n"
        if includes != None:
            for i in includes:
                self.text    += f"#include \"{self.project.lower()}_bht_{i.lower()}.h\"\n"
        self.text += "\n"
            
    def tree_vector(self, archive, bt_array):
        text          = ""
        text         += "/**\n"
        text         += f" * @brief Árvore do {(archive.lower())}.\n"
        text         += " *\n */\n"
        text         += f"const tc_bht_definition_node_t tc_{self.project.lower()}_bht_{(archive.lower())}[TC_{self.project.upper()}_BHT_{archive.upper()}_SIZE] = \n"
        text         += "{\n"
        for item in bt_array:
            index          = item[0]
            node_type      = item[1]
            if isinstance(item[2], str) and item[2][0] == '&':
                item[2]    =  f"&tc_{self.project.lower()}_bht_{archive.lower()}_" + item[2][1:]
            params         = ', '.join(map(str, item[2:]))
            text     += f"         [{index}] = {node_type}({params}), \\\n"
        text         += "};\n\n"
        return text

    def tree_general_extern(self, id):
        init_comment       = "/**\n"
        tree_brief         = " * @brief Referência as árvore que contém todas as sub árvores.\n"
        end_comment        = " *\n */\n"
        self.text         += init_comment + tree_brief + end_comment
        self.text         += f"extern const tc_bht_definition_tree_list_t tc_{self.project.lower()}_bht_{(id.lower())}[];\n\n"
        struct_brief       = " * @brief Referência a estrutura de controle da árvore.\n"
        self.text         +=  init_comment + struct_brief + end_comment
        self.text         += f"extern tc_bht_definition_tree_data_t tc_{self.project.lower()}_bht_{id.lower()};\n\n"

    def tree_general(self, id, includes, trees_size):
        init_comment       = "/**\n"
        tree_brief         = " * @brief Árvore que contém todas as sub árvores.\n"
        end_comment        = " *\n */\n"
        self.text         += init_comment + tree_brief + end_comment
        self.text         += f"const tc_bht_definition_tree_list_t tc_{self.project.lower()}_bht_{(id.lower())} [] = \n"
        self.text         += "{\n"
        self.text         += "".join(f'    {{TC_{self.project.upper()}_BHT_{i.upper()}_SIZE, tc_{self.project.lower()}_bht_{i.lower()}}}, \n' for i in includes)
        self.text         += "};\n\n"
        struct_brief       = " * @brief Estrutura de controle da árvore.\n"
        self.text         +=  init_comment + struct_brief + end_comment
        self.text         += f"tc_bht_definition_tree_data_t tc_{self.project.lower()}_bht_{id.lower()} = "
        self.text         += "{\n"
        self.text         += "    .last_node_state = TC_BHT_DEFINITION_STATUS_RUNNING,\n"
        self.text         += "    .node_index      = TC_BHT_DEFINITON_NODE_ROOT_INDEX,\n"
        self.text         += "    .tree_index      = TC_BHT_DEFINITON_NODE_ROOT_INDEX,\n"
        self.text         += f"    .tree_list_size  = sizeof(tc_{self.project.lower()}_bht_{(id.lower())}) / sizeof(tc_{self.project.lower()}_bht_{(id.lower())}[0]),\n"
        self.text         += f"    .tree_list       = tc_{self.project.lower()}_bht_{(id.lower())},\n"
        self.text         += "};\n\n"

    def create_declaration_commented(self, archive, functions):
        for function in functions:
            self.text += '/**\n'
            self.text += '* @brief \n'
            self.text += '*\n'
            self.text += '* @retval TC_BHT_DEFINITION_STATUS_SUCCESS para sucesso;\n'
            self.text += '* @retval TC_BHT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;\n'
            self.text += '* @retval TC_BHT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;\n'
            self.text += '*/\n'
            self.text += f"static tc_bht_definition_status_t tc_{self.project.lower()}_bht_{archive.lower()}_{function}(void);\n\n"

    def create_declaration_empty(self, archive, functions):
        for function in functions:
            self.text += f"static tc_bht_definition_status_t tc_{self.project.lower()}_bht_{archive.lower()}_{function}(void)\n"
            self.text += "{\n\n}\n\n"

    def create_inc(self, archive, tree_size):
        self.archive_header(archive)
        self.archive_top(archive)
        self.text += "/**\n"
        self.text += f" * @brief Tamanho da árvore {archive.lower()}.\n"
        self.text += " *\n */\n"
        self.text += f"#define TC_{self.project.upper()}_BHT_{archive.upper()}_SIZE {tree_size + 1}\n\n"
        self.text += "/**\n"
        self.text += f" * @brief Referência a árvore {archive.lower()}.\n"
        self.text += " *\n */\n"
        self.text += f"extern const tc_bht_definition_node_t tc_{self.project.lower()}_bht_{archive.lower()}[TC_{self.project.upper()}_BHT_{archive.upper()}_SIZE];\n\n"
        self.archive_end(archive)

    def create_src(self, archive, functions, text):
        self.archive_header(archive, src_file=True)
        self.archive_top(archive, src_file=True)
        if functions != None:
            self.create_declaration_commented(archive, functions)
        self.text += text
        if functions != None:
            self.create_declaration_empty(archive, functions)
        self.archive_end(archive, src=True)

    def archive_end(self, archive, src = None, endif = None):
        endif      = f"#endif /* {self.project.upper()}_BHT_{archive.upper()}_H_ */" if src == None and endif == None else ""
        self.text += endif
        local = f'Output/include/{self.project.upper()}/bht' if src == None else f'Output/src/{self.project.upper()}/bht'
        archive_name = f'{self.project.lower()}_bht_{archive}.h' if src == None else f'{self.project.lower()}_bht_{archive}.c'
        os.makedirs(local, exist_ok=True) 
        archive_address = local + '/' + archive_name
        if os.path.exists(archive_address):
            text_generate_lines = self.text.splitlines()
            j = 0
            with open(archive_address, 'r', encoding='utf-8') as archive_text:
                text_lines = archive_text.readlines()
            for i in range(len(text_lines)):
                fffff = text_generate_lines[j]
                ffffffff = text_lines[i].strip()
                if (j < len(text_generate_lines)) and (text_lines[i].strip() in text_generate_lines[j]):
                    j += 1
        output_bht = os.path.join(local, archive_name)
        with open(output_bht, 'w', encoding='utf-8') as file:
            file.write(self.text)
        self.text = ""
    
    def generate_general_tree_inc(self, trees_size):
        archive_name = f"ctrl_{self.project_id}"
        self.archive_header(archive_name)
        self.archive_top(archive_name)
        self.tree_general_extern(archive_name)
        self.archive_end(archive_name)

    def generate_general_tree_src(self, includes, trees_size):
        archive_name = f"ctrl_{self.project_id}"
        self.archive_header(archive_name, src_file=True)
        self.archive_top(archive_name, self.project_id, includes)
        self.tree_general(archive_name, includes, trees_size)
        self.archive_end(archive_name, src=True)

    def generate_blackboard_inc(self):
        self.text  = "/**\n"
        self.text += f" * @file {self.project.lower()}_bht_blackboard.h\n"
        self.text += f" * @author {self.name} " if self.name != None else ""
        self.text += f"({self.email.lower()})\n" if self.email != None else ""
        self.text += " * @brief Header da interface do blackboard.\n"
        self.text += f" * @version {self.version}\n" if (self.version != None) else ""
        self.text += f" * @date {date.today().strftime("%d/%m/%Y")}\n"
        self.text += " *\n"
        self.text += f" * @copyright Copyright © {date.today().year} {self.copyrights}. Todos os direitos reservados.\n" if self.copyrights != None else ""
        self.text += " *\n"
        self.text += " */\n\n"
        self.text += f"#ifndef {self.project.upper()}_BHT_BLACKBOARD_H_\n"
        self.text += f"#define {self.project.upper()}_BHT_BLACKBOARD_H_\n\n" 
        self.text += f"#include \"{self.project.lower()}_bht_common.h\"\n\n"
        self.text += "/**\n"
        self.text += " * @brief Tipos de buffers na blackboard.\n"
        self.text += " * \n"
        self.text += " */\n"
        self.text += f'typedef enum tc_{self.project.lower()}_bht_blackboard_buffer\n'
        self.text += '{\n'
        self.text += f'    __TC_{self.project.upper()}_BHT_BLACKBOARD_BUFFER_AMOUNT,'
        self.text += '\n}'
        self.text += f' tc_{self.project.lower()}_bht_blackboard_buffer_t;\n\n'
        self.text += "/**\n"
        self.text += " * @brief Tipos de valores na blackboard.\n"
        self.text += " * \n"
        self.text += " */\n"
        self.text += f'typedef enum tc_{self.project.lower()}_bht_blackboard_value\n'
        self.text += '{\n'
        self.text += f'    __TC_{self.project.upper()}_BHT_BLACKBOARD_VALUE_AMOUNT,'
        self.text += '\n}'
        self.text += f' tc_{self.project.lower()}_bht_blackboard_value_t;\n\n'
        self.text += "/**\n"
        self.text += " * @brief Salva um buffer específico.\n"
        self.text += " * \n"
        self.text += " * @param id Identificação do buffer a ser usado.\n"
        self.text += " * @param buffer [in] Buffer contendo os dados atualizados.\n"
        self.text += " * @param buffer_size Tamanho do buffer.\n *\n"
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_SUCCESS para sucesso,\n'
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_FAIL caso tempo máximo excedido,\n'
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada.\n'
        self.text += " */\n"
        self.text += f'tc_bht_definition_status_t tc_{self.project.lower()}_bht_blackboard_set_buffer(tc_{self.project.lower()}_bht_blackboard_buffers_t id, uint8_t *buffer, uint8_t buffer_size);\n\n'
        self.text += "/**\n"
        self.text += " * @brief Salva um item específico.\n"
        self.text += " * \n"
        self.text += " * @param id Identificação do item a ser usado.\n"
        self.text += " * @param value Novo item do item.\n *\n"
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_SUCCESS para sucesso,\n'
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_FAIL caso tempo máximo excedido,\n'
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada.\n'
        self.text += " */\n"
        self.text += f'tc_bht_definition_status_t tc_{self.project.lower()}_bht_blackboard_set_value(tc_{self.project.lower()}_bht_blackboard_values_t id, uint8_t value);\n\n'
        self.text += "/**\n"
        self.text += " * @brief Pega um buffer específico.\n"
        self.text += " * \n"
        self.text += " * @param id Identificação do buffer a ser usado.\n"
        self.text += " * @param buffer [out] Ponteiro que irá guardar o buffer.\n"
        self.text += " * @param buffer_len [out] Ponteiro que irá guardar o tamanho do buffer.\n *\n"
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_SUCCESS para sucesso,\n'
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_FAIL caso tempo máximo excedido,\n'
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada.\n'
        self.text += " */\n"
        self.text += f'tc_bht_definition_status_t tc_{self.project.lower()}_bht_blackboard_get_buffer(tc_{self.project.lower()}_bht_blackboard_buffers_t id, uint8_t *buffer, uint8_t *buffer_len);\n\n'
        self.text += "/**\n"
        self.text += " * @brief Pega um item específico.\n"
        self.text += " * \n"
        self.text += " * @param id Identificação do item a ser usado.\n"
        self.text += " * @param value [out] Ponteiro para guardar o item.\n *\n"
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_SUCCESS para sucesso,\n'
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_FAIL caso tempo máximo excedido,\n'
        self.text += ' * @retval TC_BHT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada.\n'
        self.text += " */\n"
        self.text += f'tc_bht_definition_status_t tc_{self.project.lower()}_bht_blackboard_get_value(tc_{self.project.lower()}_bht_blackboard_values_t id, uint32_t *value);\n\n'
        self.text += f"#endif /* {self.project.upper()}_BHT_BLACKBOARD_H_ */\n"

    def generate_blackboard_src(self):
        self.text  = "/**\n"
        self.text += f" * @file {self.project.lower()}_bht_blackboard.c\n"
        self.text += f" * @author {self.name} " if self.name != None else ""
        self.text += f"({self.email.lower()})\n" if self.email != None else ""
        self.text += " * @brief Interface do blackboard.\n"
        self.text += f" * @version {self.version}\n" if (self.version != None) else ""
        self.text += f" * @date {date.today().strftime("%d/%m/%Y")}\n"
        self.text += " *\n"
        self.text += f" * @copyright Copyright © {date.today().year} {self.copyrights}. Todos os direitos reservados.\n" if self.copyrights != None else ""
        self.text += " *\n"
        self.text += " */\n"
        self.text += "\n"
        self.text += f"#include \"{self.project.lower()}_bht_blackboard.h\"\n\n"
        self.text += "/**\n"
        self.text += f" * @brief Estrutura com dados pertinentes da blackboard da árvore {self.project.upper()}.\n"
        self.text += " * \n"
        self.text += " */\n"
        self.text += f"static struct tc_{self.project.lower()}_bht_blackboard\n"
        self.text += "{\n\n"
        self.text += "} self = \n"
        self.text += "{\n\n"
        self.text += "};\n\n"
        self.text += f'tc_bht_definition_status_t tc_{self.project.lower()}_bht_blackboard_set_buffer(tc_{self.project.lower()}_bht_blackboard_buffers_t id, uint8_t *buffer)\n'
        self.text += '{\n'
        self.text += '    if(buffer == NULL)\n'
        self.text += '    {\n'
        self.text += '        return TC_BHT_DEFINITION_STATUS_FAIL;\n'
        self.text += '    }\n\n'
        self.text += '    switch(id)\n'
        self.text += '    {\n'
        self.text += '        default: {\n\n'
        self.text += '            break;\n'
        self.text += '        }\n'
        self.text += '    }\n'
        self.text += '    \n'
        self.text += '    return TC_BHT_DEFINITION_STATUS_SUCCESS;\n'
        self.text += '}\n\n'
        self.text += f'tc_bht_definition_status_t tc_{self.project.lower()}_bht_blackboard_set_value(tc_{self.project.lower()}_bht_blackboard_values_t id, uint8_t value)\n'
        self.text += '{\n'
        self.text += '    switch(id)\n'
        self.text += '    {\n'
        self.text += '        default: {\n\n'
        self.text += '            break;\n'
        self.text += '        }\n'
        self.text += '    }\n'
        self.text += '    \n'
        self.text += '    return TC_BHT_DEFINITION_STATUS_SUCCESS;\n'
        self.text += '}\n\n'
        self.text += f'tc_bht_definition_status_t tc_{self.project.lower()}_bht_blackboard_get_buffer(tc_{self.project.lower()}_bht_blackboard_buffers_t id, uint8_t *buffer, uint8_t *buffer_len)\n'
        self.text += '{\n'
        self.text += '    switch(id)\n'
        self.text += '    {\n'
        self.text += '        default: {\n\n'
        self.text += '            break;\n'
        self.text += '        }\n'
        self.text += '    }\n'
        self.text += '    \n'
        self.text += '    return TC_BHT_DEFINITION_STATUS_SUCCESS;\n'
        self.text += '}\n\n'
        self.text += f'tc_bht_definition_status_t tc_{self.project.lower()}_bht_blackboard_get_value(tc_{self.project.lower()}_bht_blackboard_values_t id, uint8_t *value)\n'
        self.text += '{\n'
        self.text += '    switch(id)\n'
        self.text += '    {\n'
        self.text += '        default: {\n\n'
        self.text += '            break;\n'
        self.text += '        }\n'
        self.text += '    }\n'
        self.text += '    \n'
        self.text += '    return TC_BHT_DEFINITION_STATUS_SUCCESS;\n'
        self.text += '}\n\n'

    def generate_blackboard(self):
        self.generate_blackboard_inc()
        self.archive_end('blackboard', endif = False)
        self.generate_blackboard_src()
        output_src = os.path.join(f'Output/src/{self.project.upper()}/bht', f'{self.project.lower()}_bht_blackboard.c')
        with open(output_src, 'w', encoding='utf-8') as file:
            file.write(self.text)
        self.text = ""

    def generate_common_inc(self, max_ramification_attempts):
        self.archive_header("common")
        self.archive_top("common")
        self.text += "/**\n"
        self.text += " * @brief Número máximo de nós de tentativas em uma ramificação.\n"
        self.text += " *\n */\n"
        self.text += f"#define TC_{self.project.upper()}_BHT_COMMON_ATTEMPTS_SIZE {max_ramification_attempts}\n\n"
        self.text += "/**\n"
        self.text += " * @brief Referência o array de tentativas.\n"
        self.text += " *\n */\n"
        self.text += f"extern uint8_t tc_{self.project.lower()}_bht_commom_attempts[TC_{self.project.upper()}_BHT_COMMON_ATTEMPTS_SIZE];\n\n"
        self.archive_end("common")

    def generate_common_src(self):
        self.archive_header("common", src_file=True)
        self.archive_top("common", src_file=True)
        self.text += "/**\n"
        self.text += " * @brief Guarda o número de tentativas dos nós decorators.\n"
        self.text += " *\n */\n"
        self.text += f"uint8_t tc_{self.project.lower()}_bht_commom_attempts[TC_{self.project.upper()}_BHT_COMMON_ATTEMPTS_SIZE];\n\n"
        self.archive_end("common", src=True)

    def generate_common(self, num_max_attempts):
        self.generate_common_inc(num_max_attempts)
        self.generate_common_src()

    def generate_archives(self, archives, text, functions, attempts_max, trees_size):
        for i in range(len(archives)):
            self.create_inc(archives[i], trees_size[i])
            self.create_src(archives[i], functions[i], text[i])
        self.generate_common(attempts_max)
        self.generate_blackboard()
        self.generate_general_tree_inc(trees_size)
        self.generate_general_tree_src(archives, trees_size)