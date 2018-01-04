/*
 * Copyright (C) 2018 ScyllaDB
 */

/*
 * This file is part of Scylla.
 *
 * Scylla is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Scylla is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Scylla.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_MODULE core

#include "enum_set.hh"

#include <boost/test/unit_test.hpp>

enum class fruit { apple = 3, pear = 7, banana = 8 };

using fruit_enum = super_enum<fruit, fruit::apple, fruit::pear, fruit::banana>;

//
// `super_enum`
//

BOOST_AUTO_TEST_CASE(enum_max_sequence) {
    BOOST_REQUIRE_EQUAL(fruit_enum::max_sequence, 8);
}

BOOST_AUTO_TEST_CASE(enum_min_sequence) {
    BOOST_REQUIRE_EQUAL(fruit_enum::min_sequence, 3);
}

//
// `enum_set`
//

using fruit_set = enum_set<fruit_enum>;

BOOST_AUTO_TEST_CASE(set_contains) {
    const auto fs = fruit_set::of<fruit::apple, fruit::banana>();
    BOOST_REQUIRE(fs.contains(fruit::apple));
    BOOST_REQUIRE(!fs.contains(fruit::pear));
}

BOOST_AUTO_TEST_CASE(set_enable) {
    auto fs = fruit_set();
    fs.set(fruit::apple);
    BOOST_REQUIRE(fs.contains(fruit::apple));
}

BOOST_AUTO_TEST_CASE(set_enable_if) {
    auto fs = fruit_set();

    fs.set_if<fruit::apple>(false);
    BOOST_REQUIRE(!fs.contains(fruit::apple));

    fs.set_if<fruit::apple>(true);
    BOOST_REQUIRE(fs.contains(fruit::apple));
}

BOOST_AUTO_TEST_CASE(set_remove) {
    auto fs = fruit_set::of<fruit::pear>();
    fs.remove(fruit::pear);
    BOOST_REQUIRE(!fs.contains(fruit::pear));
}
