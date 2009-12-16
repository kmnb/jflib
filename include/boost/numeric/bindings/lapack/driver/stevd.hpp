//
// Copyright (c) 2003--2009
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_STEVD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_STEVD_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void stevd( char const jobz, integer_t const n, float* d, float* e,
            float* z, integer_t const ldz, float* work, integer_t const lwork,
            integer_t* iwork, integer_t const liwork, integer_t& info ) {
        LAPACK_SSTEVD( &jobz, &n, d, e, z, &ldz, work, &lwork, iwork, &liwork,
                &info );
    }
    inline void stevd( char const jobz, integer_t const n, double* d,
            double* e, double* z, integer_t const ldz, double* work,
            integer_t const lwork, integer_t* iwork, integer_t const liwork,
            integer_t& info ) {
        LAPACK_DSTEVD( &jobz, &n, d, e, z, &ldz, work, &lwork, iwork, &liwork,
                &info );
    }
}

// value-type based template
template< typename ValueType >
struct stevd_impl {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ,
            typename WORK, typename IWORK >
    static void invoke( char const jobz, integer_t const n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, detail::workspace2< WORK,
            IWORK > work ) {
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::vector_traits<
                VectorE >::value_type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename traits::vector_traits<
                VectorD >::value_type, typename traits::matrix_traits<
                MatrixZ >::value_type >::value) );
        BOOST_ASSERT( jobz == 'N' || jobz == 'V' );
        BOOST_ASSERT( n >= 0 );
        BOOST_ASSERT( traits::vector_size(e) >= n-1 );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( jobz, n ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( jobz, n ));
        detail::stevd( jobz, n, traits::vector_storage(d),
                traits::vector_storage(e), traits::matrix_storage(z),
                traits::leading_dimension(z),
                traits::vector_storage(work.select(real_type())),
                traits::vector_size(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())),
                traits::vector_size(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static void invoke( char const jobz, integer_t const n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work( jobz,
                n ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork( jobz,
                n ) );
        invoke( jobz, n, d, e, z, info, workspace( tmp_work, tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename VectorD, typename VectorE, typename MatrixZ >
    static void invoke( char const jobz, integer_t const n, VectorD& d,
            VectorE& e, MatrixZ& z, integer_t& info, optimal_workspace work ) {
        real_type opt_size_work;
        integer_t opt_size_iwork;
        detail::stevd( jobz, n, traits::vector_storage(d),
                traits::vector_storage(e), traits::matrix_storage(z),
                traits::leading_dimension(z), &opt_size_work, -1,
                &opt_size_iwork, -1, info );
        traits::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        traits::detail::array< integer_t > tmp_iwork( opt_size_iwork );
        invoke( jobz, n, d, e, z, info, workspace( tmp_work, tmp_iwork ) );
    }

    static integer_t min_size_work( char const jobz, integer_t const n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 1 + 4*n + n*n;
    }

    static integer_t min_size_iwork( char const jobz, integer_t const n ) {
        if ( jobz == 'N' || n < 2 )
            return 1;
        else
            return 3 + 5*n;
    }
};


// template function to call stevd
template< typename VectorD, typename VectorE, typename MatrixZ,
        typename Workspace >
inline integer_t stevd( char const jobz, integer_t const n, VectorD& d,
        VectorE& e, MatrixZ& z, Workspace work ) {
    typedef typename traits::vector_traits< VectorD >::value_type value_type;
    integer_t info(0);
    stevd_impl< value_type >::invoke( jobz, n, d, e, z, info, work );
    return info;
}

// template function to call stevd, default workspace type
template< typename VectorD, typename VectorE, typename MatrixZ >
inline integer_t stevd( char const jobz, integer_t const n, VectorD& d,
        VectorE& e, MatrixZ& z ) {
    typedef typename traits::vector_traits< VectorD >::value_type value_type;
    integer_t info(0);
    stevd_impl< value_type >::invoke( jobz, n, d, e, z, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
