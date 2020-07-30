#ifndef RIVER_CORE_CONTAINER_H
#define RIVER_CORE_CONTAINER_H

#include <map>
#include <vector>
#include <set>
#include <stack>
#include <iostream>
#include <type_traits>

namespace ri
{
    /**
     * \brief represents a dictionary with key and value
     * \param K key type
     * \param V value type
     */
    template<class K, class V>
    struct Dictionary
    {
        /**
         * \brief initialize dictionary data structure
         */
        explicit Dictionary() 
        {
            m_map = std::map<K,V>();
        }


        /**
         * \brief remove an entry from dictionary
         * \param key key to remove
         * \return whether key has been removed (only true if key has been found)
         */
        auto remove(const K& key) -> bool 
        {
            if (!this->contains(key)) 
                return false;
            m_map.erase(m_map.find(key));
            return true;
        }

        /**
         * \brief add new entry to dictionary
         * \param key key to add
         * \param value corresponding value to key
         * \return whether adding succeded (only false if key has been found)
         */
        auto add(const K& key, V value) -> bool
        {
            if(this->contains(key))
                return false;
            m_map[key] = value;
            return true;
        }

        /**
         * \brief easy and recommended way to create, edit or receive an entry of dictionary
         * if the key does not exist it add a new key to the dictionary
         * otherwise it will just update the value
         * \param key corresponding key 
         * \return value reference of entry
         */
        auto operator[](const K& key) -> V&
        {
             return m_map[key];
        }

        /**
         * \brief is the dictionary empty?
         */
        auto isEmpty() const -> bool
        {
            return m_map.empty();
        }

        /**
         * \brief does this dictionary contain given key?
         * \param key given key to search in dictionary
         * \return whether key has been found or not
         */
        auto contains(const K& key) const -> bool
        {
            return (m_map.find(key) != m_map.end());
        }

        /**
         * \brief returns amount of elements in dictionary
         */
        auto length() const -> unsigned
        {
            return m_map.size();
        }

    private:
        std::map<K,V> m_map;
    };

    /**
     * \brief represents a stack data structure
     * \param T element type
     */
    template<class T>
    struct Stack
    {
        /**
         * \brief initialize stack data structure
         */
        explicit Stack() 
        {
            m_stack = std::stack<T>();
        }

        /**
         * \brief return element from top
         */
        auto top() -> T&
        {
            return m_stack.top();
        }

        /**
         * \brief remove element from top
         */
        auto pop() -> bool
        {
            if(m_stack.empty())
                return false;
            m_stack.pop();
        }

        /**
         * \brief push new element to top
         * \param obj object you want to push in
         */
        auto push(const T& obj) -> bool
        {
            m_stack.push(obj);
            return true;
        }

        /**
         * \brief returns if stack is empty
         */
        auto isEmpty() const -> bool
        {
            return m_stack.empty();
        }

    private:
        std::stack<T> m_stack;
    };

    /**
     * \brief represents a list structure
     * \param T element type
     */
    template<class T>
    struct List
    {
        /**
         * initialize a list data structure
         */
        explicit List() 
        {
            m_vector = std::vector<T>();
        }

        /**
         * \brief returns first element of list
         */
        auto front() const -> T&
        {
            return m_vector.front();
        }

        /**
         * \brief returns last element of list
         */
        auto back() const -> T&
        {
            return m_vector.back();
        }

        /**
         * \brief remove element form list
         * please do not use this for primitve data types, instead use erase
         */
        auto remove(const T& obj) -> bool
        {
            if(std::is_fundamental<T>::value)
                throw std::runtime_error("warning: bad practise! Please do use removeAt(index) for primitve types!");
            
            for(auto it = m_vector.begin(); it != m_vector.end(); it++)
            {
                if(*it == obj)
                {
                    m_vector.erase(it);
                    return true;
                }
            }
            return false;
        }

        /**
         * \brief erase element from list
         */
        auto removeAt(int index) -> bool
        {
            if(index > this->length())
                throw std::out_of_range("index was out of range!");

            auto tmp = m_vector.begin()+index;

            for(auto it = m_vector.begin(); it != m_vector.end(); it++)
            {
                if(it == tmp)
                {
                    m_vector.erase(it);
                    return true;
                }
            }
            return false;
        }

        /**
         * \brief push item to end of the list
         */
        auto pushBack(const T& obj)
        {
            m_vector.push_back(obj);
        }

        /**
         * \brief insert item at given index
         * check index range
         */
        auto insert(int index, T obj) -> bool
        {
            if(index > this->length())
                throw std::out_of_range("index was out of range!");

            auto it = m_vector.begin();
            m_vector.insert(it+index, obj);
            return true;
        }

        /**
         * \brief classic way of accessing list element
         */
        auto operator[](int index) const -> T
        {
            if(index > this->length())
                throw std::out_of_range("index was out of range!");
            
            auto&& v = *(m_vector.begin()+index);
            return std::move(v);
        }

        /**
         * \brief returns length of list
         */
        auto length() const -> unsigned
        {
            return m_vector.size();
        }

        /**
         * \brief whether list is empty
         */
        auto isEmpty() const -> bool
        {
            return m_vector.empty();
        }

    private:
        std::vector<T> m_vector;
    };

    /**
     * \brief represents a set data structure
     * \param T element type
     */
    template<class T>
    struct Set
    {
        /**
         * \brief initialize a set data structure
         */
        explicit Set()
        {
            m_set = std::set<T>();
        }

        /**
         * \brief add an element to set
         * \param element object to insert 
         */
        auto add(const T& element) -> bool
        {
            m_set.insert(element);
            return true;
        }

        /**
         * \brief remove element from set
         * \param element given element to remove from set
         */
        auto remove(const T& element) -> bool
        {
            m_set.erase(element);
            return true;
        }

        /**
         * \brief is set empty?
         */
        auto isEmpty() const -> bool
        {
            return m_set.empty();
        }

        /**
         * \brief does the set contains given element?
         * \param element given element to compare
         */
        auto contains(T element) const -> bool
        {
            return (m_set.find(element) != m_set.end());
        }
    private:
        std::set<T> m_set;
    };
}
#endif