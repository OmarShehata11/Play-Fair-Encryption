// THE KEY MATRIX
char MATRIX[5][5];

// THE FUNCTIONS
void usage(char argv[]); // PRINT THE USAGE
int GetSize(char *Target); // GET THE SIZE OF THE STRING
int *GetPosition(char ch1, char ch2); // GET THE POSITION OF THE MESSAGE TO THE MATRIX KEY
void GenerateKey(char *key); // GENERAT THE MATRIX
char *Encrypt(int SizeOfText, char *text); // ENCRYPT THE MESSAGE
char *Decrypt(char *CipherText); // DECRYPT THE MESSAGE


