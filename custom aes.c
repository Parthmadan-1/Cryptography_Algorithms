//PARTH MADAN
//202051132
#include<stdio.h>
#include<stdint.h>  // This library is included for using  for uint8_t data type
#include<stdlib.h>    //This library is included for input/output operations



// This is a declaration of a two-dimensional array named 'sub' of size 16x16, where each element is of type 'uint8_t'
uint8_t sub[16][16] = { {
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};



const uint32_t Rcon[10] = {
    0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1B000000, 0x36000000
}; // it will be used in key generation

/* This function performs Galileo multiplication in the finite field GF(2^8),(a*b+1)
   with irreducible polynomial x^8 + x^4 + x^3 + x + 1, using the input
   operands a and b. The result is returned as an 8-bit hexadecimal value. Here a is always 0x02*/
   

uint8_t galileo_multiply(uint8_t a, uint8_t b) {
    uint8_t product = 0;
    
    /* Perform 8 iterations, one for each bit in b. */
    for (int i = 0; i < 8; i++) {
        /* If the least significant bit of b is 1, XOR a with the current product. */
        if ((b & 0x01) == 1) {
            product ^= a;
        }
        
        /* Left-shift a by 1 bit and check if its MSB is 1. */
        uint8_t msb = a & 0x80;
        a <<= 1;
        
        /* If the MSB of a is 1, XOR it with the irreducible polynomial x^8 + x^4 + x^3 + x + 1. */
        if (msb == 0x80) {
            a ^= 0x1B;
        }
        /* Right-shift b by 1 bit to process the next bit. */
        b >>= 1;
    }
    
    /* Add 1 to the product, which is equivalent to XORing it with 1. */
    product ^= 1;
    
    /* Return the final product. */
    return product;
}

uint8_t galileo_product(uint8_t a, uint8_t b) {
    uint8_t product = 0;
    
    /* Perform 8 iterations, one for each bit in b. */
    for (int i = 0; i < 8; i++) {
        /* If the least significant bit of b is 1, XOR a with the current product. */
        if ((b & 0x01) == 1) {
            product ^= a;
        }
        
        /* Left-shift a by 1 bit and check if its MSB is 1. */
        uint8_t msb = a & 0x80;
        a <<= 1;
        
        /* If the MSB of a is 1, XOR it with the irreducible polynomial x^8 + x^4 + x^3 + x + 1. */
        if (msb == 0x80) {
            a ^= 0x1B;
        }
        /* Right-shift b by 1 bit to process the next bit. */
        b >>= 1;
    }
    
    /* Add 1 to the product, which is equivalent to XORing it with 1. */
    
    /* Return the final product. */
    return product;
}


// Galois Field addition function
uint8_t GF_add(uint8_t a, uint8_t b) {
    return a ^ b;
}

// Galois Field multiplication function
uint8_t GF_multiply(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    int counter;
    uint8_t carry;
    for (counter = 0; counter < 8; counter++) {
        if (b & 1) p ^= a;
        carry = a & 0x80;
        a <<= 1;
        if (carry) a ^= 0x1b; // irreducible polynomial x^8+x^4+x^3+x+1
        b >>= 1;
    }
    return p;
}

// Function to multiply two 4x4 matrices in GF(8)
void matrix_multiply(uint8_t A[][4], uint8_t B[][4], uint8_t C[][4]) {
    int i, j, k;
    uint8_t sum;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            sum = 0;
            for (k = 0; k < 4; k++) {
                sum = GF_add(sum, GF_multiply(A[i][k], B[k][j]));
            }
            C[i][j] = sum;
        }
    }
}

void copy_to_matrix(uint8_t arr[], uint8_t mat[][4]) {
    int i, j, k = 0;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            mat[i][j] = arr[k];
            k++;
        }
    }
}


uint8_t newsubbyte(uint8_t hex_value)
{
    uint8_t first_digit = (hex_value & 0xF0) >> 4; // Extract the first digit
    uint8_t second_digit = hex_value & 0x0F; // Extract the second digit
    uint8_t hehe= sub[first_digit][second_digit];
    return hehe;
    
} //basically what this function is doing, it extracts first and second digit of our hexadecimal number and finds its corresponding subbyte

