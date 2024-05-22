#include "VarMap.h"


std::unordered_map<VarType, int> VarMap::size_table={{VarType::tiny, 1}, {VarType::small, 32}, {VarType::normal, 1024}, {VarType::big, 32768}};
Err VarMap::err_code=Err::no_error;

Var::Var(VarType type, const std::string& name, int value) : name(name), isField(false)
{
	int boundary=VarMap::size_table[type];
	if(type==VarType::tiny && value!=0 && value!=1) 
	{
		VarMap::err_code=Err::typeMisMatch;
		throw std::invalid_argument("Error. Value of tiny type can only be 0 or 1. Yours is "+std::to_string(value));
	}
	else if(type!=VarType::tiny && (value>=boundary || value<-(boundary/2))) 
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

void Var::changeValue(int nvalue)
{
	if(nvalue>=VarMap::size_table[type]) 
	{
		if(type==VarType::tiny) value=VarMap::size_table[type];
		else value=VarMap::size_table[type]-1;
	}
	else if(nvalue<-VarMap::size_table[type]/2) value=-VarMap::size_table[type]/2;
	else value=nvalue;

	if(isField)
	{
		dynamic_cast<Field*>(this)->updateItems();
	}
}

Field::Field(VarType item_type, VarType size_type, const std::string& name, int value) : Var(item_type, name, value), size_type(size_type), matr(VarMap::size_table[size_type]*VarMap::size_table[size_type], Var(item_type, "", value))
{
	isField=true;
}

void Field::updateItems()
{
	for(auto& item: matr)
	{
		item.value=value;
	}
}

Var& Field::getVar(int ind1, int ind2)
{
	if((VarMap::size_table[size_type]*ind1+ind2)>=matr.size())
	{
		VarMap::err_code=Err::outOfRange;
		throw std::invalid_argument("Error. Index of ["+std::to_string(ind1)+" "+std::to_string(ind2)+"] is out of range. Size is "+std::to_string(matr.size()));
	}
	else
	{
		return matr[VarMap::size_table[size_type]*ind1+ind2];
	}
}

void AssignOperator::perform()
{
	if(type==AssignType::Left) //a<<b
	{
		if(!left.isVar)
		{
			VarMap::err_code=Err::invalidAssign;
			throw std::invalid_argument("Error. Cant assign anything to literal.");
		}
		else
		{
			left.var->changeValue(right.value);
			//changeVar(left.var->name, right.value);
		}
	}
	else
	{
		if(!right.isVar)
		{
			VarMap::err_code=Err::invalidAssign;
			throw std::invalid_argument("Error. Cant assign anything to literal.");
		}
		else
		{
			right.var->changeValue(left.value);
			//changeVar(right.var->name, left.value);
		}
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
	stream<<nameByType(var.type)<<std::string(" ")<<var.name<<std::string(" ")<<var.value;
}

void operator<<(std::ostream& stream, Field& arr)
{
	stream<<nameByType(arr.type)<<" "<<nameByType(arr.size_type)<<" "<<arr.name<<":"<<std::endl;
	for(int i=0; i<VarMap::size_table[arr.size_type]; i++)
	{
		for(int j=0; j<VarMap::size_table[arr.size_type]; j++)
		{
			stream<<arr.matr[i*VarMap::size_table[arr.size_type]+j];
			stream<<" ";
		}
		stream<<std::endl;

	}
	/*if(arr.size_type==VarType::tiny)
	{
		stream<<arr.matr[0];
	}
	int k=0;
	bool wasPlused=false;
	if(arr.value==0) 
	{
		arr.value++;
		wasPlused=true;
	}
	for(int i=0; i<arr.matr.size()/arr.value; i++)
	{
		for(int j=0; j<arr.value; j++)
		{
			stream<<arr.matr[i*arr.value+j];
			stream<<std::string(" ");
			k=i*arr.value+j;
		}
		stream<<std::endl;
	}
	
	//remain once
	for(int i=k+1; i<arr.matr.size(); i++)
	{
		stream<<arr.matr[i];
		stream<<std::string(" ");
	}
	if(wasPlused) arr.value--;*/
}

void VarMap::addVar(Var* var)
{
	if(!map.contains(var->name))
	{
		map.insert({var->name, var});
	}
	else
	{
		err_code=Err::redefinition;
		throw std::invalid_argument("Error. Redefenition of variable "+var->name+".");
	}
}

void VarMap::changeVar(const std::string& name, int val)
{
	if(map.contains(name))
	{
		//check value on its size compatability before assigning
		if(val>=size_table[map[name]->type]) 
		{
			if(map[name]->type==VarType::tiny) map[name]->value=size_table[map[name]->type];
			else map[name]->value=size_table[map[name]->type]-1;
		}
		else if(val<-size_table[map[name]->type]/2) map[name]->value=-size_table[map[name]->type]/2;
		else map[name]->value=val;

		if(map[name]->isField)
		{
			dynamic_cast<Field*>(map[name])->updateItems();
		}
	}
	else
	{
		err_code=Err::undefined;
		throw std::invalid_argument("Error. Variable "+name+" was not defined.");
	}
}

Var* VarMap::getVar(const std::string& name)
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

void VarMap::pushOperand(Operand op)
{
	operand_stack.push(op);
}

void VarMap::pushOperator(AssignOperator op)
{
	oper_queue.push(op);
}

void VarMap::flushInit(VarType init_type, int value)
{
	for(auto& var: to_initialize)
	{
		Var* var_init=new Var(init_type, var.name, value);
		try
		{
			addVar(var_init);
		}
		catch(...)
		{
			to_initialize.clear();
			throw;
		}
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

void VarMap::flushAssignExpr()
{
	std::vector<AssignOperator> operations;
	//std::vector<Var*> vars;
	while(!oper_queue.empty())
	{
		AssignOperator oper=oper_queue.front();
		oper_queue.pop();

		oper.right=operand_stack.top();
		operand_stack.pop();
		oper.left=operand_stack.top();
		operations.push_back(oper);
	}
	operand_stack.pop();
	
	for(auto& operation: operations)
	{
		if(operation.type==AssignType::Right)
		{
			operation.perform();
		}
	}

	for(auto& operation: operations)
	{
		if(operation.type==AssignType::Left)
		{
			operation.perform();
		}

	}
}
/*void VarMap::flushAssignArr(int value)
{
	for(auto& var: to_initialize)
	{
		if(!var->isField)
		{
			err_code=Err::notAnArray;
			throw std::invalid_argument("");
		}
	}
}*/





