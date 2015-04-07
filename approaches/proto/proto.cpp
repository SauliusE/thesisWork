/*
 *  Copyright (c) 2015, Mike Achtelik  All rights reserved.
 *  Use of this source code is governed by a BSD-style license that can be
 *  found in the LICENSE file.
 */
#include "proto.h"

#include <iostream>
#include <cstring>
#include <sstream>

#include "portable_endian.h"

void Proto::parseFromStream ( std::istream& in, std::set<uint32_t> &changedFields, const std::unordered_map< uint32_t, uint8_t >& fieldTypeMap, const std::unordered_map< uint32_t, void* >& valueMap )
{
     //First parse the size..
     uint64_t size;
     decodeVarint ( in, size );

     //.. and then read max size bytes (if there are errors in the message it might read more data)
     uint64_t read = 0;
     while ( in.good() && read < size ) {

          uint64_t key;
          read += decodeVarint ( in, key );

          WIRE_TYPE wireType = getWireType ( key );
          uint32_t fieldId = getFieldNumber ( key );

          auto it = fieldTypeMap.find ( fieldId );
          if ( it != fieldTypeMap.end() ) {
               PROTO_TYPE protoType = ( PROTO_TYPE ) it->second;
               read += decode ( in, wireType, protoType, valueMap.find ( fieldId )->second );
               changedFields.insert ( fieldId );
          } else {
               //Parse/Skip unknown data
               read += decode ( in, wireType, UNKNOWN );
          }

     }

}

void Proto::writeToStream ( std::ostream &out, const std::set<uint32_t> &changedFields, const std::unordered_map< uint32_t, uint8_t >& fieldTypeMap, const std::unordered_map< uint32_t, void* >& valueMap )
{
     //First we need to calculate the size of the message..
     uint32_t size = 0;
     for ( uint32_t fieldId : changedFields ) {
          PROTO_TYPE protoType = ( PROTO_TYPE ) fieldTypeMap.find ( fieldId )->second;
          WIRE_TYPE wireType = getWireType ( protoType );
          uint32_t key = getKey ( fieldId, wireType );

          size += sizeofVarint ( key );
          size += sizeOf ( wireType, protoType, valueMap.find ( fieldId )->second );

     }

     //.. then we can write it ..
     encodeVarint ( out, size );

     //.. and the we can write the actual payload
     for ( uint32_t fieldId : changedFields ) {
          PROTO_TYPE protoType = ( PROTO_TYPE ) fieldTypeMap.find ( fieldId )->second;
          WIRE_TYPE wireType = getWireType ( protoType );
          uint32_t key = getKey ( fieldId, wireType );
          encodeVarint ( out, key );
          encode ( out, wireType, protoType, valueMap.find ( fieldId )->second );
     }

}

