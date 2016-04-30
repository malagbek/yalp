#ifdnef BASE_COL_H
#define BASE_COL_H

#include <base/macros.h>

namespace yalp
{
    class Col
    {
        int id_;
    public:
        Col()
            : id_(-1)
        {
        }
        
        explicit Col(int id)
        {
            ASSERT2(id >= 0, std::runtime_error, "invalid Col id: " << id);
            id_ = id;
        }
        
        Col(const Col &c)
            : id_(c.id_)
        {
        }
        
        Col& operator=(const Col &c)
        {
            id_ = c.id_;
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
        
        bool operator<(const Col &c) const
        {
            return id_ < c.id_;
        }
        
        bool operator==(const Col &c) const
        {
            return id_ == c.id_;
        }
    };
}

namespace std
{
    template<>
    struct hash<yalp::Col>
    {
        size_t operator()(const yalp::Col &c) const
        {
            // invalid will map to something large
            return static_cast<size_t>(c.id());
        }
    }
}

#endif
