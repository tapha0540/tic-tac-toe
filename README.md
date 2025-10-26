
 - A tictactoe game made using gtk library
	
	<img width="528" height="566" alt="Capture d’écran du 2025-10-26 15-27-40" src="https://github.com/user-attachments/assets/abc7f717-f840-4aca-99a3-864aec8d899c" />	

   to excecute the game on linux run this command
    first, install gtk by running
    ```console 
        sudo apt update
        sudo apt install libgtk-3-dev
    ```
    Install other necessary packages (optional, but recommended for building).
    ```console
        sudo apt install build-essential
    ```
    Compile the game
    ```console
        gcc src/tic_tac_toe.c `pkg-config --cflags --libs gtk+-3.0` -o build/game
    ```
    Run the game
    ```console
        build/game
    ```

