#pragma once

class Token
{
private:
	Vector<char>characters;

public:

	friend bool operator==(Token& left, Token& right);

	friend bool operator==(Token& left, const char* right);

	void print()
	{
		for (int i = 0; i < characters.size; i++)
		{
			cout << characters.get(i);
		}
	}

	//Returns true if the token contains only valid digits
	bool is_number()
	{
		for (int i = 0; i < characters.size; i++)
		{
			if (characters.get(i) > '9' || characters.get(i) < '0')
			{
				return false;
			}
		}
		return true;
	}

	//If the token contains only valid digits it returns number value of the token. Otherwise the behavior is undefined.
	int get_number_value()
	{
		int value = 0;
		int multiplier = 1;
		for (int i = characters.size-1; i >= 0; i--)
		{
			if (characters.get(i) >= '0' && characters.get(i) <= '9')
			{
				value += (characters.get(i) - '0') * multiplier;
			}
			multiplier *= 10;
		}
		return value;
	}

	char* get_pointer()
	{
		return characters.get_ptr();
	}

	unsigned int get_size()
	{
		return characters.size;
	}

	Token(Vector<char>*elements)
	{
		int j = 0;
		while (elements->get(j) == ' ' || elements->get(j) == '\t')
		{
			j++;
		}
		int k = elements->size;
		while (elements->get(k-1) == ' ' || elements->get(k-1) == '\t')
		{
			k--;
		}
		for (int i = j; i < k; i++)
		{
			characters.push_back(elements->get(i));
		}
	}
};

bool operator==(Token& left, Token& right)
{
	if (left.characters.size != right.characters.size)
	{
		return false;
	}
	for (int i = 0; i < left.characters.size; i++)
	{
		if (left.characters.get(i) != right.characters.get(i))
		{
			return false;
		}
	}
	return true;
}

bool operator==(Token& left, const char* right)
{
	int i = 0;
	while (true)
	{
		if (right[i] == '\0' && i<left.get_size())
		{
			return false;
		}
		else if (i >= left.get_size() && right[i] != '\0')
		{
			return false;
		}
		else if (i == left.get_size() && right[i] == '\0')
		{
			break;
		}
		else if (left.get_pointer()[i] != right[i])
		{
			return false;
		}
		i++;
	}
	return true;
}
