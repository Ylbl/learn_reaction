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
            std::vector<std::function<void()>> m_observers_;

        public:
            void add_observer(const std::function<void()> &f)
            {
                m_observers_.emplace_back(f);
            }

            template<class... Args> void update_observers(const std::function<void()> &f, Args &&... args)
            {
                (void)(...,args.add_observer(f));
            }

            void notify()
            {
                for (auto &observer: m_observers_)
                {
                    observer();
                }
            }
    };
}

#endif //OBSERVERNODE_H
