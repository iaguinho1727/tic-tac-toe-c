# Tic-Tac-Toe

A terminal-based Tic-Tac-Toe game written in C using raw terminal input for a smooth, real-time experience — no line-by-line typing, just move and play.

## Controls

| Key | Action |
|---|---|
| `W` / `↑` | Move cursor up |
| `S` / `↓` | Move cursor down |
| `A` / `←` | Move cursor left |
| `D` / `→` | Move cursor right |
| `Space` | Place your mark |
| `R` | Reset the game |
| `Q` / `Esc` | Quit |

## Building from source

Requires a C compiler and a POSIX-compatible system (Linux, macOS, BSDs).

```bash
autoconf
./configure
make
```

The binary will be at `out/TicTacToe`.

## Installing

```bash
sudo make install DESTDIR=/usr/local/bin
```

## Arch Linux (AUR)

```bash
yay -S tic-tac-toe-c
```

## License

[Apache License 2.0](LICENSE)