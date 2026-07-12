#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

using namespace std;
#include <iostream>


// ----------------------------------------------


/**
 * @class Map
 * @brief Template Map
 *
 * @author Li Weihao
 * @version 01
 * @date 10/07/2026 Weihao Started
 */

 template <class K, class V>
 class Map
 {
 public:
    /**
     * @brief   Constructor. Creates an empty Map with default capacity
     */
    Map();

    /**
     * @brief   Parameterised Constructor to pre-define Map size
     * @param   n - initial Size of the Map
     */
    Map(int n);

    /**
     * @brief   Destructor. Destroys the Map and releases dynamic memory
     */
    ~Map();

    /**
     * @brief   Copy Constructor
     * @param   other - the other map for this to copy
     */
    Map(const Map& other);

    /**
     * @brief   Insertion values into the Map
     * @param   key - the key for a single map record
     * @param   value - the value for a single map record
     * @return  true if replaced, false if key already exist
     */
    bool Insert(const K& key, const V& value);

    /**
     * @brief   Replaces the value for an existing key
     * @param   key - the key for a single map record
     * @param   value - the value for a single map record to replace the existing value based on the key
     * @return  true if replaced, false if key does not exist
     */
    bool ReplaceValue(const K& key, const V& value);

    /**
     * @brief   Search a map record
     * @param   key - key to a single map record
     * @return  true if found, false if not found
     */
     bool Search(const K& key) const;

     /**
     * @brief   Gets read-only access to the value for a key
     * @param   key - key to a single map record
     * @return  V - pointer to value if found, nullptr if not found
     */
    const V* GetValue(const K& key) const;

    /**
     * @brief   Checks the number of key-value pairs in the Map
     * @return  Returns the number of key-value pairs in the Map
     */
    int Size() const;

    /**
     * @brief   Get the key of a Map record at a certain index. This is used mainly by the << operator
     * @param   index - the index at which the record is to be extracted
     * @return  Returns key of the map record at a certain index
     */
    const K& GetKeyAt(int index) const;

    /**
     * @brief   Get the Value of a Map record at a certain index. This is used mainly by the << operator
     * @param   index - the index at which the record is to be extracted
     * @return  Returns Value of the map record at a certain index
     */
    const V& GetValueAt(int index) const;

    /**
     * @brief   Assigns one Map to another using deep copy
     */
    Map<K, V>& operator=(const Map<K, V>& other);

 private:
    /// Struct for a single record
    struct Entry
    {
        K key;
        V value;
    };

    /// Pointer to an array to be created
    Entry* m_entries;
    /// Number of records in the map
    int m_size;
    /// Current max number of records the Map is able to store
    int m_capacity;

    /**
     * @brief   Finds the array index of a key
     * @param   key - The key to search for
     * @return  Index of the key if found, otherwise -1
     */
    int SearchIndex(const K& key) const;

    /**
     * @brief   Helper that expands the internal dynamic array when the Map is full
     */
    void Resize();

    /**
     * @brief   Performs a deep copy from another Map
     * @param   other - The Map to copy from
     */
    void CopyFrom(const Map<K, V>& other);

    /**
     * @brief   Releases the dynamic array owned by the Map
     */
    void DeleteData();
 };


 // ----------------------------------------------
 // Constructor
template <class K, class V>
Map<K, V>::Map()
{
    m_size = 0;
    m_capacity = 10;
    m_entries = new Entry[m_capacity];  // request for memory on the heap
    if (m_entries == nullptr)           // fail to allocate memory
    {
        m_capacity = 0;
    }
}

// Constructor overload
template <class K, class V>
Map<K, V>::Map(int n)
{
    m_size = 0;
    m_capacity = n * 2;
    m_entries = new Entry[m_capacity];  // request for memory on the heap
    if (m_entries == nullptr)            // fail to allocate memory
    {
        m_capacity = 0;
    }
}

