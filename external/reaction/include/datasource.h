//
// Created by Administrator on 25-7-26.
//

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "expression.h"

namespace reaction
{
    /// @brief Datasource
    /// @tparam Type
    /// @tparam Args
    template<class Type, class... Args>
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

            /// @brief 设定值
            /// @tparam T
            /// @param t
            template<class T> void set(T &&t)
            {
                this->set_value(std::forward<T>(t));
                this->notify();
            }

            Datasource(const Datasource &) = delete;

            Datasource &operator=(const Datasource &) = delete;

            Datasource(Datasource &&) = default;

            Datasource &operator=(Datasource &&) = default;
    };

    /// @brief 数据型
    /// @tparam Type
    /// @param t
    /// @return
    template<class Type> auto var(Type &&t)
    {
        return Datasource<Type>(std::forward<Type>(t));
    }

    /// @brief 计算型
    /// @tparam Fun
    /// @tparam Args
    /// @param fun
    /// @param args
    /// @return
    template<class Fun, class... Args> auto calc(Fun &&fun, Args &&... args)
    {
        return Datasource<std::decay_t<Fun>, std::decay_t<Args>...>
                (std::forward<Fun>(fun), std::forward<Args>(args)...);
    }
} // namespace reaction

#endif  // DATASOURCE_H
