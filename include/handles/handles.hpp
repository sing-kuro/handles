/**
 * Copyright (c) 2026 Kuro Amami
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

///
/// @file handles.hpp
///

#ifndef HANDLES_HANDLES_HPP
#define HANDLES_HANDLES_HPP
#include <concepts>
#include <vector>

namespace hdl
{

///
/// @brief A class template for managing handles of type `Handle` associated with objects of type `T`.
/// @tparam Handle An unsigned integral type representing the handle.
/// @tparam T The type of the object associated with the handle.
///
template <std::unsigned_integral Handle, typename T>
class handles
{
public:
    ///
    /// @brief Insert a new object and return its associated handle.
    /// @param value The object to be inserted.
    /// @return The handle associated with the inserted object.
    ///
    constexpr Handle insert(T const &value)
    {
        auto idx = data_.size();
        data_.push_back(value);
        if (handles_.size() > idx)
        {
            Handle handle    = handles_[idx];
            indices_[handle] = idx;
            return handle;
        }
        else
        {
            handles_.push_back(idx);
            indices_.push_back(idx);
            return idx;
        }
    }

    ///
    /// @brief Insert a new object using move semantics and return its associated handle.
    /// @param value The object to be inserted.
    /// @return The handle associated with the inserted object.
    ///
    constexpr Handle insert(T &&value)
    {
        auto idx = data_.size();
        data_.push_back(std::move(value));
        if (handles_.size() > idx)
        {
            Handle handle    = handles_[idx];
            indices_[handle] = idx;
            return handle;
        }
        else
        {
            handles_.push_back(idx);
            indices_.push_back(idx);
            return idx;
        }
    }

    ///
    /// @brief Erase the object associated with the given handle.
    /// @param handle The handle whose associated object is to be erased.
    ///
    constexpr void erase(Handle handle)
    {
        auto idx  = indices_[handle];
        auto last = data_.size() - 1;
        std::swap(handles_[last], handles_[idx]);
        std::swap(indices_[last], indices_[idx]);
        std::swap(data_[last], data_[idx]);
        data_.pop_back();
    }

    ///
    /// @brief Access the object associated with the given handle.
    /// @param handle The handle whose associated object is to be accessed.
    /// @return A reference to the object associated with the given handle.
    ///
    constexpr T &at(Handle handle)
    {
        return data_.at(indices_.at(handle));
    }

    ///
    /// @brief Access the object associated with the given handle (const version).
    /// @param handle The handle whose associated object is to be accessed.
    /// @return A const reference to the object associated with the given handle.
    ///
    constexpr T const &at(Handle handle) const
    {
        return data_.at(indices_.at(handle));
    }

    ///
    /// @brief Access the object associated with the given handle without bounds checking.
    /// @param handle The handle whose associated object is to be accessed.
    /// @return A reference to the object associated with the given handle.
    ///
    constexpr T &operator[](Handle handle) noexcept
    {
        return data_[indices_[handle]];
    }

    ///
    /// @brief Access the object associated with the given handle without bounds checking (const version).
    /// @param handle The handle whose associated object is to be accessed.
    /// @return A const reference to the object associated with the given handle.
    ///
    constexpr T const &operator[](Handle handle) const noexcept
    {
        return data_[indices_[handle]];
    }

    ///
    /// @brief Reserve capacity.
    /// @param new_cap The new capacity.
    ///
    constexpr void reserve(Handle new_cap)
    {
        data_.reserve(new_cap);
        indices_.reserve(new_cap);
    }

    ///
    /// @brief Get the number of handles.
    /// @return The number of handles.
    ///
    constexpr Handle size() const
    {
        return data_.size();
    }

    std::vector<Handle> all_handles() const
    {
        std::vector<Handle> ret(handles_.begin(), handles_.begin() + data_.size());
        return ret;
    }

private:
    /// @brief A vector storing the objects of type `T`.
    std::vector<T> data_;

    /// @brief A vector storing the indices of the objects associated with each handle.
    std::vector<typename std::vector<T>::size_type> indices_;

    /// @brief A vector storing the handles of the objects at their respective indices.
    std::vector<Handle> handles_;
};

}  // namespace hdl

#endif  // HANDLES_HANDLES_HPP
