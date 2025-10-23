# Step 6: Documentation & Presentation

## Design Summary:
- Modular architecture
- Real-time event detection
- Recursive and filtered monitoring

## Usage Instructions:
- Compile using `gcc`.
- Run with permissions to access directories.
- Configure filters and logging options via arguments or config file.

## Known Limitations:
- Linux-specific implementation.
- Requires inotify support in kernel.

## Demo:
1. Start the monitor.
2. Create/modify files in the watched directory.
3. Observe logged events in real time.