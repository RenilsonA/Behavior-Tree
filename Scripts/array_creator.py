import os
import xml.etree.ElementTree as ET
from library_creator import ARCHIVE_CREATOR

node_index_invalid = 'TC_BHT_DEFINITION_TREE_UNRELATED'
node_fallback = 'Fallback'
node_sequence = 'Sequence'
node_action = 'Script'
node_condition = 'ScriptCondition'
node_decorator_attempts = 'RetryUntilSuccessful'
node_delay = 'Sleep'
node_subtree = 'SubTree'
macro_node_root = 'TC_BHT_DEFINITION_CREATE_NODE_ROOT'
macro_node_fallback = 'TC_BHT_DEFINITION_CREATE_NODE_FALLBACK'
macro_node_sequence = 'TC_BHT_DEFINITION_CREATE_NODE_SEQUENCE'
macro_node_action = 'TC_BHT_DEFINITION_CREATE_NODE_ACTION'
macro_node_condition = 'TC_BHT_DEFINITION_CREATE_NODE_CONDITION'
macro_node_decorator_attempts = 'TC_BHT_DEFINITION_CREATE_NODE_ATTEMPTS'
macro_node_delay = 'TC_BHT_DEFINITION_CREATE_NODE_ACTION_TIMEOUT'
macro_node_subtree = 'TC_BHT_DEFINITION_CREATE_NODE_SUBTREE'
archives = []
texts = []
trees_size = []
functions = []
attempts = 0
attempts_max = 0

