#ifndef BASE_SPARSE_ENTRY_H
#define BASE_SPARSE_ENTRY_H

namespace yalp
{
    struct sparse_entry_t
    {
        int id;
        double factor;

        entry_t() 
        : id(-1)
        , factor(0.0)
        {}

        entry_t(int i, double v)
        : id(i)
        , factor(v)
        {}

        entry_t(const entry_t &e)
        : id(e.id)
        , factor(e.factor)
        {}

        entry_t operator=(const entry_t &e)
        {
            id = e.id;
            factor = e.factor;
            return *this;
        }
            
        bool operator<(const entry_t &e)
        {
            return id < e.id;
        }
    };
}

#endif
