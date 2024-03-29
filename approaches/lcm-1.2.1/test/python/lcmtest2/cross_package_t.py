"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

import lcmtest2.another_type_t

import lcmtest.primitives_t

class cross_package_t(object):
    __slots__ = ["primitives", "another"]

    def __init__(self):
        self.primitives = lcmtest.primitives_t()
        self.another = lcmtest2.another_type_t()

    def encode(self):
        buf = BytesIO()
        buf.write(cross_package_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        assert self.primitives._get_packed_fingerprint() == lcmtest.primitives_t._get_packed_fingerprint()
        self.primitives._encode_one(buf)
        assert self.another._get_packed_fingerprint() == lcmtest2.another_type_t._get_packed_fingerprint()
        self.another._encode_one(buf)

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != cross_package_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return cross_package_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = cross_package_t()
        self.primitives = lcmtest.primitives_t._decode_one(buf)
        self.another = lcmtest2.another_type_t._decode_one(buf)
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if cross_package_t in parents: return 0
        newparents = parents + [cross_package_t]
        tmphash = (0xbbd3dd8a23ec1955+ lcmtest.primitives_t._get_hash_recursive(newparents)+ lcmtest2.another_type_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if cross_package_t._packed_fingerprint is None:
            cross_package_t._packed_fingerprint = struct.pack(">Q", cross_package_t._get_hash_recursive([]))
        return cross_package_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

