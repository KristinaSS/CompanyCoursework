#define _CRT_SECURE_NO_WARNINGS
#define FILE_NAME "File.bin"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//todo see all double pointers

typedef struct{
    long long ID;
    char name[50];
    char industry[30];
    double income;
    double debt;
    int workers;
} COMPANY;
typedef struct List{
    COMPANY company;
    struct List* next;
}LIST;
typedef struct Industries{
    char industry[30];
    struct Industries* next;
}INDUSTRIES;


void byIndustries(LIST** head);
void printCompany(COMPANY company);
void swap(LIST* A, LIST* B);
void sortListByIndusrty(LIST* head);
void sortListByName(LIST* head);
void insertNode(LIST** head, COMPANY company);
void deleteNodeAtPoss(LIST** head, int poss);
void freeList(LIST* head, int flag);
void readFile(LIST **head);
void writeFile(LIST* head);
COMPANY enterCompany(LIST *head);
void findCompany(LIST* head);
void deleteCompanies(LIST** head);

//todo make no void functions
//menus and main
int menu(){
    int choice;
    printf("\n\nMENU \n");
    printf("1.Add new Company\n");
    printf("2.Search Company \n");
    printf("3.Select all Companies by Industry\n");
    printf("4.Delete Companies By Debt\n");
    printf("5.exit\n\n");

    do{
        printf("Choose: ");
        scanf_s("%d", &choice);
    } while (choice < 1 || choice > 5);
    return choice;
}

int findCompanyMenu(){
    int choice;
    printf("\nFind Company\n");
    printf("1.By Keyword\n");
    printf("2. By ID\n");
    printf("3. EXIT\n");
    do{
        printf("Choice: ");
        scanf_s("%d", &choice);
    } while (choice < 1 || choice > 3);

    return choice;
}

int main() {
    COMPANY company;
    LIST* head = malloc(sizeof(LIST));
    head = NULL;

    //LIST *temp;

    readFile(&head);

    /*temp = head;
    while(temp!=NULL){
        printCompany(temp->company);
        temp = temp->next;
    }*/
    while (1){
        switch (menu()){
            case 1:
                company = enterCompany(head);
                insertNode(&head, company);
                printf("New Company added successfully!\n");
                continue;
            case 2: findCompany(head);
                continue;
            case 3: byIndustries(&head);
                continue;
            case 4: deleteCompanies(&head);
                continue;
            default:
                break;
        }
        system("pause");
        break;
    }
    writeFile(head);
    freeList(head, 1);

    return 0;
}

//functions
COMPANY enterCompany(LIST *head){
    COMPANY company;
    int temp;

    LABEL:
    while(1){
        printf("\nEnter ID: ");
        fflush(stdin);
        scanf_s("%lld", &company.ID);
        if(company.ID < 100000000000 ||  company.ID>999999999999 ){
            printf("\nTry again!\n");
            continue;
        }
        while (head){
            if (head->company.ID == company.ID){
                printf("ID already exist!\n");
                goto LABEL;
            }
            head = head->next;
        }
        break;
    }

    do{
        fflush(stdin);
        printf("Enter a name for your company: \n");
        fflush(stdin);
        gets(company.name);
        temp = strlen(company.name);
    } while (temp > 50 || temp == 0);
    do{
        printf("Enter the industry for your company: \n");
        gets(company.industry);
        temp = strlen(company.industry);
    } while (temp> 30 || temp == 0);

    do{
        printf("Enter company income: \n");
        fflush(stdin);
        scanf_s("%lf", &company.income);
    } while (company.income < 0);
    do{
        printf("Enter company debt: ");
        fflush(stdin);
        scanf_s("%lf", &company.debt);
    } while (company.debt < 0);
    do{
        printf("Enter number of employees: ");
        fflush(stdin);
        scanf_s("%d", &company.workers);
    } while (company.workers < 0);

    return company;
}

void deleteCompanies(LIST** head){
    int flag = 0, poss = 1;
    double debt;
    LIST *current = *head;
    char c;

    printf("Enter debt: ");
    scanf_s("%lf", &debt);
    printf("Do you want to delete all companies with debt higher than %.2lf <Y/N>: ", debt);
        while (1){
            fflush(stdin);
            c = toupper(c = getchar());
            if (c != 'Y' && c != 'N'){
                printf("Please enter Y/N! \n");
                continue;
            }
            break;
        }
        if (c == 'N')
            return;

    while (current){
        if (current->company.debt >= debt){
                flag = 1;
                current = current->next;
                deleteNodeAtPoss(head, poss);
        } else{
                poss++;
                current = current->next;
            }
        }
    if (!flag){
        printf("No companies with debt higher than %.2lf found!\n", debt);
    }
    else
        printf("All companies with debt over %.2lf have been deleted!\n", debt);
}

