#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void encryptor(char array1[][10], char array2[10]);
void decryptor(char array1[][10], char array2[10]);
char* predefined;

int main(void)
{
	srand(time(NULL));

	char words[10][10] = { "craftbeer", "metallica", "whitewine", "champagne", "bourgogne", "sandiego", "lafayette", "pinotnoir", "sauvignon", "dondiablo" };
	char ciphertext[10] = { NULL };

	printf("\t- Encryptor -\n");
	encryptor(words, ciphertext);
	printf("\n");
	printf("\t- Decryptor -\n");
	decryptor(words, ciphertext);

	return 0;
}

void encryptor(char array1[][10], char array2[10])
{
	int key = rand() % 19 + 1;
	char SelectedWord[10] = { NULL };

	predefined = &array1[rand() % 10];

	strcpy(SelectedWord, predefined);

	for (int i = 0; SelectedWord[i]; i++) {
		array2[i] = (SelectedWord[i] + key > 'z' ? SelectedWord[i] + key - 'z' + 'a' - 1 : SelectedWord[i] + key);
	}
	printf(" Selected word: %s\n", SelectedWord);
	printf(" Selected value of the Key: %d\n", key);
	printf(" Ciphertext: %s\n", array2);
}

void decryptor(char array1[][10], char array2[10])
{
	char Plaintext[10] = { NULL };
	printf(" Ciphertext input: %s", array2);
	printf("\n\n\n");
	int key = 1;

	while (1) {
		printf("> Guess %d <\n", key);
		printf("  Key: %d\n", key);
		for (int i = 0; array2[i]; i++) {
			Plaintext[i] = (array2[i] - key < 'a' ? array2[i] - key - 'a' + 'z' + 1 : array2[i] - key);
		}
		printf("  Plaintext:  %s\n", Plaintext);

		if (!(strcmp(predefined, Plaintext))) {
			break;
		}
		printf("Matching word not found.\n\n");
		key++;
	}

	printf("Found the correct answer!\n\n");
	printf("result: '%d' was selected as the Key.\n", key);
	printf("         '%s' was the Plaintext", Plaintext);
}