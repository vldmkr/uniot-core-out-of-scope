/*
 * This is a part of the Uniot project.
 * Copyright (C) 2016-2020 Uniot <contact@uniot.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <unity.h>

#include <CBOR.h>

using namespace uniot;

const unsigned char cbor_object_1[] = {
  0xA2,                                   // map(2)
    0x66,                                 // text(6)
      0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74, // "object"
    0x66,                                 // text(6)
      0x73, 0x69, 0x6D, 0x70, 0x6C, 0x65, // "simple"
    0x66,                                 // text(6)
      0x6E, 0x75, 0x6D, 0x62, 0x65, 0x72, // "number"
    0x18, 0x2A                            // unsigned(42)
};

void test_function_cbor_read_string(void)
{
  auto bytes = Bytes(cbor_object_1, sizeof(cbor_object_1));
  CBOR cbor(bytes);
  TEST_ASSERT_EQUAL_STRING("simple", cbor.getString("object").c_str());
}

void test_function_cbor_read_int(void)
{
  auto bytes = Bytes(cbor_object_1, sizeof(cbor_object_1));
  CBOR cbor(bytes);
  TEST_ASSERT_EQUAL(42, cbor.getInt("number"));
}

void test_function_cbor_put(void)
{
  CBOR cbor;
  cbor.put("object", "simple");
  cbor.put("number", 42);
  TEST_ASSERT_EQUAL_MEMORY(cbor_object_1, cbor.build().raw(), sizeof(cbor_object_1));
}