// Destructor
template <class K, class V>
Map<K, V>::~Map()
{
    if (m_entries != nullptr)
    {
        DeleteData();
    }
}

// ----------------------------------------------
// Copy-constructor
template <class K, class V>
Map<K, V>::Map(const Map<K, V>& other)
{
    m_entries = 0;
    m_size = 0;
    m_capacity = 0;

    CopyFrom(other);
}

// Helper for copy constructor
template <class K, class V>
void Map<K, V>::CopyFrom(const Map<K, V>& other)
{
    m_capacity = other.m_capacity;
    m_size = other.m_size;

    if(m_capacity > 0)
    {
        m_entries = new Entry[m_capacity];

        for(int i = 0; i < m_size; ++i)
        {
            m_entries[i] = other.m_entries[i];
        }
    }
    else
    {
        m_entries = 0;
    }
}

// Assignment Operator
template <class K, class V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& other)
{
    if(this != &other)
    {
        DeleteData();
        CopyFrom(other);
    }

    return *this;
}


// ----------------------------------------------
// Insert
template <class K, class V>
bool Map<K, V>::Insert(const K& key, const V& value)
{
    // Checks if the key already exists and stop insert if exist
    if (Search(key))
    {
        return false;
    }

    // Checks if size is larger than half of capacity, if so expand first
    if (m_size > m_capacity/2)
    {
        Resize();
    }

    m_entries[m_size].key = key;
    m_entries[m_size].value = value;
    ++m_size;

    return true;
}

// Resize when size exceeds limit
template <class K, class V>
void Map<K, V>::Resize()
{
    // Set new capacity to two times of what it initially was
    Entry* tempArray = new Entry[m_capacity * 2];

    // copy the data over to the temp array
    for (int i = 0; i < m_size; ++i)
    {
        tempArray[i] = m_entries[i];
    }

    // delete the original map and set the map pointer to the new map
    delete[] m_entries;
    m_entries = tempArray;
    tempArray = nullptr;

    m_capacity = m_capacity * 2;
}

// Search if a key exists and returns it's index
template <class K, class V>
bool Map<K, V>::Search(const K& key) const
{
    /*for (int i = 0; i < m_size; ++i)
    {
        if (m_entries[i].key == i)
        {
            return true;
        }
    }

    return false;*/

    return SearchIndex(key) != -1;
}


// ----------------------------------------------
// Replace value at an index
template <class K, class V>
bool Map<K, V>::ReplaceValue(const K& key, const V& value)
{
    int index = SearchIndex(key);

    // checks if key exists, if not return false
    if(index == -1)
    {
        return false;
    }

    m_entries[index].value = value;
    return true;
}

// Helper function to get index, return -1 if it doesn't
template <class K, class V>
int Map<K, V>::SearchIndex(const K& key) const
{
    for(int i = 0; i < m_size; ++i)
    {
        if(m_entries[i].key == key)
        {
            return i;
        }
    }

    return -1;
}


// ----------------------------------------------
// Get the value from a key
template <class K, class V>
const V* Map<K, V>::GetValue(const K& key) const
{
    int index = SearchIndex(key);

    if(index == -1)
    {
        return 0;
    }

    return &m_entries[index].value;
}

// Get the key at a particular index
template <class K, class V>
const K& Map<K, V>::GetKeyAt(int index) const
{
    //assert(index >= 0 && index < m_size);
    return m_entries[index].key;
}

// Get the value at a particular index
template <class K, class V>
const V& Map<K, V>::GetValueAt(int index) const
{
    //assert(index >= 0 && index < m_size);
    return m_entries[index].value;
}


// ----------------------------------------------
// Delete the Map and free the memory
template <class K, class V>
void Map<K, V>::DeleteData()
{
    delete[] m_entries;
    m_entries = 0;
    m_size = 0;
    m_capacity = 0;
}
#endif // MAP_H_INCLUDED
