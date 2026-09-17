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

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

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
