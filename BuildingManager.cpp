///////////////////////////////////////////////////////////////////////////////
//
// Name: Arturo Diaz
// Assignment: Project 3/ Building Manager
// Date: May 24, 2017
// Due Date: May 26, 2017
// Input: Integers to represent the menu choices and letters to represent the 
//        office units entered by the user.
// Description: This program manages three rental buildings. The user is given
// 		menus to choose the property to update and options of type of
// 		update. Rent an office, vacate an office, or print out the
//              building's status or delinquents. When the user exits the 
//              program, the status of all three buildings is written to a
//  		text file.
//
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdlib>

// Declare namespace
using namespace std;

struct building
{
   string name;
};

/* Main method
 * This method takes input from the user and applies all requests
 * to the different properties.
 *
 */
int main()
{
 
   //Declare variables
   const int HEIGHT = 10;
   const int WIDTH = 4;
   int buildingNum;
   int option;
   bool options = true;
   bool contin = true;
   int floorToRent;
   char unitToRent;
   int floorToVacate;
   char unitToVacate;
   string action;
   bool invalidFloor = true;
   bool invalidUnit = true;
   ofstream outstream;
   
   //Function prototypes declarations
   void printBuilding(int [HEIGHT][WIDTH],string name);
   void chooseBuild();
   void chooseOptions(string);
   void rentables(int [HEIGHT][WIDTH],string);
   void rentOffice(string,int [HEIGHT][WIDTH], int, char);
   void getFloor(string);
   void getUnit(string);
   void seeDelq(int [HEIGHT][WIDTH],string);
   void vacateables(int [HEIGHT][WIDTH], string);
   void vacateOffice(string, int [HEIGHT][WIDTH], int, char);
   void floorError();
   bool validUnit(char);

   //Building Arrays
   int EdmondsArray [10][4] = {2,1,1,1, 1,1,0,1, 0,1,1,0, 2,2,0,1, 1,1,1,1,
 			       0,1,1,1, 0,2,0,1, 1,2,1,0, 0,1,0,1, 1,1,1,1};
   int BellvueArray [10][4] = {1,1,1,1, 0,1,0,1, 1,2,1,0, 0,2,0,1, 0,1,1,1,
			       1,1,1,1, 2,2,0,1, 0,1,1,0, 1,1,0,1, 2,1,1,1};
   int BellinghamArray [10][4] = {1,1,1,1, 2,2,0,1, 0,1,1,0, 1,1,0,1, 2,1,1,1,	
				  1,1,1,1, 0,1,0,1, 1,2,1,0, 0,2,0,1, 0,1,1,1};
   //Building structs
   building Edmonds;
   Edmonds.name = "Edmonds Park"; 
   building Bellvue;
   Bellvue.name = "Bellvue Heights";
   building Bellingham;
   Bellingham.name = "Bellingham Towers";

   //While loop from beginning
   while(contin == true)
   {
      options = true;
      chooseBuild();		//Choose Building
      cin >> buildingNum;
      while(!cin)		//Validate input is an integer
      {
         cout << " Input Error. Please enter a number." << endl;
	 cin.clear();
	 cin.ignore();
 	 chooseBuild();
	 cin >> buildingNum;
      }
      if(buildingNum >=1 && buildingNum <= 4)  //Validate correct menu choice
      {
         while(options == true)
         {
            switch(buildingNum) 	//Building chosen
            {
               case 1:			
                    chooseOptions(Edmonds.name);
                    contin = true;
                    break;
               case 2:				
                    chooseOptions(Bellvue.name);
                    contin = true;
                    break;
               case 3:				
                    chooseOptions(Bellingham.name);
   	            contin = true;
              	    break;
               case 4:				//Exit the program
                    cout << " Have a nice day." << endl;
                    contin = false;
	            options = false;
                    outstream.open("Tomptom.txt");
                    //Print the buildings to the text file
		    outstream << Edmonds.name << endl;
                    for(int i = 0; i < 10; i ++)
                    {
                       for(int j = 0; j < 4; j++)
                       { 
                          outstream << EdmondsArray [i][j] << " " ;
                       }
                          outstream << endl;   
                    }
                    outstream << Bellvue.name << endl;
		    for(int i = 0; i < 10; i ++)
                    {
                       for(int j = 0; j < 4; j++)
                       { 
                          outstream << BellvueArray [i][j] << " " ;
                       }
                          outstream << endl;   
                    }
		    outstream << Bellingham.name << endl;
		    for(int i = 0; i < 10; i ++)
                    {
                       for(int j = 0; j < 4; j++)
                       { 
                          outstream << BellinghamArray [i][j] << " " ;
                       }
                          outstream << endl;   
                    }
		   
 		  
		    outstream.close();
            }
            if(contin == true) 	//Continue to options
            {
               cin >> option;
               while(!cin)	//Validate input is an integer
               {
	          cout << " Input Error. Please enter a number." << endl;
 	          cin.clear();
	          cin.ignore();
 	          cin >> option;
	       }
	       if(option >= 1 && option <= 5)	//Validate correct menu choice
	       {
                  switch(option) 	//Option chosen
                  {
                     case 1:
                          //Rent an office
		          action = "rent";
                          if(buildingNum == 1) //Edmonds
		          {
		             rentables(EdmondsArray, Edmonds.name);
		             while(invalidFloor)
		             {
		                getFloor(action);
	  	                cin >> floorToRent;
                                while(!cin)	//Validate floor input
                    	        {
	                           cout << " Input Error. Please enter a number." << endl;
 	          		   cin.clear();
	          		   cin.ignore();
 	          		   cin >> floorToRent;
	       		        }
                                if(floorToRent <=10 && floorToRent >=1) //Validate floor range
		                {
		                   while(invalidUnit)
   		                   {
                          	      getUnit(action);
                                      cin >> unitToRent;
		          	      if(validUnit(unitToRent)) //Validate unit input
		                      {
		             		 rentOffice(Edmonds.name, EdmondsArray, floorToRent, unitToRent);
  		             		 printBuilding(EdmondsArray,Edmonds.name);
			     		 invalidFloor = false;
			     		 invalidUnit = false;
		                      }
		                   } 
		                }
		                else 	//Invalid floor input
		                {
			           floorError();
			           invalidFloor = true;
  	 	                }
		             }
		          }
                          else if (buildingNum == 2) //Bellvue
		          {
		             rentables(BellvueArray, Bellvue.name);
		             while(invalidFloor)
		             {
		                getFloor(action);
	  	                cin >> floorToRent;
			        while(!cin) 	//Validate floor input
                    	        {
	                           cout << " Input Error. Please enter a number." << endl;
 	          		   cin.clear();
	          		   cin.ignore();
 	          		   cin >> floorToRent;
	       		        }
                                if(floorToRent <=10 && floorToRent >=1) //Validate floor range
		                {
		                   while(invalidUnit)
   		                   {
                          	      getUnit(action);
                                      cin >> unitToRent;
		          	      if(validUnit(unitToRent)) //Validate unit input
		                      {
		             	         rentOffice(Bellvue.name, BellvueArray, floorToRent, unitToRent);
  		             	         printBuilding(BellvueArray, Bellvue.name);
			     		 invalidFloor = false;
			     		 invalidUnit = false;
		                      }
		                   } 
		                }
		                else 	//Invalid floor input
		                {
			           floorError();
			           invalidFloor = true;
  	 	                }
		             }//end while 
		          }
		          else if (buildingNum == 3) 	//Belliingham
		          {
		             rentables(BellinghamArray, Bellingham.name);
		             while(invalidFloor)
		             {
		                getFloor(action);
	  	                cin >> floorToRent;
		  	        while(!cin)	//Validate floor input
                    	        {
	                           cout << " Input Error. Please enter a number." << endl;
 	          		   cin.clear();
	          		   cin.ignore();
 	          		   cin >> floorToRent;
	       		        }
                                if(floorToRent <=10 && floorToRent >=1) //Validate floor range
		                {
		                   while(invalidUnit)
   		                   {
                                      getUnit(action);
                                      cin >> unitToRent;
		          	      if(validUnit(unitToRent)) //Validate unit input
		                      {
		             		 rentOffice(Bellingham.name, BellinghamArray, floorToRent, unitToRent);
  		             	         printBuilding(BellinghamArray, Bellingham.name);
			     		 invalidFloor = false;
			     		 invalidUnit = false;
		                      }
		                   }  
		                }
		                else 	//Invalid floor input
		                {
			           floorError();
			           invalidFloor = true;
  	 	                }
		             }//end while 
		          }
                          break;
                     case 2:
                          //Vacate an office
		          action = "vacate";
                          if(buildingNum == 1) //Edmonds
		          {
		             vacateables(EdmondsArray, Edmonds.name);
                             while(invalidFloor)
			     {
		                getFloor(action);
	 	                cin >> floorToVacate;
			        while(!cin) //Validate floor input
                    	        {
	                           cout << " Input Error. Please enter a number." << endl;
 	          		   cin.clear();
	          		   cin.ignore();
 	          		   cin >> floorToVacate;
	       		        }
			        if(floorToVacate <= 10 && floorToVacate >= 1) //Validate floor range
 			        {
			           while(invalidUnit)
			           {
		                      getUnit(action);
		                      cin >> unitToVacate;
			              if(validUnit(unitToVacate)) //Validate unit input
			              {
		                         vacateOffice(Edmonds.name, EdmondsArray, floorToVacate,unitToVacate);
		                         printBuilding(EdmondsArray, Edmonds.name);
 				         invalidFloor = false;
				         invalidUnit = false;	
			              }
  			           }
			        }
			        else 	//Invalid floor input
			        {
			           floorError();
				   invalidFloor = true;
			        }
			     }
         	          }
                          else if (buildingNum == 2) //Bellvue
		          {
		             vacateables(BellvueArray, Bellvue.name);
                             while(invalidFloor)
			     {
		                getFloor(action);
	 	                cin >> floorToVacate;
			        while(!cin) //Validate floor input
                    	        {
	                           cout << " Input Error. Please enter a number." << endl;
 	          		   cin.clear();
	          		   cin.ignore();
 	          		   cin >> floorToVacate;
	       		        }
			        if(floorToVacate <= 10 && floorToVacate >= 1) //Validate floor range
 			        {
			           while(invalidUnit)
			           {
		                      getUnit(action);
		                      cin >> unitToVacate;
			              if(validUnit(unitToVacate)) //Validate unit input
			              {
		                         vacateOffice(Bellvue.name, BellvueArray, floorToVacate,unitToVacate);
		                         printBuilding(BellvueArray, Bellvue.name);
 				         invalidFloor = false;
				         invalidUnit = false;	
			              }
  			           }
			        }
			        else 	//Invalid floor input
			        {
			           floorError();
				   invalidFloor = true;
			        }
			     } 
		          }
                          else if (buildingNum == 3) //Bellingham
  		          {
		             vacateables(BellinghamArray, Bellingham.name);
                             while(invalidFloor)
			     {
		                getFloor(action);
	 	                cin >> floorToVacate;
			        while(!cin) 	//Validate floor input
                    	        {
	                           cout << " Input Error. Please enter a number." << endl;
 	          		   cin.clear();
	          		   cin.ignore();
 	          		   cin >> floorToVacate;
	       		        }
			        if(floorToVacate <= 10 && floorToVacate >= 1) //Validate floor range
 			        {
			           while(invalidUnit)
			           {
		                      getUnit(action);
		                      cin >> unitToVacate;
			              if(validUnit(unitToVacate)) //Validate unit input
			              {
		                         vacateOffice(Bellingham.name, BellinghamArray, floorToVacate,unitToVacate);
		                         printBuilding(BellinghamArray, Bellingham.name);
 				         invalidFloor = false;
				         invalidUnit = false;	
			              }
  			           }
			        }
			        else 	//Invalid floor input
			        {
			           floorError();
				   invalidFloor = true;
			        }
			     }
 		          }
                          break;
                     case 3:
                         //See delinquent list
                         if(buildingNum == 1)
                            seeDelq(EdmondsArray,Edmonds.name);
                         if(buildingNum == 2)
                            seeDelq(BellvueArray, Bellvue.name);
                         if( buildingNum == 3)
                            seeDelq(BellinghamArray, Bellingham.name);
                         break;
                     case 4:
                          //Print building
                          if(buildingNum == 1)
                             printBuilding(EdmondsArray,Edmonds.name);
		          if(buildingNum == 2)
                             printBuilding(BellvueArray, Bellvue.name);
                          if(buildingNum == 3)
                             printBuilding(BellinghamArray, Bellingham.name);
                          break;
                     case 5:
                          // quit
                          options = false;
                          break;
                  }//end switch
	          invalidUnit = true;
	          invalidFloor = true;
	       }
	       else
	       {
	          cout << " Input error. Please enter a number from the options." << endl;
 	       }
            }//end if
         }//end options
      }
      else
      {
	 cout << "Input error. Please enter a number from the options." << endl;
      }
   }//end while(cont)
}//end Main


