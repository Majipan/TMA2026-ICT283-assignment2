#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

using namespace std;


// ----------------------------------------------

/**
 * @class Vector
 * @brief Dynamic Array
 *
 * @author Li Weihao
 * @version 01
 * @date 14/06/2026 Weihao Started
 */

template <class T>
class Vector
{
public:
    /**
     * @brief   Constructor
     */
    Vector();

    /**
     * @brief   Constructor Overload
     * @param   n - set the capacity of the array
     */
    Vector (int n);

    /**
     * @brief   Destructor
     */
    ~Vector();

    /**
     * @brief   Copy Constructor
     * @param   other - the other vector to copy this one
     */
    Vector(const Vector& other);


    /**
     * @brief   Insert values into the Vector based on index. Create (CRUD)
     * @param   index - the index where the new element is to be inserted
     * @param   data - the element to be inserted
     * @return  Boolean for success or fail
     */
    bool Insert(int index, const T& data);

    /**
     * @brief   Delete values from the Vector based on index. Delete (CRUD)
     * @param   index - the index of the element to be deleted
     * @return  Boolean for success or fail
     */
    bool Delete (int index);

    /**
     * @brief   Read values in the Vector based on index. Read (CRUD)
     * @param   index - the index of the element to be read
     * @return  Reference of immutable T, which is the value in the Vector
     */
    const T& operator[] (int index) const;

    /**
     * @brief   Update values in the Vector based on index. Update (CRUD)
     * @param   index - the index of the element to be updated
     * @return  Reference of T, which is the value in the Vector
     */
    T& operator[] (const int& index);

    /**
     * @brief   Getter for m_size member variable
     * @return  int
     */
    int Size() const;

    /**
    * @brief   Resize the vector array to 0
    */
    void Clear();

private:
    /// Keeps track of how many elements are in the Vector array
    int m_size;
    /// The total available capacity of the Vector array
    int m_capacity;
    /// Create
    T* m_vector;        // pointer to the array
};


// ----------------------------------------------


// Constructor
template <class T>
Vector<T>::Vector()
{
    m_size = 0;
    m_capacity = 8;
    m_vector = new T[m_capacity]; // request for memory on the heap
    if(m_vector == nullptr)       // fail to allocate memory
    {
        m_capacity = 0;
    }
}

// Constructor overload
template <class T>
Vector<T>::Vector(int n)
{
    m_size = n;
    m_capacity = n * 2;
    m_vector = new T[m_capacity]; // request for memory on the heap
    if(m_vector == nullptr)       // fail to allocate memory
    {
        m_capacity = 0;
    }
}

// Destructor
template <class T>
Vector<T>::~Vector()
{
    // if m_vector is not null;
    if (m_vector != nullptr)
    {
        delete[] m_vector;
    }

}

// Copy Constructor (this vector is a new vector, but a copy of another)
template <class T>
Vector<T>::Vector(const Vector& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    m_vector = new T[m_capacity];

    for (int i = 0 ; i < m_size; ++i)
    {
        m_vector[i] = other.m_vector[i];
    }
}


// ----------------------------------------------


template <class T>
bool Vector<T>::Insert(int index, const T& data)
{
    // likely heap memory is full and unable to expand the capacity anymore
    if (m_size == m_capacity)
    {
        return false;
    }

    // check if capacity is still more than twice of size
    if (m_size > m_capacity/2)
    {
        /*
        1) create temp array 2x the capacity of m_vector
        2) copy elements of m_vector to the temp array
        3) return memory of the m_vector
        4) point m_vector to temp array
        5) set temp array to null ptr
        */
        T* tempArray = new T[m_capacity * 2];       // create new temp array

        for (int i = 0; i < m_size; ++i)            // copy elements of m_vector into the temp array
        {
            tempArray[i] = m_vector[i];
        }

        delete[] m_vector;                          // return the memory of the vector
        m_vector = tempArray;                       // point m_vector to the temp array
        tempArray = nullptr;                        // remove temp pointer

        m_capacity = m_capacity * 2;                // set new capacity
    }

    // Ensure no Out-of-bounds index
    if (index >= 0 && index <= m_size)
    {
        // Insert between existing indexes
        if (index != m_size)
        {
            // shift elements to the right from current index
            for (int i = m_size; i > index; --i)
            {
                m_vector[i] = m_vector[i-1];
            }

            // insert the new element
            m_vector[index] = data;

        }
        else
        {
            // else insert at the back, which is [m_size]
            m_vector[m_size] = data;
        }

        ++m_size;           //increase the counter
        return true;

    }
    else
    {
        return false;
    }

}


template <class T>
bool Vector<T>::Delete (int index)
{
    // Ensure no Out-of-bounds index
    if (index >= 0 && index < m_size)
    {
        /*
            1) Move all elements forward from index onwards
            2) Reduce m_size by 1
        */
        for (int i = index; i < m_size - 1; ++i)
        {
            m_vector[i] = m_vector[i+1];
        }

        --m_size;
        return true;

    }
    else
    {
        return false;
    }
}


template <class T>
const T& Vector<T>::operator[] (int index) const
{
    if (index < 0 || index > m_size - 1)
    {
        // index is out of range, throw exception
    }

    return m_vector[index];
}


template <class T>
T& Vector<T>::operator[] (const int& index)
{
    if (index < 0 || index > m_size - 1)
    {
        // index is out of range, throw exception
    }

    return m_vector[index];
}


template <class T>
int Vector<T>::Size() const
{
    return m_size;
}


template <class T>
void Vector<T>::Clear()
{
    m_size = 0;
}

#endif // VECTOR_H_INCLUDED
