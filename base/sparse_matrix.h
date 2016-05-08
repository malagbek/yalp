#ifndef BASE_SPARSE_MATRIX_H
#define BASE_SPARSE_MATRIX_H

#include <base/config.h>

namespace yalp
{
    class sparse_matrix_base
    {
    protected:
        /// number of rows
        size_t num_rows_;
        /// number of columns
        size_t num_cols_;
        /// list of columns / rows
        std::vector<sparse_vec_t> matrix_;
    public:
        /// data structure used for IO
        typedef std::vector<sparse_entry_t> sparse_list_t;
        
        sparse_matrix_base()
        : num_rows_(0)
        , num_cols_(0)
        {
        }
        
        sparse_matrix_base(size_t nr, size_t nc)
            : num_rows_(nr)
            , num_cols_(nc)
        {
            init();
        }
    
        virtual ~sparse_matrix_base()
        {
        }
        
        /// Number of matrix rows
        size_t num_rows() const
        {
            return static_cast<size_t>(num_rows_);
        }
        
        /// Number of matrix columns
        size_t num_cols() const
        {
            return static_cast<size_t>(num_cols_);
        }
        
        /// Determines number of non-zero entries
        size_t num_nz() const
        {
            size_t nnz = 0;
            for (auto it = matrix_.begin(); it != matrix_.end(); ++it)
            {
                nnz += it->size();
            }
            return nnz;
        }
        
        void resize(size_t nr, size_t nc)
        {
            num_rows_ = nr;
            num_cols_ = nc;
            internal_resize();
        }
        
        void clear()
        {
            num_rows_ = 0;
            num_cols_ = 0;
            matrix_.clear();
        }
        
        /// Sets factor of given (r,c) element to given value
        virtual void set(int r, int c, double v) = 0;
        
        /// Retrieves factor of given element
        virtual double get(int r, int c) const = 0;

        /// Retrieves elements of given row
        virtual void get_row(int r, sparse_list_t &row) const = 0;
        
        /// Retrieves elements of given column
        virtual void get_col(int c, sparse_list_t &col) const = 0;
        
        /// Removes entries for given row, does not resize matrix
        virtual void clear_row(int r) = 0;
        
        /// Removes entries for given column, does not resize matrix
        virtual void clear_col(int c) = 0;
        
        /// Removes given row and reduces #rows by 1
        virtual void erase_row(int r) = 0;
        
        /// Removes given column and #cols by 1
        virtual void erase_col(int c) = 0;
        
        /// Overwrites given row with given entries
        virtual void set_row(int r, const sparse_list_t &row) const = 0;

        /// Overwrites given column with given entries
        virtual void set_col(int c, const sparse_list_t &col) const = 0;
        
        /// Retrieves matrix in compressed sparse row format
        ///
        /// values array contains non-zero values of matrix
        /// col_idx contains column indices for each nz entry
        /// row_ptr stores start and (open)end indices for each row,
        /// e.g. row_ptr[0] = 0 and row_ptr[1] = 3 means that
        /// row 0 contains elements 0, 1, and 2. Last element int
        /// row_ptr stores total number of non-zeros
        virtual void get_csr(std::vector<double> &values,
                             std::vector<int> &col_idx,
                             std::vector<int> &row_ptr) const;
        
        /// Retrieves matrix in compressed sparse column format
        ///
        /// Works similar to csr but traverses columns.
        virtual void get_csc(std::vector<double> &values,
                             std::vector<int> &row_idx,
                             std::vector<int> &col_ptr) const;
    protected:
        /// does internal resizing
        virtual void internal_resize();
    };
    
    /// Column-based matrix
    class sparse_matrix_c : public sparse_matrix_base
    {
    public:
        virtual void set(int r, int c, double v) = 0
        {
            ASSERT2(r >= 0 && r < num_rows_ && c >= 0 && c < num_cols_,
                   std::runtime_error, "invalid row/col");
            matrix_[c].set(r, v);
        }
        
        virtual double get(int r, int c) const
        {
            ASSERT2(r >= 0 && r < num_rows_ && c >= 0 && c < num_cols_,
                   std::runtime_error, "invalid row/col");
            return matrix_[c].get(r);
        }
        
        virtual void get_row(int r, sparse_list_t &row) const
        {
            ASSERT2(r >= 0 && r < num_rows_, std::runtime_error, "invalid row");
            // slow because finding r in all columns
            row.clear();
            row.reserve(10);
            
            for (size_t i = 0; i < num_cols_; ++i)
            {
                const sparse_vec_t &c = matrix_[i];
                double v = c.get(r);
                if (v != 0.0)
                {
                    row.push_back(sparse_entry_t(i, v));
                }
            }
        }
        
        virtual void get_col(int c, sparse_list_t &col) const
        {
            ASSERT2(c >= 0 && c < num_cols_, std::runtime_error, "invalid col");
            const sparse_vec_t &entries = matrix_[c];
            entries.get_entries(col);
        }
        
        virtual void clear_row(int r)
        {
            ASSERT2(r >= 0 && r < num_rows_, std::runtime_error, "invalid row");
            for (size_t i = 0; i < num_cols_; ++i)
            {
                matrix_[i].set(r, 0.0);
            }
        }
        
        virtual void clear_col(int c)
        {
            ASSERT2(c >= 0 && c < num_cols_, std::runtime_error, "invalid col");
            matrix_[c].clear();
        }
        
        virtual void set_row(int r, const sparse_list_t &row)
        {
            ASSERT2(r >= 0 && r < num_rows_, std::runtime_error, "invalid row");
            
        }
        
        virtual void set_col(int c, const sparse_list_t &col)
        {
            ASSERT2(c >= 0 && c < num_cols_, std::runtime_error, "invalid col");
            sparse_vec_t &entries = matrix_[c];
            entries.clear();
            for (size_t i = 0; i < col.size(); ++i)
            {
                const sparse_entry_t &entry = col[i];
                ASSERT2(entry.id >= 0 && entry.id < num_rows_, std::runtime_error, "wrong row");
                entries.set(col[i].id, col[i].factor);
            }
        }
    };
}

#endif
