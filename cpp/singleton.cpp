#include "noncopyable.hpp"

#include <mutex>

// best practice after c++ 11
// it's thread-safe, because compiler will ensure that local static state variables are initialized when the function is called for the first time
// see Effective C++: Case 4 for more details
// with inheriting noncopyable class, singleton instance can not be copyed
// Singleton::GetInstance().do_something();       // ok
// Singleton instance = Singleton::GetInstance(); // failed, because Singleton instance cannot be copyed
class Singleton : noncopyable {
public:
    static Singleton* GetInstance() {
        // we don't use new to apply memory space
        // resource management will handled by compiler
        static Singleton m_instance;
        return &m_instance;
    }
    void do_something() {
        // do something here
    }
private:
    Singleton() {};
}

/**
 * @brief other Singleton realizations blow
 */

// naive singleton class
// lazy initialization
// it is not thread-safe (may create multiple instance in multi-thread environment)
class SingletonFoo1{
public:
    static SingletonFoo1* GetInstance() {
        if (!m_instance) {
            // if m_instance point to nullptr
            // use new to apply memory space
            m_instance = new SingletonFoo1();
        }
        return m_instance;
    }
    ~SingletonFoo1() {
        if (m_instance) {
            // if m_instance point to a instance
            // use delete to release memory space
            delete m_instance;
            // do not forget to move m_instance to nullptr
            m_instance = nullptr;
        }
    }
private:
    SingletonFoo1() {};
    static SingletonFoo1* m_instance;
}

// try to make SingletonFoo1 thread-safe
// we got SingletonFoo2, which is still lazy initialization but thread-safe
// but even if m_instance has been initialized, it still needs lock
class SingletonFoo2{
public:
    static SingletonFoo2* GetInstance() {
        // use a self-unlock lock to sync
        // always lock when GetInstance is called
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_instance)
            m_instance = new SingletonFoo2();
        return m_instance;
    }
    ~SingletonFoo2() {
        if (m_instance) {
            // if m_instance point to a instance
            // use delete to release memory space
            delete m_instance;
            // do not forget to move m_instance to nullptr
            m_instance = nullptr;
        }
    }
private:
    SingletonFoo2() {};
    static SingletonFoo2* m_instance;
    std::mutex m_mutex;
}

// try to avoid lock when m_instance has been initialized
// lazy initialization with DCL (Double-Check Locking)
// about DCL: https://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html
// before c++11, DCL is not reliable, refer to: https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
// after c++11, DCL has been fixed, read https://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/ for better DCL realization
class SingletonFoo3{
public:
    static SingletonFoo3* GetInstance() {
        // if m_instance has been initialized, don't lock
        if (!m_instance) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (!m_instance)
                m_instance = new SingletonFoo3();
        }
        return m_instance;
    }
    ~SingletonFoo3() {
        if (m_instance) {
            // if m_instance point to a instance
            // use delete to release memory space
            delete m_instance;
            // do not forget to move m_instance to nullptr
            m_instance = nullptr;
        }
    }
private:
    SingletonFoo3() {};
    static SingletonFoo3* m_instance;
    std::mutex m_mutex;
}
