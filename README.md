# FdS-Player

Arduino Sketch and set of librairies for utilizing the FdS Audio Interface with the Adafruit Feather Wing Mp3. This project maximizes the capabilities of the wing, enabling functionalities such as slowing down or speeding up sound files, using markers to loop specific sections of sounds, creating playlists, and more.

### Formatting SD Cards

When formatting SD cards on a Linux computer, avoid using the OS formatting software. Instead, use the following command, where /dev/sdbX represents the SD Card.

```bash
sudo mkfs.vfat -F 32 -s 64 -S 512 /dev/sdbX
```

This is the recommended method for achieving optimal writing speed when saving data. Exercise caution when executing this command, as it can potentially destroy your data (verify sdbX carefully).

### Files structure

The File Picker Class will select files using a numeric system:

```
00 Directory
- 00 Sound File Name [Secondary Information Displayed].mp3
- 01 Following Sound File Name [Secondary Information Displayed].mp3
- ...
01 Second Directory
```

You can navigate through 100 directories, each containing 100 files. If you prefer using ID3 tags, note that only V1 is currently supported (30 characters per field). The display will use the title field for primary display, and the comment field for secondary information if it exists. Otherwise, it will use the album field. This setup allows for personalization of the display specific to the player (such as showing BPM) without affecting standard tagging, as the comment field is generally unused.

Feel free to ask if you have any further questions or if you need additional information.
