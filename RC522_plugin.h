/*  This script uses the RC522 module to read an RFIC card/ tag
    and prints its UID to the Serial Monitor
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 22 // Can used any available GPIO pin 
#define SS_PIN 5   // VSPI uses GPIO 5 as the slave-select pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup_device() {
    // Initialize serial communications with the PC
    Serial.begin(115200);

    while (!Serial);                    // Do nothing if no serial port is opened

    Serial.println("Initializing...");
    SPI.begin();                        // Init VSPI bus
    mfrc522.PCD_Init();                 // Init MFRC522

    // Prints the reader's firmware version
    mfrc522.PCD_DumpVersionToSerial();
    
    Serial.println();

    Serial.println("Scan card to see UID.");
    delay(1000);

    Serial.println("Place card on card reader.");
}

void loop_device(){
    // Check if a new card is present
    if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
    }

    /*  Read the card's UID, return true if read is successful, and
        the card's UID is written in mfrc522.uid.uidByte, which is 
        an array of bytes
    */
    if (!mfrc522.PICC_ReadCardSerial()) {
    return;
    }

    Serial.print("Card UID: ");

    /*  Iterate over mfrc522.uid.uidByte and print out the bytes in 
        hexadecimal format
    */
    for (byte i = 0; i < mfrc522.uid.size; i++) {
    
    // If the HEX value is less than 0x10, add a '0' as padding
    if (mfrc522.uid.uidByte[i] < 0x10) {
        Serial.print("0");
    }

    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
    }

    Serial.println();

    // Halt communication with the card
    mfrc522.PICC_HaltA();

    Serial.println("You may now remove the card.");

    delay(2000);
    Serial.println();
    Serial.println("Place card on card reader.");
}