import serial
import time
from colorama import Fore, Style


com_port = input("Please enter the COM port : ") ##(e.g., COM3 or /dev/ttyUSB0):
ser = serial.Serial(com_port, 2400)  
time.sleep(5)  

# Text to send
text_to_send = """Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. Government should focus on sources of the next crisis, not just the last one.In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future NPAs," Rajan said in the note." Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently."""

# Send text to MCU
ser.write(text_to_send.encode())

# Read response from MCU and measure speed
start_time = time.time()
bytes_received = 0

while True:
    if ser.in_waiting > 0:
        response = ser.read(ser.in_waiting)
        print(response.decode('ISO-8859-1'), end='')
        bytes_received += len(response)

    # Calculate transmission speed every second
    elapsed_time = time.time() - start_time
    if elapsed_time >= 1:
        bps = bytes_received * 8 / elapsed_time  # Calculate bits per second
        print(f"\n{Fore.GREEN}PC Transmission Speed: {bps:.2f} bps{Style.RESET_ALL}")
        start_time = time.time()
        bytes_received = 0
    time.sleep(1);
    ser.write(text_to_send.encode())


ser.close()
