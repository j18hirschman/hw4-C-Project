//Arian Modarres
//G47029066
/*                                                            */
/*  This program reads BikeTrip information from a data      */
/*  file into an array and then prints the array              */

#include <stdio.h>
#define FILE_IN "bikeData5000.txt"
#define FILE_OUT "output.txt"

//  Define the structure to represent a BikeTrip  
typedef struct BikeTrip_struct{
   char membershipType[10];
   int startStationId, endStationId, bikeId,
       duration, startHr, startMin;
}BikeTrip;

//our function declarations
void PrintBikeTrip(BikeTrip t, FILE *outFile);
void PrintArray(BikeTrip tripArray[], int arraySize, FILE *outfile);
void FindMaxDuration(BikeTrip arrayIn[], int arraySize, FILE* outFile);
int TripsInHr(BikeTrip arrayIn[], int arraySize, int hour);
double FindAverageTripDuration(BikeTrip arrayIn[], int arraySize);

//main
int main(void)
{
   /*  Declare variables */
   int k=0, elements;
   BikeTrip tripArray[5010];

   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   // Students do not need to edit sections that 
   // create the input and output file streams
   FILE *inputFileStream, *outputFileStream;
   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   //  Open the input file stream to scan data into the array 
   inputFileStream = fopen(FILE_IN,"r");
   if (inputFileStream == NULL){
       printf("Error opening data file. \n");}
   else{
	  while (fscanf(inputFileStream, "%s %d %d %d %d %d %d",
		    tripArray[k].membershipType,&tripArray[k].startStationId,
			&tripArray[k].endStationId, &tripArray[k].bikeId, &tripArray[k].duration,
			&tripArray[k].startHr, &tripArray[k].startMin) == 7){k++;}
	  elements = k;
	}
   fclose(inputFileStream);
   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   //  Open the output file stream to write to output.txt        
   outputFileStream = fopen(FILE_OUT,"w");
   if (outputFileStream == NULL){
       printf("Error opening data file. \n");}
   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   
     fprintf(outputFileStream, "\n Calling FindMaxDuration( ) \n\n" );
     FindMaxDuration( tripArray, elements, outputFileStream);

	 int tripsInHr17 = TripsInHr( tripArray, elements, 17);
	 fprintf(outputFileStream, "\n tripsinHr17 = %d\n\n", tripsInHr17);

     fprintf(outputFileStream, "\n Print the whole array of BikeTrip structs\n\n" );
     PrintArray( tripArray, elements, outputFileStream );
     PrintBikeTrip( tripArray[3], outputFileStream );
	
	int i = 0;
	int highid = tripArray[0].bikeId;
	int hightrips = FindTripsBikeId(tripArray, elements, tripArray[0].bikeId);
	//go through the array of bike trips
	for (i = 0; i <	elements; i++) {
		//if the number of trips for the selected bikeid is higher than the max make it the max
		if (FindTripsBikeId(tripArray, elements, tripArray[i].bikeId) > hightrips) {
			highid = tripArray[i].bikeId;
			hightrips = FindTripsBikeId(tripArray, elements, tripArray[i].bikeId);
		}
	}
	//print the bikeid with the highest trips and the number of trips
	fprintf(outputFileStream, "\nBikeId with highest number of trips: %d", highid);
	fprintf(outputFileStream, "\nNumber of trips: %d", hightrips);

	//find the average duration
	double avgduration = FindAverageTripDuration(tripArray, elements);
	//print the average duration in ms and minutes
	fprintf(outputFileStream, "\nAverage duration in milliseconds: %lf", avgduration*1000*60);
	fprintf(outputFileStream, "\nAverage duration in minutes: %lf", avgduration);

   //At the end of main( ) close the output file stream
   fclose(outputFileStream);
   return 0;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function prints the longest trip
void FindMaxDuration(BikeTrip arrayIn[], int arraySize, FILE* outFile){
   int maxDuration = 0;
   int k;
   maxDuration = arrayIn[0].duration;
   for (k = 1; k < arraySize; k++ ){
      if( arrayIn[k].duration > maxDuration){
	     maxDuration = arrayIn[k].duration;
         PrintBikeTrip(arrayIn[k], outFile);
	  }
   }
   return;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of trips started for an hour
int TripsInHr(BikeTrip arrayIn[], int arraySize, int hour){
    int k;
    int count = 0;
       for (k = 0; k < arraySize; k++ ){
          if( arrayIn[k].startHr == hour ){
             count++;
          }
      }
   printf("count of trips started in hour %d: %d \n", hour, count);
   return count;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function prints the array
void PrintArray(BikeTrip tripArray[], int arraySize, FILE *outFile){
   fprintf(outFile,
           "bikeId membershipType startStationId endStationId startHr startMin duration(ms) minutes \n"); 
   int k;
   for (k = 0; k < arraySize; k++ ){
      PrintBikeTrip(tripArray[k], outFile);
   }
   return;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
/*  This function prints one BikeTrip struct           */

void PrintBikeTrip(BikeTrip t, FILE *outFile){

   fprintf(outFile, "%6d %11s %15d %12d %7d %8d %10d %6d\n",
            t.bikeId, t.membershipType,t.startStationId,t.endStationId, 
			t.startHr, t.startMin, t.duration, t.duration/1000/60);
   return;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

int FindTripsBikeId(BikeTrip arrayIn[], int arraySize, int bike) {
	int i;
	int count;
	//this will set the count of number of trips to zero
	count = 0;
	//this will go through the array of bike trips
	for (i = 0; i < arraySize; i++) {
		//if the id of the selected trip is the same as the given id, add one to count
		if (arrayIn[i].bikeId == bike) {
			count++;
		}
	}
	//returns our count
	return count;
}

double FindAverageTripDuration(BikeTrip arrayIn[], int arraySize) {
	int i;
	double sum;
	//this sets the sum to 0
	sum = 0;
	//this goes through the array for the bike trips
	for (i = 0; i < arraySize; i++) {
		//convert the duration of the selected trip to minutes and add it to sum
		sum = sum + (arrayIn[i].duration/1000/60);
	}
	//this part returns the average, sum divided by the number of trips
	return (double)sum / (double)arraySize;
}


