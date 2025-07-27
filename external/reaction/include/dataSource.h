//
// Created by Administrator on 25-7-26.
//

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "expression.h"

namespace reaction
{
/**
* @brief ?
*/
    template<class T, class... Args>
    class DataSource : public Expression<T, Args...>
    {
        public:
            using Expression<T, Args...>::Expression;

        public:
            auto get()
            {
                return this->get_value();
            }
    };
/**
* @brief var
*/
    template<class T>
    auto var(T &&t)
    {
        return DataSource<T>(std::forward<T>(t));
    }
/**
* @brief calc
* std::decay_t去掉const等干扰
*/
    template<class Fun, class... Args>
    auto calc(Fun &&fun, Args &&... args)
    {
        return DataSource<std::decay_t<Fun>,std::decay_t<Args>...>
        (std::forward<Fun>(fun),std::forward<Args>(args)...);
    }
} // namespace reaction

#endif  // DATASOURCE_H
