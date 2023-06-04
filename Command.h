#pragma once

class Command
{
private:
	Token* first_parameter=nullptr;
	Token* command=nullptr;
	Token* last_parameter=nullptr;

public:

    //Checks if the new command contains commas (if it does it means that the command has 3 parameters, otherwise it has only one and there's no need to parse it)
	bool contains_coma(Token* command)
	{
		char* characters = command->get_pointer();
		for (int i = 0; i < command->get_size(); i++)
		{
			if (characters[i] == ',')
			{
				return true;
			}
		}
		return false;
	}

    //The function will iterate characters in ,,command" from the given ,,offset" up until the point where it finds a comma (or it runs out from characters to iterate)
    //It will then proceed to put all iterated characters (except the comma) in ,,new_token" vector
	int iterate_till_coma(Token* command, int offset, Vector<char>* new_token)
	{
		char* characters = command->get_pointer();
		for(int i=offset;i<command->get_size();i++)
		{
            if (characters[i] == ',')
            {
                break;
            }
			new_token->push_back(characters[i]);
            offset = i;
		}
		return offset+2;
	}

    void print_current_command()
    {
        if (first_parameter != nullptr)
        {
            first_parameter->print();
            cout << ",";
        }
        command->print();
        if (last_parameter != nullptr)
        {
            cout << ",";
            last_parameter->print();
        }
    }

	void execute(Tree& tree)
	{
        if (first_parameter==nullptr && *command == constant_tokens.give_number)
        {
            cout << constant_tokens.give_number << PRINTING_SEPARATOR << tree.get_size() << endl;
        }
        else
        {
            if (*command == constant_tokens.selector)
            {
                if (*last_parameter == constant_tokens.give_number)
                {
                    if (first_parameter->is_number())
                    {
                        int result = tree.selectors_in_section(first_parameter->get_number_value() - 1);
                        if (result != -1)
                        {
                            print_current_command();
                            cout << PRINTING_SEPARATOR << result << endl;
                        }
                    }
                    else
                    {
                        print_current_command();
                        cout << PRINTING_SEPARATOR;
                        cout << tree.total_selector_occurences(first_parameter) << endl;
                    }
                }
                else
                {
                    Token* result = tree.get_selector(first_parameter->get_number_value() - 1, last_parameter->get_number_value() - 1);
                    if (result != nullptr)
                    {
                        print_current_command();
                        cout << PRINTING_SEPARATOR;
                        result->print();
                        cout << endl;
                    }
                }
            }
            else if (*command == constant_tokens.attribute)
            {
                if (*last_parameter == constant_tokens.give_number)
                {
                    if (first_parameter->is_number())
                    {
                        int result = tree.attributes_in_section(first_parameter->get_number_value() - 1);
                        if (result != -1)
                        {
                            print_current_command();
                            cout << PRINTING_SEPARATOR << result << endl;
                        }
                    }
                    else
                    {
                        print_current_command();
                        cout << PRINTING_SEPARATOR;
                        cout << tree.total_attribute_occurences(first_parameter) << endl;
                    }
                }
                else
                {
                    Attribute* result = tree.get_attribute(first_parameter->get_number_value() - 1, last_parameter);
                    if (result != nullptr)
                    {
                        print_current_command();
                        cout << PRINTING_SEPARATOR;
                        result->get_value()->print();
                        cout << endl;
                    }
                }
            }
            else if (*command == constant_tokens.value)
            {
                Attribute* found_attribute = tree.get_attribute_for_selector(first_parameter, last_parameter);
                if (found_attribute != nullptr)
                {
                    print_current_command();
                    cout << PRINTING_SEPARATOR;
                    found_attribute->get_value()->print();
                    cout << endl;
                }
            }
            else if (*command == constant_tokens.deleting)
            {
                if (*last_parameter == constant_tokens.deleting_entire_section)
                {
                    if (tree.delete_section(first_parameter->get_number_value()-1))
                    {
                        print_current_command();
                        cout << PRINTING_SEPARATOR << DELETING_MASSAGE << endl;
                    }
                }
                else
                {
                    if (tree.delete_attribute(first_parameter->get_number_value()-1, last_parameter))
                    {
                        print_current_command();
                        cout << PRINTING_SEPARATOR << DELETING_MASSAGE << endl;
                    }
                }
            }
        }
	}

    //The object constructor will recive token containing a command and parse it if necesarry 
	Command(Token* command)
	{
		if (contains_coma(command))
		{
			int offset = 0;
			Vector<char>new_token;
			offset = iterate_till_coma(command, offset, &new_token);
			first_parameter = new Token(&new_token);
            new_token.clear();
			offset = iterate_till_coma(command, offset, &new_token);
			this->command = new Token(&new_token);
            new_token.clear();
			offset = iterate_till_coma(command, offset, &new_token);
			last_parameter = new Token(&new_token);
		}
		else
		{
			this->command = command;
		}
	}




};