```
Options:
  -bitrate               bitrate in kilobit/s. (default: estimated by output size)
  -fps                   target framerate. (default: 60)
  -port                  streaming port. (default: 8080)
  -allow_input           enable/disable remote input. (default: 1)
  -password password     required for socket authentication. (default: no password)
  -display_number        display number to capture. (default: 0)
  -gop                   group of pictures. (default 18)
  -video_buffer_size     video buffer size. (default 768x768)
```

## Fork Changes:
- Mouse Cursor
- Latest JSMpeg
- Linux Support
- Socket Authentication
- Message Server
- Display Changing
- Shared Clipboard
- File Uploading

##

#### Mouse Cursor
The hosts cursor position is now drawn client sided. The cursor position (and display number) is sent each frame in the first 12 bytes of the message.

##

#### Latest JSMpeg
This fork uses the latest JSMpeg used with some additions found [here](https://github.com/ollydev/jsmpeg/commit/26f97f40b2d29542e6a4d8a5c07d22c4c5d5acd8).

##

#### Linux Support
This fork only supports Linux currently. Most of the Windows code already exists in the repository, I just haven't got round to testing and setting up automated building.

##

#### Socket Authentication:
`-password secret` would require `?password=secret` appended to the URL. If the password does not match the socket connection is closed. Unsure how secure this is, so depend on at your own risk.

##

#### Message Server:
I encountered a issue where when a lot of messages were being sent the image quality would reduce. 
To solve this another socket is opened on the next port (port + 1). If external access is needed remember to port forward both streaming and message ports (8080 and 8081 if using default ports).

In addition to above, all incoming messages are now serviced on a separate thread which may improve streaming.
##

#### Display Changing:
Support has been added to change displays client sided. Append `?display=50` to the URL to switch to X display 50. 

For example another display can be created using X virtual framebuffer. You'll also likely also want to spawn a desktop enviroment, this can be done the same way VNC servers do it with `~/vnc/xstartup` file.

Example xstartup for xfce4:
```
#!/bin/sh

unset SESSION_MANAGER
unset DBUS_SESSION_BUS_ADDRESS

xrdb $HOME/.Xresources
xsetroot -solid grey
exec dbus-launch startxfce4
```

Example to create another display with a desktop environment:
```
Xcfb: 50 &
DISPLAY=:50 ./xstartup &
```

##

#### Shared Clipboard:
Clipboard is shared when `ctrl + c` or `ctrl + v` is pressed. You'll need to install `xclip` for this to work :`sudo apt-get install xclip`

##

#### File Uploading:
Drag-drop a file onto the player and it will upload it to the servers `/home/user/Downloads/` directory. While a upload is in progress sending input will not work.

