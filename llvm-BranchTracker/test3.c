#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//add
void Add()
{
	struct data{
		char Product_name[100];
		char Company_name[100];
		char Price[20];
		char Warranty[20];
		char Qty_avai[20];
		char Model_no[40];
	}Item;	
	FILE *fp;
	fp = fopen("automobile_database.txt","a");
	printf("Enter Product name : ");
	scanf("%s", Item.Product_name);
	printf("Enter Company name : ");
	scanf("%s", Item.Company_name);
	printf("Enter Price of the product : ");
	scanf("%s", Item.Price);
	printf("Enter Warranty of the product : ");
	scanf("%s", Item.Warranty);
	printf("Enter number of items available : ");
	scanf("%s", Item.Qty_avai);
	printf("Enter Model no : ");
	scanf("%s", Item.Model_no);
	fprintf(fp, "%s     %s     %s     %s     %s     %s\n", Item.Product_name, Item.Company_name, Item.Price, Item.Warranty, Item.Qty_avai, Item.Model_no);
	fclose(fp);
	printf("\nThe new product is successfully added\n");
}

//delete
struct data
{
    char Product_name[100];
    char Company_name[100];
    char Price[20];
    char Warranty[20];
    char Quantity[20];
    char Model[40];
};
void utl(char s[])/*Upper case to lower case conversion*/
{
    int c=0;
    while(s[c])
    {
        if(s[c]>='A' && s[c]<='Z')
        {
            s[c]=s[c]+32;
        }
        c++;
    }
}
void delete()
{
    FILE*fp;
    FILE*ft;
    int a;
    int i=0;
    int j;
    struct data store;
    struct data temp;
    
    fp=fopen("automobile_database.txt","r");
    if(fp==NULL)
    {
        printf("File not accessed");
        return;
    }
    do
    {
        fscanf(fp,"%s     %s     %s     %s     %s     %s",store.Product_name,store.Company_name,store.Price,store.Warranty,store.Quantity,store.Model);
        i++;
    } 
    while(!feof(fp));
    
    printf("1.To delete a product with specified company name.\n2.To delete products with specified warranty\n0.To quit\n");
    printf("\nEnter a number to perform the operation : ");
    scanf("%d",&a);
    while(1)
    {
        if(a!=1 && a!=0 && a!=2)
        {
            printf("Enter a valid option:");
            scanf("%d",&a);
        }
        else
        {
            break;
        }
    }
   
    fseek(fp,0,SEEK_SET);             
    if(a==1)
    {
        char input1[20];
        char input2[20];
        int k=0;
        while (1)
        {
            printf("\nEnter Product name : ");
            scanf("%s",input1);
            utl(input1);
            printf("Enter Company name : ");
            scanf("%s",input2);
            utl(input2);
            k=0;
            fseek(fp,0,SEEK_SET);
            do
            {
                k++;
                if(k>i)
                {
                    break;
                }
                fscanf(fp,"%s     %s     %s     %s     %s     %s",store.Product_name,store.Company_name,store.Price,store.Warranty,store.Quantity,store.Model);
                strcpy(temp.Product_name,store.Product_name);
                utl(store.Product_name);
                utl(temp.Product_name);
                strcpy(temp.Company_name,store.Company_name);
                utl(temp.Company_name);
                utl(store.Company_name);
            }
            while(strcmp(input1,temp.Product_name)!=0 || strcmp(input2,temp.Company_name)!=0 ); 
            if(strcmp(input1,store.Product_name)==0 && strcmp(input2,store.Company_name)==0)
            {
                printf("\nThe specified item is deleted successfully.\n");
                break;
            }
            if(k>i)
            {
                printf("\nUnable to find the company or the product you entered\n");
                printf("Please enter a valid company and product name\n");
            }
                
        }
        fseek(fp,0,SEEK_SET);   
        ft=fopen("temp.txt","a");
        for(j=0;(j<i-1) && (!feof(fp));++j)
        {
            fscanf(fp,"%s     %s     %s     %s     %s     %s",store.Product_name,store.Company_name,store.Price,store.Warranty,store.Quantity,store.Model);
            strcpy(temp.Company_name,store.Company_name);
            utl(temp.Company_name);
            if(strcmp(input2,temp.Company_name)!=0)
            {
                fprintf(ft,"%s     %s     %s     %s     %s     %s\n",store.Product_name,store.Company_name,store.Price,store.Warranty,store.Quantity,store.Model);
            }
        }
    }
    fseek(fp,0,SEEK_SET);             
    if(a==2)
    {
        char input3[20];
        int k=0;
        while (1)
        {
            printf("Enter Warranty(in years) : ");
            scanf("%s",input3);
            k=0;
            fseek(fp,0,SEEK_SET);
            do
            {
                k++;
                if(k>i)
                {
                    break;
                }
                fscanf(fp,"%s     %s     %s     %s     %s     %s",store.Product_name,store.Company_name,store.Price,store.Warranty,store.Quantity,store.Model);
            }
            while(strcmp(input3,store.Warranty)!=0); 
            if(strcmp(input3,store.Warranty)==0)
            {
                printf("\nThe products with specified warranty have been successfully deleted.\n");
                break;
            }
            if(k>i)
            {
                printf("No product found with the given warranty\nEnter a");
            } 
        }
        fseek(fp,0,SEEK_SET);   
        ft=fopen("temp.txt","a");
        for(j=0;(j<i-1) && (!feof(fp));++j)
        {
            fscanf(fp,"%s     %s     %s     %s     %s     %s",store.Product_name,store.Company_name,store.Price,store.Warranty,store.Quantity,store.Model);
            //if((strcmp(input1,store.Product_name)!=0) && (strcmp(input2,store.Company_name)!=0))
            if(strcmp(input3,store.Warranty)!=0)
            {
                fprintf(ft,"%s     %s     %s     %s     %s     %s\n",store.Product_name,store.Company_name,store.Price,store.Warranty,store.Quantity,store.Model);
            }
        }
    }
    if(a==0)
    {
        return;
    }
    fclose(fp);
    fclose(ft);
    
    remove("automobile_database.txt");
    rename("temp.txt","automobile_database.txt");
    
}
//search
#include<stdio.h>
#include<string.h>
struct Item
{
  char Product_name[100];
  char Company_name[100];
 	char Price[20];
  char Warranty[20];
  char Quantity_available[20];
  char Model_number[70];
};
	void upper_con(char *str)
	{
		int i;
		char *ch;
		for(i=0; ((ch = (str + i))) && *ch != '\0'; i++)
		{
			if(*ch >= 97 && *ch <= 122)
			{
			*ch -= 32;
			}
		}
	}			
	void search()
	{
		char ch,product[100];
		int count=0,count1=0;
		printf("Enter the product : ");
		scanf("%s",product);
		FILE *fp;
		fp=fopen("automobile_database.txt","r");
		do
		{
			while((ch=fgetc(fp))!='\n'&&ch!=EOF)
			{
			  continue;
			}
			count++;
		}
		while(ch=='\n');
		fclose(fp);
		struct Item array[count];
		fp=fopen("automobile_database.txt","r");
		for(int i=0;i<count;i++)
		{
 			fscanf(fp,"%s %s %s %s %s %s",array[i].Product_name,array[i].Company_name,array[i].Price,array[i].Warranty,array[i].Quantity_available,array[i].Model_number);
		}
		for (int i=0;i<count;i++)
		{
 			upper_con(product);
 			upper_con(array[i].Product_name);
 			if (strcmp(array[i].Product_name,product)==0) 
  		{
   			count1=10;
   			printf("\nProduct_name : %s\nCompany_name : %s\nPrice : %s\nWarranty : %s\nQuantity : %s\nModel_number :  %s\n",array[i].Product_name,array[i].Company_name,array[i].Price,array[i].Warranty,array[i].Quantity_available,array[i].Model_number);
  		}
		}
		if(count1==0)
		{
			printf("\nSORRY!!..specified product is unavailable.\n");
		}
		fclose(fp);
	}

