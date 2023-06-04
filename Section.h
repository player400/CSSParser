#pragma once

class Section
{
private:
	LinkedList<Token*>* selectors;
	LinkedList<Attribute*>* attributes;
	unsigned int attribute_number = 0;

	//Function takes a token representing ONE SINGLE selector from ,,add_selectors" method and adds it to the list (unless it's already there)
	void add_selector(Token* selector)
	{
		if (!search_for_selector(selector))
		{
			selectors->add(selector);
		}
	}

public:

	unsigned int get_attribute_number()
	{
		return attribute_number;
	}

	unsigned int get_selector_number()
	{
		return selectors->get_size();
	}

	//Function returns a list element containing attribute with a given name or nullptr, if such attribute does not exist.
	LinkedList<Attribute*>::ListElement<Attribute*>* search_for_element_containing_attribute(Token* name)
	{
		if (attributes->get_size() == 0)
		{
			return nullptr;
		}
		auto current = attributes->root->next_element();
		while (true)
		{
			if (current->get_data()!=nullptr && * (current->get_data()->get_name()) == *(name))
			{
				return current;
			}
			if (current != attributes->last)
			{
				current = current->next_element();
			}
			else
			{
				return nullptr;
			}
		}
	}

	Attribute* search_for_attribute(Token* name)
	{
		auto pointer = search_for_element_containing_attribute(name);
		if (pointer != nullptr)
		{
			return pointer->get_data();
		}
		return nullptr;
	}

	bool delete_attribute(Token* name)
	{
		auto pointer = search_for_element_containing_attribute(name);
		if (pointer != nullptr && pointer->get_data() != nullptr)
		{
			delete pointer->get_data();
			pointer->set_data(nullptr);
			attribute_number--;
			return true;
		}
		return false;
	}

	Token* get_selector(int index)
	{
		if (index >= selectors->get_size())
		{
			return nullptr;
		}
		return (*selectors)[index]->get_data();
	}

	Attribute* get_attribute(int index)
	{
		if (index >= attributes->get_size());
		return (*attributes)[index]->get_data();
	}

	bool search_for_selector(Token* name)
	{
		if (selectors->get_size() == 0)
		{
			return false;
		}
		auto current = selectors->root->next_element();
		while (true)
		{
			if (*(current->get_data()) == *name)
			{
				return true;
			}
			if (current != selectors->last)
			{
				current = current->next_element();
			}
			else
			{
				return false;
			}
		}
	}

	//Function takes a token representing ONE SINGLE attribute, cross-checks with existing selectors for collisions and adds to the list of selectors or updates value
	void add_attribute(Token* attribute)
	{
		Attribute* new_attribute = new Attribute(attribute);
		Attribute* existing = search_for_attribute(new_attribute->get_name());
		if (existing == nullptr)
		{
			attributes->add(new_attribute);
			attribute_number++;
		}
		else
		{
			auto pointer = search_for_element_containing_attribute(new_attribute->get_name());
			pointer->set_data(new_attribute);
			delete existing;
		}
	}

	//Function takes a token, that may contain one or more selectors separeted by commas and parses it.
	void add_selectors(Token* selectors)
	{
		char* characters = selectors->get_pointer();
		Vector<char>* selector = new Vector<char>;
		for (int i = 0; i < selectors->get_size(); i++)
		{
			if (characters[i] == ',')
			{
				Token* new_token = new Token(selector);
				if(new_token->get_size()>0)
				{
					add_selector(new_token);
				}
				else
				{
					delete new_token;
				}
				delete selector;
				selector = new Vector<char>;
			}
			else
			{
				selector->push_back(characters[i]);
			}
		}
		Token* new_token = new Token(selector);
		if (new_token->get_size() > 0)
		{
			add_selector(new_token);
		}
		else
		{
			delete new_token;
		}
		delete selector;
	}

	Section()
	{
		selectors = new LinkedList<Token*>;
		attributes = new LinkedList<Attribute*>;
	}

	~Section()
	{
		delete selectors;
		delete attributes;
	}
};