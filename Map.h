#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

using namespace std;


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
     * @brief   Constructor overload to pre-define Map size
     * @param   n - initial Size of the Map
     */
    Map(int n);

    /**
     * @brief   Destructor. Destroys the Map and releases dynamic memory
     */
    ~Map();

    /**
     * @brief   Copy Constructor
     * @param   other - the other map to copy this one
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
     * @brief   Expands the internal dynamic array when the Map is full
     * @return  true if resizing succeeds, false otherwise
     */
    bool Resize();

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


#endif // MAP_H_INCLUDED
