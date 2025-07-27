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
/**
* @brief 占位
*/
    template<class Type, class... Args>
    class DataSource;

/**
* @brief 类型萃取
*/
    template<class Type>
    struct ExpressionTraits
    {
        using type = Type;
    };

/**
* @brief 类型萃取(特化)
*/
    template<class Type>
    struct ExpressionTraits<DataSource<Type> >
    {
        using type = Type;
    };

/**
* @brief 类型萃取(特化)
*/
    template<typename Fun, typename... Args>
    struct ExpressionTraits<DataSource<Fun, Args...> >
    {
        using type = std::invoke_result_t<Fun, typename ExpressionTraits<Args>::type...>;
    };

/**
* @brief 方便调用
*/
    template<class Fun, class... Args>
    using ReturnType = typename ExpressionTraits<DataSource<Fun, Args...>>::type;
/**
* @brief ?
*/
    template<class Fun, class... Args>
    class Expression : public Resource<ReturnType<Fun, Args...> >
    {
        private:
            Fun m_fun_;
            std::tuple<std::reference_wrapper<Args>...> m_args_;

        private:
            void evaluate()
            {
                auto result = [&]<std::size_t... I>(std::index_sequence<I...>)
                {
                    return std::invoke(m_fun_,
                                       std::get<I>(m_args_).get().get()...);
                }(std::make_index_sequence<std::tuple_size_v<decltype(m_args_)> >{});

                this->update_value(result);
            }

        public:
            template<class F, class... A>
            Expression(F &&f, A &&... args)
                : Resource<ReturnType<Fun, Args...> >(),
                  m_fun_(std::forward<F>(f)),
                  m_args_(std::forward<A>(args)...)
            {
                evaluate();
            }
    };

    template<class Type>
    class Expression<Type>
            : public Resource<Type>
    {
        public:
            using Resource<Type>::Resource;
    };
} // reaction

#endif //EXPRESSION_H