//quantity
void quantity()
{
	struct inventory
	{
		char Product_name[25];
		char Company_name[25];
		char Price[10];
		char Warranty[10];
		int Qty_avai;
		char Model_no[20];
	} Items[100];
	FILE *fp;
	fp = fopen("automobile_database.txt","r");
	int i=0,j;
	int count=0;
	char ch;
	char *tem;
	while((ch=fgetc(fp))!=EOF)
	{
		fseek(fp,-1,SEEK_CUR);
		fscanf(fp,"%s %s %s %s %d %s", Items[i].Product_name, Items[i].Company_name, Items[i].Price, (Items[i].Warranty), &(Items[i].Qty_avai), Items[i].Model_no);
		fgets(tem, 0, fp);
		i++;
	}
	int n;
	while(1)
	{
		printf("\nEnter the value of the quantity:");
		scanf("%d",&n);
		printf("\nThe products and their companies with quantity less than %d:\n",n);
		for(j=0;j<i-1;j++)
		{
			
			if(n>(Items[j].Qty_avai))
			{
				count++;
				printf("\n%d.Product : %s\nCompany Name : %s\nQuantity : %d\n",count,Items[j].Product_name,Items[j].Company_name,Items[j].Qty_avai);
			}	
		}
		if(count<1)
		{
			printf("\nSorry!There are no products less than the quantity %d.\nTry Again\n",n);
		}
		else
		{
			break;
		}
	}
	fclose(fp);
}
//sort
// void Upper_con(char *str);
// void Sort_Price()
// {
// 	struct inventory{
// 		char Product_name[100];
// 		char Company_name[100];
// 		int Price;
// 		char Warranty[20];
// 		char Qty_avai[20];
// 		char Model_no[40];
// 	};
// 	struct inventory Items[200];
// 	struct inventory Pro_type[20];
// 	struct inventory temp;
// 	char tem_str1[20], tem_str2[20], Product[20];
// 	int i, ch, opt;
// 	int Low_lim, Upp_lim;
// 	char *tem;
// 	printf("Enter Product name : ");
// 	scanf("%s", Product);
// 	FILE *fp;
// 	fp = fopen("automobile_database.txt","r");
// 	for(i=0; (ch = fgetc(fp)) != EOF; i++)
// 	{
// 		fseek(fp, -1, SEEK_CUR);
// 		fscanf(fp, "%s     %s     %d     %s     %s     %s", Items[i].Product_name, Items[i].Company_name, &(Items[i].Price), Items[i].Warranty, Items[i].Qty_avai, Items[i].Model_no);
// 		fgets(tem, 0, fp); 
// 	}
// 	int k = i;
// 	int count=0, j=0, r=0, index[20];
// 	for(i=0; i<k; i++)
// 	{
// 		strcpy(tem_str1, Items[i].Product_name);
// 		Upper_con(Product);
// 		Upper_con(tem_str1);
// 		if(strcmp(Product, tem_str1) == 0)
// 		{
// 			count = 1;
// 			Pro_type[j] = Items[i];
// 			j++;									
// 		}
// 	}		
// 	if(count == 0)
// 	{
// 		printf("SORRY!!!\nPRODUCT IS UNAVAILABLE !!!");
// 	}
// 	else
// 	{
// 		int p,q,min;
// 		for(p=0; p<j-1; p++)
// 		{
// 			r++;
// 			min = p;
// 			for(q=p+1; q<j; q++)
// 			{
// 				if(Pro_type[q].Price < Pro_type[min].Price)
// 				{
// 					min = q;
// 				}
// 			}
// 			temp = Pro_type[min];
// 			Pro_type[min] = Pro_type[p];
// 			Pro_type[p] = temp;	
// 		}
		 
