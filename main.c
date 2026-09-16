#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPECIALTY_COUNT 4
#define WARD_COUNT 4
#define MAX_BEDS 20

const char specialtyNames [SPECIALTY_COUNT][30] = {"General Practice(OPD)", "Paediatrics", "Cardiology", "Neurology"};
const double specialtyFees [SPECIALTY_COUNT] = {1500.00, 2500.00, 4500.00, 5000.00};
const int consultationTimes [SPECIALTY_COUNT] = {15, 20, 30, 30};
const int dailyPatientCaps [SPECIALTY_COUNT] = {30, 20, 12, 10};

const char wardNames [WARD_COUNT][30] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU (Intensive Care Unit)"};
const double wardRates[WARD_COUNT] = {3000.00, 6000.00, 12000.00, 25000.00};
const int wardCapacities[WARD_COUNT] = {20, 10, 10, 5};

int main()
{

    return 0;
}
