#include "VarMap.h"


std::unordered_map<VarType, int> VarMap::size_table={{VarType::tiny, 1}, {VarType::small, 32}, {VarType::normal, 1024}, {VarType::big, 32768}};
Err VarMap::err_code=Err::no_error;

Var::Var(VarType type, const std::string& name, int value) : name(name)
{
	int boundary=VarMap::size_table[type];
	if(type==VarType::tiny && value!=0 && value!=1) 
	{
		VarMap::err_code=Err::typeMisMatch;
		throw std::invalid_argument("Error. Value of tiny type can only be 0 or 1. Yours is "+std::to_string(value));
	}
	else if(value>=boundary || value<-(boundary/2)) 
	{
		VarMap::err_code=Err::typeMisMatch;
		throw std::invalid_argument("Error. value "+std::to_string(value)+" does not fit boudaries of type "+nameByType(type)+".");
	}
	else 
	{
		this->type=type;
		this->value=value;
	}
}

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
		err_code=Err::redefinition;
		throw std::invalid_argument("Error. Redefenition of variable "+var.name+".");
	}
}

void VarMap::changeVar(const std::string& name, int val)
{
	if(map.contains(name))
	{
		//check value on its size compatability before assigning
		if(val>=size_table[map[name].type]) map[name].value=size_table[map[name].type]-1;
		else if(val<-size_table[map[name].type]/2) map[name].value=-size_table[map[name].type]/2;
		else map[name].value=val;
	}
	else
	{
		err_code=Err::undefined;
		throw std::invalid_argument("Error. Variable "+name+" was not defined.");
	}
}

Var VarMap::getVar(const std::string& name)
{
	if(map.contains(name)) return map[name];
	else
	{
		err_code=Err::undefined;
		throw std::invalid_argument("Error. Variable "+name+" was not defined.");
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
		Var var_init(init_type, var.name, value);
		addVar(var_init);
	}
	to_initialize.clear();
}

void VarMap::flushAssign(int value)
{
	for(auto& var: to_initialize)
	{
		changeVar(var.name, value);
	}
	to_initialize.clear();
}







