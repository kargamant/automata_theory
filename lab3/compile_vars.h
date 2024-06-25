#ifndef COMPILE_VARS_H
#define COMPILE_VARS_H
Map labirint{"labirint.txt"};
//labirint.changeCellType(3, 4, CellType::obstacle);
VarMap* vm=new VarMap();
std::stack<VarMap*> program_stack;
std::unordered_map<std::string, Ast*> declared_funcs;
std::ofstream bison_logger("report_bison.txt");
#endif