void findCompany(LIST* head) {
    LIST *copy = head;
    int choice = findCompanyMenu(), count = 0 ;
    char keyword[50];
    int res = 0;
    long long ID = 0;

    if (!choice)
        return;

    if (choice == 1) {
        printf("\nEnter keyword (Notice: case sensitive): ");
        getchar();
        gets(keyword);
    } else {
        if (choice == 2) {
            printf("\nEnter ID: ");
            scanf_s("%lld", &ID);
        } else
            return;
    }
    while (head!= NULL) {
        if (ID != 0) {
            if (ID == head->company.ID) {
                printCompany(head->company);
                return;
            }
        } else {
            if (strstr(head->company.name, keyword)) {
                    printf("\nID: %lld      ", head->company.ID);
                    printf("Name: %s\n", head->company.name);
                    count++;
                }
            }
        head = head->next;
        }
    if(count == 0){
        printf("No companies found! \n");
        return;
    }
    printf("Enter the id of the company you want to see: \n");
    scanf_s("%lld", &ID);
        while(copy){
            if (ID == copy->company.ID) {
                printCompany(copy->company);
                return;
            }
            copy = copy->next;
        }
        printf("Company Not found!\n");

}

void byIndustries(LIST **head) {

    if (*head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    sortListByIndusrty(*head);

    LIST* current = *head;
    int flag = 1;
    while (current){
        if (flag){
            printf("\nIndustry: %s\n", current->company.industry);
            flag = 0;
        }

        if (current->next){
            if (strcmp(current->company.industry, current->next->company.industry)!=0){
                flag = 1;
            }
        }
        current = current->next;
    }
    printf("\nEnter the name of the industry whose companies you want to see?\n");
    char industry[30];
    getchar();
    gets(industry);
    sortListByName(*head);
    LIST *cur = *head;
    flag = 0;

    while (cur){
        if(strcmp(cur->company.industry, industry)== 0) {
            printCompany(cur->company);
            flag =1;
        }
        cur= cur->next;
    }
    if(flag == 0){
        printf("\nNo companies in %s have been found! \n", industry);
    }
}

//utils

void swap(LIST* A, LIST* B){
    COMPANY temp = A->company;
    A->company = B->company;
    B->company = temp;
}

void sortListByIndusrty(LIST* head){
    int flag;
    LIST *temp1;
    LIST *temp2 = NULL;

    if (head == NULL)
        return;

    do
    {
        flag = 0;
        temp1 = head;

        while (temp1->next != temp2)
        {
            if (strcmp(temp1->company.industry,temp1->next->company.industry)>0){
                swap(temp1, temp1->next);
                flag = 1;
            }
            temp1 = temp1->next;
        }
        temp2 = temp1;
    }
    while (flag);
}

void sortListByName(LIST* head){
    int flag;
    LIST *temp1;
    LIST *temp2 = NULL;

    if (head == NULL)
        return;

    do
    {
        flag = 0;
        temp1 = head;

        while (temp1->next != temp2)
        {
            if (strcmp(temp1->company.name,temp1->next->company.name)>0){
                swap(temp1, temp1->next);
                flag = 1;
            }
            temp1 = temp1->next;
        }
        temp2 = temp1;
    }
    while (flag);
}

void printCompany(COMPANY company){
    printf("\nID:       %lld\n", company.ID);
    printf("Name:       %s\n", company.name);
    printf("Industry:   %s\n", company.industry);
    printf("Income:     %.2lf\n", company.income);
    printf("Debt:       %.2lf\n", company.debt);
    printf("Employees:  %d\n", company.workers);

}

//nodes

void insertNode(LIST** head, COMPANY company) {
    LIST *newNode = (LIST *) malloc(sizeof(LIST));
    LIST *currentNode = *head;

    newNode->company = company;
    newNode->next = NULL;

    if ((*head)== NULL) {
        *head = newNode;
        return;
    }
    while (currentNode->next) {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}

void freeList(LIST* head, int flag){
    LIST* cur;

    while (head){
        cur = head;
        head = (head)->next;
        free(cur);
    }
    if(flag == 1)
        free(head);
}

void deleteNodeAtPoss(LIST** head, int poss){
    int i;
    LIST *temp1 = (*head);

    LIST *temp2 = temp1->next;
    if (poss == 1){
        (*head) = temp1->next;
        free(temp1);
        return;
    }

    for (i = 0; i < poss - 2; i++){
        temp1 = temp1->next;
    }

    temp1->next = temp2->next;
    free(temp2);
}

//files

void readFile(LIST **head){
    FILE* fp;
    COMPANY company;

    if ((fp = fopen(FILE_NAME, "rb"))==NULL){
        printf("Error opening file!\n");
        freeList(*head,1);
        fclose(fp);
        exit(-1);
    }

    if (*head)
        freeList(*head, 0);

    while (fread(&company, sizeof(company), 1, fp)== 1){
        insertNode(head, company);
    }

    fclose(fp);
    printf("File successfully read! \n");
}

void writeFile(LIST* head){
    FILE* fp;

    if (!head){
        printf("List is empty!\n");
        return;
    }

    if (!(fp = fopen(FILE_NAME, "wb"))){
        printf("Error while opening file");
        return;
    }

    while (head){
        if (fwrite(&head->company, sizeof(COMPANY), 1, fp) != 1){
            printf("Error occured while writing on file\n");
            freeList(head,1);
            fclose(fp);
            exit(1);
        }
        head = head->next;
    }

    fclose(fp);
}
