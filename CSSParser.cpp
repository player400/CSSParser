#define FREE_ATTRIBUTES 1
#define ATTRBUTES 2
#define SELECTORS 3

#define INIT_VECTOR_CAP 2

#define BLOCK_SIZE 8

#define PRINTING_SEPARATOR " == "
#define DELETING_MASSAGE "deleted"

#include <iostream>

using namespace std;

struct ConstantTokens
{
    const char* start_execution = "????";
    const char* start_parsing = "****";
    const char* give_number = "?";
    const char* attribute = "A";
    const char* selector = "S";
    const char* value = "E";
    const char* deleting = "D";
    const char* deleting_entire_section = "*";

    const char* selector_separator = ",";
    const char* attribute_separator = ";";
    const char* block_start_separator = "{";
    const char* block_end_separator = "}";
} constant_tokens;

#include "list.h"
#include "vector.h"
#include "Token.h"
#include "Attribute.h"
#include "Section.h"
#include "Block.h"
#include "Tree.h"
#include "Command.h"

Tree tree;

void get_characters(Vector<char>* characters)
{
    char temporary_char;
    while (true)
    {
        temporary_char = getchar();
        if (temporary_char == EOF)
        {
            break;
        }
        if (temporary_char >= ' ' || temporary_char == '\n')
        {
            characters->push_back(temporary_char);
        }
    }
}

void tokenize(Vector<char>* characters, Vector<Token*>* tokens)
{
    Vector<char>* current_token = new Vector<char>;
    for (int i = 0; i < characters->size; i++)
    {
        char current = characters->get(i);
        if (current == '{' || current == '}' || current == '\n' || current == ';')
        {
            if (current_token->size > 0)
            {
                Token* temporary = new Token(current_token);
                tokens->push_back(temporary);
                delete current_token;
                current_token = new Vector<char>;
            }
            if (current != '\n')
            {
                current_token->push_back(current);
                Token* temporary = new Token(current_token);
                tokens->push_back(temporary);
                delete current_token;
                current_token = new Vector<char>;
            }
        }
        else
        {
            current_token->push_back(current);
        }
    }
    if (current_token->size > 0)
    {
        Token* temporary = new Token(current_token);
        tokens->push_back(temporary);
        delete current_token;
    }
}

int parse(Vector<Token*>* tokens, int offset)
{
    Token** array = tokens->get_ptr();
    Section* current_section = nullptr;
    int state = FREE_ATTRIBUTES;
    offset--;
    while (true)
    {
        offset++;
        if (array[offset]->get_size() == 0)
        {
            continue;
        }
        if (*(array[offset]) == constant_tokens.start_execution)
        {
            break;
        }
        if (*array[offset] == constant_tokens.block_end_separator)
        {
            state = FREE_ATTRIBUTES;
            current_section = nullptr;
            continue;
        }
        if (*array[offset] == constant_tokens.block_start_separator)
        {
            state = ATTRBUTES;
            if (current_section == nullptr)
            {
                current_section = tree.create_section();
            }
            continue;
        }
        if (state == FREE_ATTRIBUTES)
        {
            if (!( * array[offset + 1] == constant_tokens.attribute_separator))
            {
                current_section = tree.create_section();
                current_section->add_selectors(array[offset]);
                state = SELECTORS;
                continue;
            }
            else
            {
                if (current_section == nullptr)
                {
                    current_section = tree.create_section();
                }
                current_section->add_attribute(array[offset]);
            }
        }
        if (state == ATTRBUTES && !(*array[offset]==constant_tokens.attribute_separator))
        {
            current_section->add_attribute(array[offset]);
        }
        if (state == SELECTORS && !(*array[offset]==constant_tokens.selector_separator))
        {
            current_section->add_selectors(array[offset]);
        }
    }
    return offset+1;
}

int execute(Vector<Token*>* tokens, int offset)
{
    Token** array = tokens->get_ptr();
    while (true)
    {
        Token* current_token = array[offset];
        if (offset >= tokens->size || *(array[offset]) == constant_tokens.start_parsing)
        {
            break;
        }
        Command command(array[offset]);
        command.execute(tree);
        offset++;
    }
    return offset+1;
}

int main()
{
    Vector<char>characters;
    get_characters(&characters);
    Vector<Token*> tokens;
    tokenize(&characters, &tokens);
    int offset = 0;
    while (offset < tokens.size)
    {
        offset = parse(&tokens, offset);
        offset = execute(&tokens, offset);
    }
}
