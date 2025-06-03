from btree_array_creator import BTREE_ARRAY

archive = 'tree-examples/simple.xml'#esp32_epaper.xml'
output = 'Output'
name = "Renilson Almeida"
email = "joserenilson.silva@edge.ufal.br"
version = "1.0"
copyrights = ""
project = "main"
main_tree = 'subtree'

x = BTREE_ARRAY()
x.set_archive_data(name, email, version, copyrights, project)
x.create_trees(archive = archive, output = output, main_tree = main_tree)