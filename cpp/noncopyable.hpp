// refer to boost::noncopyable

class noncopyable{
protected:
    // make constructor & distructor protected
    // for prohibiting create noncopyable class' instance
    noncopyable() = default;
    ~noncopyable() = default;
private:
    // disable copy constructor and = operator
    noncopyable(const noncopyable&) = delete;
    const noncopyable& operator=(const noncopyable&) = delete;
}