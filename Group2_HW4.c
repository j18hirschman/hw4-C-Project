/*                                                            */
/*  This program reads BikeTrip information from a data      */
/*  file into an array and then prints the array              */

#include <stdio.h>
#define FILE_IN "bikeData5000.txt"
#define FILE_OUT "output.txt"

//  Define structure to represent a BikeTrip  
typedef struct BikeTrip_struct{
   char membershipType[10];
   int startStationId, endStationId, bikeId,
       duration, startHr, startMin;
}BikeTrip;

//function declarations
void PrintBikeTrip(BikeTrip t, FILE *outFile);
void PrintArray(BikeTrip tripArray[], int arraySize, FILE *outfile);
void FindMaxDuration(BikeTrip arrayIn[], int arraySize, FILE* outFile);
int TripsInHr(BikeTrip arrayIn[], int arraySize, int hour);
//Following three function declarations for question 7-Jack
int FindTripsStartStationId(const BikeTrip arrayIn[], int arraySize, int station);
int FindTripsEndStationId(const BikeTrip arrayIn[], int arraySize, int station);
int TripsInStationPair(const BikeTrip arrayIn[], int arraySize, int startStation, int endStation);

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

   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   //Testing portion for question 7-Jack
   fprintf(outputFileStream, "%d trips started at your selected station.\n" , FindTripsStartStationId(tripArray, 5010, 31263));
   fprintf(outputFileStream, "%d trips ended at your selected station.\n" , FindTripsEndStationId(tripArray, 5010, 31101));
   fprintf(outputFileStream, "%d trips between your selected station pair.\n" , TripsInStationPair(tripArray, 5010, 31200, 31201));
   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   
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

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
/*  These functions answer question 7-Jack           */
//First function finds number of trips started from a station
int FindTripsStartStationId(const BikeTrip arrayIn[], int arraySize, int station) {
	int i = 0;
	int numTrips = 0;
	for (i = 0; i < arraySize; i++) {
		if (arrayIn[i].startStationId == station) {
			numTrips++;
		}
	}
	return numTrips;
}
//This function finds number of trips ended at a station
int FindTripsEndStationId(const BikeTrip arrayIn[], int arraySize, int station) {
	int i = 0;
	int numTrips = 0;
	for (i = 0; i < arraySize; i++) {
		if (arrayIn[i].endStationId == station) {
			numTrips++;
		}
	}
	return numTrips;
}
//This function finds number of trips started and ended between a pair of stations
int TripsInStationPair(const BikeTrip arrayIn[], int arraySize, int startStation, int endStation) {
	int i = 0;
	int numTrips = 0;
	for (i = 0; i < arraySize; i++) {
		if ((arrayIn[i].startStationId == startStation) && (arrayIn[i].endStationId == endStation)) {
			numTrips++;
		}
	}
	return numTrips;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
