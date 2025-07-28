//
// Created by Administrator on 25-7-26.
//

#ifndef RESOURCE_H
#define RESOURCE_H

#include <memory>
#include <stdexcept>

namespace reaction {
    template <class T>
    class Resource {
    private:
        /**
        * @brief 保存的值
        */
        std::unique_ptr<T> m_ptr_;

    public:
        /**
        * @brief 其一构造
        */
        Resource() : m_ptr_(nullptr) {
        }

        /**
        * @brief 其二构造
        */
        template <class Type>
        Resource(Type&& t): m_ptr_(std::make_unique<T>(std::forward<Type>(t))) {
        }

    public:
        /**
        * @brief 获取值
        */
        T& get_value() const {
            if (!m_ptr_) {
                throw std::runtime_error("Resource is not initialized");
            }
            return *m_ptr_;
        }

        /**
        * @brief 更新值
        */
        template <class Type>
        void update_value(Type&& t) {
            if (!m_ptr_) {
                m_ptr_ = std::make_unique<T>(std::forward<Type>(t));
            }
            *m_ptr_ = std::forward<Type>(t);
        }

        /**
        * @brief 安全
        * todo 用法?
        */
        Resource(const Resource&) = delete;

        Resource& operator=(const Resource&) = delete;

        Resource(Resource&&) = default;

        Resource& operator=(Resource&&) = default;
    };
} // reaction

#endif //RESOURCE_H
