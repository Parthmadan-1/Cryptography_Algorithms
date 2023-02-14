#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int substitution[16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};   //to find what to substitute corresponding to each 4 bit
int per[16]={0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};  // permutation array to see swapping of bits position 
int inverse[16]={14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5}; //inverse of substitution box
unsigned int round_key(unsigned int key, int iteration) // this function gives round key corresponding to each round
{ // each round key is 16 bits long
    int start= ( (4* iteration)-4);
    unsigned res=0;
    for(int i= start;i< start+16;i++)
    {
        if((key >> i)& 1) res+= (1<< (i- start ));
    }
    return res;
}
unsigned int xorr( unsigned int x, unsigned int y )  // this function gives us xor of two unsigned numbers
{   unsigned int result=0;
    for( int i=0;i<16;i++)
    {
        int temp = (( (x>>i) & 1) ^ ((y>>i)& 1));
        if(temp == 1) result+= (1<<i);
    }
    return result;
}
int main()
{
    unsigned int plaintext, key;  
    printf("enter plain text(16 bits)(max: 65535, min:0):\n");
    scanf("%u", &plaintext); // taking plain text as input from user
    printf("entered plain text: %u \n", plaintext);
    printf("enter key (32 bits)(max:4294967295, min:0):\n");
    scanf("%u", &key);  // taking key from user as input
    printf("entered key: %u \n", key);
    for(int round=1;round<6;round++)
    {
       printf("key generated round %d : %u \n",round, round_key(key, round));  // printing round keys corresponding to each round
    }
    unsigned text= plaintext;
    for( int round=1;round<4;round++) // performing xor, substitution, permutation for first 3 rounds
    {
        bool check[16]={false, false, false,false, false, false,false, false, false,false, false, false,false, false, false, false}; /// used this array to check if the bit is already swapped or not

        unsigned after_xor= xorr(text,round_key(key, round));  //xor
        unsigned after_sub=0;
        for(int i=0;i<4;i++) //substitution
        {
            unsigned temp=0;
            for(int j=  4*i; j< ((4*i)+4);j++)
            {
                if( (after_xor >> j)& 1) temp+=( 1<< (j- (4*i)));
            }
            unsigned temp2= ( substitution[temp]);
            int y=0;
            for( int k= 4*i; k< (((4*i)+4));k++)
            {
               if( ((temp2 >> y)& 1) )  after_sub+= ( 1<<k);
               y++;
            }
        }


        unsigned after_per= 0;
        for( int i=0;i<16;i++)
        { //permutation
          if(check[i] == false)
          {
            int j= per[i];
            int bit1= ((after_sub >> i)& 1);
            int bit2= ((after_sub >> j)& 1);
            if(i!=j)
            {
            
            if(bit1) after_per+=( 1 << j);
            if(bit2) after_per+=(1 << i);
            check[j]= true;
            }
          else
          { 
            if( (after_sub >> i)& 1)
            after_per+=(1<<i);
          }
          }

        }
        text= after_per;
        printf("plain text after round %d encryption is %u  \n", round, text );

    }
    //round 4
    unsigned after_xor1= xorr(text,round_key(key, 4));
    unsigned after_sub1=0;
        for(int i=0;i<4;i++)
        {
            unsigned temp=0;
            for(int j=  4*i; j< ((4*i)+4);j++)
            {
                if( (after_xor1 >> j)& 1) temp+=( 1<< (j- (4*i)));
            }
            unsigned temp2= ( substitution[temp]);
            int y=0;
            for( int k= 4*i; k< (((4*i)+4));k++)
            {
               if( ((temp2 >> y)& 1) )  after_sub1+= ( 1<<k);
               y++;
            }
        }
    printf("plain text after round 4 encryption is %u   \n", after_sub1 );
    // round 5
    after_xor1= xorr(after_sub1,round_key(key, 5));
    printf("plain text after round 5 encryption is %u   \n", after_xor1 );

    // now performing decryption
   
   //round 5
   after_xor1= xorr(after_xor1, round_key(key,5));
   printf("text after round 5 decryption is : %u \n", after_xor1);

   //round4
    after_sub1=0;
        for(int i=0;i<4;i++)
        {
            unsigned temp=0;
            for(int j=  4*i; j< ((4*i)+4);j++)
            {
                if( (after_xor1 >> j)& 1) temp+=( 1<< (j- (4*i)));
            }
            unsigned temp2= ( inverse[temp]);
            int y=0;
            for( int k= 4*i; k< (((4*i)+4));k++)
            {
               if( ((temp2 >> y)&1) )  after_sub1+= ( 1<<k);
               y++;
            }
        }
    
    
    after_xor1= xorr(after_sub1, round_key(key,4));
    printf("text after round 4 decryption is : %u \n", after_xor1);

    // round 3,2,1
    unsigned final=after_xor1;
    for( int round=3;round>0;round--)
    {
        bool check[16]={false, false, false,false, false, false,false, false, false,false, false, false,false, false, false, false};
        
        unsigned after_per= 0;
        for( int i=0;i<16;i++)
        {
          if(check[i] == false)
          {
            
            int j= per[i];
            if(i!=j)
            {
            int bit1= ((final >> i)& 1);
            int bit2= ((final >> j)& 1);
            if(bit1) after_per+=( 1 << j);
            if(bit2) after_per+=(1<<i);
            check[j]= true;
          }
           else
          { if( (final >> i)& 1)
            after_per+=(1<<i);
          }
          }

        }
        unsigned after_sub=0;
            for(int i=0;i<4;i++)
        {
            unsigned temp=0;
            for(int j=  4*i; j< ((4*i)+4);j++)
            {
                if( (after_per >> j)& 1) temp+=( 1<< (j- (4*i)));
            }
            unsigned temp2= ( inverse[temp]);
            int y=0;
            for( int k= 4*i; k< (((4*i)+4));k++)
            {
               if( ((temp2 >> y)&1) )  after_sub+= ( 1<<k);
               y++;
            }
        }
        


        unsigned  after_xor= xorr(after_sub,round_key(key, round));

        final=after_xor;
        printf("text after round %d decryption is : %u \n", round, final);

    }
    return 0;
   
}
