import wmi

c = wmi.WMI()

for os in c.Win32_OperatingSystem():
	print(os.Caption)

for usb in c.Win32_USBHub():
    print(f"Name: {usb.Name}, DeviceID: {usb.DeviceID}")
