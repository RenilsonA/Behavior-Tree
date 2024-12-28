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

    def set_text(self, project_id = None, name = None, email = None, version = None, copyrights = None, project = None):
        self.project_id = project_id if project_id != None else input("Put your Project ID:")
        self.name = name if name != None else input("Put your name:")
        self.email = email if email != None else input("Put your email:")
        self.version = version if version != None else input("Put your project version:")
        self.copyrights = copyrights if copyrights != None else input("Put your copyrights:")
        self.project = project if project != None else input("Put your project ID:")
        if self.project != "":
            self.project = self.project + "_"

    def archive_header(self, archive, src_file = None):
        today          = date.today()
        self.text      = "/**\n"
        self.text     += f" * @file {self.project.lower()}bt_{(archive.lower())}." 
        self.text     += "h\n" if src_file == None else "c\n"
        if ((self.name != "") and (self.email != "")):
            self.text += f" * @author {self.name} " if self.name != "" else ""
            self.text += f"({self.email.lower()})" if self.email != "" else ""
            self.text += "\n"
        self.text     += f" * @brief Header da interface " if src_file == None else " * @brief Interface "
        self.text     += f"das variáveis comuns do {self.project.lower()}.\n" if archive == "common" else f"da behavior tree {archive.lower()}.\n"
        self.text     += f" * @version {self.version}\n" if (self.version != "") else ""
        self.text     += f' * @date {today.strftime("%d/%m/%Y")}\n'
        self.text     += f" *\n * @copyright Copyright © {today.year} {self.copyrights}. Todos os direitos reservados.\n" if self.copyrights != "" else ""
        self.text     += " *\n */\n\n"

    def archive_top(self, archive, src_file = False, includes = None):
        if src_file == False:
            self.text    += f"#ifndef {self.project.upper()}BT_{archive.upper()}_H_\n"
            self.text    += f"#define {self.project.upper()}BT_{archive.upper()}_H_\n\n"
            if archive == 'common':
                self.text    += f'#include "bt_definition.h"\n'
            else:
                self.text    += f'#include "{self.project.lower()}bt_blackboard.h"\n'
        else:
            self.text    += f"#include \"{self.project.lower()}bt_{archive.lower()}.h\"\n"
        if includes != None:
            for i in includes:
                self.text    += f"#include \"{self.project.lower()}bt_{i.lower()}.h\"\n"
        self.text += "\n"
            
    def tree_vector(self, archive, bt_array):
        text = ""
        for item in bt_array:
            index          = item[0]
            node_type      = item[1]
            if isinstance(item[2], str):
                item[2]    =  f"&{self.project.lower()}" + item[2]
            params         = ', '.join(map(str, item[2:]))
            text     += f"         [{index}] = {node_type}({params}), \\\n"
        return text

    def create_declaration_commented(self, archive, functions):
        for function in functions:
            self.text += '/**\n'
            self.text += '* @brief \n'
            self.text += '*\n'
            self.text += '* @retval BT_DEFINITION_STATUS_SUCCESS para sucesso;\n'
            self.text += '* @retval BT_DEFINITION_STATUS_FAIL caso ainda não tenha recebido a respectiva resposta;\n'
            self.text += '* @retval BT_DEFINITION_STATUS_STAND_BY caso ainda não esteja configurada;\n'
            self.text += '*/\n'
            self.text += f"bt_definition_status_t {self.project.lower()}bt_{archive.lower()}_{function}(void);\n\n"

    def create_declaration_empty(self, archive, functions):
        for function in functions:
            self.text += f"bt_definition_status_t {self.project.lower()}bt_{archive.lower()}_{function}(void)\n"
            self.text += "{\n"
            self.text += "  return BT_DEFINITION_STATUS_SUCCESS;\n}\n\n"

    def create_inc(self, archive, functions):
        self.archive_header(archive)
        self.archive_top(archive)
        if functions != None:
            self.create_declaration_commented(archive, functions)
        self.archive_end(archive)

    def create_src(self, archive, functions):
        self.archive_header(archive, src_file=True)
        self.archive_top(archive, src_file=True)
        if functions != None:
            self.create_declaration_empty(archive, functions)
        self.archive_end(archive, src=True)

    def archive_end(self, archive, src = None, endif = None):
        endif      = f"#endif /* {self.project.upper()}BT_{archive.upper()}_H_ */" if src == None and endif == None else ""
        self.text += endif
        local = f'Output/include/{self.project[:-1].lower()}/bt' if src == None else f'Output/src/{self.project[:-1].lower()}/bt'
        archive_name = '' if self.project.lower() == '' else f'{self.project.lower()}'
        archive_name += f'bt_{archive}.h' if src == None else f'bt_{archive}.c'
        os.makedirs(local, exist_ok=True) 
        output_bht = os.path.join(local, archive_name)
        with open(output_bht, 'w', encoding='utf-8') as file:
            file.write(self.text)
        self.text = ""
    
    def tree_general_inc(self, tree_size):
        self.text         += "/**\n"
        self.text         += f" * @brief Tamanho da árvore {self.project.lower()}.\n"
        self.text         += " *\n */\n"
        self.text         += f"#define {self.project.upper()}BT_ARRAY_SIZE {tree_size}\n\n"
        self.text         += "/**\n"
        self.text         += f" * @brief Array contendo os nós da árvore {self.project[:-1].lower()}.\n"
        self.text         += " *\n */\n"
        self.text         += f"extern const bt_definition_node_t {self.project.lower()}bt_array[{self.project.upper()}BT_ARRAY_SIZE];\n\n"
        self.text         += "/**\n"
        self.text         += f" * @brief Externaliza estrutura de controle da árvore {self.project[:-1].lower()}, caso precise.\n"
        self.text         += " *\n */\n"
        self.text         += f"extern bt_definition_tree_data_t {self.project.lower()}bt_struct;\n\n"

    def tree_general_src(self, bt_array):
        self.text         += "/**\n"
        self.text         += f" * @brief Array contendo os nós da árvore {self.project[:-1].lower()}.\n"
        self.text         += " *\n */\n"
        self.text         += f"const bt_definition_node_t {self.project.lower()}bt_array[{self.project.upper()}BT_ARRAY_SIZE] = \n"
        self.text         += "{\n"
        for item in bt_array:
            self.text     += item
        self.text         += "};\n\n"
        self.text         += "/**\n"
        self.text         += f" * @brief Estrutura de controle da árvore {self.project[:-1].lower()}.\n"
        self.text         += " *\n */\n"
        self.text         += f"bt_definition_tree_data_t {self.project.lower()}bt_struct = "
        self.text         += "{\n"
        self.text         += "    .last_node_state = BT_DEFINITION_STATUS_RUNNING,\n"
        self.text         += "    .node_index      = BT_DEFINITON_NODE_FIRST_INDEX,\n"
        self.text         += "    .condition_index = 0,\n"
        self.text         += f"    .tree_size       = {self.project.upper()}BT_ARRAY_SIZE,\n"
        self.text         += f"    .tree            = {self.project.lower()}bt_array,\n"
        self.text         += "};\n\n"

    def generate_general_tree_inc(self, tree_size):
        archive_name = f"array_{self.project_id}" if self.project_id != "" else "array"
        self.archive_header(archive_name)
        self.archive_top(archive_name)
        self.tree_general_inc(tree_size)
        self.archive_end(archive_name)
        
    def generate_general_tree_src(self, archives, bt_array):
        archive_name = f"array_{self.project_id}" if self.project_id != "" else "array"
        self.archive_header(archive_name, src_file = True)
        self.archive_top(archive_name, src_file = True, includes = archives)
        self.tree_general_src(bt_array)
        self.archive_end(archive_name, src = True)

    def generate_blackboard_inc(self):
        self.text  = "/**\n"
        self.text += f" * @file {self.project.lower()}bt_blackboard.h\n"
        if ((self.name != "") and (self.email != "")):
            self.text += f" * @author {self.name} " if self.name != "" else ""
            self.text += f"({self.email.lower()})\n" if self.email != "" else ""
        self.text += " * @brief Header da interface da blackboard.\n"
        self.text += f" * @version {self.version}\n" if (self.version != "") else ""
        self.text += f" * @date {date.today().strftime('%d/%m/%Y')}\n"
        self.text += " *\n"
        self.text += f" * @copyright Copyright © {date.today().year} {self.copyrights}. Todos os direitos reservados.\n" if self.copyrights != "" else ""
        self.text += " *\n"
        self.text += " */\n\n"
        self.text += f"#ifndef {self.project.upper()}BT_BLACKBOARD_H_\n"
        self.text += f"#define {self.project.upper()}BT_BLACKBOARD_H_\n\n" 
        self.text += f"#include \"{self.project.lower()}bt_common.h\"\n\n"
        self.text += "\n"
        self.text += "/**\n"
        self.text += f" * @brief Estrutura dos dados usado na árvore {self.project.upper()}.\n"
        self.text += " * \n"
        self.text += " */\n"
        self.text += f"struct {self.project.lower()}bt_blackboard\n"
        self.text += "{\n\n};\n\n"
        self.text += "/**\n"
        self.text += f" * @brief Estrutura com dados pertinentes da blackboard da árvore {self.project.upper()}.\n"
        self.text += " * \n"
        self.text += " */\n"
        self.text += f"extern struct {self.project.lower()}bt_blackboard {self.project.lower()}bt_data;\n\n"
        self.text += f"#endif /* {self.project.upper()}BT_BLACKBOARD_H_ */\n"

    def generate_blackboard_src(self):
        self.text  = "/**\n"
        self.text += f" * @file {self.project.lower()}bt_blackboard.c\n"
        if ((self.name != "") and (self.email != "")):
            self.text += f" * @author {self.name} " if self.name != "" else ""
            self.text += f"({self.email.lower()})\n" if self.email != "" else ""
        self.text += " * @brief Interface do blackboard.\n"
        self.text += f" * @version {self.version}\n" if (self.version != "") else ""
        self.text += f" * @date {date.today().strftime('%d/%m/%Y')}\n"
        self.text += " *\n"
        self.text += f" * @copyright Copyright © {date.today().year} {self.copyrights}. Todos os direitos reservados.\n" if self.copyrights != "" else ""
        self.text += " *\n"
        self.text += " */\n"
        self.text += "\n"
        self.text += f"#include \"{self.project.lower()}bt_blackboard.h\"\n\n"
        self.text += "/**\n"
        self.text += f" * @brief Estrutura com dados pertinentes da blackboard da árvore {self.project.upper()}.\n"
        self.text += " * \n"
        self.text += " */\n"
        self.text += f"struct {self.project.lower()}bt_blackboard {self.project.lower()}bt_data = \n"
        self.text += "{\n\n"
        self.text += "};\n"

    def generate_blackboard(self):
        self.generate_blackboard_inc()
        self.archive_end('blackboard', endif = False)
        self.generate_blackboard_src()
        output_src = os.path.join(f'Output/src/{self.project[:-1].lower()}/bt', f'{self.project.lower()}bt_blackboard.c')
        with open(output_src, 'w', encoding='utf-8') as file:
            file.write(self.text)
        self.text = ""

    def generate_common_inc(self, max_ramification_attempts):
        self.archive_header("common")
        self.archive_top("common")
        self.text += "/**\n"
        self.text += " * @brief Número máximo de nós de tentativas em uma ramificação.\n"
        self.text += " *\n */\n"
        self.text += f"#define {self.project.upper()}BT_COMMON_ATTEMPTS_SIZE {max_ramification_attempts}\n\n"
        self.text += "/**\n"
        self.text += " * @brief Referência o array de tentativas.\n"
        self.text += " *\n */\n"
        self.text += f"extern uint8_t {self.project.lower()}bt_commom_attempts[{self.project.upper()}BT_COMMON_ATTEMPTS_SIZE];\n\n"
        self.archive_end("common")

    def generate_common_src(self):
        self.archive_header("common", src_file=True)
        self.archive_top("common", src_file=True)
        self.text += "/**\n"
        self.text += " * @brief Guarda o número de tentativas dos nós decorators.\n"
        self.text += " *\n */\n"
        self.text += f"uint8_t {self.project.lower()}bt_commom_attempts[{self.project.upper()}BT_COMMON_ATTEMPTS_SIZE];\n\n"
        self.archive_end("common", src=True)

    def generate_common(self, num_max_attempts):
        self.generate_common_inc(num_max_attempts)
        self.generate_common_src()

    def generate_archive_tree(self, archive, functions):
        self.create_inc(archive, functions)
        self.create_src(archive, functions)

    def generate_tree_array(self, archives, text, tree_size):
        self.generate_general_tree_inc(tree_size)
        self.generate_general_tree_src(archives, text)

    def generate_archives(self, archives, text, functions, attempts_max, tree_size):
        for i in range(len(functions)):
            self.generate_archive_tree(archives[i], functions[i])
        self.generate_common(attempts_max)
        self.generate_blackboard()
        self.generate_tree_array(archives, text, tree_size)