/*
Copyright (c) 2013 Andrey Goryachev <andrey.goryachev@gmail.com>
Copyright (c) 2011-2013 Other contributors as noted in the AUTHORS file.

This file is part of Kora.

Kora is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

Kora is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KORA_UTILITY_HPP
#define KORA_UTILITY_HPP

#include "kora/platform.hpp"

// Write KORA_NONCOPYABLE(YourClass) in YourClass to delete copy constructor/assignment operator.
#define KORA_NONCOPYABLE(type) \
type(const type&) = delete; \
type& operator=(const type&) = delete;

#ifdef KORA_NOT_BAD
    #define KORA_NOEXCEPT noexcept
#else
    #define KORA_NOEXCEPT throw()
#endif

#if !defined(KORA_NOT_BAD)
    #define nullptr __null
#endif

#ifdef __GNUC__
    #define KORA_NORETURN __attribute__ ((__noreturn__))
#else
    #define KORA_NORETURN [[noreturn]]
#endif

#define KORA_API __attribute__ ((__visibility__ ("default")))

#ifdef __GNUC__
    #define KORA_PUSH_VISIBLE _Pragma("GCC visibility push(default)")
    #define KORA_POP_VISIBILITY _Pragma("GCC visibility pop")
#else
    #define KORA_PUSH_VISIBLE
    #define KORA_POP_VISIBILITY
#endif

KORA_PUSH_VISIBLE
#include <boost/assert.hpp>
KORA_POP_VISIBILITY

#include <type_traits>
#include <utility>

namespace kora {

// It's like std::decay, but doesn't convert arrays to pointers.
template<class T>
struct pristine {
    typedef typename std::remove_cv<
        typename std::remove_reference<T>::type
    >::type type;
};

// Use it instead of std::enable_if to enable a specialization if your dependent type T has
// some nested type.
// Usage: template<class T> struct some_struct<T, typename depends<T::nested_type>::type> { }
template<class T, class Result = void>
struct requieres_type {
    typedef Result type;
};

// Use it instead of std::enable_if to enable a specialization if your dependent type T has
// some method.
// Usage:
// template<class T>
// struct some_struct<T, typename requires_method<void(T::*)(int, double), T::method_name>::type> { }
template<class Method, Method, class Result = void>
struct requires_method {
    typedef Result type;
};

} // namespace kora

#endif
