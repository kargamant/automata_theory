import pydot

(graph,) = pydot.graph_from_dot_file('../automato.dot')
graph.write_png('../automato.png')
