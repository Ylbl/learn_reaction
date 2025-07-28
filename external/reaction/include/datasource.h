//
// Created by Administrator on 25-7-26.
//

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "expression.h"

namespace reaction
{
    template <class Type, class... Args>
    class Datasource : public Expression<Type, Args...>
    {
    public:
        using Expression<Type, Args...>::Expression;
/**
* @brief ...
* TODO const用法?
*/
        auto get() const
        {
            return this->get_value();
        }
    };

    template <class Type> auto var(Type&& t)
    {
        return Datasource<Type>(std::forward<Type>(t));
    }

    template <class Fun, class... Args> auto calc(Fun&& fun, Args&&... args)
    {
        return Datasource<std::decay_t<Fun>, std::decay_t<Args>...>
            (std::forward<Fun>(fun), std::forward<Args>(args)...);
    }
} // namespace reaction

#endif  // DATASOURCE_H
