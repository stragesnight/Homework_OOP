// englplus.cpp
// overloaded '+' operator adds two Distances
// overloaded '-' operator subtracts two Distances
// modified by Shelest Oleksandr to add overloaded '-' operator.
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////
class Distance                    //English Distance class
   {
   private:
      int feet;
      float inches;
   public:                        //constructor (no args)
      Distance() : feet(0), inches(0.0)
         {  }                     //constructor (two args)
      Distance(int ft, float in) : feet(ft), inches(in) 
         {  }
      void getdist()              //get length from user
         {
         cout << "\nEnter feet: ";  cin >> feet;
         cout << "Enter inches: ";  cin >> inches;
         }
      void showdist() const       //display distance
         { cout << feet << "\'-" << inches << '\"'; }

      Distance operator+(Distance) const;  	//add 2 distances
	  Distance operator-(Distance) const; 	//subtract two distances 
   };
//--------------------------------------------------------------
                                  //add this distance to d2
Distance Distance::operator+(Distance d2) const 	//return sum
   {
   int f = feet + d2.feet;        //add the feet
   float i = inches + d2.inches;  //add the inches
   if(i >= 12.0)                  //if total exceeds 12.0,
      {                           //then decrease inches
      i -= 12.0;                  //by 12.0 and
      f++;                        //increase feet by 1
      }                           //return a temporary Distance
   return Distance(f,i);          //initialized to sum
   }
Distance Distance::operator-(Distance d2) const		// return result of subtraction
   {
   int f = feet - d2.feet; 		  //subtract the feet
   float i = inches - d2.inches;  //subtract the inches
   if (i < 0) 					  //if total is less than 0,
      { 						  //then increase inches
	  i += 12.0; 				  //by 12 and  
	  f--; 						  //decrease feet by 1
	  } 					      //return a temporary Distance
   return Distance(f,i); 		  // initialized to result of subtraction
   }
////////////////////////////////////////////////////////////////
int main()
   {
   cout << "Overloaded '+' and '-' operators.";  cout << endl;
   cout << "Subtraction operator '-' is added by ";
   cout << "Shelest Oleksandr for Homework №11.";
   Distance dist1, dist3, dist4;   //define distances
   dist1.getdist();                //get dist1 from user

   Distance dist2(11, 6.25);       //define, initialize dist2

   dist3 = dist1 + dist2;          //single '+' operator

   dist4 = dist1 + dist2 + dist3;  //multiple '+' operators
                                   //display all lengths
   cout << "dist1 = ";  dist1.showdist(); cout << endl;
   cout << "dist2 = ";  dist2.showdist(); cout << endl;
   cout << "dist3 = ";  dist3.showdist(); cout << endl;
   cout << "dist4 = ";  dist4.showdist(); cout << endl;

   Distance dist5, dist6; 		   //define distances
   dist5 = dist3 - dist2; 		   //single '-' operators
   dist6 = dist4 - dist2 - dist1;  //multiple '-' operators
								   //display all new length
   cout << "subtraction."; cout << endl;
   cout << "dist5 (must equal dist1) = ";  dist5.showdist(); cout << endl;
   cout << "dist6 = ";  dist6.showdist(); cout << endl;

   cin.ignore(1, '\0'); 		   //pause the program
   cin.get(); 					   //then return 0
   return 0;
   }