uint32_t Proto::sizeOf ( WIRE_TYPE wireType, PROTO_TYPE type, void *value )
{
     switch ( wireType ) {
     case VARINT: {
          if ( value ) {
               switch ( type ) {

               case UINT32:
                    return sizeofVarint ( * ( ( uint32_t* ) value ) );

               case UINT64:
                    return sizeofVarint ( * ( ( uint64_t* ) value ) );

               case INT32:
                    return sizeofVarint ( * ( ( int32_t* ) value ) );

               case INT64:
                    return sizeofVarint ( * ( ( int64_t* ) value ) );

               case BOOL:
                    return sizeofVarint ( * ( ( bool* ) value ) );

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          }
     }
     break;

     case BIT_64: {
          if ( value ) {
               switch ( type ) {

               case DOUBLE:
                    return 8;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          }


     }
     break;

     case LENGTH_DELIMITED: {
          if ( value ) {
               switch ( type ) {

               case STRING:
               case BYTES: {
                    uint32_t size = ( ( std::string* ) value )->size();
                    return size + sizeofVarint ( size );
               }

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }


          }

     }
     break;

     case BIT_32: {
          if ( value ) {
               switch ( type ) {

               case FLOAT:
                    return 4;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          }


     }
     break;

     default:
          std::cerr << "Can not encode unknown wire type" << std::endl;
          break;

     }

     return 0;
}

void Proto::encode ( std::ostream &out, WIRE_TYPE wireType, PROTO_TYPE type, void *value )
{
     switch ( wireType ) {
     case VARINT: {
          if ( value ) {
               switch ( type ) {

               case UINT32:
                    encodeVarint ( out, * ( ( uint32_t* ) value ) );
                    break;

               case UINT64:
                    encodeVarint ( out, * ( ( uint64_t* ) value ) );
                    break;

               case INT32:
                    encodeVarint ( out, * ( ( int32_t* ) value ) );
                    break;

               case INT64:
                    encodeVarint ( out, * ( ( int64_t* ) value ) );
                    break;

               case BOOL:
                    encodeVarint ( out, * ( ( bool* ) value ) );
                    break;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          }
     }
     break;

     case BIT_64: {
          if ( value ) {
               switch ( type ) {

               case DOUBLE:
                    out.write ( ( char* ) value, 8 );
                    break;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          }
     }
     break;

     case LENGTH_DELIMITED: {
          if ( value ) {
               switch ( type ) {

               case STRING:
               case BYTES: {
                    std::string &str = * ( ( std::string* ) value );
                    encodeVarint ( out, str.size() );
                    out.write ( str.c_str(), str.size() );

               }
               break;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }

          }

     }
     break;

     case BIT_32: {
          if ( value ) {
               switch ( type ) {

               case FLOAT:
                    out.write ( ( char* ) value, 4 );
                    break;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          }


     }
     break;

     default:
          std::cerr << "Can not encode unknown wire type" << std::endl;
          break;

     }
}

uint32_t Proto::decode ( std::istream &in, WIRE_TYPE wireType, PROTO_TYPE type, void *value )
{
     uint32_t read = 0;
     switch ( wireType ) {
     case VARINT: {
          uint64_t v;
          read += decodeVarint ( in, v );
          if ( value ) {
               switch ( type ) {

               case UINT32:
                    * ( ( uint32_t* ) value ) = ( uint32_t ) v;
                    break;

               case UINT64:
                    * ( ( uint64_t* ) value ) = ( uint64_t ) v;
                    break;

               case INT32:
                    * ( ( int32_t* ) value ) = ( int32_t ) v;
                    break;

               case INT64:
                    * ( ( int64_t* ) value ) = ( int64_t ) v;
                    break;

               case BOOL:
                    * ( ( bool* ) value ) = ( bool ) v;
                    break;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          }
     }
     break;

     case BIT_64: {
          if ( value ) {
               switch ( type ) {

               case DOUBLE:
                    in.read ( ( char* ) value, 8 );
                    read += 8;
                    break;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          } else {
               in.ignore ( 8 );
               read += 8;
          }
     }
     break;

     case LENGTH_DELIMITED: {
          uint64_t size;
          read += decodeVarint ( in, size );
          if ( value ) {
               switch ( type ) {

               case STRING:
               case BYTES: {
                    std::string &str = * ( ( std::string* ) value );
                    str.resize ( size );
                    in.read ( &str.front(), size );
                    read += size;
               }
               break;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          } else {
               in.ignore ( size );
          }
     }
     break;

     case BIT_32: {
          if ( value ) {
               switch ( type ) {

               case FLOAT:
                    in.read ( ( char* ) value, 4 );
                    read += 4;
                    break;

               default:
                    std::cerr << "Unknown type" << std::endl;
                    break;

               }
          } else {
               in.ignore ( 4 );
               read += 4;
          }
     }
     break;

     default:
          std::cerr << "Can not decode unknown wire type" << std::endl;
          break;

     }

     return read;
}

uint32_t Proto::decodeVarint ( std::istream &in, uint64_t &value )
{
     uint32_t size = 0;
     int shift = 0;
     uint8_t c;
     value = 0;

     do {
          c = in.get();
          value |= ( uint64_t ) ( c & 0x7F ) << shift;
          shift += 7;
          ++size;
     } while ( in.good() && ( c & 0x80 ) != 0 );

     value = le64toh ( value );

     return size;
}

void Proto::encodeVarint ( std::ostream &out, uint64_t value )
{
     value = htole64 ( value );
     do {
          char nextByte = value & ( uint8_t ) 0x7F;
          value >>= 7;

          if ( value ) {
               nextByte |= ( uint8_t ) 0x80;
          }

          out.put ( nextByte );

     } while ( value );
}

uint8_t Proto::sizeofVarint ( uint64_t value )
{
     uint8_t size = 0;
     value = htole64 ( value );
     do {
          char nextByte = value & ( uint8_t ) 0x7F;
          value >>= 7;

          if ( value ) {
               nextByte |= ( uint8_t ) 0x80;
          }

          ++size;

     } while ( value );

     return size;
}

Proto::WIRE_TYPE Proto::getWireType ( Proto::PROTO_TYPE type )
{
     switch ( type ) {
     case INT32:
          return VARINT;
     case INT64:
          return VARINT;
     case UINT32:
          return VARINT;
     case UINT64:
          return VARINT;
     case FLOAT:
          return BIT_32;
     case DOUBLE:
          return BIT_64;
     case BOOL:
          return VARINT;
     case STRING:
     case BYTES:
          return LENGTH_DELIMITED;
     default:
          return OTHER;
     }
}
