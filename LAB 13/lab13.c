#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int studentNo;
    char name[50];
    char department[50];
};

struct Node {
    struct Student student;
    struct Node* next;
};

struct Node* head = NULL;

// Dosyaya yeni bir öðrenci kaydý ekleme
void addStudentToFile(struct Student student) {
    FILE* file = fopen("students.txt", "ab");
    if (file == NULL) {
        printf("Dosya olusturulamadi veya acilamadi.\n");
        return;
    }
    fwrite(&student, sizeof(struct Student), 1, file);
    fclose(file);
}

// Dosyadaki tüm öðrenci kayýtlarýný listeye ekleme
void addStudentsToList() {
    FILE* file = fopen("students.txt", "rb");
    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    struct Student student;
    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->student = student;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            struct Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    fclose(file);
}

// Öðrenci listesini ekrana yazdýrma
void printStudents() {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("Ogrenci No: %d\n", temp->student.studentNo);
        printf("Isim: %s\n", temp->student.name);
        printf("Bolum: %s\n\n", temp->student.department);
        temp = temp->next;
    }
}

// Öðrenci arama
void searchStudent(int studentNo) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->student.studentNo == studentNo) {
            printf("Ogrenci No: %d\n", temp->student.studentNo);
            printf("Isim: %s\n", temp->student.name);
            printf("Bolum: %s\n\n", temp->student.department);
            return;
        }
        temp = temp->next;
    }
    printf("Ogrenci bulunamadi.\n");
}

int main() {
    int choice;
    struct Student student;

    addStudentsToList();

    while (1) {
        printf("Menu:\n");
        printf("1. Ogrenci ekle\n");
        printf("2. Tum ogrencileri listele\n");
        printf("3. Ogrenci ara\n");
        printf("4. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Ogrenci No: ");
                scanf("%d", &student.studentNo);
                printf("Isim: ");
                scanf("%s", student.name);
                printf("Bolum: ");
                scanf("%s", student.department);

                addStudentToFile(student);
                addStudentsToList();
                break;
            case 2:
                printStudents();
                break;
            case 3:
                printf("Aranacak Ogrenci No: ");
                scanf("%d", &student.studentNo);
                searchStudent(student.studentNo);
                break;
            case 4:
                printf("Programdan cikiliyor...\n");
                return 0;
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }

        printf("\n");
    }

    return 0;
}

