#include <bits/stdc++.h>

using namespace std;

#define Matrix_Side 8

vector<pair<int, int> > MatrixIndex =
    {
      {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7},

      {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},

      {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7},

      {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7},

      {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7},

      {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7},

      {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7},

      {7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7},

    };

//Function for generating 64 byte key.
string generateKey(){

    char key[129];

    //random_device rd; mt19937 gen(rd);

    uniform_int_distribution<int> dist(-128, 127);
    mt19937 gen(time(nullptr));

    for(int i=0; i<64; i++)
        key[i]=dist(gen);

    key[128]='\0';

    return key;

    }


//Function to convert integer value to a hexadecimal string of size 2
template< typename T >
string int_to_hex( T i )
{
  stringstream stream;
  stream << setfill ('0') << setw(8) << hex << i;
  return stream.str();
}



void encrypt_Matrix( char array_in[8][8],string &outString,string key,int ShuffleKey[])
{


  int count;
  string concat;
  int asciiVal;
  char eChar;
  int a,b,c,d;
  count=0;

//Encrypting the block using the first 64 bytes of the key.
  for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){


          cout<<array_in[i][j]<<setw(2)<<"="<<static_cast<int>(array_in[i][j]);

          eChar = array_in[i][j] ^ key[count];
          array_in[i][j] = eChar;

          asciiVal = static_cast<int>(array_in[i][j]);

          cout<<setfill(' ')<<internal<<setw(4)<<"->"<<array_in[i][j]<<setw(4)<<":"<<static_cast<int>(array_in[i][j])<<setw(2)<<":"<<int_to_hex(asciiVal)<<endl;

          count++;
        }
      }



//Shuffling of the matrix using the key generated via shuffling the vector pair.
  for(int i=0; i<32; i++){
    a=ShuffleKey[4*i];
    b=ShuffleKey[4*i+1];
    c=ShuffleKey[4*i+2];
    d=ShuffleKey [4*i+3];

    swap(array_in[a][b] , array_in[c][d]);
  }





//Concatinating each block of encrypted string to the Output string.
  count = 0;
  for(int i=0; i<8; i++){

    for(int j=0; j<8; j++){

      asciiVal = static_cast<int>(array_in[i][j]);

      concat = int_to_hex(asciiVal);
      outString = outString + concat;

      count++;
   }
  }



}

string enc_Mcypher(string in_string,string &key ,int ShuffleKey[])
{
  //random_device rd;
  //mt19937 gen(rd);

  uniform_int_distribution<int> dist(0, 127);
  mt19937 gen(time(nullptr));

  key = generateKey();
//  int ShuffleKey[];




  char enc_matrix[8][8];
  int i,stringlen,dividend,remainder;
  int count=0;
  string Output="";

  stringlen=in_string.length();

  dividend = stringlen/64;
  remainder= stringlen%64;

  if(dividend != 0){

    for(i=0; i<dividend; i++){
          count=0;
          for(int j=0; j<8; j++){

              for(int k=0; k<8; k++){
                    enc_matrix[j][k]= in_string[count + 64*i];
                    count++;
                  }//end of for

                }//end of for

/*After 64 elements have been entered ,do the encryption  and store it in some string (to concatenate later) or write to a file.*/

            encrypt_Matrix(enc_matrix,Output,key,ShuffleKey);
          }//end of for

      }//end of if

  if(remainder != 0){


  if(dividend == 0){
      i=0;}


  count=64*dividend;

  for(int h=0; h<8; h++){

    for(int j=0; j<8; j++){

        if(remainder == count - 64*i)
            enc_matrix[h][j] = '\0'; //To indicate string termination.

        else if(count - 64*i> remainder)
            enc_matrix[h][j] = dist(gen);  //padding the remaining indexes with zeros to fill the matrix.

        else
            enc_matrix[h][j]=in_string[count];

        count++;

        }//end of for

    }//end of for

/*After 64 elements have been entered ,do the encryption  and store it in some string (to concatenate later) or write to a file.*/

    encrypt_Matrix(enc_matrix,Output,key,ShuffleKey);
}//end of if

return Output;
}//end of function




