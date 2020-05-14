#include "../libs/Schedule.h"
#include "../libs/ListStudent.h"

static ListStudent listStudent;

#define SIZE_NAME 40
#define SIZE_EMAIL 120
#define SIZE_NAME_DISCIPLINE 80
#define SIZE_PHONES 15

enum OPTIONS {
  INSERT = 1,
  DELETE,
  SEARCH,
  SHOW,
  EXIT
};

static int menu() {
  int option;
  printf("1. Inserir aluno\n");
  printf("2. Excluir aluno\n");
  printf("3. Buscar aluno\n");
  printf("4. Listar alunos\n");
  printf("5. Sair\n");

  printf("Escolha uma opção: ");
  
  // TODO: Validar a escolha
  scanf("%d", &option);

  return option;
}


//Lógica para inserir telefones em um estudante
static void insertPhones(Student student) {
  char phones[SIZE_PHONES];
  int iteration = 0;

  ListPhones listPhones = student_getListPhones(student);

  printf("\n==========Contato==========\n");
  printf("Para finalizar digite \"Parar\"\n");
  
  while(true) {
    
    setbuf(stdin, NULL); // Limpa o buffer

    printf("%d - Number: ", iteration++);
    fgets(phones, SIZE_PHONES, stdin);
    phones[strlen(phones) - 1] = '\0';

    setbuf(stdin, NULL); // Limpa o buffer

    if(strcmp(phones, "Parar") == 0 || strcmp(phones, "parar") == 0)
      break;
    
    listPhones_add(listPhones, phones);

  }
}

//Lógica para inserir disciplinas em um estudante
static void insertDisciplines(Student student) {
  
  int id;
  char name[SIZE_PHONES];
  int iteration = 1;

  ListDiscipline listDiscipline = student_getListDiscipline(student);

  printf("\n==========Disciplinas==========\n");
  printf("Deve inserir pelo menos uma\n");
  
  while(true) {
    
    printf("%d - Disciplina:\n", iteration++);
    printf("Código: ");
    scanf("%d", &id);

    setbuf(stdin, NULL); // Limpa o buffer

    printf("Nome: ");
    fgets(name, SIZE_NAME_DISCIPLINE, stdin);
    name[strlen(name) - 1] = '\0';

    setbuf(stdin, NULL); // Limpa o buffer
    
    Discipline discipline = new_Discipline(id, name);
    listDiscipline_add(listDiscipline, discipline);

    printf("Deseja continuar inserindo? [s/n]");
    fgets(name, SIZE_NAME_DISCIPLINE, stdin);
    name[strlen(name) - 1] = '\0';

    if(strcmp(name, "N") == 0 || strcmp(name, "n") == 0)
      break;

    printf("\n");
  }
}

// Inserção do estudante
static void insertStudent() {

  Student student = NULL;
  int registry = rand();
  char name[SIZE_NAME];
  char email[SIZE_EMAIL];

  // LINUX
  system("clear");
  // system("cls"); Windows

  setbuf(stdin, NULL);

  printf("Inserir novo estudante: \n");
  printf("Número de matricula: %d\n", registry);
  printf("Digite o nome: ");
  fgets(name, SIZE_NAME, stdin);
  name[strlen(name) - 1] = '\0';

  setbuf(stdin, NULL);

  printf("Digite o email: ");
  fgets(email, SIZE_EMAIL, stdin);
  email[strlen(email) - 1] = '\0';
  
  // Instância de estudante
  student = new_Student(registry, name, email);

  listStudent_add(listStudent, student);

  insertPhones(student);
  insertDisciplines(student);
  printf("Inserido com seucesso!\n");
}

void start() {
  
  // Instância a lista
  listStudent = new_ListStudent();
  
  int keep = 1;
  do {
    // LINUX
    system("clear");
    // system("cls"); Windows

    int option = menu();

    switch(option) {
      case EXIT:
        keep = 0;
      break;
      case INSERT:
        insertStudent();
      break;
    }
  } while(keep);
}

void stop() {
  destruct_ListStudent(listStudent);
}