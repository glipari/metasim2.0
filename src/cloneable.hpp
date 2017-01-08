#ifndef __CLONEABLE_HPP__
#define __CLONEABLE_HPP__

#define BASE_CLONEABLE(Type) \
    virtual std::unique_ptr<Type> clone() const = 0;
 
#define CLONEABLE(Base, Type)                                \
    virtual std::unique_ptr<Base> clone() const { return std::unique_ptr<Base>(new Type(*this)); }

// template <typename Root, typename Base, typename Derived>
// class Cloneable : public Base
// {
// public:
//     using Base::Base;
    
//     std::unique_ptr<Root> clone() const
//     {
//         return std::unique_ptr<Root>(
//             new Derived(static_cast<Derived const &>(*this))
//             );
//     }

// protected:
//     typedef Cloneable<Root, Base, Derived> CloneableBase;
// };

#endif
