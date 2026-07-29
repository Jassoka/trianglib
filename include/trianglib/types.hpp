//
// Created by jassoka on 7/16/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_TYPES_H
#define DELENAUYTESSELATIONGENERATION_TYPES_H

#include <trianglib/vectorTypes.hpp>


namespace trianglib::util
{
    /**
     * Helper function to call nth_impl directly
     * nth_impl for a given type T must be defined in namespace trianglib::util::vectors
     */
    template <std::size_t I, typename T>
    auto nth(const T& p) {
        return vectors::nth_impl<I, T>::get(p);
    }

    /**
     * @brief Helper alias for getting a vector type's scalar type
     * get_scalar_type_impl for a given type T must be defined in namespace trianglib::util::vectors
     */
    template <typename T>
    using get_scalar_type = decltype(vectors::get_scalar_type_impl<T>::get());

    /**
     * Helper function to call set_nth_impl directly
     * set_nth_impl for a given type T must be defined in namespace trianglib::util::vectors
     */
    template <std::size_t I, typename T>
    void set_nth(T& p, const get_scalar_type<T> x) {
        return vectors::set_nth_impl<I, T>::set(p, x);
    }
}

#endif //DELENAUYTESSELATIONGENERATION_TYPES_H
