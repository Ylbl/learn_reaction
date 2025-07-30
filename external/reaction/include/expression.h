//
// Created by Administrator on 25-7-26.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <type_traits>
#include <utility>

#include "resource.h"

namespace reaction
{
    /// @brief 占位
    /// @tparam Type
    /// @tparam Args
    template<class Type, class... Args>
    class Datasource;

    /// @brief 类型萃取
    /// @tparam Type
    template<class Type>
    struct ExpressionTraits
    {
        using type = Type;
    };

    /// @brief 类型萃取
    /// @tparam Fun
    /// @tparam Args
    template<class Fun, class... Args>
    struct ExpressionTraits<Datasource<Fun, Args...> >
    {
        using type = std::invoke_result_t<Fun, typename ExpressionTraits<Args>::type...>;
    };

    /// @brief 类型萃取,特化版
    /// @tparam Type
    template<class Type>
    struct ExpressionTraits<Datasource<Type> >
    {
        using type = Type;
    };

    /// @brief 方便调用.
    /// Resource构造函数只接受一个类型
    /// ReturnType<Fun, Args...>的结果就是那个要的类型
    template<class Fun, class... Args>
    using ReturnType = typename ExpressionTraits<Datasource<Fun, Args...> >::type;

    /// @brief Expression
    /// @tparam Fun
    /// @tparam Args
    template<typename Fun, typename... Args>
    class Expression : public Resource<ReturnType<Fun, Args...> >
    {
        private:
            Fun m_fun_;
            /// @brief 更方便好用的类型
            /// std::reference_wrapper<Args>...=参数包
            /// 什么类型的参数?==>用std::reference_wrapper 包装过的
            std::tuple<std::reference_wrapper<Args>...> m_args_;

        private:
            void evaluate()
            {
                /// @brief ...
                /// auto result=[&]<std::size_t I>(类型 参数1){实现}(传入参数);
                /// TODO std::make_index_sequence<std::tuple_size_v<decltype(m_args_)>>{}啥子意思
                auto result = [&]<std::size_t... I>(std::index_sequence<I...>)
                {
                    return std::invoke(m_fun_, std::get<I>(m_args_).get().get()...);
                }(std::make_index_sequence<std::tuple_size_v<decltype(m_args_)> >{});

                this->update_value(result);
            }

            /// @brief ...
            /// Resource<ReturnType<Fun, Args>>()初始化类就应该用这个类拿到的Fun,Args
            /// m_fun_(std::forward<F>(fun))自己的变量就用Expression(F&& fun, A&&... args)拿到的
        public:
            template<class F, class... A>
            Expression(F &&fun, A &&... args)
                : Resource<ReturnType<Fun, Args...> >(),
                  m_fun_(std::forward<F>(fun)),
                  m_args_(std::forward<A>(args)...)
            {
                evaluate();
            }
    };

    template<typename Type>
    class Expression<Type> : public Resource<Type>
    {
        public:
            using Resource<Type>::Resource;
    };
} // reaction

#endif //EXPRESSION_H
