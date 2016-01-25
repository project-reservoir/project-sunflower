import sys
import hid
import time
from ctypes import *
import argparse

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Project Reservoir Binary Signing Tool')
    parser.add_argument("--file", help="binary file to sign", action="store", default=None, required=True)
    args = parser.parse_args()
    
    with f as 