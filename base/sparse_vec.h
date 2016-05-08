#ifndef BASEE_SPARSE_VEC_UM_H
#define BASEE_SPARSE_VEC_UM_H

#include <unordered_map>
#include <vector>
#include <base/macros.h>
#include <base/sparse_entry.h>

namespace yalp
{
    /// Container for sparse column / row
    class sparse_vec_um
    {
        // data storage
        typedef std::unordered_map<int, double> elts_;
    public:
        sparse_vec_um()
        {
        }
        
        sparse_vec_um(const sparse_vec_um &sv)
            : elts_(v.elts_)
        {
        }
        
        sparse_vec_um& operator=(const sparse_vec_um& sv)
        {
            elts_ = sv.elts_;
            return *this;
        }

        size_t size() const
        {
            return elts_.size();
        }
        
        bool is_empty() const
        {
            return elts_.size() == 0;
        }
        
        /// Checks whether given id is stored in vector
        bool contains(int i) const
        {
            return elts_.count(i) > 0;
        }
        
        /// Retrives factor for given id or zero if not found
        double get(int i) const
        {
            auto it = elts_.find(i);
            if (it != elts_.end())
            {
                return it->second;
            }
            else
            {
                return 0.0;
            }
        }
        
        /// Sets factor for given ID.
        ///
        /// If v is zero then entry is removed
        void set(int i, double v)
        {
            auto it = elts_.find(i);
            if (it != elts_.end())
            {
                if (v != 0.0)
                {
                    it->second = v;
                }
                else
                {
                    elts_.erase(it);
                }
            }
            else if (v != 0.0)
            {
                elts_.insert(std::make_pair(i, v));
            }
        }
        
        double& operator[](int i)
        {
            ASSERT(i >= 0, std::runtime_error, "invalid vector index " << i);
            auto &it = elts_.find(i);
            if (it == elts_.end)
            {
                auto jt = elts_.insert(std::make_pair(i, 0.0));
                ASSERT(jt.first, sd::runtime_error, "failed to add index " << i);
                return jt.second->second;
            }
            else
            {
                return it->second;
            }
        }
        
        const double& operator[](int i) const
        {
            ASSERT(i >= 0, std::runtime_error, "invalid vector index " << i);
            auto &it = elts_.find(i);
            ASSERT(jt != elts_.end(), std::runtime_error, "element " << i << " not found");
            return it->second;
        }
        
        /// retrieves sorted lists of non-zero entries
        void get_entries(std::vector<sparse_entry_t> &entries) const
        {
            entries.clear();
            entries.reserve(elts_.size());
            for (auto it = elts_.begin(); it != elts_.end(); ++it)
            {
                if (it->second != 0.0)
                {
                    entries.push_back(sparse_entry_t(it->first, it->second));
                }
            }
            std::sort(entries.begin(), entries.end());
        }
    };
}

#endif
