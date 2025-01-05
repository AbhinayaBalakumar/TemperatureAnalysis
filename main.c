// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define DATA_FILE "GlobalTemperatures.csv"
// #define NUM_MONTHS 12

// int main() {
//     FILE *file = fopen(DATA_FILE, "r");
//     if (file == NULL) {
//         fprintf(stderr, "Error opening file %s\n", DATA_FILE);
//         return 1;
//     }

//     // Skip the header line
//     char buffer[1024];
//     fgets(buffer, sizeof(buffer), file);

//     // Initialize variables to store yearly totals and counts
//     int year = 1750;
//     double yearly_total = 0.0;
//     int num_years = 0;
//     int min_year = 1750;
//     int max_year = 1750;
//     double cold = 8;
//     double hot = 8;
//     FILE *outputFile = fopen("plot.data", "w");
//         if (outputFile == NULL) {
//             fprintf(stderr, "Error creating plot file.\n");
//             return 1;
//         }
//     // Iterate through each line in the file
//     while (fgets(buffer, sizeof(buffer), file) != NULL) {
//         // Extract year and temperature from the line
//         char *token = strtok(buffer, ",");
//         int data_year = atoi(token);
//         token = strtok(NULL, ",");
//         double temperature = atof(token);

//         // Check if the current year matches the year we're calculating for
//          if(data_year >= 1760){
      
//         if (data_year == year) {
//             yearly_total += temperature;
//         } else {
//             // Calculate the yearly average and print it
//            if(year >= 1760){
//             double yearly_average = yearly_total / NUM_MONTHS;
//             fprintf(outputFile,"Year %d: %.2f\n", year, yearly_average);
//             // if(yearly_average < cold){
//             //   min_year = year;
//             //   cold = yearly_average;
//             // }
//             // else if(yearly_average > hot){
//             //   max_year = year;
//             //   hot = yearly_average;
//             // }
//             }
//             // Reset variables for the next year
//             year = data_year;
//             yearly_total = temperature;
//             num_years++;
//         }
//    }}
//   // Calculate and print the average for the last year
//   double last_year_average = yearly_total / NUM_MONTHS;
//   fprintf(outputFile, "Year %d: %.2f\n", year, last_year_average);

//   if(last_year_average < cold){
//     min_year = year;
//     cold = last_year_average;
//   }
//   else if(last_year_average > hot){
//     max_year = year;
//     hot = last_year_average;
//   }

//     // Print the number of years processed
//     // printf("Total years processed: %d\n", num_years);
//     printf("Hottest Year: %.2lf degrees in %d.\n", hot, max_year);
//     printf("Coldest Year: %.2lf degrees in %d.", cold, min_year);

//     fclose(file);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define NUM_CENTURIES 3

double averageTemperatures[NUM_CENTURIES] = {0};
double lowTemperatures[NUM_CENTURIES] = {0};
double highTemperatures[NUM_CENTURIES] = {0};
int YEARS_PER_CENTURY[NUM_CENTURIES] = {50,100,16};

void processTemperature(double a, double l, double h, double *average, double *low, double *high) {
    *average += a;
    *low += l;
    *high += h;
    
}

int getCenturyIndex(int year) {
     if (year >= 1850 && year <= 1899)
        return 0; // 19th century
    else if (year >= 1900 && year <= 1999)
        return 1; // 20th century
    else if (year >= 2000 && year <= 2015)
        return 2; // 21st century
    else
        return -1;
}

int main() {
    FILE *file = fopen("GlobalTemperatures.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file); // skip header

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        int year;
        double landAvgTemp, landMaxTemp, landMinTemp;
        sscanf(line, "%d-%*d-%*d,%lf,%*f,%lf,%*f,%lf,%*f", &year, &landAvgTemp, &landMaxTemp, &landMinTemp);

        int centuryIndex = getCenturyIndex(year);
        if (centuryIndex != -1) {
            processTemperature(landAvgTemp, landMaxTemp, landMinTemp, &averageTemperatures[centuryIndex], &lowTemperatures[centuryIndex], &highTemperatures[centuryIndex]);
        }
    }

    fclose(file);

    FILE *outputFile = fopen("plot.data", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error creating plot file.\n");
        return 1;
    }
  
    for (int i = 0; i < NUM_CENTURIES; i++) {
      
        fprintf(outputFile, "%d %.2f %.2f %.2f\n",(19+i), averageTemperatures[i] / (YEARS_PER_CENTURY[i]*12), lowTemperatures[i] / (YEARS_PER_CENTURY[i]*12), highTemperatures[i] / (YEARS_PER_CENTURY[i]*12));
    }

    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define DATA_FILE "GlobalTemperatures.csv"
// #define NUM_MONTHS 12

// int main() {
//     FILE *file = fopen(DATA_FILE, "r");
//     if (file == NULL) {
//         fprintf(stderr, "Error opening file %s\n", DATA_FILE);
//         return 1;
//     }

//     // Skip the header line
//     char buffer[1024];
//     fgets(buffer, sizeof(buffer), file);

//     // Initialize variables to store yearly totals and counts
//     int year = 1750;
//     double yearly_total = 0.0;
//     int num_years = 0;
//     int min_year = 1750;
//     int max_year = 1750;
//     double cold = 8;
//     double hot = 8;
//     FILE *outputFile = fopen("plot.data", "w");
//         if (outputFile == NULL) {
//             fprintf(stderr, "Error creating plot file.\n");
//             return 1;
//         }
//     // Iterate through each line in the file
//     while (fgets(buffer, sizeof(buffer), file) != NULL) {
//         // Extract year and temperature from the line
//         char *token = strtok(buffer, ",");
//         int data_year = atoi(token);
//         token = strtok(NULL, ",");
//         double temperature = atof(token);

//         // Check if the current year matches the year we're calculating for
//          if(data_year >= 1760){

//         if (data_year == year) {
//             yearly_total += temperature;
//         } else {
//             // Calculate the yearly average and print it
//            if(year >= 1760){
//             double yearly_average = yearly_total / NUM_MONTHS;
//             fprintf(outputFile,"Year %d: %.2f\n", year, yearly_average);
//             }
//             // Reset variables for the next year
//             year = data_year;
//             yearly_total = temperature;
//             num_years++;
//         }
//    }}
//   // Calculate and print the average for the last year
//   double last_year_average = yearly_total / NUM_MONTHS;
//   fprintf(outputFile, "Year %d: %.2f\n", year, last_year_average);

//     // Print the number of years processed
//     printf("Total years processed: %d\n", num_years);

//     fclose(file);
//     return 0;
// }

