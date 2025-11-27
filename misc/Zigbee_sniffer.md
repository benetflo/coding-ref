# Sniffer setup guide

Debugging Zigbee problems can be made simpler using a sniffer to view the traffic. This guide describes how to build a sniffer using a Raspberry Pi and an nRF5240 dongle.

## Components

- [Raspberry Pi 5](https://www.raspberrypi.com/products/raspberry-pi-5/)
- [Raspberry Pi 5 case](https://www.raspberrypi.com/products/raspberry-pi-5-case/)
- [Raspberry Pi 27W USB-C power supply](https://www.raspberrypi.com/products/27w-power-supply/)
- [nRF52840 dongle](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-Dongle)
- MicroSD card
- Ethernet cable (optional)

All components are available from [DigiKey](https://www.digikey.se/), [Mouser](https://www.mouser.se), and other electronics distributors.

## Assembly

All components can be put together without any tools. No soldering is needed. Only an MicroSD card reader is required to initially flash OS.

## Setup

1. Download and install the [Raspberry Pi Imager](https://www.raspberrypi.com/software/).

1. Select the following:
    
    - **Device**: Raspberry Pi 5
    - **Operating system**: Raspberry Pi OS 64-bit
    - **Storage**: Your MicroSD card

1. When prompted to apply OS customization settings, click **edit settings**:

    Under General set:

    - **Hostname**: sniffer
    - **Username**: user
    - **Password**: password
    - **WiFi SSID**: Your WiFi's SSID
    - **WiFi password**: Your WiFi's password

    Under Services set:

    - **Enable SSH**: Yes

1. Click **save** and then confirm the remaining steps to flash the MicroSD card.

1. Once complete, insert the MicroSD card into the Raspberry Pi and power it on. It may take a few minutes to boot.

1. Connect to the Raspberry Pi using SSH:

    ```sh
    ssh user@sniffer.local

    # Enter the password you chose before
    ```

1. Update the OS:

    ```sh
    sudo apt update

    sudo apt full-upgrade
    ```

1. Create a [Tailscale]() account if you do not already have one, and setup Tailscale on your local machine.

1. Setup Tailscale on the Raspberry Pi:

    ```sh
    curl -fsSL https://tailscale.com/install.sh | sh

    sudo tailscale up

    # Paste the generated link into your browser to complete the setup
    ```

1. Enable VNC on the Raspberry Pi:

    ```sh
    sudo raspi-config

    # Choose to Interface Options → VNC → Enable
    ```

1. Install Wireshark:

    ```sh
    sudo apt install wireshark

    sudo dpkg-reconfigure wireshark-common

    # Choose yes

    sudo chmod +x /usr/bin/dumpcap
    ```

1. Download the sniffer extension:

    ```sh
    mkdir -p ~/.local/lib/wireshark/extcap
  
    wget https://raw.githubusercontent.com/NordicSemiconductor/nRF-Sniffer-for-802.15.4/refs/heads/master/nrf802154_sniffer/nrf802154_sniffer.py -P ~/.local/lib/wireshark/extcap

    chmod +x ~/.local/lib/wireshark/extcap/nrf802154_sniffer.py
    ```

1. On your local machine, download and install the [nRF Connect for Desktop](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-Desktop) 

1. Open nRF Connect for Desktop and install the Programmer tool.

1. Again, on your local machine, download the [firmware file](https://github.com/NordicSemiconductor/nRF-Sniffer-for-802.15.4/blob/master/nrf802154_sniffer/nrf802154_sniffer_nrf52840dongle.hex) for the nRF5280 dongle.

1. Plug the nRF52840 dongle into you local machine, and using the Programmer tool, write the `.hex` file. Once complete, the green LED on dongle will blink, indicating that it's ready.

1. Move the dongle from you local machine to the Raspberry Pi.

1. Connect to the Raspberry Pi desktop using a [VNC viewer](https://www.realvnc.com).

1. Open Wireshark. The **nRF Sniffer for 802.15.4: /dev/ttyACM0** capture interface should be shown.

1. Navigate to **Edit** → **Preferences** → **Protocols** → **Zigbee** → **Pre-configured Keys: Edit** and enter your Zigbee network key.

## Usage

1. The sniffer can now be installed at a site. Simply plug into power and an internet connection.

1. Using Tailscale connect again over VNC to the Raspberry Pi desktop.

1. Open Wireshark and start the sniffer.

1. The Raspberry Pi can now be accessed from anywhere and periodically checked.