// 		printf("1: Display sorted price list for the entered product.\n2: Display the products having the price in the specified range.\n");
// 		printf("Choose your option : ");	
// 		scanf("%d", &opt); 
// 		if(opt == 1)
// 		{
// 			for(i=0; i<j; i++)
// 			{
// 	 			printf("\nProduct name : %s\n", Pro_type[i].Product_name);
//         			printf("Company name : %s\n", Pro_type[i].Company_name);
//           			printf("Price : Rs.%d/-\n",Pro_type[i].Price);
//          			printf("Warranty : %s\n", Pro_type[i].Warranty);
//          			printf("Qty available : %s\n", Pro_type[i].Qty_avai);
//          			printf("Model number : %s\n", Pro_type[i].Model_no);
// 			}
// 		}
// 		else if(opt == 2)
// 		{
// 			int tem = 0;
// 			printf("Enter Lower Limit and Upper limit of the range\n");
// 			printf("Enter Lower Limit(in Rs.) : ");
// 			scanf("%d", &Low_lim);
// 			printf("Enter Upper Limit(in Rs.) : ");
// 			scanf("%d", &Upp_lim);
// 			for(i=0; i<j; i++)
// 			{
// 				if(Pro_type[i].Price >= Low_lim && Pro_type[i].Price <= Upp_lim)
// 				{
// 					tem = 1;
// 					printf("\nProduct name : %s\n", Pro_type[i].Product_name);
//                 			printf("Company name : %s\n", Pro_type[i].Company_name);
//                 			printf("Price : Rs.%d/-\n",Pro_type[i].Price);
//                 			printf("Warranty : %s\n", Pro_type[i].Warranty);
//                 			printf("Qty available : %s\n", Pro_type[i].Qty_avai);
//                  			printf("Model number : %s\n", Pro_type[i].Model_no);
// 				}
// 			}
// 			if(tem == 0)
// 			{
// 				printf("\nThere are no products with the price in between given range.");
// 			}
// 		}
// 	}
// }
//other
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct pilha{
    int i;
    struct pilha *prox;
}Pilha;



