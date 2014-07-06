/*!
@file
Adapts `boost::mpl::list`.

@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ADAPTED_MPL_LIST_HPP
#define BOOST_HANA_ADAPTED_MPL_LIST_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/comparable.hpp>
#include <boost/hana/core.hpp>
#include <boost/hana/detail/enable_if.hpp>
#include <boost/hana/functor.hpp>
#include <boost/hana/type.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/transform.hpp>
#include <type_traits>


namespace boost { namespace hana {
    struct MplList;

    template <typename T>
    struct datatype<T, detail::enable_if_t<
        std::is_same<
            typename boost::mpl::sequence_tag<T>::type,
            boost::mpl::aux::list_tag
        >::value
    >> {
        using type = MplList;
    };

    namespace mpl_list_detail {
        //! @todo Remove the need for this.
        template <typename F>
        struct wrap {
            template <typename ...x>
            using apply = decltype((*(F*)0)(type<x>...));
        };
    }

    template <>
    struct Functor::instance<MplList> : Functor::fmap_mcd {
        template <typename F, typename Xs>
        static constexpr auto fmap_impl(F, Xs) {
            return typename ::boost::mpl::transform<Xs, mpl_list_detail::wrap<F>>::type{};
        }
    };

    template <>
    struct Comparable::instance<MplList, MplList> : Comparable::equal_mcd {
        template <typename Xs, typename Ys>
        static constexpr auto equal_impl(Xs, Ys) {
            return bool_<boost::mpl::equal<Xs, Ys>::type::value>;
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_ADAPTED_MPL_LIST_HPP
