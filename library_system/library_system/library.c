
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define ADMIN_PASSWORD "admin666"
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
void load_books();              //����ͼ����Ϣ
void load_users();              //�����û���Ϣ
void save_books();              //����ͼ����Ϣ
void save_users();              //�����û���Ϣ
void admin_system();            //����Աϵͳ
void user_system();             //�û�ϵͳ
void add_book();                //����鼮
void view_books();              //�鿴�鼮
void borrow_book();             //�����鼮
void return_book();             //�黹�鼮
void delete_book();             //ɾ��ͼ��
void press_to_continue();       //�����ĵȴ��û���������ĺ���
int get_valid_int_input();      //������֤����
void password_admin();          //����Ա������֤����
void exit_project();            //�˳�������
void view_borrowed_books();     //����ѽ�ͼ��
void view_pointed_book();       //����ָ����ŵ�ͼ��


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
        password_admin();
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
    char filepath[] = "D:\\c_work\\users.txt";
    FILE* file = fopen(filepath, "r");
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
        printf("2. �鿴����ͼ��\n");
        printf("3. �鿴�ѽ�ͼ��\n");
        printf("4. ɾ��ͼ��\n");
        printf("5. ����ͼ��\n");
        printf("6. �˳�����\n");
        printf("������ѡ��: \n");
        scanf("%d", &choice);
        switch (choice) {
        case 1: add_book(); break;
        case 2: view_books(); break;
        case 3: view_borrowed_books(); break;
        case 4: delete_book(); break;
        case 5: view_pointed_book(); break;
        case 6: exit_project();
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
        printf("3. ����ͼ��\n");
        printf("4. �˳�����\n");
        printf("������ѡ��: \n");
        scanf("%d", &choice);
        switch (choice) {
        case 1: borrow_book(); break;
        case 2: return_book(); break;
        case 3: view_pointed_book(); break;
        case 4: exit_project();
        default: printf("��Ч����\n"); break;
        }
        press_to_continue();  // �����󰴻س�����
    }
}

//���ͼ��
void add_book() {
    int id;
    printf("������ͼ���ţ�\n");
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
    printf("������������\n");
    fgets(books[book_count].name, 100, stdin);
    books[book_count].name[strcspn(books[book_count].name, "\n")] = '\0'; // ������з�

    printf("���������ߣ�\n");
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
    printf("������Ҫɾ����ͼ����: \n");
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
    printf("�������û� ID��\n");
    user_id = get_valid_int_input();
    printf("����������ĵ�ͼ�� ID��\n");
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
    printf("�������û� ID��\n");
    user_id = get_valid_int_input();
    printf("������黹��ͼ�� ID��\n");
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
        printf("��Ч���룬����������: \n");
    }
    return input;
}

//����Ա������֤����

void password_admin() {
    while(1){
        char password[20];
        printf("���������Ա����\n");
        scanf("%s", &password);
        if (strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("������ȷ�������������Աϵͳ\n");
            admin_system();
            break;
        }
        else {
            printf("�����������������\n");
        }
    }
}

//�˳�����
void exit_project() {
    exit(0);
}

//����ѽ��鼮
void view_borrowed_books() {
    int book_found = 0;
    for (int i = 0; i < book_count; i++) {
        if (books[i].is_borrowed) {
            book_found = 1;
            printf("ͼ���ţ�%d, ͼ������%s, ���ߣ�%s\n",
                books[i].id,
                books[i].name,
                books[i].author);
            for (int j = 0; j < user_count; j++) {
                if (users[j].borrowed_book_id == books[i].id) {
                    printf(" �����ˣ�%s (�û�ID: %d)\n", users[j].name, users[j].id);
                    break;
                }
            }
        }
    }
    // ���û�н�����鼮��������ʾ
    if (!book_found) {
        printf("��ǰû���ѽ�����鼮\n");
    }
}

//���ݱ�Ų鿴ͼ����Ϣ
void view_pointed_book() {
    int book_found = 0;
    int book_id = 0;
    printf("������Ҫ���ҵ��鼮���");
    scanf("%d", &book_id);
    for (int i = 0; i < book_count; i++) {
        if (book_id == books[i].id) {
            book_found = 1;
            printf("ͼ���ţ�%d, ͼ������%s, ���ߣ�%s\n",
                books[i].id,
                books[i].name,
                books[i].author);
        }
    }
    if (!book_found) {
        printf("����û�б������ͼ��");
    }
}