void decrypt_Matrix(char (&array_in)[8][8],string &outString, string key,int ShuffleKey[])
{

  int count;
  int asciiVal;
  int a,b,c,d,e,f,g,h;

  char output_slice[65];

    //Shuffling of the matrix using the key generated via shuffling the vector pair.
      for(int i=0; i<32; i++){
        a=4*i;
        b=4*i+1;
        c=4*i+2;
        d=4*i+3;

        e=ShuffleKey[a];f=ShuffleKey[b];g=ShuffleKey[c];h=ShuffleKey[d];
        swap(array_in[e][f] , array_in[g][h]);
      }

    count=0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){

            array_in[i][j] = array_in[i][j] ^ key[count];
            output_slice[count]=array_in[i][j];
            count++;

          }
        }

  output_slice[65]='\0';
  string conCat;
  conCat=output_slice;
  outString=outString+conCat;


}





//Decryption
string denc_Mcypher(string in_string,string key,int ShuffleKey[])
{

  char denc_matrix[8][8];
  int i,stringlen,dividend,remainder;
  int count=0;
  int number;

  string Output="";
  string inHex;
  char temp[] = { ' ' , ' ' , ' ' , ' ' ,' ' , ' ' , ' ' , ' ' , '\0'};

  stringlen=in_string.length();
  dividend = stringlen/512;
  remainder= stringlen%512;

  //cout<<"\n\nTEST denc_Mcypher"<<endl;
  if(dividend != 0){
    int overflow=0;

    for(i=0; i<dividend; i++){
        count=0;
        for(int j=0; j<8; j++){

            for(int k=0; k<8; k++){

                temp[0]=in_string[count*8 + 512*i];
                temp[1]=in_string[count*8 + 512*i + 1];
                temp[2]=in_string[count*8 + 512*i + 2];
                temp[3]=in_string[count*8 + 512*i + 3];
                temp[4]=in_string[count*8 + 512*i + 4];
                temp[5]=in_string[count*8 + 512*i + 5];
                temp[6]=in_string[count*8 + 512*i + 6];
                temp[7]=in_string[count*8 + 512*i + 7];

                inHex = temp;

                //cout<<"\nString="<<inHex;
                if(overflow < stringlen/8)
                  {denc_matrix[j][k]= stoul(inHex , 0 , 16);
                  //cout<<"String Test succeeded.";
                }

                count++;
                overflow++;
                }//end of for
            }//end of for

/*After 64 elements have been entered , do the decryption and store it in some string (to concatenate later) or write to a file.*/

            decrypt_Matrix(denc_matrix,Output,key,ShuffleKey);
    }//end of for

}//end of if

return Output;
}


int main()
{

  uniform_int_distribution<int> dist(0, 127);
  mt19937 gen(time(nullptr));

  string s1,s2,s3,inKey;
    int ShuffleKey[128];
  //CLI input.
  cout<<"Enter a string to encrypt."<<endl;
  getline(cin,s1);
  //cout<<"Entered string length is : "<<s1.length()<<endl;

//Shufling the vector pairs.
  vector<pair<int,int>> MatrixKey(MatrixIndex);
  shuffle(MatrixKey.begin(),MatrixKey.end(),gen);

//Storing the shuffling order in an integer array as an key.
  for(auto i=0; i<64; i++){
    ShuffleKey[2*i]= MatrixKey[i].first;
    ShuffleKey[2*i+1]= MatrixKey[i].second;
  }
    inKey=generateKey();
  s2=enc_Mcypher(s1,inKey,ShuffleKey);

  cout<<"\n\nThe encrypted string is:"<<endl;
  cout<<s2<<endl;


  s3=denc_Mcypher(s2,inKey,ShuffleKey);

  cout<<"Entered encrypted string length is : "<<s2.length()<<endl;
  cout<<"\n\nThe decrypted string is:"<<endl;
  cout<<s3<<endl;

  return 0;

}
