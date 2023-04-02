# Anthony Redamonti
# Dr. Syed Shazli
# CSE-644: Internet Security
# 3-5-2023

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/bio.h> /* BasicInput/Output streams */
#include <openssl/err.h> /* errors */
#include <openssl/ssl.h> /* core library */
#include <openssl/evp.h>
#include <ctype.h>
#include <unistd.h>

#define BuffSize 1024
#define WordSize 16
#define InitVectorSize 32

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
	EVP_CIPHER_CTX *ctx;
	int len;
	int ciphertext_len;
	/* Create and initialise the context */
	if(!(ctx = EVP_CIPHER_CTX_new())){
		EVP_CIPHER_CTX_cleanup(ctx);
		printf("error occurred\n");
		return 0;
	}
	 /*
	 * Initialise the encryption operation. IMPORTANT - ensure you use a key
	 * and IV size appropriate for your cipher
	 * In this example we are using 256 bit AES (i.e. a 256 bit key). The
	 * IV size for *most* modes is the same as the block size. For AES this
	 * is 128 bits
	 */
	 if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)){
		EVP_CIPHER_CTX_cleanup(ctx);
		printf("error occurred\n");
		return 0;
	 }
	 
	 /*
	 * Provide the message to be encrypted, and obtain the encrypted output.
	 * EVP_EncryptUpdate can be called multiple times if necessary
	 */
	 if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)){
		EVP_CIPHER_CTX_cleanup(ctx);
		printf("error occurred\n");
		return 0;
	 }
	 
	 ciphertext_len = len;
	 
	 /*
	 * Finalise the encryption. Further ciphertext bytes may be written at
	 * this stage.
	 */
	if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)){
		EVP_CIPHER_CTX_cleanup(ctx);
		printf("error occurred\n");
		return 0;
	}
	
	ciphertext_len += len;
	return ciphertext_len;
}

int main(){

	unsigned char plainText[] = "This is a top secret.";
	unsigned char cipherText[] = "764aa26b55a4da654df6b19e4bce00f4ed05e09346fb0e762583cb7da2ac93a2";
	unsigned char* initializationVector = (unsigned char*)"aabbccddeeff00998877665544332211";

	int plainTextLen = strlen((const char*)plainText);
	unsigned char word[WordSize];
	unsigned char cipherOutput[64];
	int outputBufferLength;
	
	FILE *wordsListFile = fopen("WordsList.txt", "r");

	int max = 0;	
	int count = 0; 
	int wordSelector = 150; // select a word to print to the console
 
	while(fgets(word, WordSize, wordsListFile)){		

		int wordLen = strlen(word);
		word[wordLen-2] = '\0'; // end the word with the NULL character
		wordLen = strlen(word);

		// adjust the padding of each word if needed
		// all words should be size 16
		while(wordLen < WordSize){
			word[wordLen] = '#';
			wordLen++;
			if(wordLen == WordSize){
				word[wordLen] = '\0'; 			
			}	
		}

		unsigned char* key = (unsigned char*)word;		
		if(count == wordSelector){printf("key: ");}
		
		// print the key for debugging purposes
		for(int j = 0; j < wordLen; j++){
		    if(count == wordSelector){
			printf("%c", key[j]);
			if(j == wordLen-1){printf("\n");}
		    }
		}	

		// length of key is now 16 bytes
		// convert key to hexadecimal
		unsigned char formattedKey[33];

		for(int i = 0; i < 16; i++){
    			sprintf(formattedKey+2*i, "%.2x", key[i]);
		}

		formattedKey[32] = '\0';
		
		if(count == wordSelector){printf("formatted key: ");}
		// print the formatted key for debugging purposes
		for(int j = 0; j < 32; j++){
		    if(count == wordSelector){
			printf("%c", formattedKey[j]); 
			if(j == 31){printf("\n");}
		    }
		}

		int cipher_len = encrypt(plainText, plainTextLen, formattedKey, initializationVector, cipherOutput);

		unsigned char formattedOutput[65]; 

		// format the ciphertext to hexadecimal
		for(int i = 0; i < 64; i++){
			unsigned char ciphOutputByte[1];
			sprintf(ciphOutputByte, "%02x", cipherOutput[i]);
			unsigned char ciphTextByte = cipherText[i];
			formattedOutput[i] = ciphOutputByte[0];
		}
		formattedOutput[64] = '\0';
		if(count == wordSelector){printf("formatted cipher output: ");}

		// print the formatted key for debugging purposes
		for(int j = 0; j < 64; j++){
		    if(count == wordSelector){
			printf("%c", formattedOutput[j]);
			if(j == 63){printf("\n");}
		    }
		}

		int index = 0; 
		while((index < 64) && (formattedOutput[index] == cipherText[index])){
		    index = index + 1;
		}
		
		// record the maximum bytes we were able to match in a row
		if(index > max){max = index;}

		// if we matched all 64 bytes, we have found a solution
		if(max == 64){
		    printf("match found!\n");
		    printf("word: %s\n", word);
		}
		else{
			// nothing to do at this time.	
		}

		count = count + 1;
	}
	
	printf("max num of bytes matching in a row: %d\n", max);	
	printf("ciphertext solution: %s\n", cipherText);
	fclose(wordsListFile);
	return 0;
}
