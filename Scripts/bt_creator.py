from array_creator import BT_ARRAY

folder = 'tree-examples'
main_tree = 'example'
project_id ='modem_tree'
name = "Renilson Almeida"
email = "joserenilson.silva@edge.ufal.br"
version = "1.0"
copyrights = "Trucks Control S/A"
project = 'EG915U'

x = BT_ARRAY()
x.set_archive_data(project_id, name, email, version, copyrights, project)
x.create_trees(folder, main_tree)