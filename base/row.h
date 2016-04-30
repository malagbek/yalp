#ifdnef BASE_ROW_H
#define BASE_ROW_H

#include <base/macros.h>

namespace yalp
{
    class Row
    {
        int id_;
    public:
        Row()
            : id_(-1)
        {
        }
        
        explicit Row(int id)
        {
            ASSERT2(id >= 0, std::runtime_error, "invalid row id: " << id);
            id_ = id;
        }
        
        Row(const Row &r)
            : id_(r.id_)
        {
        }
        
        Row& operator=(const Row &r)
        {
            id_ = r.id_;
            return *this;
        }
        
        int id() const
        {
            return id_;
        }
        
        bool is_valid() const
        {
            return id_ >= 0;
        }
        
        bool operator<(const Row &r) const
        {
            return id_ < r.id_;
        }
        
        bool operator==(const Row &r) const
        {
            return id_ == r.id_;
        }
    };
}

namespace std
{
    template<>
    struct hash<yalp::Row>
    {
        size_t operator()(const yalp::Row &r) const
        {
            // invalid will map to something large
            return static_cast<size_t>(r.id());
        }
    }
}

#endif
