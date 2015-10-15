//Link para o problema: http://olimpiada.ic.unicamp.br/pratique/programacao/nivel1/2010f1p1_times
// 100 pontos - 01/09/14
#include <iostream>
#include <string>
using namespace std;

struct Team;

struct Player
{
	string name;
	Player* next;
};

struct Team
{
	Player* head;
};

//Funções

//Adiciona o jogador no time
void push(Team* p, string name)
{
	Player* add = new Player;
	add->name = name;
	add->next = p->head;
	p->head = add;
}

//Imprime o time
void printTeam(Team* p, int x)
{
	cout << "Time " << x << endl;
	Player* curr = p->head;
	while (curr != NULL)
	{
		cout << curr->name << endl;
		curr = curr->next;
	}
	cout << endl;
}

//Ordenador de lista (Selection sort) para os times 
void sortTeam(Team* p)
{
	Player* curr = p->head;
	Player* i;
	Player* j;
    for(i = curr; i!=NULL && i->next != NULL; i=i->next)
    {
        Player* min;
        min = i;
        for(j = i->next; j != NULL ; j=j->next)
        {
            if(j->name < min->name)
                min = j;
        }
        if(min!=i)
        {
            string temp;
            temp = min->name;
            min->name = i->name;
            i->name = temp;
        }
    }
}

//Particionamento necessário para o quicksort
int part(int* skill, string* name, int begin, int end)
{
    int i = begin-1;
    int pivot = skill[end];

    for (int j = begin; j <= end; j++)
    {
        if (skill[j] >= pivot)
        {
            i++;
            //swap skill
            int aux = skill[j];
            skill[j] = skill[i];
            skill[i] = aux;
            //swap name
            string aux2 = name[j];
            name[j] = name[i];
            name[i] = aux2;
        }
    }

    return i;
}

//Quicksort para os vetores que guardam os nomes e o nível de habilidade dos jogadores
void quickSort(int* skill, string* name, int begin, int end)
{
    if (end > begin)
    {
        int pos = part(skill, name, begin, end);
        quickSort(skill, name, begin, pos-1);
        quickSort(skill, name, pos+1, end);
    }
}

int main()
{
	int numbers_players, numbers_teams;
	//Entrada dos tamanhos do vetores
	cin >> numbers_players >> numbers_teams;
	//Vetor de listas
	Team* vecLists[numbers_teams];
	//Vetores com os nomes e skills
	string name[numbers_players];
	int skill[numbers_players];
	

	//Entrada de cada elemento dos vetores
	for (int i = 0; i < numbers_players; i++)
	{
		cin >> name[i] >> skill[i];
	}

	//Ordena simultaneamente em ordem crescente os elementos dos vetores com base no vetor skill
	quickSort(skill, name, 0, numbers_players-1);


	for (int i = 0; i < numbers_teams; i++)
	{
		//Cria uma lista para cada time
		vecLists[i] = new Team;
		vecLists[i]->head = NULL;

		//Aloca cada jogador em seu devido time (lista)
		for (int j = i; j < numbers_players; j = j + numbers_teams)
		{
			push(vecLists[i], name[j]);
		}

		//Ordena a lista em ordem alfabética
		sortTeam(vecLists[i]);
		
		//Imprime os times com os nomes ordenados e jogadores devidamente separados
		printTeam(vecLists[i], i+1);
	}
}