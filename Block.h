#pragma once

class Block
{
private:
	Section** sections;
	unsigned int size = 0;

public:

	unsigned int get_size()
	{
		return size;
	}

	Section* get_section(int index)
	{
		return sections[index];
	}

	//The function will delete the section (and throw exception if the section does not exist, so it needs to be check before calling this function).
	//It will then proceed to move the whole array to fill in the gap
	void delete_section(int index)
	{
		delete sections[index];
		for (int i = index; i < size - 1; i++)
		{
			sections[i] = sections[i + 1];
		}
		sections[size - 1] = nullptr;
		size--;
	}

	//The function returns 0 if there was no attribute to delete, 1 if attribute has been deleted and 2 if attribute was deleted and the whole section is now empty and should be deleted as well (it is a signel for ,,delete_attribute" method in class ,,Tree").
	int delete_attribute(int index, Token* name)
	{
		if (sections[index]->delete_attribute(name))
		{
			if (sections[index]->get_attribute_number() == 0)
			{
				delete_section(index);
				return 2;
			}
			return 1;
		}
		return 0;
	}

	Section* create_section()
	{
		sections[size] = new Section;
		Section* pointer = sections[size];
		size++;
		return pointer;
	}

	Block()
	{
		sections = new Section*[BLOCK_SIZE];
		for (int i = 0; i< BLOCK_SIZE; i++)
		{

			sections[i] = nullptr;
		}
	}
};