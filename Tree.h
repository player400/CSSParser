#pragma once

class Tree
{
private:
	LinkedList<Block*>*blocks;
	unsigned int size = 0;

	Section* get_section(int index, Block** block = nullptr, int* in_block_index = nullptr)
	{

		if (index >= size)
		{
			return nullptr;
		}
		if (size > 0)
		{
			auto current = blocks->root->next_element();
			while (true)
			{
				if (index >= current->get_data()->get_size())
				{
					index -= current->get_data()->get_size();
				}
				else
				{
					if (block != nullptr)
					{
						*block = current->get_data();
					}
					if (in_block_index != nullptr)
					{
						*in_block_index = index;
					}
					return current->get_data()->get_section(index);
				}
				if (current == blocks->last)
				{
					break;
				}
				else
				{
					current = current->next_element();
				}
			}
		}
		return nullptr;
	}

public:
	unsigned int get_size()
	{
		return size;
	}

	//The functions creates a new section in the CSS tree and returns pointer to it.
	Section* create_section()
	{
		size++;
		if (blocks->get_size() > 0)
		{
			if (blocks->last->get_data()!=nullptr && blocks->last->get_data()->get_size() < BLOCK_SIZE)
			{
				return blocks->last->get_data()->create_section();
			}
		}
		blocks->add(new Block);
		return blocks->last->get_data()->create_section();
	}

	//Returns -1 if sections does not exist
	int selectors_in_section(int index)
	{
		Section* section_picked = get_section(index);
		if (section_picked != nullptr)
		{
			return section_picked->get_selector_number();
		}
		return -1;
	}

	//Returns -1 if section does not exist
	int attributes_in_section(int index)
	{
		if (get_section(index) != nullptr)
		{
			return get_section(index)->get_attribute_number();
		}
		return -1;
	}

	//The function returns selector number j in the section number i
	Token* get_selector(int i, int j)
	{
		if (i > size - 1)
		{
			return nullptr;
		}
		Section* picked_section = get_section(i);
		if (picked_section==nullptr || picked_section->get_selector_number() - 1 < j)
		{
			return nullptr;
		}
		return picked_section->get_selector(j);
	}

	//The function returns attribute with the given name from the section number i
	Attribute* get_attribute(int i, Token* name)
	{
		if (i > size - 1)
		{
			return nullptr;
		}
		return get_section(i)->search_for_attribute(name);
	}

	//The function counts how many times given selector occurs in the entire tree
	unsigned int total_selector_occurences(Token* selector)
	{
		int sum = 0;
		if (size > 0)
		{
			auto current = blocks->last;
			while (current != blocks->root)
			{

				for (int i = 0; i < current->get_data()->get_size(); i++)
				{
					Section* section = current->get_data()->get_section(i);
					if (section != nullptr)
					{
						if (section->search_for_selector(selector))
						{
							sum++;
						}
					}
				}
				current = current->previous_element();
			}
		}
		return sum;
	}

	//The function counts how many times attribute with the given name occurs in the entire tree
	unsigned int total_attribute_occurences(Token* name)
	{
		int sum = 0;
		if (size > 0)
		{
			auto current = blocks->last;
			while (current != blocks->root)
			{

				for (int i = 0; i < current->get_data()->get_size(); i++)
				{
					Section* section = current->get_data()->get_section(i);
					if (section != nullptr)
					{
						if (section->search_for_attribute(name) != nullptr)
						{
							sum++;
						}
					}
				}
				current = current->previous_element();
			}
		}
		return sum;
	}

	//Function will return true if section has been removed and false if there was nothing to remove in the first place
	bool delete_section(int index)
	{
		Block* block_to_delete_from;
		int number_of_section;
		auto pointer_to_section = get_section(index, &block_to_delete_from, &number_of_section);
		if (pointer_to_section != nullptr)
		{
			block_to_delete_from->delete_section(number_of_section);
			size--;
			return true;
		}
		return false;
	}

	//Function will return true if attribute has been removed and false if there was nothing to remove in the first place
	bool delete_attribute(int index, Token* name)
	{
		Block* block_to_delete_from;
		int number_of_section;
		auto pointer_to_section = get_section(index, &block_to_delete_from, &number_of_section);
		if (pointer_to_section != nullptr)
		{
			int result = block_to_delete_from->delete_attribute(number_of_section, name);
			if (result == 2)
			{
				size--;
			}
			if (result != 0)
			{
				return true;
			}
		}
		return false;
	}

	//Function will return attribute with the given name from section containing given selector (if there's multiple it will return the last one)
	Attribute* get_attribute_for_selector(Token* selector, Token* name)
	{
		if (size > 0)
		{
			auto current = blocks->last;
			while (current != blocks->root)
			{

				for (int i = current->get_data()->get_size()-1; i >= 0; i--)
				{
					if (current->get_data()->get_section(i)!=nullptr && current->get_data()->get_section(i)->search_for_selector(selector))
					{
						Attribute* attribute = current->get_data()->get_section(i)->search_for_attribute(name);
						if (attribute != nullptr)
						{
							return attribute;
						}
					}
				}
				current = current->previous_element();
			}
			return nullptr;
		}
		return nullptr;
	}

	Tree()
	{
		blocks = new LinkedList<Block*>;
	}

	~Tree()
	{
		delete blocks;
	}
};