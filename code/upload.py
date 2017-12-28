#!/usr/python

import os
import sys
import serial.tools.list_ports
from signal import SIGKILL


class CommandFirmware:
    def __init__(self):
        pass

    def complete_command(self, command_list):
        command = ""
        for cm in command_list:
            command += cm + " "
        return command

    def autoDetectPort(self):
        ports = list(serial.tools.list_ports.comports())
        Port = []
        for p in ports:
            Port.append(p[0])
        return Port[0]

    def upload_firmware_esptool(self):
        command_upload = []
        command_upload.append("esptool.py")
        command_upload.append("--port")
        command_upload.append(self.autoDetectPort())
        command_upload.append("--baud")
        command_upload.append("1500000")
        command_upload.append("write_flash")
        command_upload.append("0x00000")
        command_upload.append(".pioenvs/esp12e/firmware.bin")
        os.system(self.complete_command(command_upload))

    def build_firmware_platformIO(self):
        os.system("platformio run")

    def clear_firmware_platformIO(self):
        os.system("platformio run --target clean")

    def erase_flash(self):
        command_erase_firmware = []
        command_erase_firmware.append("esptool.py")
        command_erase_firmware.append("--port")
        command_erase_firmware.append(self.autoDetectPort())
        command_erase_firmware.append("erase_flash")
        os.system(self.complete_command(command_erase_firmware))

    def open_monitor_pio(self):
        command_open = []
        command_open.append("pio")
        command_open.append("device")
        command_open.append("monitor")
        command_open.append("--port")
        command_open.append(self.autoDetectPort())
        command_open.append("--baud")
        command_open.append("115200")
        os.system(self.complete_command(command_open))

    def close_monitor_pid(self):
        pids = [pid for pid in os.listdir('/proc') if pid.isdigit()]
        for pid in pids:
            if "pio" in open(os.path.join('/proc', pid, 'cmdline')).read():
                os.kill(int(pid), SIGKILL)


try:
    command = sys.argv[1:][0]
except:
    command = ""

command_firmware = CommandFirmware()

if command == "run" or command == "r":
    print "Build Firmware with PlatformIO"
    command_firmware.build_firmware_platformIO()
elif command == "upload" or command == "u":
    print "Upload Firmware with esptool"
    command_firmware.close_monitor_pid()
    command_firmware.build_firmware_platformIO()
    command_firmware.upload_firmware_esptool()
elif command == "clean":
    print "Clean Firmware with esptool"
    command_firmware.clear_firmware_platformIO()
elif command == "erase" or command == "e":
    print "Erase Firmware"
    command_firmware.erase_flash()
elif command == "monitor" or command == "m":
    print "Open Monitor with PIO"
    command_firmware.open_monitor_pio()
elif command == "close" or command == "c":
    print "Close Monitor with PID"
else:
    print "Full Command!"
    command_firmware.close_monitor_pid()
    command_firmware.build_firmware_platformIO()
    command_firmware.upload_firmware_esptool()
    command_firmware.open_monitor_pio()
