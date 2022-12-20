#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "../include/PlayFair.h"


// JUST PRINT THE USAGE
void usage(char argv[])
{
	printf("USAGE : %s [OPTION..]\nOPTIONS:\n\t-k KEY:\tSet the value of key.\n\t-e TEXT:\tto encrypt the text.\n\t-d CIPHERTEXT:\tdecrypt the cipher text (ciphertext has to be all in uppercase).\n\t-h:\tprint the help page and exit.\n\nAUTHORED BY : OMAR SHEHATA \n", argv);
	exit(1);	
}

// GET SIZE OF STRING & MAKE IT ALL IN UPPER CASE
int GetSize(char *Target)
{
	int counter = 0, SizeOfData = 0;
	while(*(Target+counter) != '\0')
	{
		*(Target+counter) = toupper(*(Target+counter));
		counter++;
		SizeOfData++;
	}


	return SizeOfData;
}



int *GetPosition(char ch1, char ch2)
{
	static int position[4];

	if (ch1 == 'J')
		ch1 = 'I';

	if (ch2 == 'J')
		ch2 = 'I';


	for (int i = 0; i < 5; i++)
		for (int j =0; j < 5; j++)
		{
			if (MATRIX[i][j] == ch1)
			{
				position[0] = i;
				position[1] = j;
			}
			else if(MATRIX[i][j] == ch2)
			{
				position[2] = i;
				position[3] = j;
			}
		}

		return position;
}

void GenerateKey(char *key)
{
	char FinalKey[25];
	int counter, SizeOfKey, CharAscii = 65;

	SizeOfKey = GetSize(key);


	// PUT THE KEY THE USER PUTTED TO THE FINAL KEY
	for (int i = 0; i < SizeOfKey; i++)
		FinalKey[i] = key[i];


	// GENERATE THE KEY (THE REST OF IT)
	for (int i = SizeOfKey; i < 26; i++)
	{
		// FIRST CHECK IF THE CURRENT CHAR IS RESIDE ALREADY IN THE KEY THE USER ENTERED.
		for (int j = 0; j < SizeOfKey; j++)
			if ((FinalKey[j] == (char)CharAscii) || (FinalKey[j] == 'J' && CharAscii == 73)) // THE SECOND CONDITION TO CHECK IF THE USER ENTERED 'J', TO SKIP THE 'I' AND 'J' TOO.		
			{
				CharAscii++;
				j = -1;
			}

		if (CharAscii == 74) // IF IT = J, THEN SKIP.
				CharAscii++;

		FinalKey[i] = (char) CharAscii;
		CharAscii++;
	}



   counter = -1; // TO USE IT IN THE NEXT LOOP, FOR A PURPOSE

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			{
				counter ++; // TO MAKE EVERY LOOP START WITH IT, THE FIRST AND THE SECOND TOO.
				MATRIX[i][j] = FinalKey[counter];
			}
	
	counter = 0;

	printf("\n");
	printf("\n");

	// DISPLAY THE MATRIX
	for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
				printf("%c | ", MATRIX[i][j]);
			printf("\n");
		}


}

