#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

template <class elemType>
class stack{
public:
    virtual elemType pop() = 0;
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType & obj) = 0;
    virtual elemType top() const = 0;
    virtual ~stack() {}
};

#endif // STACK_H_INCLUDED
