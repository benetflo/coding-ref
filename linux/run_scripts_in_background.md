Create a script that you want to run as a background process.

Make the script executable if it is a bash script:
```
chmod +x example.sh
```

Run the script in the background
```
python3 example.py &
./example.sh &
./a.out &
```

Automatic run at boot with systemd. First create a service-file: "/etc/systemd/system/example.service"
```
[Unit]
Description=Example Service

[Service]
ExecStart=/usr/bin/python3 /home/pi/example.py
Restart=always
User=pi

[Install]
WantedBy=multi-user.target

```
Activate and start:

```
sudo systemctl daemon-reload
sudo systemctl enable example.service
sudo systemctl start example.service
```