bool pop(Pilha **topo);
void push(Pilha **p, int vert);
Pilha* inicializa();
int verifica(Pilha *p, int vertice);
void printPilha(Pilha *p);
/*
Nós representam as cidades
Arestas representam as rodovias
*/


#define MAX_CIDADES 20

// Estrutura que armazena os caminhos de ciclos e suas proporções
typedef struct caminho{
	Pilha *p; //Vertices do caminho
	double prop;// Proporcao do caminho
	struct caminho *prox;
}Caminho;


// Funções Lista

// Exibe o caminho do ciclo e sua respectiva proporção
int printCaminho(Caminho *c){
	int count=0;
	for(Caminho *i = c; i != NULL; i = i->prox){
		printPilha(i->p);
		printf("\n%.2lf\n\n",i->prop);
		count++;
	}
	return count;
}

// Insere o registro de um ciclo
void insere_caminho(Caminho **L, Pilha *no, double proporcao){
	Caminho *novo = calloc(1,sizeof(Caminho));
	if(!novo){
		printf("\nErro na alocação do caminho");
		exit(1);
	}
	novo->p = inicializa();
	for(Pilha *aux = no; aux != NULL; aux = aux->prox) // Copia a pilha (inversamente) para o caminho
		push(&novo->p, aux->i);
	novo->prop = proporcao;
	novo->prox = *L;
	*L = novo;
}

// Remoção dos nós da lista e desalocação dos mesmos
void remove_caminhos(Caminho **L){
	Caminho *aux = *L, *aux2;
	while(aux != NULL){
		while(pop(&aux->p)) // Desaloca todos os nós da pilha
			continue;
		aux2 = aux->prox;
		free(aux); // Para desalocar um nó da lista
		aux = aux2;
	}
	*L = NULL;
}

// Desaloca as listas internas e zera a quantidade de caminhos de cada vértice da matriz
void zera_matriz(double MA[][20], int tam){
	for(int i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			MA[i][j] = -1.0;
		}
	}
}

// Retorna a melhor proporcao dentre os ciclos
// Calcula a quantidade de ciclos
double melhor_proporcao(Caminho *caminhos, int *ciclos){
	double melhorProp = 0.0;
	*ciclos = 0;
	while(caminhos){
		melhorProp = melhorProp < caminhos->prop ? caminhos->prop : melhorProp;
		(*ciclos)++;
		caminhos = caminhos->prox;
	}
	return melhorProp;
}

