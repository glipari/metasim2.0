#ifndef __CLONEABLE_HPP__
#define __CLONEABLE_HPP__

#define BASE_CLONEABLE(Type) \
    virtual std::unique_ptr<Type> clone() const = 0;
 
#define CLONEABLE(Base, Type)                                \
    virtual std::unique_ptr<Base> clone() const { return std::unique_ptr<Base>(new Type(*this)); }

#endif
