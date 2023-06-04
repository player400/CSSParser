#pragma once

template<typename T>
class LinkedList
{
private:
    unsigned int size = 0;

public:
    template<typename T>
    class ListElement
    {
    private:
        ListElement<T>* next;
        ListElement<T>* previous;
        T data;

    public:

        ListElement<T>* create(T data)
        {
            next = new ListElement<T>(this, data);
            return next;
        }

        ListElement<T>* previous_element()
        {
            return previous;
        }

        void set_next(ListElement<T> next)
        {
            this->next = next;
        }

        void set_previous(ListElement<T> previous)
        {
            this->previous = previous;
        }

        ListElement<T>* next_element()
        {
            return next;
        }

        T get_data()
        {
            return data;
        }

        void set_data(T data)
        {
            this->data = data;
        }

        ListElement()
        {

        }

        ListElement(ListElement<T>* previous, T data)
        {
            this->previous = previous;
            this->data = data;
        }
    };

    ListElement<T>* root;

    ListElement<T>* last;

    ListElement<T>* get_element(int index)
    {
        ListElement<T>* current = root;
        for (int i = 0; i <= index; i++)
        {
            current = current->next_element();
        }
        return current;
    }

    void delete_element(int index)
    {
        ListElement<T>* deleted = get_element(index);
        deleted->next_element()->set_previous(deleted->previous_element());
        deleted->previous_element()->set_next(deleted->next_element());
        delete deleted;
    }

    T get_data(int index)
    {
        return get_element(index)->get_data();
    }

    ListElement<T>* add(T data)
    {
        ListElement<T>* new_element = last->create(data);
        last = new_element;
        size++;
        return new_element;
    }

    ListElement<T>* operator[](int index)
    {
        return get_element(index);
    }

    LinkedList()
    {
        root = new ListElement<T>();
        last = root;
    }

    int get_size()
    {
        return size;
    }

    ~LinkedList()
    {
        ListElement<T>* current = last;
        for (int i = 0; i < size; i++)
        {
            ListElement<T>* to_delete = current;
            current = current->previous_element();
            delete to_delete;
        }
        delete root;
    }


};