char *Encrypt(int SizeOfText, char *text)
{

	int counter = 0, index = 0, SizeOfFinalText;
	char FinalText[100];
	int *CharsPostions;
	static char  CipherText[100];

	// TO SPLIT THE TEXT ENTERED TO MAKE IT READY FOR ENCRYPTION.
	for (int i = 0; i < SizeOfText; i++)
	{
		if (text[i+1] == '\0') // IF I IN THE LAST CHARACTER. ADD THE CHAR AND 'X' THEN SKIP.
		{
			FinalText[counter] = text[i];
			FinalText[counter+1] = 'X';
			counter += 2;
			break;
		}

		if(text[i] == text[i+1]) // IF THERE IS TWO EQUALLED CHARATERS BESIDE EACH OTHER
		{
			FinalText[counter] = text[i];
			FinalText[counter+1] = 'X';
			counter += 2;
			continue;
		}
		// IF THERE NO EQUAL CASE OR IN THE LAST CHAR.
		FinalText[counter] = text[i]; 
		FinalText[counter+1] = text[i+1];
		i++; // TO SKIP 2 CHARS IN THE TEXT VARIABLE. BECAUSE WE PUT BOTH ALL TO THE FINAL TEXT.
		counter += 2;
	}

	FinalText[counter] = '\0'; // TO NULL THE STRING.

	printf("final string (before the last encryptio phase): %s\n", FinalText);

	SizeOfFinalText = GetSize(FinalText);
	

	// NOW, LET'S DO THE ENCRYPTTTTTTTT -_-
	counter = 0;

	while (index < SizeOfFinalText)
	{
		CharsPostions = GetPosition(FinalText[index], FinalText[index+1]);

		// SAME ROW
		if (*(CharsPostions) == *(CharsPostions+2) )
		{	
			if (*(CharsPostions+1) == 4)
				*(CharsPostions+1) = -1;

			if (*(CharsPostions+3) == 4)
				*(CharsPostions+3) = -1;
			
			CipherText[counter] = MATRIX[*CharsPostions][*(CharsPostions+1)+1];
			CipherText[counter+1] =  MATRIX[*CharsPostions][*(CharsPostions+3)+1];
		}

		// SAME COLOUMN
		else if (*(CharsPostions + 1) == *(CharsPostions + 3 ) )
		{
			if (*(CharsPostions) == 4)
				*(CharsPostions) = -1;

			if (*(CharsPostions+2) == 4)
				*(CharsPostions+2) = -1;
		
			CipherText[counter] = MATRIX[*CharsPostions + 1][*(CharsPostions+1)];
			CipherText[counter+1] =  MATRIX[*(CharsPostions+2) + 1][*(CharsPostions+1)];

		}
		
		else
		{
			CipherText[counter] = MATRIX[*CharsPostions][*(CharsPostions+3)];
			CipherText[counter+1] =  MATRIX[*(CharsPostions+2)][*(CharsPostions+1)];
		}

		counter += 2;
		index += 2;


	}
	CipherText[counter] = '\0';

	return CipherText;


}

char *Decrypt(char *CipherText)
{
	int counter = 0, index = 0;
	static char ReadableText[100];
	int *CharsPostions;

	while(CipherText[index] != '\0')
	{

		CharsPostions = GetPosition(CipherText[index], CipherText[index+1]);

		// SAME ROW
		if (*(CharsPostions) == *(CharsPostions+2) )
		{	
			if (*(CharsPostions+1) == 0)
				*(CharsPostions+1) = 5;

			if (*(CharsPostions+3) == 0)
				*(CharsPostions+3) = 5;
			
			ReadableText[counter] = MATRIX[*CharsPostions][*(CharsPostions+1)-1];
			ReadableText[counter+1] =  MATRIX[*CharsPostions][*(CharsPostions+3)-1];
		}

		// SAME COLOUMN
		else if (*(CharsPostions + 1) == *(CharsPostions + 3 ) )
		{
			if (*(CharsPostions) == 0)
				*(CharsPostions) = 5;

			if (*(CharsPostions+2) == 0)
				*(CharsPostions+2) = 5;
		
			ReadableText[counter] = MATRIX[*CharsPostions - 1][*(CharsPostions+1)];
			ReadableText[counter+1] =  MATRIX[*(CharsPostions+2) - 1][*(CharsPostions+1)];

		}
		
		else
		{
			ReadableText[counter] = MATRIX[*CharsPostions][*(CharsPostions+3)];
			ReadableText[counter+1] =  MATRIX[*(CharsPostions+2)][*(CharsPostions+1)];
		}

		// TO REMOVE THE 'X' IF IT WAS ADDED BEFORE (NOT IN THE ORIGIN TEXT)
		if (ReadableText[counter-1] == 'X' && ReadableText[counter-2] == ReadableText[counter])
		{
			ReadableText[counter-1] = ReadableText[counter];
			ReadableText[counter] = ReadableText[counter+1];
			counter--;
		}


		counter += 2;
		index += 2;


	}
	if(ReadableText[counter-1] == 'X') // TO CHECH IF THERE IS AN EXTRA 'X' IN THE END OF THE TEXT TO REMOVE IT.
		ReadableText[counter-1] = '\0';
	else
		ReadableText[counter] = '\0';

	return ReadableText;

}