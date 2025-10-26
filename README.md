	![A screenShot of the game](images/screenshot-1)
 - A tictactoe game made using gtk libray
    to excecute the game on linux run this command
    first, install gtk by running
    ```
        sudo apt update
        sudo apt install libgtk-3-dev
    ```
    Install other necessary packages (optional, but recommended for building).
    ```
        sudo apt install build-essential
    ```
    Compile the game
    ```
        gcc src/tic_tac_toe.c `pkg-config --cflags --libs gtk+-3.0` -o build/game
    ```
    Run the game
    ```bash
        build/game
    ```

