#include "Header.h"

int main() {
    COMPANY company;
    LIST* head = malloc(sizeof(LIST));
    head = NULL;

    readFile(&head);

    //LIST *temp;
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

