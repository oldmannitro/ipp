# ipp - iOS Photo Manager

`ipp` is a command-line tool designed to help manage photos on iOS devices. It allows you to copy your favorite photos from an iOS device (mounted via `ifuse`) to a specified destination on your local machine.

## Features

*   Selects favorite photos from the iOS Photos database.
*   Copies selected photos to a specified destination.

## Requirements

*   `sqlite3`: For interacting with the iOS Photos database (`Photos.sqlite`).
*   `ifuse`: To mount the iOS filesystem. This tool assumes the iOS device is already mounted.

## Building

To build the `ipp` executable, navigate to the project's root directory and run `make`:

```bash
make
```

## Usage

The `ipp` program requires two arguments: the iOS mount point and the destination directory. It must be run as root.

```bash
sudo ./ipp <ios_mount_point> <destination_directory>
```

**Example:**

```bash
sudo ./ipp /mnt/ios ~/my_ios_photos
```

This command will copy all favorite photos from the iOS device mounted at `/mnt/ios` to the `~/my_ios_photos` directory.

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.