// Exibe os resultados e grava em um arquivo txt
bool resultados(Caminho *caminhos, double P_arq, int n_caso){
	FILE *resultado;
	int res, n_ciclos;
	double melhorProp = melhor_proporcao(caminhos,&n_ciclos);


	if(melhorProp >= P_arq){
		printf("\n\nCaso número %2d\n%3d Rotas cíclicas\nProporção de lucro desejada %.2lf\nMelhor proporção de lucro encontrada %.2lf\nRelação lucro encontrado com o esperado %.2lf\n", n_caso,n_ciclos, P_arq,melhorProp, melhorProp / P_arq);
		resultado = fopen("resultados.txt","a");
		if(!resultado){
			printf("Falha ao abrir/criar o arquivo");
			exit(1);
		}


		res = fprintf(resultado,"\n\nCaso número %2d\n%3d Rotas cíclicas\nProporção de lucro desejada %.2lf\nMelhor proporção de lucro encontrada %.2lf\nRelação lucro encontrado com o esperado %.2lf\n", n_caso,n_ciclos, P_arq,melhorProp, melhorProp / P_arq);
		if(res == EOF){
			printf("\n\nErro na gravação dos dados no arquivo\n");
			exit(1);
		}
		fclose(resultado);
		return true;
	}else{
		printf("\n\nCaso número %2d\nSem rotas cíclicas encontradas para a proporção de lucro desejada! (P=%.2lf) :(\n",n_caso,P_arq);
		resultado = fopen("resultados.txt","a");
		if(!resultado){
			printf("Falha ao abrir/criar o arquivo");
			exit(1);
		}

		int res = fprintf(resultado,"\n\nCaso número %2d\nSem rotas cíclicas encontradas para a proporção de lucro desejada! (P=%.2lf) :(\n",n_caso,P_arq);
		if(res == EOF){
			printf("\n\nErro na gravação dos dados no arquivo\n");
			exit(1);
		}
		fclose(resultado);
		return false;
	}

}

