#pragma once

class Attribute
{
private:
	Token* name;
	Token* value;

public:

	Token* get_name()
	{
		return name;
	}

	Token* get_value()
	{
		return value;
	}

	//The object constructor recieves a token containing both name and value of the attribute, separated with ';'. It then proceeds to parse them and put in respective tokens inside the object.
	Attribute(Token* full)
	{
		Vector<char> name;
		Vector<char> value;
		char* token = full->get_pointer();
		int i = 0;
		while (token[i]!=':')
		{
			name.push_back(token[i]);
			i++;
		}
		i++;
		while (i < full->get_size())
		{
			value.push_back(token[i]);
			i++;
		}
		this->name = new Token(&name);
		this->value = new Token(&value);
	}

	~Attribute()
	{
		delete name;
		delete value;
	}
};