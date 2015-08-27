#include <fstream>
#include <iostream>
#include <string>
using namespace std;
 
int main ()
{
    
   char data[100];
   string str="helloworld!aslfjalejw12334567890";

   // open a file in write mode.
   ofstream outfile;
   outfile.open("afile.dat", ios::trunc);

   cout << "Writing to the file" << endl;
   cout << "Enter your name: "; 
   cin.getline(data, 100);

   // write inputted data into the file.
   outfile << data << endl;

   cout << "Enter your age: "; 
   cin >> data;
   cin.ignore();
   
   // again write inputted data into the file.
   outfile << data << endl;
   outfile << str << endl;   
   outfile << "123456p" << endl;

   // close the opened file.
   outfile.close();

   // open a file in read mode.
   ifstream infile; 
   infile.open("afile.dat"); 
   infile.seekg( 9 );
   cout << "Reading from the file" << endl; 
   infile >> data; 

   // write the data at the screen.
   cout << data << endl;
   
   // again read the data from the file and display it.
   infile >> data; 
   cout << data << endl; 

   infile >> data; 
   cout << data << endl; 
   infile.seekg(0,ios::beg);
   infile >> data; 
   cout << data << endl; 
   infile.seekg(-6,ios::end);
   infile >> data; 
   cout << data << endl; 
   // close the opened file.
   infile.close();

   return 0;
}
