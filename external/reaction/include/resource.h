//
// Created by Administrator on 25-7-26.
//

#ifndef RESOURCE_H
#define RESOURCE_H

#include <memory>
#include <exception>
#include <stdexcept>

namespace reaction
{
    template<class Type>
    class Resource
    {
        private:
            std::unique_ptr<Type> m_ptr_;

        public:
            Resource(const Resource &) = delete;

            Resource &operator=(const Resource &) = delete;

            Resource(Resource &&) = default;

            Resource &operator=(Resource &&) = default;
/**
* @brief ?
*/
            Resource() : m_ptr_(nullptr) {}

            template<class T>
            Resource(T &&t): m_ptr_(std::make_unique<Type>(std::forward<T>(t))) {}

            Type &get_value()
            {
                if (!m_ptr_)
                {
                    throw std::runtime_error("Resource is not initialized");
                }

                return *m_ptr_;
            }

            template<class T>
            void update_value(T &&t)
            {
                if (!m_ptr_)
                {
                    m_ptr_ = std::make_unique<Type>(std::forward<T>(t));
                }

                *m_ptr_ = std::forward<T>(t);
            }
    };
} // reaction

#endif //RESOURCE_H
