/*
 *  Copyright (c) 2015, Mike Achtelik  All rights reserved.
 *  Use of this source code is governed by a BSD-style license that can be
 *  found in the LICENSE file.
 */
#ifndef _PROTO_H_
#define _PROTO_H_

#include <string>
#include <unordered_map>
#include <set>

class Proto {

public:
    enum WIRE_TYPE { VARINT = 0, BIT_64 = 1, LENGTH_DELIMITED = 2, BIT_32 = 5, OTHER = 255 };
    enum PROTO_TYPE { DOUBLE = 5, FLOAT = 4, INT32 = 0, INT64 = 1, UINT32 = 2, UINT64 = 3, BOOL = 6, BYTES = 7, STRING = 8, UNKNOWN = 255 };
    
    static void parseFromStream( std::istream& in, std::set< uint32_t> &changedFields, const std::unordered_map< uint32_t, uint8_t >& fieldTypeMap, const std::unordered_map< uint32_t, void* >& valueMap );
    static void writeToStream(std::ostream &out, const std::set< uint32_t> &changedFields, const std::unordered_map< uint32_t, uint8_t >& fieldTypeMap, const std::unordered_map< uint32_t, void* >& valueMap);

    static void encode(std::ostream &out, WIRE_TYPE wireType, PROTO_TYPE type, void *value = nullptr);
    static uint32_t decode( std::istream& in, Proto::WIRE_TYPE wireType, Proto::PROTO_TYPE type, void* value = nullptr );
    static uint32_t sizeOf ( WIRE_TYPE wireType, PROTO_TYPE type, void *value );

    static uint32_t decodeVarint(std::istream &in, uint64_t &value);
    static void encodeVarint(std::ostream &out, uint64_t value);
    static uint8_t sizeofVarint ( uint64_t value );
    
    static WIRE_TYPE getWireType ( PROTO_TYPE type );

    static constexpr WIRE_TYPE getWireType(uint32_t key) { return (WIRE_TYPE) (key & 0x7); }
    static constexpr uint32_t getFieldNumber(uint32_t key) { return (key >> 3); }
    static constexpr uint32_t getKey(uint32_t fieldNumber, uint8_t wireType) { return (fieldNumber << 3) | wireType; }

};

#endif
