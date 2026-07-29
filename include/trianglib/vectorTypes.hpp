//
// Created by jassoka on 7/29/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_VECTORTYPES_H
#define DELENAUYTESSELATIONGENERATION_VECTORTYPES_H
namespace trianglib::util::vectors
{
    /**
     * Unintialised template for getting the n-th element of a vector type
     * @tparam I Position
     * @tparam T Vector type
     * @note Must implement get(T&) method
     */
    template <std::size_t I, typename T>
    struct nth_impl;

    /**
     * Unintialised template for setting the n-th element of a vector type
     * @tparam I Position
     * @tparam T Vector type
     * @note Must implement set(T&) method
     */
    template <std::size_t I, typename T>
    struct set_nth_impl;

    /**
     * Unintialised template for getting a vector type's scalar type
     * @note Must implement get() method
     */
    template <typename T>
    struct get_scalar_type_impl;
}

/** Implementation for std::array */
namespace trianglib::util::vectors
{
    template <std::size_t I, std::size_t N, typename scalarType>
    struct nth_impl<I, std::array<scalarType, N>> {
        static auto get(const std::array<scalarType, N>& arr) {
            return arr[I];
        }
    };

    template <std::size_t I, std::size_t N, typename scalarType>
    struct set_nth_impl<I, std::array<scalarType, N>> {
        static void set(std::array<scalarType, N>& arr, const scalarType x) {
            arr[I] = x;
        }
    };

    template<std::size_t N, typename scalarType>
    struct get_scalar_type_impl<std::array<scalarType, N>>
    { static scalarType get(); };
}

#endif //DELENAUYTESSELATIONGENERATION_VECTORTYPES_H