void left_shift_circular(uint8_t arr[4]) {
    uint8_t temp = arr[0];
    arr[0] = arr[1];
    arr[1] = arr[2];
    arr[2] = arr[3];
    arr[3] = temp;
}

void xor_uint32_t_uint8_t(uint32_t num, uint8_t arr[4], uint8_t new[4]) {
    //uint8_t* ptr = (uint8_t*) &num; // Get a pointer to the bytes of the uint32_t number
    uint8_t pt[4]={0};
	for(int i=3;i>=0;i--)
	{
		pt[i]^=num&0xff;
		num=num>>8;
	}
	for (int i = 0; i < 4; i++) {
        new[i] = pt[i] ^ arr[i]; // XOR the corresponding bytes of the uint32_t and uint8_t arrays
    }
}

uint8_t roundkey(uint8_t keys[16], uint8_t key[4][44]) //this is my round key generation function
{   
    
  for ( int i=0;i<44;i++)
  {
    
        if(i<=3) // for rounds o to 3
        {
            key[0][i]= keys[4*i];
            key[1][i]= keys[4*i +1];
            key[2][i]= keys[4*i +2];
            key[3][i]= keys[4*i+ 3];

        }
        else  // for rounds 4 to 44
        {
            uint8_t temp[4]= {key[0][i-1],key[1][i-1],key[2][i-1],key[3][i-1]};
            if(i%4 ==0)
            {
                left_shift_circular(temp);
                temp[0]= newsubbyte( temp[0]);
                temp[1]= newsubbyte( temp[1]);
                temp[2]= newsubbyte( temp[2]);
                temp[3]= newsubbyte(temp[3]);
                uint32_t hehe = Rcon[i/4 -1] ;
                uint8_t new[4];
                xor_uint32_t_uint8_t(hehe, temp, new);
                temp[0]=new[0];
                temp[1]=new[1];
                temp[2]=new[2];
                temp[3]=new[3];
                
              


            }

            key[0][i]=( key[0][i-4] ^ temp[0]);
            key[1][i]=( key[1][i-4] ^ temp[1]);
            key[2][i]= (key[2][i-4] ^ temp[2]);
            key[3][i]=( key[3][i-4] ^ temp[3]);
        }
    
  }
}

void xor1(int c, uint8_t n[4][4], uint8_t p[4][4] )
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            n[i][j]= p[i][j];
        }
    }
}

void shift_rows(uint8_t state[4][4]) {
    // Shift second row one position to the left
    uint8_t temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;
    
    // Shift third row two positions to the left
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Shift fourth row three positions to the left
    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
} // used while encryption


void inv_shift(uint8_t arr[][4], int n) { //used while decrytpion
    for(int i=0; i<n; i++) {
        // Calculate the number of positions to shift for this row
        int shift_amount = i;

        // Perform the circular shift by the calculated amount
        for(int s=0; s<shift_amount; s++) {
            // Store the last element of the row
            int last = arr[i][n-1];

            // Shift all elements of the row to the right by one
            for(int j=n-1; j>0; j--) {
                arr[i][j] = arr[i][j-1];
            }

            // Put the last element at the beginning of the row
            arr[i][0] = last;
        }
    }
}




void xor(int i, uint8_t mat[4][4], uint8_t rounds[176])
{
    int k=0;
    for(int j=0;j<4;j++)
    {
        for(int l=0;l<4;l++)
        {
            mat[l][j]^=rounds[i*16 + k];
            k++;
        }
    }
}

uint8_t findindex(uint8_t plaintext)
{
    uint8_t temp=0;
    for(int i=0;i<16;i++)
    for(int j=0;j<16;j++)
    {
        if(sub[i][j]==plaintext)
            temp=i;
            temp<<=4;
            temp^=j;
    }
    return temp;
}

void inv_sub(uint8_t arr[4][4]) // this is the inverse substitution function
{
    for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
    {
        arr[i][j]= galileo_product(141,findindex(arr[i][j])^1);
    }
}

