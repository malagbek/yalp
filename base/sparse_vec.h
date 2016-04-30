#ifndef BASEE_SPARSE_VEC_UM_H
#define BASEE_SPARSE_VEC_UM_H

#include <unordered_map>
#include <vector>
#include <base/macros.h>

namespace yalp
{
    /// Container for sparse column / row
    class sparse_vec_um
    {
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

        bool is_empty() const
        {
            return elts_.size() == 0;
        }
        
        bool contains(int i) const
        {
            return elts_.count(i) > 0;
        }
        
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
        
        /// retrieves sorted lists of indices and factors
        void get(std::vector<int> &indices, std::vector<double> &factors) const
        {
            indices.clear();
            indices.reserve(elts_.size());
            for (auto it = elts_.begin(); it != elts_.end(); ++it)
            {
                indices.push_back(it->first);
            }
            std::sort(indices.begin(), indices.end());
            factors.clear();
            factors.reserve(elts_.size());
            for (auto it = indices.begin(); it != indices.end(); ++it)
            {
                factors.push_back(elts_[*it]);
            }
        }
    };
}

#endif
