
#define _CRT_SECURE_NO_WARNINGS//.See online help for details.library_system	D : \desktop\ALL\ALLwork\library_system\library_system\library.c	154
#include<stdio.h>

//ͼ��ṹ��
typedef struct {
    int id;
    char name[100];
    char author[100];
    int is_borrowed; //0�ɽ裬1���ɽ�
} Book;

//�û��ṹ��
typedef struct {
    int id;
    char name[100];
    int borrowed_book_id; //�û���ͼ���id
} User;

//��������
void load_books();
void load_users();
void save_books();
void save_users();
void admin_system();
void user_system();
void add_book();
void view_books();
void borrow_book();
void return_book();
void delete_book();
void press_to_continue();  // �����ĵȴ��û���������ĺ���
int get_valid_int_input(); // ������֤����

//ȫ�ֱ�������ͼ����û���Ϣ
Book books[200];
User users[200];
int book_count = 0;
int user_count = 0;

//������
int main() {
    load_books();
    load_users();
    int choice;
    a:
    printf("=======ͼ�����ϵͳ=======\n");
    printf("����1�������Աϵͳ\n");
    printf("����2�����û�ϵͳ\n");
    scanf("%d", &choice);
    if (choice == 1) {
        admin_system();
    }
    else if (choice == 2) {
        user_system();
    }
    else {
        printf("��Ч����\n");
    }
    return 0;
}

//����ͼ����Ϣ
void load_books() {
    char filepath[] = "D:\\c_work\\books.txt";  // ���Ըĳɴ������ļ���ȡ·��
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("�޷����ļ� %s������·����Ȩ�ޣ�\n", filepath);
        return;
    }
    while (fscanf(file, "%d,%99[^,],%99[^,],%d\n",
        &books[book_count].id,
        books[book_count].name,
        books[book_count].author,
        &books[book_count].is_borrowed) == 4) {
        book_count++;
    }
    fclose(file);
}

//�����û���Ϣ
void load_users() {
    FILE* file = fopen("D:\\c_work\\users.txt", "r");
    if (!file) {
        printf("�޷����ļ� D:\\c_work\\users.txt ������·����Ȩ�ޣ�\n");
        return;
    }

    char line[256]; // ��ʱ�洢һ������
    while (fgets(line, sizeof(line), file)) {
        if (user_count >= 100) {
            printf("�û������ﵽ���ޣ�\n");
            break;
        }

        // ʹ�� sscanf ��ȡ�ֶ�
        if (sscanf(line, "%d,%99[^,],%d",
            &users[user_count].id,
            users[user_count].name,
            &users[user_count].borrowed_book_id) == 3) {
            user_count++;
        }
        else {
            printf("��������������һ�У�%s\n", line);
        }
    }

    fclose(file);
    printf("�û���Ϣ������� һ�������� %d ���û���\n", user_count);
}

//����ͼ����Ϣ
void save_books() {
    FILE* file = fopen("D:\\c_work\\books.txt", "w");
    if (file) {
        for (int i = 0; i < book_count; i++) {
            fprintf(file, "%d,%s,%s,%d\n",
                books[i].id,
                books[i].name,
                books[i].author,
                books[i].is_borrowed);
        }
        fclose(file);
    }
}

//�����û���Ϣ
void save_users() {
    FILE* file = fopen("D:\\c_work\\users.txt", "w");
    if (file) {
        for (int i = 0; i < user_count; i++) {
            fprintf(file, "%d,%s,%d\n",
                users[i].id,
                users[i].name,
                users[i].borrowed_book_id);
        }
        fclose(file);
    }
}

//����Աϵͳ
void admin_system() {
    int choice;
    while (1) {  // ʹ��ѭ���ù���Ա��ν��в���
        printf("======= ����Աϵͳ =======\n");
        printf("1. ���ͼ��\n");
        printf("2. �鿴ͼ��\n");
        printf("3. ɾ��ͼ��\n");
        printf("4. ����\n");
        printf("������ѡ��: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1: add_book(); break;
        case 2: view_books(); break;
        case 3: delete_book(); break;
        case 4: return;
        default: printf("��Ч����\n"); break;
        }
        press_to_continue();  // �����󰴻س�����
    }
}

//�û�ϵͳ
void user_system() {
    int choice;
    while (1) {  // ʹ��ѭ�����û���ν��в���
        printf("======= �û�ϵͳ =======\n");
        printf("1. ����ͼ��\n");
        printf("2. �黹ͼ��\n");
        printf("3. ����\n");
        printf("������ѡ��: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1: borrow_book(); break;
        case 2: return_book(); break;
        case 3: return;
        default: printf("��Ч����\n"); break;
        }
        press_to_continue();  // �����󰴻س�����
    }
}