/* printBuilding function
 * @ params  int [][]
 * @ return  void
 * This function prints the building array passed in
 */
void printBuilding( int pb [10][4], string name)
{
   cout << name << endl;
   for(int i = 0; i < 10; i ++)
   {
      for(int j = 0; j < 4; j++)
      { 
        cout << " " << pb [i][j];
      }
      cout << endl;   
   }
}

/* chooseBuild function
 * This function prints the menu of buildings to choose from
 */
void chooseBuild()
{
   cout << " Please choose from the menu below: " << endl;
   cout << " 1. Edmonds Park" << endl;
   cout << " 2. Bellvue Heights" << endl;
   cout << " 3. Bellingham Towers" << endl;
   cout << " 4. Exit program" << endl;
}

/* chooseOption function
 * @params   string name
 * @return   void
 * This function prints the menu of the options to choose from
 */
void chooseOptions(string name)
{
   cout << " Please choose one of the options for " << name << "." << endl;
   cout << " 1. Rent an office" << endl;
   cout << " 2. Vacate an office" << endl;
   cout << " 3. See a list of delinquent tenants" << endl;
   cout << " 4. Print entire building status" << endl;
   cout << " 5. Quit" << endl;
}

/* rentOffice function
 * @params   int[][] vcants,  string name
 * @return   void
 * This function prints the units that are available to rent
 */
