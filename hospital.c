#include <stdio.h>
#include <string.h>

#define MAX 100

/* Nested structure */
struct Date
{
    int day;
    int month;
    int year;
};

/* Structure for Inpatient details */
struct Inpatient
{
    int roomNo;
    int admissionDays;
};

/* Structure for Outpatient details */
struct Outpatient
{
    struct Date appointmentDate;
    char doctorName[50];
};

/* Union - stores only one type of additional information at a time */
union AdditionalInfo
{
    struct Inpatient inpatient;
    struct Outpatient outpatient;
};

/* Main Patient structure */
struct Patient
{
    int id;
    char name[50];
    int age;
    char gender;

    int category;   /* 1 = Inpatient, 2 = Outpatient */

    union AdditionalInfo info;
};


/* Function to add a patient */
void addPatient(struct Patient p[], int *count)
{
    if (*count >= MAX)
    {
        printf("\nPatient limit reached!\n");
        return;
    }

    printf("\n--- ADD PATIENT ---\n");

    printf("Enter Patient ID: ");
    scanf("%d", &p[*count].id);

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", p[*count].name);

    printf("Enter Age: ");
    scanf("%d", &p[*count].age);

    printf("Enter Gender (M/F): ");
    scanf(" %c", &p[*count].gender);

    printf("\nSelect Patient Category:\n");
    printf("1. Inpatient\n");
    printf("2. Outpatient\n");
    printf("Enter choice: ");
    scanf("%d", &p[*count].category);

    if (p[*count].category == 1)
    {
        printf("\nEnter Room Number: ");
        scanf("%d", &p[*count].info.inpatient.roomNo);

        printf("Enter Admission Days: ");
        scanf("%d", &p[*count].info.inpatient.admissionDays);
    }
    else if (p[*count].category == 2)
    {
        printf("\nEnter Appointment Date (DD MM YYYY): ");
        scanf("%d %d %d",
              &p[*count].info.outpatient.appointmentDate.day,
              &p[*count].info.outpatient.appointmentDate.month,
              &p[*count].info.outpatient.appointmentDate.year);

        printf("Enter Doctor Name: ");
        scanf(" %[^\n]", p[*count].info.outpatient.doctorName);
    }
    else
    {
        printf("Invalid category!\n");
        return;
    }

    (*count)++;

    printf("\nPatient added successfully!\n");
}


/* Function to display one patient */
void displayPatient(struct Patient p)
{
    printf("\n-----------------------------\n");
    printf("Patient ID     : %d\n", p.id);
    printf("Patient Name   : %s\n", p.name);
    printf("Age            : %d\n", p.age);
    printf("Gender         : %c\n", p.gender);

    if (p.category == 1)
    {
        printf("Category       : Inpatient\n");
        printf("Room Number    : %d\n", p.info.inpatient.roomNo);
        printf("Admission Days  : %d\n", p.info.inpatient.admissionDays);
    }
    else if (p.category == 2)
    {
        printf("Category       : Outpatient\n");

        printf("Appointment    : %02d-%02d-%04d\n",
               p.info.outpatient.appointmentDate.day,
               p.info.outpatient.appointmentDate.month,
               p.info.outpatient.appointmentDate.year);

        printf("Doctor Name    : %s\n",
               p.info.outpatient.doctorName);
    }

    printf("-----------------------------\n");
}
/* Function to display all patients */
void displayAll(struct Patient p[], int count)
{
    int i;

    if (count == 0)
    {
        printf("\nNo patients available.\n");
        return;
    }

    printf("\n===== ALL PATIENTS =====\n");

    for (i = 0; i < count; i++)
    {
        displayPatient(p[i]);
    }
}


/* Function to search patient */
void searchPatient(struct Patient p[], int count)
{
    int id, i, found = 0;

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (p[i].id == id)
        {
            printf("\nPatient found!\n");
            displayPatient(p[i]);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nPatient not found!\n");
    }
}


/* Function to update patient */
void updatePatient(struct Patient p[], int count)
{
    int id, i, found = 0;

    printf("\nEnter Patient ID to update: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (p[i].id == id)
        {
            found = 1;

            printf("\nPatient found. Enter new details.\n");

            printf("Enter New Name: ");
            scanf(" %[^\n]", p[i].name);

            printf("Enter New Age: ");
            scanf("%d", &p[i].age);

            printf("Enter New Gender (M/F): ");
            scanf(" %c", &p[i].gender);

            printf("\nSelect New Category:\n");
            printf("1. Inpatient\n");
            printf("2. Outpatient\n");
            printf("Enter choice: ");
            scanf("%d", &p[i].category);

            if (p[i].category == 1)
            {
                printf("Enter New Room Number: ");
                scanf("%d", &p[i].info.inpatient.roomNo);

                printf("Enter New Admission Days: ");
                scanf("%d", &p[i].info.inpatient.admissionDays);
            }
            else if (p[i].category == 2)
            {
                printf("Enter New Appointment Date (DD MM YYYY): ");
                scanf("%d %d %d",
                      &p[i].info.outpatient.appointmentDate.day,
                      &p[i].info.outpatient.appointmentDate.month,
                      &p[i].info.outpatient.appointmentDate.year);

                printf("Enter New Doctor Name: ");
                scanf(" %[^\n]", p[i].info.outpatient.doctorName);
            }

            printf("\nPatient information updated successfully!\n");
            break;
        }
    }
     if (!found)
    {
        printf("\nPatient not found!\n");
    }
}
/* Main function */
int main()
{
    struct Patient patients[MAX] = {0};
    int count = 0;
    int choice;
     printf("========================================\n");
    printf("   HOSPITAL PATIENT INFORMATION SYSTEM\n");
    printf("========================================\n");
    do
    {
        printf("\n\n========== MENU ==========\n");
        printf("1. Add Patient\n");
        printf("2. Search Patient\n");
        printf("3. Update Patient\n");
        printf("4. Display All Patients\n");
        printf("5. Display Structure Sizes\n");
        printf("6. Exit\n");
        printf("==========================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPatient(patients, &count);
                break;

            case 2:
                searchPatient(patients, count);
                break;

            case 3:
                updatePatient(patients, count);
                break;

            case 4:
                displayAll(patients, count);
                break;

            case 5:
                printf("\n===== SIZE OF STRUCTURES =====\n");
                printf("Size of Date structure          : %zu bytes\n",
                       sizeof(struct Date));

                printf("Size of Inpatient structure     : %zu bytes\n",
                       sizeof(struct Inpatient));

                printf("Size of Outpatient structure    : %zu bytes\n",
                       sizeof(struct Outpatient));

                printf("Size of Union                   : %zu bytes\n",
                       sizeof(union AdditionalInfo));

                printf("Size of Patient structure       : %zu bytes\n",
                       sizeof(struct Patient));
                break;

            case 6:
                printf("\nThank you! Program terminated.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}