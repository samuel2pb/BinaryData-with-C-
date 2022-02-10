#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

struct Cadastro 
{
	int pront;
	int idade, telefone;
	char nome[50], curso[10], email[50], sexo;
	float nota1 , nota2; 	
};

Cadastro cad;  
FILE *arq; 

void Mostra(int*a, float*c)
{
		
	printf(" Prontuario:%d\n", *a);
	printf(" Media: %.2f\n", *c);
	printf("\n");
	
}

int FindPosicao(int a)
{
	int cont=0, p=0;
	fseek(arq, 0,SEEK_SET);    //Posiciona o cursor do fluxo no inicio do arquivo.
	while(!feof(arq))
	{
		if(fread(&cad , sizeof(cad), 1, arq)==1)
		{
		if(a == cad.pront)
		p = cont+1;    //posição numérica da estrutura a ser modificada.
		}
		cont++;
	}
		return(p);
}

void Altera()
{
	int pront=0, telefone=0, idade, posicao=0;
	char nome[50], curso[10], email[50], sexo;
	float nota1=0 , nota2=0;

	printf(" ====>Forneca o prontuario ao qual serao aplicadas alteracoes<====\n");
	scanf("%d", &pront); fflush(stdin); 
	arq = fopen("Alunos.dat", "r+b");
	if(arq == NULL)
	printf(" Erro na abertura do arquivo!\n");
	else
		posicao = FindPosicao(pront);

	fseek(arq, sizeof(cad)*(posicao-1),SEEK_SET); //posiciona o cursor do fluxo na estrutura a ser modificada pelo arquivo.
	fread(&cad,sizeof cad , 1 , arq); 
	strcpy(nome,cad.nome);
	strcpy(curso,cad.curso);
	strcpy(email, cad.email);
	telefone = cad.telefone;
	nota1 = cad.nota1; nota2 = cad.nota2 ;
	sexo = cad.sexo;
	idade = cad.idade;
	pront = cad.pront;
	
	if(posicao != 0)
	{
	int x , y;
	printf(" ====Selecione a opcao desejada<====\n");
	printf(" ==>[1]- Alterar email\n");
	printf(" ==>[2]- Alterar telefone\n");
	printf(" ==>[3]- Alterar Nota 1\n");
	printf(" ==>[4]- Alterar Nota 2\n");
	scanf("%d",&y); 
	switch(y) 
		{ 
		case 1 : 	
		printf("==>Digite o email:\n");
		scanf("%s", cad.email);
		strcpy(cad.nome,nome);
		strcpy(cad.curso,curso);
		cad.telefone = telefone;
		cad.nota1 = nota1; cad.nota2 = nota2;
		cad.sexo = sexo;
		cad.idade = idade;
		cad.pront = pront;
		break;
		
		case 2 : 
		printf("==>Digite a telefone :\n");
		scanf("%d", &cad.telefone); 
		strcpy(cad.nome,nome);
		strcpy(cad.email, email);
		strcpy(cad.curso,curso);
		cad.nota1 = nota1; cad.nota2 = nota2;
		cad.sexo = sexo;
		cad.idade = idade;
		cad.pront = pront;
		break;
		
		case 3 : 
		printf("==>Digite a Nota 1 :\n");
		scanf("%f", &cad.nota1);
		strcpy(cad.nome,nome);
		cad.telefone = telefone;
		strcpy(cad.email, email);
		strcpy(cad.curso,curso);
		cad.nota2 = nota2;
		cad.sexo = sexo;
		cad.idade = idade;
		cad.pront = pront;	
		break;
		
		case 4 : 
		printf("==>Digite a Nota 2:\n");
		scanf("%f", &cad.nota2);
		strcpy(cad.nome,nome);
		cad.telefone = telefone;
		strcpy(cad.email, email);
		strcpy(cad.curso,curso);
		cad.nota1 = nota1;
		cad.sexo = sexo;
		cad.idade = idade;
		cad.pront = pront;	
		break;			
		}
		
		fseek(arq, sizeof(cad)*(posicao-1),SEEK_SET); //posiciona novamente o cursor de fluxo sobre a estrutura a ser modificada
		x = fwrite(&cad , sizeof(cad), 1, arq); //realiza a gravação.
		if(x==1)	
			printf("=====>Gravacao realizada!<=====\n");
		else
			printf("\n====>Erro na gravacao<==== !\n");
	}
	fclose(arq);
}

void criar()
{ 
	char c;
	printf(" ==>Deseja realmente iniciar um novo arquivo ?<==\n");
	printf("\n digite [S] para sim [N]para nao\n");
	c = getch();
	if(c == 's'|| c == 'S')
	{
		arq = fopen("Alunos.dat", "wb");
		printf(" ===>Um novo arquivo foi aberto !<===");
	}
	fclose(arq);		
}

void Ctodos()
{
	float media;
	arq	= fopen("Alunos.dat", "rb");
	while(fread(&cad , sizeof(cad), 1, arq))
		{
			media = (cad.nota1 + cad.nota2)/2;
			printf(" Nome: %s\n", cad.nome); 
			Mostra(&cad.pront,&media);
		}
	fclose(arq);
}

