//
// Created by Kristina on 5/20/2019.
//
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

//Menus

int menu();
int findCompanyMenu();

//Functions
void byIndustries(LIST** head);
COMPANY enterCompany(LIST *head);
void findCompany(LIST* head);
void deleteCompanies(LIST** head);
//Utils
void printCompany(COMPANY company);
void swap(LIST* A, LIST* B);
void sortListByIndustry(LIST* head);
void sortListByName(LIST* head);
//Nodes and Lists
void insertNode(LIST** head, COMPANY company);
void deleteNodeAtPoss(LIST** head, int poss);
void freeList(LIST* head, int flag);
//Files
void readFile(LIST **head);
void writeFile(LIST* head);

