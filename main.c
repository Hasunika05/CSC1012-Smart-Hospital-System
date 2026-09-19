#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPECIALTY_COUNT 4
#define WARD_COUNT 4
#define MAX_BEDS 20
#define MAX_PATIENTS 72

const char specialtyNames [SPECIALTY_COUNT][30] = {"General Practice(OPD)", "Paediatrics", "Cardiology", "Neurology"};
const double specialtyFees [SPECIALTY_COUNT] = {1500.00, 2500.00, 4500.00, 5000.00};
const int consultationTimes [SPECIALTY_COUNT] = {15, 20, 30, 30};
const int dailyPatientCaps [SPECIALTY_COUNT] = {30, 20, 12, 10};

const char wardNames [WARD_COUNT][30] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU (Intensive Care Unit)"};
const double wardRates[WARD_COUNT] = {3000.00, 6000.00, 12000.00, 25000.00};
const int wardCapacities[WARD_COUNT] = {20, 10, 10, 5};

int bedOccupancy [WARD_COUNT][MAX_BEDS] = {0};

int specialtyQueueCounts [SPECIALTY_COUNT] = {0};

int patientCount = 0;

char patientNames [MAX_PATIENTS][50] = {0};
char patientGender [MAX_PATIENTS] = {0};
int patientAges [MAX_PATIENTS] = {0};
int urgencyLevels [MAX_PATIENTS] = {0};
int specialtyIDs [MAX_PATIENTS] = {0};
int admissionStatus [MAX_PATIENTS] = {0};
int wardIDs [MAX_PATIENTS] = {0};
int daysAdmitted [MAX_PATIENTS] = {0};

int assignedBedNumbers [MAX_PATIENTS]= {0};

int waitingTimes [MAX_PATIENTS] = {0};
double emergencySurcharges [MAX_PATIENTS] = {0};
double wardStayCosts [MAX_PATIENTS] = {0};
double grossTotals [MAX_PATIENTS] = {0};
double discounts [MAX_PATIENTS] = {0};
double finalPayableAmounts [MAX_PATIENTS] = {0};

void registerPatient ();
double calculateEmergencySurcharge (double basefee, int urgency);
double wardCost (int wardID, int noOfDays);
double calculateDiscount (double grossTotals, int patientAge);
void printPatientBill (int index);
void viewBedStatus();
void displayPriorityList();
void generateReports();