void CpC()
{
	char curso[10];
	printf(" Digite o Curso desejado \n");
	printf(" [ECA]; [BCC]; [LTS]; [MAT];\n ");
	scanf("%s",curso);
	arq	= fopen("Alunos.dat", "rb");
	while(fread(&cad , sizeof(cad), 1, arq))
	{
		if(strcmp(curso, cad.curso) == 0 )
		{
			printf(" Aluno: %s \n ", cad.nome );
			printf("\n");
		}
	}
	fclose(arq);
}

void Caprovados()
{
	float media;
	arq	= fopen("Alunos.dat", "rb");
	printf(" ====>Alunos aprovados <==== \n " ); 
	while(fread(&cad , sizeof(cad), 1, arq) ) 
	{
		media = (cad.nota1 + cad.nota2)/2;
		if(media>=6)
		{
			printf(" Nome: %s\n", cad.nome); 
			Mostra(&cad.pront,&media);
		}	
	}
	fclose(arq);
}

void Creprovados()
{
	float media;
	arq	= fopen("Alunos.dat", "rb");
	printf("====>Alunos reprovados<==== \n " ); 
	while(fread(&cad , sizeof(cad), 1, arq))
	{
		media = (cad.nota1 + cad.nota2)/2;
		if(media<4)
		{
			printf(" Nome: %s\n", cad.nome); 
			Mostra(&cad.pront,&media);
		}
	}
	fclose(arq);
}

void Cexame()
{
	float media;
	arq	= fopen("Alunos.dat", "rb");
	printf("====>Alunos de Exame<==== \n " ); 
	while(fread(&cad , sizeof(cad), 1, arq))
	{
		media = (cad.nota1 + cad.nota2)/2;
		if(media<6&&media>=4)
		{
			printf(" Nome: %s\n", cad.nome); 
			Mostra(&cad.pront,&media);
		}
	}	
	fclose(arq);
}

main()
{
	int x=0, ctrl = 1,  z , pront=0; 
	char c;
	do {
		printf(" =====>Digite a opcao desejada<=====\n\n");
		printf(" [1]---Criar arquivo\n");
		printf(" [2]---Incluir alunos\n");
		printf(" [3]---Consultar todos os alunos\n");
		printf(" [4]---Consultar alunos por curso\n");
		printf(" [5]---Consultar alunos aprovados\n");
		printf(" [6]---Consultar alunos reprovados\n");
		printf(" [7]---Consultar alunos de exame\n");
		printf(" [8]---Alterar cadastro\n");
		printf(" [9]---Finalizar o programa\n");
		scanf("%d", &x);
		printf("\n");
		system("cls");
		switch(x)
		{
		
			case 1 : 
			
			printf(" ==>Deseja realmente iniciar um novo arquivo ?<==\n");
			printf("\n digite [S] para sim [N]para nao\n");
			c = getch();
			if(c == 's'|| c == 'S')
			{
				arq = fopen("Alunos.dat", "wb");
				printf(" ===>Um novo arquivo foi aberto !<===");
			}
			fclose(arq);
			system("cls");
			break;
		
			case 2 : 
			 
			arq = fopen("Alunos.dat", "a+b");
			if(arq == NULL)
			printf(" Erro na abertura do arquivo!\n");
			else
			{
				printf(" Atribua um prontuario:");
				scanf("%d",&pront); fflush(stdin);
				while(!feof(arq))
				{
				fread(&cad , sizeof(cad), 1, arq);
				if(pront == cad.pront )
					{
				printf(" Nao pode haver prontuarios iguais!");
				exit(1);
					} 
				}
			if(pront!=0)
			{
				cad.pront = pront;
				printf(" Digite o nome do aluno:\n");
				scanf("%s", cad.nome);
				printf(" Digite a idade do aluno:\n");
				scanf("%d", &cad.idade);
				printf(" Sexo do aluno (F)ou (M):\n");
				cad.sexo = getche();
				printf("\n");
				printf(" Digite o Curso [BCC],[ECA],[LTS],[MAT] :\n");
				scanf("%s",cad.curso);
				printf(" Digite a primeira nota:\n");
				scanf("%f", &cad.nota1);
				printf(" Digite a segunda nota:\n");
				scanf("%f", &cad.nota2);
				printf(" Digite o Telefone do aluno:\n");
				scanf("%d", &cad.telefone); 
				printf(" Digite o email do aluno:\n");
				scanf("%s", cad.email);
				z = fwrite(&cad , sizeof(cad), 1, arq);
				if(z==1)	
					printf("=====>Gravacao realizada!<=====\n");
				else
					printf("\n====>Erro na gravacao<==== !\n");
			}
		}
			fclose(arq);
			printf("\n");
			break;
		
			case 3 : 
			Ctodos();
			printf("\n");
			break;
		
			case 4 : 
			CpC();
			printf("\n");
			break; 
		
			case 5 : 
			Caprovados();
			printf("\n");
			break;
		
			case 6 : 
			Creprovados();
			printf("\n");
			break;
		
			case 7 : 
			Cexame();
			printf("\n");
			break;
		
			case 8 :
			Altera();
			break;
		
			case 9 : 
			printf(" O programa esta sendo finalizado\n");
			ctrl = 0;
			break;
		}

	}while(ctrl!=0);
	exit(1);
}