// Exibe a matriz de adjacência para testes
void print_matriz(double MA[][MAX_CIDADES], int tam){
	printf("\n\n     ");
	for(int i = 0; i < tam; i++)
		printf("  %2d  ", i);
	printf("\n");
	for(int i = 0; i < tam; i++){
		printf("%2d   ", i);
		for(int j = 0; j < tam; j++)
			printf("%.2lf ", MA[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

// Pode retornar se houve ciclo / custo do ciclo / vetor com os vértices do ciclo
void encontra_ciclos(double MA[][MAX_CIDADES], int tam,Caminho **listaCaminhos){
	// 1 Inicialize L como uma pilha vazia e uma estrutura para armazenar os caminhos
	int i,j,k/*,cont = 1,cont2=1,c*/;
	double propP = 0.0;
	Pilha *topo = inicializa();
	// 2 Insira o nó atual na pilha e verifique se o nó é igual ao início da pilha, se for igual, há um ciclo fechado (guarda o caminho*** e verifica a proporção), senão verifica se algum outro nó da pilha é igual, se for igual, ciclo aberto, retira o nó (descontar a proporção) e parte para outro, senão continua o algoritmo
	for(i = 0; i < tam; i++){ // Loop dos vértices
		push(&topo, i);
		/*printf("push %d",i);
		printPilha(topo);
		printf("\n\nInicia no V%d\n\n",i);
		cont2=0;
		c=0;*/
		k = i;
		j = 0;
		propP = 0.0;

		while(topo != NULL){
			for(; j < tam; j++){ // 3 Dentro do nó, verifique se há algum arco de saída, se sim, vá para o passo 4, senão pule para o passo 5
				if(MA[k][j] > -1.0){ // 4 Escolha um arco de saída e siga para obter o próximo nó atual

					push(&topo, j);
					/*
					// DEBUG
					printf("push  %d",j);
					printPilha(topo);
					printf("\n\n%d Proporcao= propAtual=%.2lf + MA=%.2lf\n",cont2,propP,MA[k][j]);
					printPilha(topo);
					cont2++; */

					// Verifica o vértice inserido na pilha se existe
					switch(verifica(topo,j)){
						case 1: // Ciclo fechado: verifica se existe o caminho, se não existir salvar caminho, se existir, retira o nó da pilha

							/*
							// DEBUG
							printf("\nCiclo fechado #%d________\n\n",cont);
							cont++;
							printPilha(topo);
							printf("\n_____________________________________\n\n");
							printf("\nLista de caminhos #%d_____________________________________\n\n",cont-1);
							printCaminho(*listaCaminhos);
							printf("\n_____________________________________\n\n"); */



							propP += MA[k][j];
							insere_caminho(&(*listaCaminhos),topo,propP); //Adiciona na lista o caminho
							// DEBUG
							// printf("Ciclo inserido");

							// Se existe, retira o vértice e continua
							propP -= MA[k][j];
							j = topo->i;
							pop(&topo);
							if(!topo) // Caso de loop no vértice
								break;
							k = topo->i;
							break;
						case -1: // Ciclo aberto (caminho com o ciclo + vértices iniciais), retira o nó que acabou de ser inserido, se for a base o algoritmo acaba as interações para este vértice

							/*
							// DEBUG
							printf("\n\n__________Ciclo aberto encontrado___________\n\n");
							printf("\n\nCiclo aberto #%d________\n\n",cont2);
							cont2++;
							printPilha(topo);
							printf("\n____________________________________\n\n"); */

							j = topo->i;
							pop(&topo);
							k = topo->i;
							break;
						case 0: // Não houve repetições, continua normalmente
							propP += MA[k][j];
							k = j;
							j = -1;
							break;
					}
					if(!topo) // Caso de loop no vértice
						break;
				}
			}
			if(!topo) // Caso de loop no vértice
				break;
			while(j == tam){ // Caso o novo topo da pilha seja o último vértice da matriz, o j não iria alcançar o for acima, executaria no máximo duas vezes: O(1)
				j = k;
				pop(&topo); // O final foi alcançado, remova o nó e volte para o anterior, se for o nó inicial não há ciclos e o algoritmo terminará
				if(!topo)
					break;
				k = topo->i;
				propP -= MA[k][j];
				j++;
			}
		}
	}
}


//main
int main()
{
	printf("WELCOME TO C AUTOMOBILE INVENTORY MANGEMENT DATABASE!\n\n");
	while(1)
	{
		printf("Main Menu:\n");
		printf("----------\n");
		printf("1.Display all the Products with company names and their parameters.\n");
		printf("2.Display the parameters of the specified Product.(search)\n");
		printf("3.Display the items with prices of the specified product in sorted order or in a given range.\n");
		printf("4.Display the products with warranty less than or greater than or equal to given value or in a given range.\n");
		printf("5.Display the products with quantity less than given value.\n");
		printf("6.Add an item.\n");
		printf("7.Delete an item or items with specified warranty.\n");
		printf("8.Modify a parameter.\n");
		printf("9.Quit the program.\n");
		int n;
		printf("\nChoose a number to perform the corresponding action : ");
		scanf("%d",&n);
		FILE *fp;
		char m;
		switch(n)
		{
			case 1:
				printf("\nYou have chosen to view all the parameters.\n\n");
				fp = fopen("automobile_database.txt","r");
				view(fp);
				fclose(fp);
				break;
			case 2:
				printf("\nYou have chosen to search a specified item.\n");
				search();
				break;
			case 3:
				printf("\nYou have chosen to display the items with prices of a specified product in sorted order or in a given range.\n");
				Sort_Price();
				break;
			case 4:
				printf("\nYou have chosen to display the products with warranty less than or greater than or equal to given value or in a given range.\n");
				warranty();
				break;
			case 5:
				printf("\nYou have chosen to display the products with quantity less than given value.\n");
				quantity();
				break;
			case 6:
				printf("\nYou have chosen to add an item.\n");
				Add();
				break;
			case 7:
				printf("\nYou have chosen to delete an item or items of  specified warranty.\n");
				delete();
				break;
			case 8:
				printf("\nYou have chosen to modify a parameter\n");
				modify();
				break;
			case 9:
				printf("\nProgram is terminated as you have chosen to quit.\n");
				return 0;
			default:
				printf("Enter Valid Option.\n");

		};
		printf("\n");
		printf("\n");
	}

	return 0;
}