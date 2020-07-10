#include <stddef.h>

template <typename T>
class smartPtr
{
public:
    smartPtr()
    : m_ptr(nullptr)
    , m_counter(new size_t(0))
    {
    }

    smartPtr(T* P)
    : m_ptr(P)
    , m_counter(new size_t(1))
    {
    }

    smartPtr(const smartPtr<T> &P)
    : m_ptr(P.m_ptr)
    , m_counter(P.m_counter)
    {
        Inc();
    }

    ~smartPtr()
    {
        Dec();
    }

    smartPtr operator=(T* P)
    {
        Dec();
        if (P)
        {
            m_ptr = P;
            m_counter = new size_t(1);
        }
        else
        {
            m_ptr = nullptr;
            m_counter = new size_t(0);
        }
        return *this;
    }

    smartPtr operator=(smartPtr<T> &P)
    {
        if (this != &P)
        {
            Dec();
            m_ptr = P.m_ptr;
            m_counter = P.m_counter;
            Inc();
        }
        return *this;
    }

    operator bool() const
    {
        return m_counter != 0;
    }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    template<typename C> friend class smartPtr;

    template<typename C>
    smartPtr(const smartPtr<C> &P)
    : m_ptr(P.m_ptr)
    , m_counter(P.m_counter)
    {
        Inc();
    }

    template<typename C>
    smartPtr<T> operator=(smartPtr<C> &P)
    {
        Dec();
        m_ptr = P.m_ptr;
        m_counter = P.m_counter;
        Inc();
        return *this;
    }

    template<typename C>
    smartPtr<C> Cast() const
    {
        C* converted = dynamic_cast<C*>(m_ptr);
        smartPtr<C> result;
        if (converted)
        {
            result.m_ptr = converted;
            result.m_counter = m_counter;
            result.Inc();
        }
        return result;
    }

    inline int getPtrPointer() const { return *m_ptr; }
    inline size_t getPtrCounter() const { return *m_counter; }

private:
    T* m_ptr;
    size_t* m_counter;

    void Inc()
    {
        if (m_counter)
            ++*m_counter;
    }

    void Dec()
    {
        if (m_counter && --*m_counter == 0)
        {
            delete m_ptr;
            delete m_counter;
            m_ptr = nullptr;
            m_counter = nullptr;
        }
    }
};