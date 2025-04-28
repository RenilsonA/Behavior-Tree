from btree_array_creator import BTREE_ARRAY

folder = 'tree-examples'
output = 'Output'
main_tree = 'example'
name = "Renilson Almeida"
email = "joserenilson.silva@edge.ufal.br"
version = "1.0"
copyrights = ""
project = "test"

x = BTREE_ARRAY()
x.set_archive_data(name, email, version, copyrights, project)
x.create_trees(folder = folder, output = output, main_tree = main_tree)