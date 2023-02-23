#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function to convert J into I
void convert_j_to_i(char *message){
    for (int i = 0; i < strlen(message); i++){
        if(message[i]=='j'){
            message[i]='i';
        }
    }
}

//Function to adjust the length of text and handle repition.
void prepare(char message[])
{
    int len = 100;
    char *temp = calloc(len, sizeof(char));
    int j = 0;
    //handles repition
    for (int i = 0; i < strlen(message); i++)
    {
        if (message[i] == message[i + 1])
        {
            temp[j++] = message[i];
            temp[j] = 'x';
            temp[++j] = message[i + 1];
        }
        else
        {
            temp[j++] = message[i];
        }
    }
    int size = strlen(temp);
    //Make sures the length is even
    if (size % 2 != 0)
    {
        temp[size++] = 'x';
        temp[size] = '\0';
    }
    printf("\nEdited Message: %s", temp);
    strcpy(message, temp);
}

//Function to generate key matrix for the playfair cipher from given key
void generatekeymatrix(char key[], int ks, char keymatrix[5][5])
{
    int i, j, k, flag = 0, *visited;
    visited = (int *)calloc(26, sizeof(int));
    for (i = 0; i < ks; i++)
    {
        if (key[i] != 'j')
            visited[key[i] - 97] = 2;
    }

    visited['j' - 97] = 1;

    i = 0;
    j = 0;

    for (k = 0; k < ks; k++)
    {
        if (visited[key[k] - 97] == 2)
        {
            visited[key[k] - 97] -= 1;
            keymatrix[i][j] = key[k];
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }

    for (k = 0; k < 26; k++)
    {
        if (visited[k] == 0)
        {
            keymatrix[i][j] = (char)(k + 97);
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }
    printf("The Key Matrix is:\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%c  ", keymatrix[i][j]);
        }
        printf("\n");
    }
}

//Encryption function for playfair cipher
char *encrypt_playfair(char *message, char keymap[5][5])
{
    int i, j, r1 = 0, r2 = 0, c1 = 0, c2 = 0, k;
    for (i = 0; i < strlen(message); i++)
    {
        if (i % 2 == 0)
        {
            for (k = 0; k < 5; k++)
            {
                for (j = 0; j < 5; j++)
                {
                    if (keymap[k][j] == message[i])
                    {
                        r1 = k;
                        c1 = j;
                    }
                    if (keymap[k][j] == message[i + 1])
                    {
                        r2 = k;
                        c2 = j;
                    }
                }
            }
            if (r1 == r2)
            {
                if (c2 == 4)
                {
                    message[i] = keymap[r1 % 5][(c1 + 1) % 5];
                    message[i + 1] = keymap[r2 % 5][0];
                }
                else
                {
                    message[i] = keymap[r1 % 5][(c1 + 1) % 5];
                    message[i + 1] = keymap[r2 % 5][(c2 + 1) % 5];
                }
            }
            else if (c1 == c2)
            {
                if (r2 == 4)
                {
                    message[i] = keymap[(r1 + 1) % 5][c1 % 5];
                    message[i + 1] = keymap[0][c2 % 5];
                }
                else
                {
                    message[i] = keymap[(r1 + 1) % 5][c1 % 5];
                    message[i + 1] = keymap[(r2 + 1) % 5][c2 % 5];
                }
            }
            else if (r1 != r2 && c1 != c2)
            {
                message[i] = keymap[r1 % 5][c2 % 5];
                message[i + 1] = keymap[r2 % 5][c1 % 5];
            }
            i++;
        }
        else
        {
            i++;
        }
    }
    return message;
}

//Decryption function for playfair cipher
char *decrypt_playfair(char *encryptmsg, char keymap[5][5])
{
    int i, j, r1 = 0, r2 = 0, c1 = 0, c2 = 0, k;
    for (i = 0; i < strlen(encryptmsg); i++)
    {
        r1 = 0, r2 = 0, c1 = 0, c2 = 0;
        if (i % 2 == 0)
        {
            for (k = 0; k < 5; k++)
            {

                for (j = 0; j < 5; j++)
                {
                    if (keymap[k][j] == encryptmsg[i])
                    {
                        r1 = k;
                        c1 = j;
                    }
                    if (keymap[k][j] == encryptmsg[i + 1])
                    {
                        r2 = k;
                        c2 = j;
                    }
                }
            }
            if (r1 == r2)
            {
                if (c2 == 0)
                {
                    encryptmsg[i] = keymap[r1 % 5][(c1 - 1 + 5) % 5];
                    encryptmsg[i + 1] = keymap[r2 % 5][4];
                }
                else
                {
                    encryptmsg[i] = keymap[r1 % 5][(c1 - 1 + 5) % 5];
                    encryptmsg[i + 1] = keymap[r2 % 5][(c2 - 1 + 5) % 5];
                }
            }
            else if (c1 == c2)
            {
                if (r2 == 0)
                {
                    encryptmsg[i] = keymap[(r1 - 1 + 5) % 5][c1 % 5];
                    encryptmsg[i + 1] = keymap[4][c2 % 5];
                }
                else
                {
                    encryptmsg[i] = keymap[(r1 - 1 + 5) % 5][c1 % 5];
                    encryptmsg[i + 1] = keymap[(r2 - 1 + 5) % 5][c2 % 5];
                }
            }
            else if (r1 != r2 && c1 != c2)
            {
                encryptmsg[i] = keymap[r1 % 5][c2 % 5];
                encryptmsg[i + 1] = keymap[r2 % 5][c1 % 5];
            }
            i++;
        }
        else
        {
            i++;
        }
    }
    return encryptmsg;
}


