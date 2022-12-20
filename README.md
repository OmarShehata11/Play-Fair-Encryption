


# INTRODUCTION 

This task aims to implement the PlayFair algorithm by C programming language. Written by: Omar Shehata 



## HOW TO USE IT: 

first download it and run it by :
```bash
cd bin
make
./PlayFair
```

At the first run without any options, it will print the Usage message: 

```bash
USAGE : ./PlayFair [OPTION..]

OPTIONS: 
`        `-k KEY: Set the value of key.
`        `-e TEXT:        to encrypt the text.
`        `-d CIPHERTEXT:  decrypt the cipher text (ciphertext has to be all in uppercase). 
          -h:     print the help page and exit.

AUTHORED BY : OMAR SHEHATA
```
Here we have three important options, “-k key” this option is always needed to provide the key of the algorithm. Then “-e text” if you want to encrypt a text with the specified key. And “-d ciphertext” to decrypt the ciphertext back again (notice that the ciphertext have to be in uppercase otherwise the program will run in an unexpected way.). 

Let’s take an example: ``` ./PlayFair -k omar -e hello``` 

Here we specified the key to be “omar” (not important to be in either lower or upper case). And the text “hello” to encrypt (also the case isn’t important). 

When I run the program, it will print:  
```bash
O | M | A | R | B |

C | D | E | F | G | 

H | I | K | L | N |

P | Q | S | T | U | 

V | W | X | Y | Z |

final string : HELXLO

the size of final text : 6
the cipher text : KCKYHR
```
- The first thing to note is the generated key printed in a matrix shape, then the final string (which is the text after modification according to the rules of the algorithm to make it ready to be encrypted) then the size of the final text, and at last the CipherText. 
- So the encryption of the hello text with the key omar, will generate the ciphertext: KCKYHR, so let’s then try to decrypt that string to make sure that the program is running well. 

We will write at the terminal: ```./PlayFair -k omar -d KCKYHR``` And it will print to us:  
```bash
O | M | A | R | B |

C | D | E | F | G | 

H | I | K | L | N |

P | Q | S | T | U | 

V | W | X | Y | Z |

the plain text : HELLO
```
Now, we see that it printed the generated key again, and the plain text correctly, notice that I have entered the ciphertext in the terminal in uppercase. 

So now you know how to use the program, let’s then discuss simply some of the internals of the code itself. 

## CODE INTERNALS 

When we open the source code, we will find 5 function and the main, every function are in some cases related to each other to achieve the algorithm. Let’s start with them. 

**Usage**  

This function is the easiest one, it just prints the usage message when you run the program without any argument or run it with the -h argument. 

**GetSize** 

I made this function to retrieve the size of strings we are using. in C there is no data type called string, so I have to deal with the strings in either defining an array of characters or a pointer to character. And both I can’t make sure what’s the size of the string it really holds, so I made this function to help me with it. 

**GetPosition** 

This function is really useful while decrypting and encrypting, because it retrieve the position of the characters I’m dealing with right now from the matrix (key), to decide whether to move up or down and so on according the Encryption or The decryption process. 

**GenerateKey** 

This function Is just generating the key according to the entered value and print it off. 

**Encryption** 

This function is the heart of the program, it takes the Plain text and the size of it, and try to Encrypt that text according to the rules of the algorithm, ![](Aspose.Words.dc635080-c815-4380-bb20-83315fcfbdb6.002.png)and of course it uses inside of it the GetPosition function to help it to identity the position of the characters to Encrypt. 

**Decrypt** 

Same as Encrypt of the rules but of course logically, but it’s the opposite of it. And also, it calls the ![](Aspose.Words.dc635080-c815-4380-bb20-83315fcfbdb6.003.png)GetPosition to help. 

**main** 

Inside the main function, we would see the ***getopt*** function, to help us in dealing with the argument passed. And we have only four argument we are expecting. (k) which the key option (has to accept an argument with it, which is the key value), and (e) which is the encrypt option (and also have to accept another argument with it which is the plain text), (d) the decrypt option (accept the cipher text to decrypt), and finally the (h) help option which just print the usage message. 

Then we will call the ***GenerateKey*** function with the key value passed to generate the key, and sit it to the global variable called (MATRIX) which is an 2-d array with 5\*5 dimensions. 

And at last, it checks the ***eflag*** and the ***dflag*** to decide whether the user wants to encrypt ot decrypt (or even both). 