void rentables(int vacants[10][4], string name)
{ 
   int floor = 10;
   cout << " The offices available to rent at " << name << " are: " << endl;
   for (int i = 0; i < 10;i++)
   {
      for( int j = 0; j < 4;j++)
      { 
         if(vacants[i][j] == 0 || vacants[i][j] == 2)
         {
            if (j == 0)
	    {
               cout << " " << floor << "A " ;
            }
            else if( j == 1)
            {
		cout << " " << floor << "B " ;
            }
            else if(j == 2)
            {
		cout << " " << floor << "C " ;
            }
            else
            {
		cout << floor << "D " ;
            }
         }
      }
      floor--;
   }
   cout << endl;
}

/* getFloor function
 * @ params string
 * @ return void
 * This function asks the user for the floor of the office to rent
 */
void getFloor(string action)
{
   cout << " What is the floor number of the office you would like to " << action << "?" << endl;
}

/* getUnit function
 * @ params string
 * @ return void
 * This function asks the user for the letter of the office to rent 
 */
void getUnit(string action)
{
   cout << " What is the letter of the office that you would like to " << action << "?" << endl;
}

/* rentOffice function
 * @ params  string, int [][], int, char
 * @ return  void
 * This function validates that the office is rentable and rents it if true
 */
void rentOffice(string name, int rentOut[10][4],int floor, char unit)
{
   int iVal;
   int jVal;
   iVal = 10 - floor;
   if(unit == 'A')
   {
      jVal = 0;
   }
   if(unit == 'B')
   {
      jVal = 1;
   }
   if(unit == 'C')
   {
      jVal = 2;
   }
   if(unit == 'D')
   {
      jVal = 3;
   }
   if(rentOut[iVal][jVal] == 1)
   {
      cout << " Sorry, " << floor << unit << " is occupied and in good standing." << endl;
   }
   else
   {
      rentOut[iVal][jVal] = 1;
      cout << " Office " << floor << unit << " at " << name << " has been rented." << endl;
   }
}