int main() {
  

    uint8_t plaintext[16]; // Declare an array of 16 uint8_t values for plaintext
    int i; // Declare a counter variable for the loop

    printf("Enter 16 hexadecimal values for plaintext:\n"); // Prompt the user to enter 16 hexadecimal values

    for(i = 0; i < 16; i++) { // Loop through each element of the array
        scanf("%hhx", &plaintext[i]); // Read a hexadecimal value from the user input and store it in the current array element
    }

    printf(" Plaintext values:\n"); // Print a label for the array values
    
    for(i = 0; i < 16; i++) { // Loop through each element of the array
        printf("%02X ", plaintext[i]); // Print the hexadecimal value of the current array element with two digits and a space separator
    }

    printf("\n");


    uint8_t key[16]; // Declare an array of 16 uint8_t values for key
    int j=0; // Declare a counter variable for the loop

    printf("Enter 16 hexadecimal values for key:\n"); // Prompt the user to enter 16 hexadecimal values

    for(j= 0; j < 16; j++) { // Loop through each element of the array
        scanf("%hhx", &key[j]); // Read a hexadecimal value from the user input and store it in the current array element
    }

    printf(" key values:\n"); // Print a label for the array values

    for(j = 0; j < 16; j++) { // Loop through each element of the array
        printf("%02X ", key[j]); // Print the hexadecimal value of the current array element with two digits and a space separator
    }

    
    // new mixcolumn matrix
   uint8_t M[4][4] = {
        {1, 4, 4, 5},
        {5, 1, 4, 4},
        {4, 5, 1, 4},
        {4, 4, 5, 1}
    };

       uint8_t Minverse[4][4] = {
        {165, 7, 26, 115},
        {115, 165, 7, 26},
        {26, 115, 165, 7},
        {7, 26, 115, 165}
    };

 int k=0;
    uint8_t temp[4][4];
    for ( j = 0; j < 4; j++) {
    for ( i = 0; i < 4; i++) {
        temp[i][j] = plaintext[k];
        k++;
    }
    }
  
 

int l=0;
    uint8_t newmat[4][4];
    for ( j = 0; j < 4; j++) {
    for ( i = 0; i < 4; i++) {
        newmat[i][j] = plaintext[l];
        l++;
    }
    }



    uint8_t round_key[4][44]; // in this matrix, I will store all 44 words, each word is of 4 bytes or 32 bits, each word is stored column wise
    roundkey(key, round_key); // I have called the round key generation function, which will store round keys in round_key
    
   
    uint8_t rounds[176];
    for ( j = 0; j < 44; j++) {
    for ( i = 0; i < 4; i++) {
        rounds[j * 4 + i] = round_key[i][j];
    } // converted 4*44 round key matrix to 176 size array for ease
   }
    // pre round transformation
      xor(0, newmat, rounds); //xor 



// for round 1 to round 9
    for(int round=1;round<10;round++)
    {
    for(  i=0;i<4;i++)
    {
        for ( j=0;j<4;j++)
        {
      newmat[i][j]= newsubbyte(galileo_multiply(0x02, newmat[i][j]));// subbyte function
        }
    }

    
    uint8_t after_mix[4][4];
    shift_rows(newmat); // shift rows function

    matrix_multiply(M, newmat, after_mix); // mix column function
 
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            newmat[i][j]= after_mix[i][j];
        }
    }
 

xor(round, newmat, rounds); // xor function( with round keys)




    }

    //round10
    for( int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
      newmat[i][j]= newsubbyte(galileo_multiply(0x02, newmat[i][j]));
        }
    }

    shift_rows(newmat);

      xor(10, newmat, rounds);

printf("\nEncrypted text :\n"); // this is my final encrypted text
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                printf("%x ", newmat[j][i]);
            }
            
        }
    
    

    

// now, we will run decryption


    // round 10 for decryption
    xor(10, newmat, rounds);
    inv_shift(newmat,4);
    inv_sub(newmat);


    
    
// round 9 to round 1 decryption
    for( int i=9;i>0;i--)
    {
        xor(i, newmat, rounds); // xor will remain same in decryption as well.
        uint8_t after_mix[4][4];
        matrix_multiply(Minverse, newmat, after_mix); //inverse mix column, minverse is passed here
        for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            newmat[i][j]= after_mix[i][j];
        }
    }

    inv_shift(newmat,4); // inverse shift function, it will right shift now
    inv_sub(newmat); // inverse subbyte function




    }

    xor1(0, newmat, temp); // pre round decryption function,it will be same as encryption

printf("decrypted is \n");
    for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                printf("%x ", newmat[j][i]);
            }
            
        }
      

  
    





}
