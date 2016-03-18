import sys
import time
from ctypes import *
import argparse
import zlib

def sign_dandelion(filename):
    f = open(filename, "rb")
    bytes = bytearray(f.read())
    f.close()

    image_size = len(bytes)
    
    bytes[16] = (image_size) & 0xFF
    bytes[17] = (image_size >> 8) & 0xFF
    bytes[18] = (image_size >> 16) & 0xFF
    bytes[19] = (image_size >> 24) & 0xFF
    
    crc32 = zlib.crc32(str(bytes[4:]), 0) & 0xFFFFFFFF
    print("CRC32: 0x%08X" % crc32)
    print("Length: 0x%08X" % image_size)
    
    bytes[0] = (crc32)& 0xFF
    bytes[1] = (crc32 >> 8) & 0xFF
    bytes[2] = (crc32 >> 16) & 0xFF
    bytes[3] = (crc32 >> 24) & 0xFF
    
    f = open(filename, "w+b")
    f.write(bytes)
    f.close()
    
def sign_sunflower(filename):
    f = open(filename, "rb")
    bytes = bytearray(f.read())
    f.close()
    
    image_size = len(bytes)
    
    bytes[404] = (image_size) & 0xFF
    bytes[405] = (image_size >> 8) & 0xFF
    bytes[406] = (image_size >> 16) & 0xFF
    bytes[407] = (image_size >> 24) & 0xFF
    
    crc32a = zlib.crc32(str(bytes[0:392]), 0) & 0xFFFFFFFF
    crc32b = zlib.crc32(str(bytes[400:]), 0) & 0xFFFFFFFF
    
    print("CRC32: 0x%08X" % crc32a)
    print("CRC32: 0x%08X" % crc32b)
    
    bytes[392] = (crc32a) & 0xFF
    bytes[393] = (crc32a >> 8) & 0xFF
    bytes[394] = (crc32a >> 16) & 0xFF
    bytes[395] = (crc32a >> 24) & 0xFF
    
    bytes[396] = (crc32b) & 0xFF
    bytes[397] = (crc32b >> 8) & 0xFF
    bytes[398] = (crc32b >> 16) & 0xFF
    bytes[399] = (crc32b >> 24) & 0xFF
    
    f = open(filename, "w+b")
    f.write(bytes)
    f.close()
    
if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Project Reservoir Binary Signing Tool')
    parser.add_argument("--sunflower", help="binary file to sign", action="store", default=None, required=False)
    parser.add_argument("--dandelion", help="binary file to sign", action="store", default=None, required=False)
    args = parser.parse_args()
    
    if args.dandelion:
        sign_dandelion(args.dandelion)
        
    if args.sunflower:
        sign_sunflower(args.sunflower)
    
    if args.dandelion == None and args.sunflower == None:
        bytes = bytearray([0xEF, 0xBE, 0xAD, 0xDE])
    
        crc32 = zlib.crc32(str(bytes), 0) & 0xFFFFFFFF
        print("CRC32: 0x%08X" % crc32)
    