/* seeDelq function
 * @ params  int [][], string
 * @ return  void
 * This function searches and prints the delinquent offices of the given array
 */
void seeDelq(int delqs[10][4], string name)
{
   cout << " The delinquent offices at " << name << " are: " << endl;
   int floor = 10;
   for(int i = 0; i < 10; i++)
   {
      for(int j = 0; j < 4; j++)
      {
         if(delqs[i][j] == 2)
         {
	    if (j == 0)
            {
               cout << " " << floor << "A ";
            }
            else if( j == 1)
            {
	       cout << " " << floor << "B ";
	    }
            else if(j == 2)
            {
	       cout << " " << floor << "C ";
            }
            else
            {
	       cout << floor << "D ";
            }
         }
      }
      floor--;
   }
   cout << endl;
}

/* vacateables function
 * @ params  int [][], string
 * @ return  void
 * This function displays the units that are available to vacate in the given array
 */
void vacateables(int occsAndDelqs [10][4], string name)
{
   int floor = 10;
   cout << " The offices available to vacate at " << name << " are: " << endl;
   for (int i = 0; i < 10;i++)
   {
      for( int j = 0; j < 4;j++)
      { 
         if(occsAndDelqs[i][j] == 1 || occsAndDelqs[i][j] == 2)
         {
            if (j == 0)
	    {
               cout << " " << floor << "A " ;
            }
            else if( j == 1)
            {
		cout << " " << floor << "B " ;
            }
            else if(j == 2)
            {
		cout << " " << floor << "C " ;
            }
            else
            {
		cout << floor << "D " ;
            }
         }
      }
      floor--;
   }
   cout << endl;
}

