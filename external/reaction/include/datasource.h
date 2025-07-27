//
// Created by Administrator on 25-7-26.
//

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "expression.h"

namespace reaction
{
    class Datasource
    {
        public:
            auto get()
            {

            }
    };

    template<class T>
    auto var(T &&t)
    {
        return Datasource();
    }

    template<class F, class... Args>
    auto calc(F &&f, Args &&... args) {}
} // namespace reaction

#endif  // DATASOURCE_H
