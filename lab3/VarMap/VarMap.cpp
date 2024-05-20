#include "VarMap.h"


VarType typeByName(const std::string& type_name)
{
	if(type_name=="tiny")
	{
		return VarType::tiny;
	}
	else if(type_name=="small")
	{
		return VarType::small;
	}
	else if(type_name=="normal")
	{
		return VarType::normal;
	}
	else if(type_name=="big")
	{
		return VarType::big;
	}
	else
	{
		//throw 
	}
}

std::string nameByType(VarType& type)
{
	switch(type)
	{
		case VarType::tiny:
			return "tiny";
		case VarType::small:
			return "small";
		case VarType::normal:
			return "normal";
		case VarType::big:
			return "big";
	}
}

void operator<<(std::ostream& stream, Var& var)
{
	stream<<nameByType(var.type)<<std::string(" ")<<var.name<<std::string(" ")<<var.value<<std::endl;
}

void VarMap::addVar(Var var)
{
	if(!map.contains(var.name))
	{
		map.insert({var.name, var});
	}
	else
	{
		//throw
	}
}

void VarMap::changeVar(const std::string& name, int val)
{
	if(map.contains(name))
	{
		//check value on its size compatability before assigning
		map[name].value=val;
	}
	else
	{
		//throw
	}
}

Var VarMap::getVar(const std::string& name)
{
	if(map.contains(name)) return map[name];
	else
	{
		//throw
	}
}


void VarMap::pushVarToInit(const std::string& name)
{

	to_initialize.emplace_back(VarType::tiny, name, 0);	
}

void VarMap::flushInit(VarType init_type, int value)
{
	for(auto& var: to_initialize)
	{
		var.type=init_type;
		var.value=value;
		addVar(var);
	}
	to_initialize.clear();
}









