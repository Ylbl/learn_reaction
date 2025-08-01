//
// Created by Administrator on 25-7-31.
//
#ifndef OBSERVERNODE_H
#define OBSERVERNODE_H

#include <functional>

#include  "vector"

namespace reaction
{
    class ObserverNode
    {
        private:
            /// @brief 观察者容器
            std::vector<ObserverNode *> m_observers_;

        public:
            /// @brief 虚函数
            virtual void change_value() {}

            /// @brief 添加观察者
            /// args就是传进来的a b等组成的包
            /// @tparam Args
            /// @param args
            template<class... Args> void add_observers(Args &&... args)
            {
                (..., args.m_observers_.emplace_back(this));
            }

            /// @brief 通知观察者
            void notify()
            {
                for (auto &observer: m_observers_)
                {
                    observer->change_value();
                }
            }
    };
}

#endif //OBSERVERNODE_H