//���ͼ��
void add_book() {
    int id;
    printf("������ͼ���ţ�");
    scanf("%d", &id);
    getchar(); // ������з�

    // ���ͼ�����Ƿ��Ѿ�����
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) {
            printf("��ͼ�����Ѵ��ڣ�����������һ����ͬ�ı�ţ�\n");
            return;  // ͼ�����Ѵ��ڣ��˳�����
        }
    }

    // �����Ų����ڣ�������������������
    printf("������������");
    fgets(books[book_count].name, 100, stdin);
    books[book_count].name[strcspn(books[book_count].name, "\n")] = '\0'; // ������з�

    printf("���������ߣ�");
    fgets(books[book_count].author, 100, stdin);
    books[book_count].author[strcspn(books[book_count].author, "\n")] = '\0'; // ������з�

    books[book_count].id = id;
    books[book_count].is_borrowed = 0; // Ĭ�Ͽɽ�
    book_count++;

    save_books();
    printf("ͼ����ӳɹ���\n");
}

//ɾ��ͼ��
void delete_book() {
    int book_id = 0;
    printf("������Ҫɾ����ͼ����: ");
    scanf("%d", &book_id);

    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == book_id) {
            if (books[i].is_borrowed == 1) {
                printf("��ͼ�����ڱ����ģ��޷�ɾ����\n");
                return; // ͼ�����ڽ��ģ��޷�ɾ��
            }
            found = 1;
            for (int j = i; j < book_count - 1; j++) {
                books[j] = books[j + 1];
            }
            book_count--;
            printf("ͼ��ɾ���ɹ���\n");
            break;
        }
    }
    if (!found) {
        printf("δ�ҵ���ͼ�飡\n");
    }
}

//�鿴����ͼ��
void view_books() {
    for (int i = 0; i < book_count; i++) {
        printf("ͼ���ţ�%d,ͼ������%s,���ߣ�%s,�Ƿ�ɽ裺%s\n",
            books[i].id,
            books[i].name,
            books[i].author,
            books[i].is_borrowed ? "���ɽ�" : "�ɽ�");
    }
}

//����ͼ��
void borrow_book() {
    int user_id, book_id;
    printf("�������û� ID��");
    user_id = get_valid_int_input();
    printf("����������ĵ�ͼ�� ID��");
    book_id = get_valid_int_input();

    int found_user = 0, found_book = 0;
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == user_id) {
            found_user = 1;
            if (users[i].borrowed_book_id != 0) {
                printf("�û��Ѿ�����һ���飬�޷��ٽ裡��ǰ�ѽ��ĵ�ͼ�� ID �ǣ�%d\n",
                    users[i].borrowed_book_id);
                return;
            }
            break;
        }
    }
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == book_id) {
            found_book = 1;
            if (books[i].is_borrowed) {
                printf("��ͼ���Ѿ������ģ��޷����ģ�\n");
                return;
            }
            books[i].is_borrowed = 1;
            for (int j = 0; j < user_count; j++) {
                if (users[j].id == user_id) {
                    users[j].borrowed_book_id = book_id;
                    printf("���ĳɹ���\n");
                    save_books();
                    save_users();
                    return;
                }
            }
        }
    }

    if (!found_user) {
        printf("δ�ҵ����û���\n");
    }
    if (!found_book) {
        printf("δ�ҵ���ͼ�飡\n");
    }
}

//�黹ͼ��
void return_book() {
    int user_id, book_id;
    printf("�������û� ID��");
    user_id = get_valid_int_input();
    printf("������黹��ͼ�� ID��");
    book_id = get_valid_int_input();

    int found_user = 0, found_book = 0;
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == user_id) {
            found_user = 1;
            if (users[i].borrowed_book_id != book_id) {
                printf("���û���δ���Ĵ��飡\n");
                return;
            }
            break;
        }
    }

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == book_id) {
            found_book = 1;
            books[i].is_borrowed = 0;
            printf("�黹�ɹ���\n");

            for (int j = 0; j < user_count; j++) {
                if (users[j].id == user_id) {
                    users[j].borrowed_book_id = 0;
                    save_books();
                    save_users();
                    return;
                }
            }
        }
    }

    if (!found_user) {
        printf("δ�ҵ����û���\n");
    }
    if (!found_book) {
        printf("δ�ҵ���ͼ�飡\n");
    }
}

//�ȴ��û����س�����
void press_to_continue() {
    printf("������ɣ����س�����...\n");
    getchar();  // ������뻺�����еĻ��з�
    getchar();  // �ȴ��û����س�
}

//����������ȷ���Ϸ�
int get_valid_int_input() {
    int input;
    while (scanf("%d", &input) != 1) {
        while (getchar() != '\n');  // ������뻺����
        printf("��Ч���룬����������: ");
    }
    return input;
}
