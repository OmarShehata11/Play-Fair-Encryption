#include "PlayFair.c"


int main(int argc, char *argv[])
{

	if (argc == 1) // IF NOT ENTERED ANY KEY.
		usage(argv[0]);
	
	int SizeOfText, eflag = 0, dflag = 0, kflag = 0, opt;

	char *text, *CipherText, *CipherText2, *ReadableText, *key = "ab\0";

	text = malloc(100); 

opterr = 0;

	while ( (opt =getopt(argc, argv, ":k:e:d:h")) != -1 )
	{
		switch (opt)
		{

			case 'h':
				usage(argv[0]);
				break;

			case 'k' : // TO ACCEPT THE KEY
				key = optarg;
				break;

			case 'e' : // SET THE ENCRYPT FLAG
				eflag = 1;
				text = optarg;				
				break;


			case 'd' : // SET THE DECRYPT FLAG
				dflag = 1;
				CipherText2 = optarg;
				break;


			case '?' : 
				fprintf(stderr, "unknown argument : -%c\n\n", optopt);
				break;	
		}
	}


GenerateKey(key);

if(eflag)
{
	SizeOfText = GetSize(text);
	CipherText = Encrypt(SizeOfText, text);
	printf("\nthe cipher text : %s\n", CipherText);	
}

if(dflag)
{
	ReadableText = Decrypt(CipherText2);
	printf("\nthe plain text : %s\n", ReadableText);
}
	return 0;
}