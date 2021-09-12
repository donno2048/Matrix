# Matrix

![video](./wakeup.gif)

## Compile

### Linux

```bash
gcc matrix.c -o matrix -lncurses -Ofast
```

### Windows

```bat
gcc matrix.c -o matrix.exe -Llib -Ofast -Iinclude -lpdcurses
```

## Use

### Linux

```bash
./matrix
```

### Windows

```bat
.\matrix.exe
```

0-9 set speed (<kbd>0</kbd>,<kbd>1</kbd>,<kbd>2</kbd>,<kbd>3</kbd>,<kbd>4</kbd>,<kbd>5</kbd>,<kbd>6</kbd>,<kbd>7</kbd>,<kbd>8</kbd>,<kbd>9</kbd>)

!-& set color (<kbd>!</kbd>,<kbd>@</kbd>,<kbd>#</kbd>,<kbd>$</kbd>,<kbd>%</kbd>,<kbd>^</kbd>,<kbd>&</kbd>)

<kbd>Ctrl</kbd>+<kbd>C</kbd> quit (on Windows twice)
