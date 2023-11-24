# FdS-Player

Arduino Sketch for using the FdS Audio Interface with the Adafruit Feather Wing Mp3. This project makes full use of the wing, including the ability to slow down or speed up sound files, use markers to loop on certain portions of sounds, create playlists, etc.

### Formatting SD Cards

When using a Linux computer, SD cards should be formatted not with the OS formatting software, but with the following command, where /dev/sdbX represents the SD Card.

```bash
sudo mkfs.vfat -F 32 -s 64 -S 512 /dev/sdbX
```

This is the only way to have good writing speed when saving data.
Please do this carefully, this command can detroy your datas (sdbX must be carefully verified).

### Files structure

The File Picker Class will select files using a numeric system:

```
00 Directory
- 00 Name of the sound file [Secondary information displayed].mp3
- 01 Name of the following [Secondary information displayed].mp3
- ...
01 Second directory
```

You'll then be able to navigate through 100 Directory of 100 files each.

Feel free to ask if you have any further questions or if you need additional information.