//Encryption function for caesar cipher
char *encrypt_caesar(char *message, int key)
{
	int i;
	char ch;
	for (i = 0; message[i] != '\0'; ++i)
	{
		ch = message[i];

		if (ch >= 'a' && ch <= 'z')
		{
			ch = (ch + key - 97) % 26 + 97;
			message[i] = ch;
		}
	}
	return message;
}

//Decryption function for caesar cipher
char *decrypt_caesar(char *message, int key)
{
	int i;
	char ch;
	char *msg;
	for (i = 0; message[i] != '\0'; ++i)
	{
		ch = message[i];

		if (ch >= 'a' && ch <= 'z')
		{
			ch = (ch - key - 97 + 26) % 26 + 97;
			message[i] = ch;
		}
	}
	return message;
}

//Encryption function for affine cipher
char *encrypt_affine(char *message, int a, int b)
{
    int i;
    char ch;
    for (i = 0; message[i] != '\0'; ++i)
    {
        ch = message[i];

        if (ch >= 'a' && ch <= 'z')
        {
            ch = (char)((((a * (ch - 'a')) + b) % 26) + 'a');
            message[i] = ch;
        }
    }
    return message;
}
int modInverse(int a, int m)
{
    int m0 = m;
    int y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1)
    {
        int q = a / m;
        int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}
//Decryption function for affine cipher
char *decrypt_affine(char *message, int a, int b)
{
    int i;
    char ch;
    //find inverse
    int a_inv = modInverse(a,26);
    // int flag = 0;
    // for (int i = 0; i < 26; i++)
    // {
    //     flag = (a * i) % 26;
    //     if (flag == 1)
    //     {
    //         a_inv = i;
    //         break;
    //     }
    // }
    for (i = 0; message[i] != '\0'; ++i)
    {
        ch = message[i];

        if (ch >= 'a' && ch <= 'z')
        {
            ch = (char)(((a_inv * ((ch - 'a' - b + 26)) % 26)) + 'a');
            message[i] = ch;
        }
    }
    // printf("%d", a_inv);
    return message;
}

//Main
int main()
{

    char key[30];
    char message[100];
    char s[100];
    char keymatrix[5][5];
    char *playfairMsg;
    char *affineMsg;
    char *caesarMsg;
    char *msg;
    int i = 0;
    //Adjusting the plaintext according to given parameters
    printf("PLAYFAIR CIPHER \n\n");
    printf("Enter your plain text:");
    scanf("%s", message);
    convert_j_to_i(message);
    prepare(message);
    printf("\nPrepared word delta: %s", message);
    //Getting the key for Playfair Cipher
    printf("\nEnter key: ");
    scanf("%s", key);
    convert_j_to_i(key);
    int len = strlen(key);
    generatekeymatrix(key, len, keymatrix);
    int size = strlen(message);
    playfairMsg = encrypt_playfair(message, keymatrix);
    printf("\nEncrypted message: %s", playfairMsg);
    msg = decrypt_playfair(playfairMsg, keymatrix);
    printf("\nDecrypted message: %s", msg);

    printf("\n\nCEASER CIPHER \n");
	// int i, key;
	// char message[] = "suyash";
	// // printf("Enter a message to encrypt: ");
	// // gets(caesarMsg);
	// printf("Enter key: ");
	// scanf("%d", &key);
	caesarMsg = encrypt_caesar(playfairMsg, 3);
	printf("Encrypted message: %s", caesarMsg);
    printf("\nDecrypted message: %s", decrypt_caesar(caesarMsg,3));

    printf("\n\nAFFINE CIPHER \n");
    affineMsg = encrypt_affine(caesarMsg, 7, 5);
    printf("Encrypted message: %s", affineMsg);
    printf("\nDecrypted message: %s", decrypt_affine(affineMsg,7,5));
    return 0;
}