/* vacateOffice function
 * @ params  string, int [][], int, char
 * @ return  void
 * This function verifies that an office is vacant and vacates it if true
 */
void vacateOffice(string name, int vacates [10][4], int floor, char unit)
{
   int iVal;
   int jVal;
   iVal = 10 - floor;
   if(unit == 'A')
   {
      jVal = 0;
   }
   if(unit == 'B')
   {
      jVal = 1;
   }
   if(unit == 'C')
   {
      jVal = 2;
   }
   if(unit == 'D')
   {
      jVal = 3;
   }
   if(vacates[iVal][jVal] == 0)
   {
      cout << " Sorry, " << floor << unit << " is already vacant." << endl;
   }
   else
   {
      vacates[iVal][jVal] = 0;
      cout << " Office " << floor << unit << " at " << name << " has been vacated." << endl;
   }
}

/* floorError function
 * This function displays an error message for incorrect floor range
 *
 */
void floorError()
{
   cout << " Input Error. Floor must be beween 1 and 10." << endl;
}

/* validUnit function
 * @ params  char
 * @ return  bool
 * This function validate the unit letter entered 
 */
bool validUnit(char in)
{
   if(in=='A' || in == 'B' || in == 'C' || in == 'D')
   {
      return true;
   }
   else
   {
      cout << " Unit letter must be A, B, C, or D" << endl;
	return false;
   }

}

