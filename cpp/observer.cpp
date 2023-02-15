#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Observer{
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Subject{
private:
    vector<unique_ptr<Observer>> observers;
public:
    void append(unique_ptr<Observer>& observer) {
        observers.emplace_back(std::move(observer));
    }

    void notify() {
        for (auto& ob : observers)
            ob->update();
    }
};

class ObserverA : public Observer{
public:
    void update() override {
        printf("ObserverA update!\n");
    }
};

class ObserverB : public Observer{
public:
    void update() override {
        printf("ObserverB update!\n");
    }
};

int main() {
    Subject sub;
    unique_ptr<Observer> a = make_unique<ObserverA>();
    unique_ptr<Observer> b = make_unique<ObserverB>();
    sub.append(a);
    sub.append(b);
    sub.notify();
}