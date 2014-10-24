/*
    Copyright (c) 2013-2014 Andrey Goryachev <andrey.goryachev@gmail.com>
    Copyright (c) 2011-2014 Other contributors as noted in the AUTHORS file.

    This file is part of Leonidia.

    Leonidia is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Leonidia is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LEONIDIA_DYNAMIC_ERROR_HPP
#define LEONIDIA_DYNAMIC_ERROR_HPP

#include "leonidia/utility.hpp"

#include <stdexcept>

namespace leonidia {

class LEONIDIA_API json_parsing_error_t :
    public std::invalid_argument
{
public:
    json_parsing_error_t(size_t offset, std::string message) :
        std::invalid_argument("parsing error - " + message),
        m_offset(offset),
        m_message(message)
    { }

    size_t
    offset() const LEONIDIA_NOEXCEPT {
        return m_offset;
    }

    const char*
    message() const LEONIDIA_NOEXCEPT {
        return m_message.data();
    }

private:
    size_t m_offset;
    std::string m_message;
};

} // namespace leonidia


#endif