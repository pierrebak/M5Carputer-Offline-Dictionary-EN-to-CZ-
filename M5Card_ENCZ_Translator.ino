#include "M5Cardputer.h"
#include "Police_with_accents.h" // <-- Custom size 12 font
#include <SD.h>

// --- CONFIGURATION ---
#define DICTIONARY_PATH "/dico_final.csv" // The only data file on the SD card

// Give our imported font a simple name (must match the name in the .h file)
#define ma_police Police_with_accents

// --- GLOBAL VARIABLES ---
String currentInput = ""; 
String result = "Ready."; 

// --- FUNCTION PROTOTYPES ---
void drawUI();
String searchDictionary(String& searchTerm);
void printWrapped(const String& text, int x, int y, int maxWidth);

// =================================================================
//  SETUP
// =================================================================
void setup() {
    // M5Cardputer Initialization
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true); 
    M5.Lcd.setRotation(1); 
    
    // Set our custom font as the default
    M5.Lcd.setFont(&ma_police); 
    
    // Display startup messages
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(10, 20); 
    M5.Lcd.println("Simple Dictionary");
    
    // Use smaller system font for technical details
    M5.Lcd.setTextFont(1); 
    
    if (!SD.begin()) {
        M5.Lcd.println("SD Error!"); while (1);
    }
    
    if (!SD.exists(DICTIONARY_PATH)) {
        M5.Lcd.println("dico_final.csv not found!"); while(1);
    }
    
    // If everything is OK, switch to the main interface
    result = "Type a word...";
    drawUI();
}

// =================================================================
//  LOOP
// =================================================================
void loop() {
    M5Cardputer.update();

    // Keyboard handling (based on your examples)
    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        Keyboard_Class::KeysState keyState = M5Cardputer.Keyboard.keysState();
        bool needsRedraw = false;

        // Delete key
        if (keyState.del && currentInput.length() > 0) {
            currentInput.remove(currentInput.length() - 1); needsRedraw = true;
        } 
        // Enter key
        else if (keyState.enter && currentInput.length() > 0) {
            result = "Searching...";
            drawUI(); 
            String searchResult = searchDictionary(currentInput);
            result = searchResult.isEmpty() ? "Not found." : searchResult;
            needsRedraw = true;
        } 
        // Other keys
        else {
            for (auto c : keyState.word) {
                if ((uint8_t)c >= 32) { currentInput += c; needsRedraw = true; }
            }
        }
        if (needsRedraw) { drawUI(); }
    }
    delay(20);
}

// =================================================================
//  Functions
// =================================================================

/**
 * @brief Searches the dictionary by reading the CSV line by line.
 * @param searchTerm The English word to search for.
 * @return The Czech translation, or an empty string if not found.
 */
String searchDictionary(String& searchTerm) {
    searchTerm.toLowerCase();
    File dictFile = SD.open(DICTIONARY_PATH);
    if (!dictFile) return "File error";
    String translation = "";
    while(dictFile.available()) {
        String line = dictFile.readStringUntil('\n');
        int comma = line.indexOf(',');
        if (comma > 0) {
            if (line.substring(0, comma) == searchTerm) {
                translation = line.substring(comma + 1);
                translation.trim();
                break; // Word found, stop searching
            }
        }
    }
    dictFile.close();
    return translation;
}

/**
 * @brief Displays text, wrapping it to multiple lines if necessary.
 * @param text The text to display.
 * @param x The starting X coordinate.
 * @param y The starting Y coordinate of the first line.
 * @param maxWidth The maximum width in pixels before wrapping.
 */
void printWrapped(const String& text, int x, int y, int maxWidth) {
    std::vector<String> words;
    int lastSpace = -1;
    for (int i = 0; i < text.length(); i++) {
        if (text.charAt(i) == ' ') {
            words.push_back(text.substring(lastSpace + 1, i));
            lastSpace = i;
        }
    }
    words.push_back(text.substring(lastSpace + 1));

    String currentLine = "";
    for (const auto& word : words) {
        String testLine = currentLine + (currentLine.isEmpty() ? "" : " ") + word;
        if (M5.Lcd.textWidth(testLine) > maxWidth) {
            M5.Lcd.setCursor(x, y);
            M5.Lcd.println(currentLine);
            y += M5.Lcd.fontHeight(); 
            currentLine = word;
        } else {
            currentLine = testLine;
        }
    }
    M5.Lcd.setCursor(x, y);
    M5.Lcd.println(currentLine);
}

/**
 * @brief Displays the final user interface.
 */
void drawUI() {
    M5.Lcd.setFont(&ma_police);
    
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);

    // "EN" label on its own line
    M5.Lcd.setCursor(5, 10); 
    M5.Lcd.print("EN");

    // Input frame below
    M5.Lcd.drawRect(5, 35, 230, 30, WHITE);

    // Input text inside the frame
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setCursor(10, 42); 
    M5.Lcd.print(currentInput);

    // "CZ" label and result
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(5, 75); 
    M5.Lcd.print("CZ");
    
    M5.Lcd.setTextColor(CYAN);
    printWrapped(result, 10, 95, 220);
}