
# Arduino LCD Text Scroller

This Arduino sketch enables scrolling text display on Liquid Crystal Display (LCD). Rows and columns can be customised further It provides functionalities to display text in a scrolling manner, ensuring that longer messages are adequately presented within the limited screen space.


## Features

- Text Display: Displays text messages on an LCD screen.
- Scrolling Styles:
    - Text Shift on Limit: Shifts the entire text horizontally to ensure that all characters are displayed within the specified LCD dimensions. If the text exceeds the width of the LCD, it scrolls horizontally to reveal the hidden characters.
    - Scrolling Up Style: Scrolls the text vertically, moving it upward to reveal hidden lines of text. It scrolls line by line until all lines have been displayed.
- Dynamic Length Handling: Automatically adjusts for varying message lengths.
- Customizable Rows and Columns: Easily configure the number of rows and columns on your LCD display.


## Requirements

- Hardware: Arduino board, Liquid Crystal Display (LCD), and required connections.
- Software: Arduino IDE (Integrated Development Environment).
## Installation

1. Connect the LCD to the Arduino board according to the specified pin configuration.
2. Open the Arduino IDE.
3. Copy the provided code into a new Arduino sketch.
4. Customize the numRows and numCols variables in the code to match your LCD dimensions.
5. Upload the sketch to your Arduino board.
    
## Usage

1. Connect the Arduino board to a power source.
2. Open the serial monitor in the Arduino IDE.
3. Enter text messages to be displayed on the LCD screen. Each message should be terminated by pressing the Enter key.
4. Choose the desired scrolling style by commenting out or removing the function call for one style and uncommenting or adding the function call for the other style in the loop function of the code.
5. The sketch will automatically process the messages and display them on the LCD screen using the selected scrolling style.


## Customization

- **Rows and Columns**: Adjust the `numRows` and `numCols` constants in the code to match your LCD dimensions.

  ```cpp
  const uint8_t numRows = 2;  // Change this value to match the number of rows on your LCD
  const uint8_t numCols = 16; // Change this value to match the number of columns on your LCD

- You can comment the scrolling style you don't want to use or just copy the part of code you want to use.
## Notes

- Ensure that the connections between the Arduino board and the LCD are correctly established.
- Check the serial monitor for debugging messages or to observe the processing of input text.
- If extremely larger text is needed to print, consider adjusting the data types of variables such as len, numSubStr, and others to accommodate larger values. Using long long, double, or size_t might be more suitable in such cases.
## Author

- Pyae Sone Hein - [GitHub](https://github.com/Pyisoe-Thame)


## License
This project is licensed under the MIT License - see the [LICENSE](https://choosealicense.com/licenses/mit/) file for details.

