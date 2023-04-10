#include <bits/stdc++.h>
//#include<ranges>

using namespace std;

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


string generateKey(int (&array)[64]){

  char key[65];

  random_device rd;
  uniform_int_distribution<int> dist(0, 127);

  //mt19937 gen(rd);
  mt19937 gen(time(nullptr));
  for(int i=0; i<64; i++){

    key[i]=dist(gen);
    array[i]= dist(gen);
  }
    key[64]='\0';

    return key;

}

int main(){

 string Rkey;
 int array[64];
 int a,b,c,d;

 //Generating Key
Rkey = generateKey(array);

 for(int i=0; i<63; i++)
  {
    cout<<Rkey[i]<<" ";

  }

cout<<"\n\nPrinting the vectors: \n\n";

c=0;
for(auto i=MatrixIndex.begin(); i!=MatrixIndex.end(); i++){
  cout<<i->first<<" "<<i->second<<" --";
  c++;
  if(c%8==0)
    cout<<endl;

}

vector<pair<int,int>> abc(MatrixIndex);

cout<<"\n\nPrinting the copied vectors: \n\n";

for(auto i=abc.begin(); i!=abc.end(); i++){
  cout<<i->first<<" "<<i->second<<" --";
  c++;
  if(c%8==0)
    cout<<endl;

}

//Shuffling the function
  uniform_int_distribution<int> dist(0, 127);
  //mt19937 gen(rd);
  mt19937 gen(time(nullptr));

  shuffle(abc.begin(),abc.end(),gen);

  cout<<"\n\nPrinting the Shuffled values: \n\n";

  for(auto i=abc.begin(); i!=abc.end(); i++){
    cout<<i->first<<" "<<i->second<<" --";
    c++;
    if(c%8==0)
      cout<<endl;

  }


  int ShuffleKey[128];

  for(auto i=0; i<64; i++){
    ShuffleKey[2*i]= abc[i].first;
    ShuffleKey[2*i+1]= abc[i].second;
  }

cout<<"\n\n";
  for(int i=0; i<128; i++){
    cout<<ShuffleKey[i]<<" ";

    c++;
    if(c%8==0)
      cout<<endl;
  }



int array2D[8][8];

c=0;
for(int i=0; i<8;i++)
  for(int j=0; j<8;j++)
    {
      array2D[i][j]=c;
      c++;
    }
cout<<"TESTING ARRAY: BEFORE SHUFFLING\n\n";
    for(int i=0; i<8;i++){
      for(int j=0; j<8;j++)
        {
          cout << array2D[i][j] <<" ";
        }
          cout<<"\n";
        }

cout<<"TESTING ARRAY AFTER SHUFFLING:\n\n";

  for(int i=0; i<32; i++){
    a=ShuffleKey[4*i];
    b=ShuffleKey[4*i+1];
    c=ShuffleKey[4*i+2];
    d=ShuffleKey [4*i+3];

    cout <<"("<<a<<","<<b<<")"<<setw(2)<<"("<<c<<","<<d<<")";
    swap(array2D[a][b] , array2D[c][d]);
  }

cout<<"TESTING AFTER SHUFFLING THE ARRAY USING THE SHUFFLED KEY\n"<<endl;
  for(int i=0; i<8;i++){
    for(int j=0; j<8;j++)
      {
        cout << array2D[i][j]<<" ";
      }
        cout<<"\n";
      }

string abcd ="ffffffc4";

char value1 = stoul(abcd , 0 , 16);

cout<<"\nValue "<<abcd<<" = "<<value1;
  return 0;

}
