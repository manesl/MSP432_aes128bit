# MSP432_aes128bit
I performed an encryption and decryption of 128 bits of data using a 128 bit key and the aes mode is called electronic code book.


When you run this in debug mode in CCS, you can inspect the data[ ] and decrypt_data[ ] values in the watch window to see if they match or not after encryption and decryption. The value I selected for encryption was 8 half-word(16 bits) long and each half-word was '4369'. After encryption, every half word gave some encrypted value (starting first half word gave 239) and after decryption, I got back the original '4369' value. I have attached pictures for reference.
