#pragma once

#include "ZPrimitives.h"

template <class T>
class TIterator
{
protected:
    TIterator(T* p_Current) : m_pCurrent(p_Current) {}

public:
    T* m_pCurrent;
};

template <class T>
class TArray
{
public:
    TArray() :
        m_pStart(nullptr),
        m_pEnd(nullptr),
        m_pLast(nullptr),
        m_pAllocationEnd(nullptr)
    {
    }

    void push_back(const T& p_Value)
    {
        // TODO: Inline support.
        size_t s_Size = size();
        resize(s_Size + 1);
        m_pStart[s_Size] = p_Value;
    }

	T* erase(T* p_Value) {
		size_t s_Size = size();

		for (size_t i = 0; i < s_Size; i++) {
			if (m_pStart[i] != p_Value) {
				continue;
			}

			// TODO: Call destructor?

			for (size_t j = i; j < s_Size - 1; j++) {
				m_pStart[j] = m_pStart[j + 1];
			}

			resize(s_Size - 1);
			return &m_pStart[i];
		}
	}


    void resize(size_t p_Size)
    {
        // TODO: Inline support.
        if (capacity() == p_Size)
            return;

        if (m_pStart == nullptr)
        {
            m_pStart = reinterpret_cast<T*>(malloc(sizeof(T) * p_Size));
            m_pEnd = m_pStart + p_Size;
            m_pAllocationEnd = m_pEnd;
            return;
        }

        m_pStart = reinterpret_cast<T*>(realloc(m_pStart, sizeof(T) * p_Size));
        m_pEnd = m_pStart + p_Size;
        m_pAllocationEnd = m_pEnd;
    }

    void clear()
    {
        if (m_pStart == nullptr)
            return;

        // TODO: Free individual items.

        if (!fitsInline() || !hasInlineFlag())
            free(m_pStart);

        m_pStart = m_pEnd = m_pAllocationEnd = nullptr;
    }
    inline size_t size() const
    {
        if (fitsInline() && hasInlineFlag())
            return m_nInlineCount;

        return (reinterpret_cast<uintptr_t>(m_pEnd) - reinterpret_cast<uintptr_t>(m_pStart)) / sizeof(T);
    }
    inline size_t capacity() const
    {
        if (fitsInline() && hasInlineFlag())
            return m_nInlineCapacity;

        return (reinterpret_cast<uintptr_t>(m_pAllocationEnd) - reinterpret_cast<uintptr_t>(m_pStart)) / sizeof(T);
    }
    inline T& operator[](size_t p_Index) const
    {
        return begin()[p_Index];
    }
    inline T* begin()
    {
        if (fitsInline() && hasInlineFlag())
            return reinterpret_cast<T*>(&m_pStart);

        return m_pStart;
    }

    inline T* end()
    {
        if (fitsInline() && hasInlineFlag())
            return begin() + m_nInlineCount;

        return m_pEnd;
    }

    inline T* begin() const
    {
        if (fitsInline() && hasInlineFlag())
            return (T*)(&m_pStart);

        return m_pStart;
    }

    inline T* end() const
    {
        if (fitsInline() && hasInlineFlag())
            return begin() + m_nInlineCount;

        return m_pEnd;
    }

    inline T* find(const T& p_Value) const
    {
        T* s_Current = begin();

        while (s_Current != end())
        {
            if (*s_Current == p_Value)
                return s_Current;

            ++s_Current;
        }

        return m_pEnd;
    }

    bool fitsInline() const
    {
        return sizeof(T) <= sizeof(T*) * 2;
    }

    bool hasInlineFlag() const
    {
        return (m_nFlags >> 62) & 1;
    }
public:
    T* m_pStart;
    T* m_pEnd;
    T* m_pLast;

    union
    {
        T* m_pAllocationEnd;
        int64_t m_nFlags;

        struct
        {
            uint8_t m_nInlineCount;
            uint8_t m_nInlineCapacity;
        };
    };
};

template<typename T>
class TFixedArray
{
public:
 /*   inline size_t size() const
    {
        return (reinterpret_cast<uintptr_t>(m_pEnd) - reinterpret_cast<uintptr_t>(m_pStart)) / sizeof(T);
    }

    inline size_t capacity() const
    {
        return (reinterpret_cast<uintptr_t>(m_pEnd) - reinterpret_cast<uintptr_t>(m_pStart)) / sizeof(T);
    }

    inline T& operator[](size_t p_Index) const
    {
        return m_pStart[p_Index];
    }

    inline T* begin()
    {
        return m_pStart;
    }

    inline T* end()
    {
        return m_pEnd;
    }

    inline T* begin() const
    {
        return m_pStart;
    }

    inline T* end() const
    {
        return m_pEnd;
    }

    inline T* find(const T& p_Value) const
    {
        T* s_Current = m_pStart;

        while (s_Current != m_pEnd)
        {
            if (*s_Current == p_Value)
                return s_Current;

            ++s_Current;
        }

        return m_pEnd;
    }
    */
public:
    T* m_pStart;
    T* m_pEnd;
};