int main()
{
    int choice = 0;
    do{
    printf("==================================\n");
    printf("      SMART HOSPITAL SYSTEM\n");
    printf("==================================\n");
    printf("1. Register Patient\n");
    printf("2. View Bed Status\n");
    printf("3. Display Priority List\n");
    printf("4. Generate Reports\n");
    printf("5. Exit\n");

    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch (choice){
        case 1:
            registerPatient ();
            break;
        case 2:
            viewBedStatus();
            break;
        case 3:
            displayPriorityList();
            break;
        case 4:
            void generateReports();
            break;
        case 5:
            printf("Exiting Smart Hospital System.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }

    }while(choice != 5);


    return 0;
}

void registerPatient (){

    int index = patientCount;
    if (index >= MAX_PATIENTS){
        printf("Hospital registration limit reached.\n");
        return;
    }
    printf("Enter the patient name: ");
    scanf(" %49[^\n]", patientNames[index]);
    do{
        printf("Enter the gender (M - male, F - female): ");
        scanf(" %c", &patientGender[index]);
    }while (patientGender[index] != 'M' && patientGender[index] != 'F');
    printf("Enter the patient age: ");
    scanf("%d", &patientAges[index]);
    do{
        printf("Enter the emergency level (1 = Normal, 2 = Urgent, 3 = Critical): ");
        scanf("%d", &urgencyLevels[index]);
    }while(urgencyLevels[index] < 1 || urgencyLevels[index] > 3);
    do{
        printf("1. General Practice (OPD)\n");
        printf("2. Paediatrics\n");
        printf("3. Cardiology\n");
        printf("4. Neurology\n");
        printf("Enter the Specialty ID (1 to 4): ");
        scanf("%d", &specialtyIDs[index]);
    }while(specialtyIDs[index] < 1 || specialtyIDs[index] > 4);

    int specialtyIndex = specialtyIDs[index] - 1;
    if (specialtyQueueCounts[specialtyIndex] >= dailyPatientCaps[specialtyIndex]){
        printf ("Daily patient limit reached for this specialty.\n");
        return;
    }


    do{
        printf("Is the patient admitted to a ward? (1 = Yes, 0 = No): ");
        scanf("%d", &admissionStatus[index]);
    }while(admissionStatus[index] != 0 && admissionStatus[index] != 1);
    if(admissionStatus[index] == 0){
        wardIDs[index] = 0;
        daysAdmitted[index] = 0;
        assignedBedNumbers[index] = 0;
    }
    else {
        for(int i = 0; i < WARD_COUNT; i++ ){
            printf("%d. %s\n", i + 1, wardNames[i]);
        }

        do{
        printf("Enter the ward ID (1 to 4): ");
        scanf("%d", &wardIDs[index]);
        }while(wardIDs[index] < 1 || wardIDs[index] > WARD_COUNT);
        do{
        printf("Enter the number of days admitted: ");
        scanf("%d", &daysAdmitted[index]);
        }while(daysAdmitted[index]<1);
        int wardIndex = wardIDs[index] - 1;

        int bedfound = 0;
        for(int i = 0; i < wardCapacities[wardIndex]; i++){
            if (bedOccupancy[wardIndex][i] == 0){
                bedOccupancy[wardIndex][i] = 1;
                assignedBedNumbers[index] = i + 1;
                bedfound = 1;
                break;
            }
        }
        if (bedfound == 0){
            printf("No available beds in the selected ward.\n");
            return;
        }


    }

    waitingTimes[index] = specialtyQueueCounts[specialtyIndex] * consultationTimes[specialtyIndex];
    specialtyQueueCounts[specialtyIndex] = specialtyQueueCounts[specialtyIndex] + 1;

    emergencySurcharges[index] = calculateEmergencySurcharge (specialtyFees[specialtyIndex],urgencyLevels[index]);
    wardStayCosts[index] = wardCost(wardIDs[index],daysAdmitted[index]);

    grossTotals[index] = specialtyFees[specialtyIndex] + emergencySurcharges[index] + wardStayCosts[index];
    discounts[index] = calculateDiscount(grossTotals[index],patientAges[index]);
    finalPayableAmounts[index] = grossTotals[index] - discounts[index];
    printPatientBill (index);

    patientCount = patientCount + 1;

    printf("Patient registered successfully.\n");

}

double calculateEmergencySurcharge (double basefee, int urgency){
    double surcharge = 0;
    switch (urgency){

        case 1 :
            surcharge = 0;
            break;
        case 2 :
            surcharge = basefee * (0.20);
            break;
        case 3 :
            surcharge = basefee * (0.50);
            break;
    }
    return surcharge;
}

double wardCost (int wardID, int noOfDays){

    if (wardID == 0){
        return 0;
    }
    else{
        int wardIndex = wardID - 1;
        return wardRates[wardIndex] * noOfDays;
    }

}

double calculateDiscount (double grossTotal, int patientAge){

    if(patientAge <5 || patientAge >65){
        return grossTotal * 0.15;
    }
    else{
        return 0;
    }
}

void printPatientBill (int index){

    int specialtyIndex = specialtyIDs[index] - 1;

    printf("===========================================\n");
    printf("      SMART HOSPITAL ADMISSION & BILL\n");
    printf("-------------------------------------------\n");
    printf("Patient ID               : PAT-%d\n",1001 + index);
    if(patientGender[index] == 'M'){
        printf("Patient Name             : Mr. %s\n", patientNames[index]);
    }
    else {
        printf("Patient Name             : Miss. %s\n", patientNames[index]);
    }
    if(patientAges[index] <5 || patientAges[index] >65){
        printf("Age                      : %d Years (15%% Subsidy Eligible)\n",patientAges[index]);
    }
    else{
        printf("Age                      : %d Years \n",patientAges[index]);
    }
    switch(specialtyIDs[index]){
        case 1:
            printf("Speciality               : General Practice (OPD)\n");
            break;
        case 2:
            printf("Speciality               : Paediatrics\n");
            break;
        case 3:
            printf("Speciality               : Cardiology\n");
            break;
        case 4:
            printf("Speciality               : Neurology\n");
            break;
    }
    switch(wardIDs[index]){
        case 1:
            printf("Assigned Ward            : General Ward (Bed #%02d)\n", assignedBedNumbers[index]);
            break;
        case 2:
            printf("Assigned Ward            : Paediatric Ward (Bed #%02d)\n", assignedBedNumbers[index]);
            break;
        case 3:
            printf("Assigned Ward            : Surgical Ward (Bed #%02d)\n", assignedBedNumbers[index]);
            break;
        case 4:
            printf("Assigned Ward            : ICU (Bed #%02d)\n", assignedBedNumbers[index]);
            break;
        default:
            printf("Not admitted.\n");
    }
    switch(urgencyLevels[index]){
        case 1:
            printf("Urgency Level            : Level 1(Normal)\n");
            break;
        case 2:
            printf("Urgency Level            : Level 2(Urgent)\n");
            break;
        case 3:
            printf("Urgency Level            : Level 3(Critical)\n");
            break;
    }
    printf("-------------------------------------------\n");
    printf("Base Consultation Fee    : LKR %.2f\n", specialtyFees[specialtyIndex]);
    switch (urgencyLevels[index]){
        case 1 :
            printf("Emergency Surcharge      : LKR %.2f \n", emergencySurcharges[index]);
            break;
        case 2 :
            printf("Emergency Surcharge      : LKR %.2f (20%%)\n", emergencySurcharges[index]);
            break;
        case 3 :
            printf("Emergency Surcharge      : LKR %.2f (50%%)\n", emergencySurcharges[index]);
            break;
    }
    printf("Ward Stay Cost (%d Days) : LKR %.2f\n", daysAdmitted[index], wardStayCosts[index]);
    printf("-------------------------------------------\n");
    printf("Gross Total Bill         : LKR %.2f\n", grossTotals[index]);
    printf("Age Subsidy Discount     : LKR %.2f\n", discounts[index]);
    printf("-------------------------------------------\n");
    printf("Final Payable Amount     : LKR %.2f\n", finalPayableAmounts[index]);
    printf("Estimated Waiting Time   : %d mins\n", waitingTimes[index]);
    printf("===========================================\n");

}

void viewBedStatus(){

    for (int i = 0; i < WARD_COUNT; i++){
        printf("\n%s\n", wardNames[i]);

        for (int j = 0; j < wardCapacities[i]; j++){
            if (bedOccupancy[i][j] == 0){
            printf("Bed %02d  :  Available\n", j + 1);
            }
            else {
            printf("Bed %02d  :  Occupied\n", j + 1);
            }
        }
    }
}

void displayPriorityList(){
    if (patientCount == 0){
        printf("No patients registered.\n");
        return;
    }

    int priorityOrder[MAX_PATIENTS];

    for (int i = 0; i < patientCount; i++){
        priorityOrder[i] = i;
    }

    for (int i = 0; i < patientCount - 1; i++){
        for (int j = 0; j < patientCount - 1 - i; j++){
            if (urgencyLevels[priorityOrder[j]] < urgencyLevels[priorityOrder[j + 1]]){
                int temp = priorityOrder[j];
                priorityOrder[j] = priorityOrder[j + 1];
                priorityOrder[j + 1] = temp;
            }
        }
    }

    printf("\n===========================================\n");
    printf("            PATIENT PRIORITY LIST\n");
    printf("===========================================\n");

    for (int i = 0; i < patientCount; i++){
        int patientIndex = priorityOrder[i];

        printf("PAT-%d  |  %s  |  ",
               1001 + patientIndex,
               patientNames[patientIndex]);

        switch (urgencyLevels[patientIndex]){
            case 1:
                printf("Level 1 - Normal\n");
                break;

            case 2:
                printf("Level 2 - Urgent\n");
                break;

            case 3:
                printf("Level 3 - Critical\n");
                break;
        }
    }

    printf("===========================================\n");
}

void generateReports(){

    if (patientCount == 0){
        printf("No patients registered.\n");
        return;
    }
    int normalcount = 0;
    int urgentcount = 0;
    int criticalcount = 0;

    for (int i = 0; i < patientCount; i++){
        switch (urgencyLevels[i]){
            case 1:
                normalcount++;
                break;
            case 2:
                urgentcount++;
                break;
            case 3:
                criticalcount++;
                break;
        }
    }

    double totalRevenue = 0;
    double totalDiscounts = 0;

    for (int i = 0; i < patientCount; i++){
        totalRevenue = totalRevenue + finalPayableAmounts[i];
    }
    for (int i = 0; i < patientCount; i++){
        totalDiscounts = totalDiscounts + discounts[i];
    }

    printf("\n===========================================\n");
    printf("          HOSPITAL SUMMARY REPORT\n");
    printf("===========================================\n");

    printf("Total Patients Registered : %d\n", patientCount);
    printf("Normal Patients           : %d\n", normalcount);
    printf("Urgent Patients           : %d\n", urgentcount);
    printf("Critical Patients         : %d\n", criticalcount);

    printf("-------------------------------------------\n");

    printf("Total Revenue             : LKR %.2f\n", totalRevenue);
    printf("Total Discounts Granted   : LKR %.2f\n", totalDiscounts);

    printf("-------------------------------------------\n");
    printf("Bed Occupancy Percentage\n");

    for (int i = 0; i < WARD_COUNT; i++){
        int occupiedBeds = 0;

        for (int j = 0; j < wardCapacities[i]; j++){
            if (bedOccupancy[i][j] == 1){
            occupiedBeds++;
            }
        }

        double occupancyPercentage = ((double)occupiedBeds / wardCapacities[i]) * 100;

        printf("%s : %.2f%%\n", wardNames[i], occupancyPercentage);
    }

    int highestIndex = 0;

    for (int i = 1; i < patientCount; i++){
        if (finalPayableAmounts[i] > finalPayableAmounts[highestIndex]){
        highestIndex = i;
        }
    }
    printf("-------------------------------------------\n");

    printf("Highest Paying Patient    : %s\n", patientNames[highestIndex]);

    printf("Total Bill                : LKR %.2f\n", finalPayableAmounts[highestIndex]);

    printf("===========================================\n");

}
