import time
from ctypes import *
import socket

DANDELION_DEVICE = 1
SUNFLOWER_DEVICE = 2

class FR1_PAYLOAD(Structure):
    _pack_ = True
    _fields_ = [("report_id", c_ubyte), 
                ("device_type", c_ubyte),
                ("address", c_ubyte * 4),
                ("payload", c_ubyte * 256)]
    
    def __init__(self):
        self.report_id = 0x01
        
    def __str__(self):
        data_str = ""
        for byte in self.payload:
            data_str += "0x%02x " % byte
        return "address = 0x%08x, payload = \n %s" % (self.get_address(), data_str)
    
    def set_device(self, type):
        self.device_type = type
    
    def set_address(self, address):
        self.address[3] = (address >> 24) & 0xFF
        self.address[2] = (address >> 16) & 0xFF
        self.address[1] = (address >> 8) & 0xFF
        self.address[0] = address & 0xFF
        
class FR2_START(Structure):
    _pack_ = True
    _fields_ = [("report_id", c_ubyte), 
                ("device_type", c_ubyte)]
    
    def __init__(self):
        self.report_id = 0x02
        
    def set_device(self, type):
        self.device_type = type
 
class FR3_VALIDATE(Structure):
    _pack_ = True
    _fields_ = [("report_id", c_ubyte), 
                ("device_type", c_ubyte)]
    
    def __init__(self):
        self.report_id = 0x03
        
    def set_device(self, type):
        self.device_type = type

class FR4_EXIT_MODE(Structure):
    _pack_ = True
    _fields_ = [("report_id", c_ubyte)]
    
    def __init__(self):
        self.report_id = 0x04

class FR5_ACK(Structure):
    _pack_ = True
    _fields_ = [("report_id", c_ubyte)]
    
    def __init__(self):
        self.report_id = 0x05

class FR6_NACK(Structure):
    _pack_ = True
    _fields_ = [("report_id", c_ubyte)]
    
    def __init__(self):
        self.report_id = 0x06
        
class FR7_END(Structure):
    _pack_ = True
    _fields_ = [("report_id", c_ubyte)]
    
    def __init__(self):
        self.report_id = 0x07
        
class SunflowerTCP:
    sock = None
    
    sunflower_image_size = 256 * 1024
    dandelion_image_size = 128 * 1024
    
    def __init__(self, addr, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((addr, port))
        # clear the input buffer
        self.sock.recv(100)

    def send_tcp_payload(self, fr):
        tcp_buffer = (c_ubyte * sizeof(fr))()
        memmove(tcp_buffer, byref(fr), sizeof(fr))
        self.sock.send(tcp_buffer)
        
        if self.get_tcp_ack() != True:
            print "TCP did not ACK!"
            exit()
    
    def get_tcp_ack(self):
        data = self.sock.recv(1)
        if (ord(data) == 6):
            print "NAK received!"
            
        return (ord(data) == 5)
    
    def enter_fw_update_mode(self):
        self.sock.send("mf\n")
        
    def exit_fw_update_mode(self):
        pack = FR7_END()
        self.send_tcp_payload(pack)
        
        pack = FR4_EXIT_MODE()
        self.send_tcp_payload(pack)
    
    def shutdown(self):
        self.sock.close()

def dandelion_image_memory_test(sf):

    sf.enter_fw_update_mode()
    
    fr = FR2_START()
    fr.set_device(DANDELION_DEVICE)
    sf.send_tcp_payload(fr)
    
    address = 0x00000000
    while address < SunflowerTCP.dandelion_image_size:
        fr = FR1_PAYLOAD()
        fr.set_device(DANDELION_DEVICE)
        fr.set_address(address)
        for j in range(0, len(fr.payload)):
            fr.payload[j] = 1 << 3
        
        sf.send_tcp_payload(fr)
        
        address += len(fr.payload)
        
        print "Wrote address %d" % (address)
    
    sf.exit_fw_update_mode()
    
if __name__ == '__main__':
    
    sf = SunflowerTCP("192.168.0.136", 1337)
    
    dandelion_image_memory_test(sf)
    
    sf.shutdown()