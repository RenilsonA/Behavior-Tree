# Expande os arquivos fonte
file(GLOB SRC_MAIN "main.c")
file(GLOB SRC_SRC "src/*.c")
file(GLOB SRC_BTREE "src/btree_main/*.c")
file(GLOB SRC_BT "bt/src/*.c")
file(GLOB SRC_BUILD "build/btree_main/*.c")

# Registra o componente
idf_component_register(SRCS ${SRC_MAIN}
                            ${SRC_SRC}
                            ${SRC_BTREE}
                            ${SRC_BT}
                            ${SRC_BUILD}
                    INCLUDE_DIRS "."
                                 "include"
                                 "include/btree_main"
                                 "bt/include"
                                 "build/btree_main")