class BT_ARRAY:
    def __init__(self):
        self.node_number = 0
        self.subtree_root_data = [255, 255]
        self.tree_id = 0
        self.tree_index = 0
        self.main_tree = ""
        self.tree = []
        self.tree_function = []
        self.folder = ""
        self.library = ARCHIVE_CREATOR()

    def get_max_attempts(self):
        return self.max_attempts_nodes

    def set_archive_data(self, project_id = None, name = None, email = None, version = None, copyrights = None, project = None):
        self.library.set_text(project_id=project_id, name=name, email=email, version=version, copyrights=copyrights, project=project)

    def set_children(self):
        if(self.node_number == 0):
            return

        node_type = self.tree[-1][1]

        if macro_node_fallback == node_type or macro_node_sequence == node_type or \
           macro_node_decorator_attempts == node_type:
            self.tree[-1][2] = self.node_number

    def set_sibling(self):
        for i in range(1, len(self.tree)):
            sibling_index = 255
            parent_index = self.tree[i][0]
            for j in range(len(self.tree) - 1, i, -1):
                if parent_index == self.tree[j][-1]:
                    self.tree[j][-2] = sibling_index
                    sibling_index = self.tree[j][0]

    def mount_nodes(self, element, node_parent_number):
        global attempts
        global attempts_max
        self.node_number += 1

        is_decoration_attempts = False

        if node_fallback == element.tag:
            node = [self.node_number, macro_node_fallback, 255, 255, node_parent_number]
            node_parent_number = self.node_number

        elif node_sequence == element.tag:
            node = [self.node_number, macro_node_sequence, 255, 255, node_parent_number]
            node_parent_number = self.node_number

        elif node_action == element.tag:
            node = [self.node_number, macro_node_action, "&" + element.get('code'), 255, node_parent_number]
            node_parent_number -= 1
            if not element.get('code') in self.tree_function:
                self.tree_function.append(element.get('code'))

        elif node_condition == element.tag:
            node = [self.node_number, macro_node_condition, "&" + element.get('code'), 255, node_parent_number]
            node_parent_number -= 1
            if not element.get('code') in self.tree_function:
                self.tree_function.append(element.get('code'))

        elif node_decorator_attempts == element.tag:
            node = [self.node_number, macro_node_decorator_attempts, 255, element.get('num_attempts'), f'&tc_{self.library.project.lower()}_bht_commom_attempts[{attempts}]', 255,  node_parent_number]
            node_parent_number = self.node_number
            attempts += 1
            is_decoration_attempts = True
            if attempts > attempts_max:
                attempts_max = attempts

        elif node_delay == element.tag:
            node = [self.node_number, macro_node_delay, element.get('msec'), 255,  node_parent_number]
            node_parent_number = self.node_number

        elif node_subtree == element.tag:
            tree_elements = [item for item in archives if element.get('ID') in archives]
            tree_num = '' if len(tree_elements) == 0 else str(len(tree_elements))
            node = [self.node_number, macro_node_subtree, element.get('ID') + tree_num, 255,  node_parent_number]
            node_parent_number = self.node_number
            subtree = BT_ARRAY()
            subtree.set_archive_data(self.library.project_id, self.library.name, self.library.email, self.library.version, self.library.copyrights, self.library.project)
            subtree.process_tree(self.folder, element.get('ID'), self.tree_id, self.node_number)

        else:
            self.node_number = 0
            node = [self.node_number, macro_node_root, self.subtree_root_data[0], 1, self.subtree_root_data[1]]

        self.set_children()
        self.tree.append(node)

        for child in element:
            self.mount_nodes(child, node_parent_number)

        if is_decoration_attempts:
            attempts -= 1

    def open_xml(self, archive, id = None):
        tree = ET.parse(archive)
        root = tree.getroot()
        for behavior_tree in root.findall('BehaviorTree'):
            self.tree_id = behavior_tree.get('ID')
            if self.tree_id == self.main_tree:
                self.tree_function.clear()
                self.mount_nodes(behavior_tree, 0)
                self.set_sibling()
                if self.tree_id in archives:
                    elements = [element for element in archives]
                    elements_count = len(elements)
                    self.tree_id += str(elements_count)
                    archives.append(self.tree_id)
                else:
                    archives.append(self.tree_id)
                text = self.library.tree_vector(self.tree_id, self.tree)
                self.tree.clear()
                texts.append(text)
                trees_size.append(self.node_number)
                functions.append(self.tree_function)

    def load_archives(self, id = None):
        trees = os.listdir(self.folder)
        for archive in trees:
            self.open_xml(f"{self.folder}/{archive}", id)

    def process_tree(self, folder, id, parent_tree, local_parent_tree):
        self.folder = folder
        self.main_tree = id
        self.subtree_root_data[0] = parent_tree
        self.subtree_root_data[1] = local_parent_tree
        self.load_archives(id)

    def root_treatment(self, i):
        find_root = "ROOT("
        index = texts[i].find(find_root)
        x = 0
        j = len(find_root)
        while(index != -1):
            x += index
            start = x + j
            end = start
            while texts[i][end] != ",":
                end += 1
            tree = texts[i][start : end]
            if(tree != '255'):
                text  = ""
                text  = texts[i][:start]
                text += str(archives.index(tree))
                text += texts[i][end:]
                texts[i] = text
            index = texts[i][end:].find(find_root)
            x = len(texts[i][:end])

    def subtree_treatment(self, i):
        find_subtree = "SUBTREE("
        index = texts[i].find(find_subtree)
        x = 0
        j = len(find_subtree)
        while(index != -1):
            x += index
            start = x + j
            end = start
            while texts[i][end] != ",":
                end += 1
            subtree = texts[i][start : end]
            text  = ""
            text  = texts[i][:start]
            text += str(archives.index(subtree))
            text += texts[i][end:]
            texts[i] = text
            index = texts[i][end:].find(find_subtree)
            x = len(texts[i][:end])

    def create_trees(self, folder = None, main_tree = None):
        self.folder = folder if folder != None else input("Put archive folder:")
        self.main_tree = main_tree if main_tree != None else input("Put your main tree:")
        self.load_archives()
        archives.reverse()
        texts.reverse()
        trees_size.reverse()
        functions.reverse()
        for i in range(len(texts)):
            self.root_treatment(i)
            self.subtree_treatment(i)
        self.library.generate_archives(archives, texts, functions, attempts_max, trees_size)
        self.max_attempts_nodes = 0