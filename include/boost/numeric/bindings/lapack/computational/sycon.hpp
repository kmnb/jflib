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

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SYCON_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_SYCON_HPP

#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/is_complex.hpp>
#include <boost/numeric/bindings/traits/is_real.hpp>
#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//$DESCRIPTION

// overloaded functions to call lapack
namespace detail {
    inline void sycon( char const uplo, integer_t const n, float* a,
            integer_t const lda, integer_t* ipiv, float const anorm,
            float& rcond, float* work, integer_t* iwork, integer_t& info ) {
        LAPACK_SSYCON( &uplo, &n, a, &lda, ipiv, &anorm, &rcond, work, iwork,
                &info );
    }
    inline void sycon( char const uplo, integer_t const n, double* a,
            integer_t const lda, integer_t* ipiv, double const anorm,
            double& rcond, double* work, integer_t* iwork, integer_t& info ) {
        LAPACK_DSYCON( &uplo, &n, a, &lda, ipiv, &anorm, &rcond, work, iwork,
                &info );
    }
    inline void sycon( char const uplo, integer_t const n,
            traits::complex_f* a, integer_t const lda, integer_t* ipiv,
            float const anorm, float& rcond, traits::complex_f* work,
            integer_t& info ) {
        LAPACK_CSYCON( &uplo, &n, traits::complex_ptr(a), &lda, ipiv, &anorm,
                &rcond, traits::complex_ptr(work), &info );
    }
    inline void sycon( char const uplo, integer_t const n,
            traits::complex_d* a, integer_t const lda, integer_t* ipiv,
            double const anorm, double& rcond, traits::complex_d* work,
            integer_t& info ) {
        LAPACK_ZSYCON( &uplo, &n, traits::complex_ptr(a), &lda, ipiv, &anorm,
                &rcond, traits::complex_ptr(work), &info );
    }
}

// value-type based template
template< typename ValueType, typename Enable = void >
struct sycon_impl{};

// real specialization
template< typename ValueType >
struct sycon_impl< ValueType, typename boost::enable_if< traits::is_real<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorIPIV, typename WORK,
            typename IWORK >
    static void invoke( char const uplo, MatrixA& a, VectorIPIV& ipiv,
            real_type const anorm, real_type& rcond, integer_t& info,
            detail::workspace2< WORK, IWORK > work ) {
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(ipiv) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(work.select(real_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        BOOST_ASSERT( traits::vector_size(work.select(integer_t())) >=
                min_size_iwork( traits::matrix_num_columns(a) ));
        detail::sycon( uplo, traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(ipiv), anorm, rcond,
                traits::vector_storage(work.select(real_type())),
                traits::vector_storage(work.select(integer_t())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorIPIV >
    static void invoke( char const uplo, MatrixA& a, VectorIPIV& ipiv,
            real_type const anorm, real_type& rcond, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< real_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        traits::detail::array< integer_t > tmp_iwork( min_size_iwork(
                traits::matrix_num_columns(a) ) );
        invoke( uplo, a, ipiv, anorm, rcond, info, workspace( tmp_work,
                tmp_iwork ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorIPIV >
    static void invoke( char const uplo, MatrixA& a, VectorIPIV& ipiv,
            real_type const anorm, real_type& rcond, integer_t& info,
            optimal_workspace work ) {
        invoke( uplo, a, ipiv, anorm, rcond, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 2*n;
    }

    static integer_t min_size_iwork( integer_t const n ) {
        return n;
    }
};

// complex specialization
template< typename ValueType >
struct sycon_impl< ValueType, typename boost::enable_if< traits::is_complex<ValueType> >::type > {

    typedef ValueType value_type;
    typedef typename traits::type_traits<ValueType>::real_type real_type;

    // user-defined workspace specialization
    template< typename MatrixA, typename VectorIPIV, typename WORK >
    static void invoke( char const uplo, MatrixA& a, VectorIPIV& ipiv,
            real_type const anorm, real_type& rcond, integer_t& info,
            detail::workspace1< WORK > work ) {
        BOOST_ASSERT( uplo == 'U' || uplo == 'L' );
        BOOST_ASSERT( traits::matrix_num_columns(a) >= 0 );
        BOOST_ASSERT( traits::leading_dimension(a) >= std::max(1,
                traits::matrix_num_columns(a)) );
        BOOST_ASSERT( traits::vector_size(ipiv) >=
                traits::matrix_num_columns(a) );
        BOOST_ASSERT( traits::vector_size(work.select(value_type())) >=
                min_size_work( traits::matrix_num_columns(a) ));
        detail::sycon( uplo, traits::matrix_num_columns(a),
                traits::matrix_storage(a), traits::leading_dimension(a),
                traits::vector_storage(ipiv), anorm, rcond,
                traits::vector_storage(work.select(value_type())), info );
    }

    // minimal workspace specialization
    template< typename MatrixA, typename VectorIPIV >
    static void invoke( char const uplo, MatrixA& a, VectorIPIV& ipiv,
            real_type const anorm, real_type& rcond, integer_t& info,
            minimal_workspace work ) {
        traits::detail::array< value_type > tmp_work( min_size_work(
                traits::matrix_num_columns(a) ) );
        invoke( uplo, a, ipiv, anorm, rcond, info, workspace( tmp_work ) );
    }

    // optimal workspace specialization
    template< typename MatrixA, typename VectorIPIV >
    static void invoke( char const uplo, MatrixA& a, VectorIPIV& ipiv,
            real_type const anorm, real_type& rcond, integer_t& info,
            optimal_workspace work ) {
        invoke( uplo, a, ipiv, anorm, rcond, info, minimal_workspace() );
    }

    static integer_t min_size_work( integer_t const n ) {
        return 2*n;
    }
};


// template function to call sycon
template< typename MatrixA, typename VectorIPIV, typename Workspace >
inline integer_t sycon( char const uplo, MatrixA& a, VectorIPIV& ipiv,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type const anorm,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type& rcond, Workspace work ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    sycon_impl< value_type >::invoke( uplo, a, ipiv, anorm, rcond, info,
            work );
    return info;
}

// template function to call sycon, default workspace type
template< typename MatrixA, typename VectorIPIV >
inline integer_t sycon( char const uplo, MatrixA& a, VectorIPIV& ipiv,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type const anorm,
        typename traits::type_traits< typename traits::matrix_traits<
        MatrixA >::value_type >::real_type& rcond ) {
    typedef typename traits::matrix_traits< MatrixA >::value_type value_type;
    integer_t info(0);
    sycon_impl< value_type >::invoke( uplo, a, ipiv, anorm, rcond, info,
            optimal_workspace() );
    return info;
}

}}}} // namespace boost::numeric::bindings::lapack

#endif
