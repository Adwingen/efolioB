#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include <math.h>

#define MAXSTR 1024

//******ESTRUTURAS DE DADOS ******//

//********************************//

typedef struct Satellite
{
    char nome[MAXSTR];
    float distancia;

    struct Satellite* pNextSatellite;

} StructSatellite;

typedef struct Planeta
{
    char nome[MAXSTR];
    float distancia;

    struct Planeta* pNextPlanet;
    StructSatellite* pFirstSattelite;

} StructPlaneta;

typedef struct Estrela
{
    char nomeEstrela[MAXSTR];

    StructPlaneta* pFirstPlanet;

} StructEstrela;

typedef struct CaminhoParaEstacao
{
    StructEstrela* pStar;
    StructPlaneta* pPlanet;
    StructSatellite* pSatelitte;

} StructCaminhoParaEstacao;

typedef struct PontoRota
{
    char nomeBody[256];
    struct PontoRota* pNextPonto;

} StructPontoRota;

typedef struct DistanciaViagem
{
    int distancia;
    struct DistanciaViagem* pNextDistancia;

} StructDistanciaViagem;

typedef struct Itenerario
{
    // Origem
    StructCaminhoParaEstacao* pOrigem;

    // Destino
    StructCaminhoParaEstacao* pDestino;

    // Lista do pontos da rota
    StructPontoRota* pPontos;

    // Distancias entre pontos da rota
    StructDistanciaViagem* pDistancias;

} StructItenerario;


//******FUNCOES E PROCEDIMENTOS ******//

//************************************//


StructEstrela* createStart(char* nomeStar)
{
    StructEstrela* pStar = (StructEstrela*)malloc(sizeof(StructEstrela));

    // Mete o texto
    strcpy(pStar->nomeEstrela, nomeStar);

    // Inicializa o pointer para os planetas
    pStar->pFirstPlanet = NULL;

    return pStar;
}

void CriarPlaneta(StructEstrela* pStar, char* nome, float distancia)
{
    // Criar o elemento

    StructPlaneta* pNewPlanet = (StructPlaneta*)malloc(sizeof(StructPlaneta));
    strcpy(pNewPlanet->nome, nome);
    pNewPlanet->distancia = distancia;
    pNewPlanet->pNextPlanet = NULL;
    pNewPlanet->pFirstSattelite = NULL;

    // Ver se � o primeiro planeta
    if (pStar->pFirstPlanet == NULL)
    {
        pStar->pFirstPlanet = pNewPlanet;
    }
    else //tem mais planetas
    {
        StructPlaneta* pPlanet = pStar->pFirstPlanet;
        while (pPlanet->pNextPlanet)//percorre a lista
        {
            pPlanet = pPlanet->pNextPlanet;
        }

        // ultimo planeta
        // anexar o novo elemento � lista
        pPlanet->pNextPlanet = pNewPlanet;
    }
}

void CriarSatelite(StructEstrela* pStar, char* nome, float distancia)
{
    // Criar o elemento
    StructSatellite* pNewSatellite = (StructSatellite*)malloc(sizeof(StructSatellite));
    strcpy(pNewSatellite->nome, nome);
    pNewSatellite->distancia = distancia;
    pNewSatellite->pNextSatellite = NULL;

    // Ver onde o vamos colocar
    // Localizar o �ltimo planeta
    StructPlaneta* pPlanet = pStar->pFirstPlanet;
    while (pPlanet->pNextPlanet)
    {
        pPlanet = pPlanet->pNextPlanet;
    }

    // Se o planeta ainda n�o tiver satelites, este ser� o primeiro
    if (pPlanet->pFirstSattelite == NULL)
    {
        pPlanet->pFirstSattelite = pNewSatellite;
    }
    else
    {
        // Caso haja mais satelites, encontrar o �ltimo
        StructSatellite* pSatellite = pPlanet->pFirstSattelite;
        while (pSatellite->pNextSatellite != NULL)
        {
            pSatellite = pSatellite->pNextSatellite;
        }

        // Fazer append na lista
        pSatellite->pNextSatellite = pNewSatellite;

    }


}

// FUNC�ES PARA ORDENA��O

// Estas 4 fun��es 'compare by' t�m como �nico objectivo receber 2 objectos
// e retornar um valor que indica se devem ser trocados ou n�o. Eles v�o ser
// usados como argumentos nas fun��es sortPlanetsByCriteria e
// sortSattelitesByCriteria. Estas 2 fun��es sabem ordenar listas (uma sabe
// ordenar planetas e a outra sabe ordenar sat�lites), mas n�o querem saber
// qual � o crit�rio. O que elas recebem � uma fun��o que faz a compara��o
// por elas. Mesmo que no futuro, fosse necess�rio um novo crit�rio para a
// ordena��o, a �nica coisa a fazer, seria criar uma fun��o de compara��o nova
// semelhante a estas 'compareBy' e providenciar � respectiva fun��o de sort

int compareByNamePlanet(StructPlaneta* planetA, StructPlaneta* planetB)
{
    return strcmp(planetA->nome, planetB->nome) > 0;
}

int compareByNameSatellite(StructSatellite* satelliteA, StructSatellite* satelliteB)
{
    return strcmp(satelliteA->nome, satelliteB->nome) > 0;
}

int compareByDistancePlanet(StructPlaneta* planetA, StructPlaneta* planetB)
{
    return planetA->distancia > planetB->distancia;
}

int compareByDistanceSatellite(StructSatellite* satelliteA, StructSatellite* satelliteB)
{
    return satelliteA->distancia > satelliteB->distancia;
}

// Estas duas fun��es sabem fazer a troca dos conte�dos entre estruturas.
// Visto termos 2 tipos de estruturas, temos de ter 2 fun��es que saibam trocar
// os conte�dos tanto de planetas como de sat�lites.
// Percebi que o exemplo que dei provocou alguma confus�o com o membro 'data'.
// Ora, nesse exemplo, o membro 'data' nada mais � que um exemplo para algo que
// 'mora' dentro de cada n�. No nosso caso n�s j� temos definido o que existe dentro
// de cada n�. No nosso caso, a nossa 'data' s�o os nomes dos objectos, dist�ncias, etc.
// N�o � necess�rio adicionar mais nada �s nossas estruturas.
// Estas fun��es limitam-se ent�o a trocar o conte�do de um objecto para o outro.

void swapPlanetas(StructPlaneta* a, StructPlaneta* b)
{
    // Trocar o nome
    char tempName[256];
    strcpy(tempName, a->nome);
    strcpy(a->nome, b->nome);
    strcpy(b->nome, tempName);

    // Trocar a distancia
    float tempDistancia = a->distancia;
    a->distancia = b->distancia;;
    b->distancia = tempDistancia;

    // Trocar os sat�lites
    // Isto � importante, sen�o os sat�lites de um planeta
    // iam ficar 'agarrados' ao planeta errado.
    StructSatellite* tempFirstSattelite = a->pFirstSattelite;
    a->pFirstSattelite = b->pFirstSattelite;
    b->pFirstSattelite = tempFirstSattelite;
}

void swapSatelittes(StructSatellite* a, StructSatellite* b)
{
    // Trocar o nome
    char tempName[256];
    strcpy(tempName, a->nome);
    strcpy(a->nome, b->nome);
    strcpy(b->nome, tempName);

    // Trocar a dist�ncia
    float tempDistancia = a->distancia;
    a->distancia = b->distancia;
    b->distancia = tempDistancia;
}

// Estas s�o as fun��es que ser�o chamadas para efectuar a ordena��o tanto dos
// planetas (sortPlanetsByCriteria), como dos sat�lites (sortSattelitesByCriteria).
// Como o nome sugere, estas fun��es sabem efectuar um sort, mas n�o sabem qual �
// o crit�rio a usar. � aqui que entram as 4 fun��es do inicio. Elas s�o 'enviadas'
// para estas fun��es e dependendo daquilo que elas dizem, o algoritmo chama ou n�o
// a fun��o de swap:
//  - A fun��o sortPlanetsByCriteria    ir� chamar a func��o swapPlanetas
//  - A fun��o sortSattelitesByCriteria ir� chamar a func��o swapSatelittes
// Neste momento, cada uma delas pode receber 2 fun��es de crit�rio (uma que ordena
// por nome, e outra que ordena por dist�ncia, que s�o o que � necess�rio)
//  - A fun��o sortPlanetsByCriteria pode receber estas fun��es de crit�rio:
//       - compareByNamePlanet
//       - compareByDistancePlanet
//  - A fun��o sortSattelitesByCriteria pode receber estas fun��es de crit�rio:
//       - compareByNameSatellite
//       - compareByDistanceSatellite

void sortPlanetsByCriteria(StructPlaneta* pFirstPlanet, int (*fCompare)(StructPlaneta*, StructPlaneta*))
{
    int swapped;
    StructPlaneta* ptr1;
    StructPlaneta* lptr = NULL;

    if (pFirstPlanet == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        ptr1 = pFirstPlanet;

        while (ptr1->pNextPlanet!= lptr)
        {
            if (fCompare(ptr1, ptr1->pNextPlanet) > 0)
            {
                swapPlanetas(ptr1, ptr1->pNextPlanet);
                swapped = 1;
            }

            ptr1 = ptr1->pNextPlanet;
        }
        lptr = ptr1;

    } while (swapped);
}

void sortSattelitesByCriteria(StructSatellite* pFirstSatelitte, int (*fCompare)(StructSatellite*, StructSatellite*))
{
    int swapped;
    StructSatellite* ptr1;
    StructSatellite* lptr = NULL;

    if (pFirstSatelitte == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        ptr1 = pFirstSatelitte;

        while (ptr1->pNextSatellite != lptr)
        {
            if (fCompare(ptr1, ptr1->pNextSatellite) > 0)
            {
                swapSatelittes(ptr1, ptr1->pNextSatellite);
                swapped = 1;
            }

            ptr1 = ptr1->pNextSatellite;
        }
        lptr = ptr1;

    } while (swapped);
}

// Estas fun��es s�o apenas para que 'descomplicar' o switch e assim, ele
// ficar mais limpo. O que elas fazem, � aplicar o sort indicado pelo seu
// nome aos planetas e de seguida aos sat�lites dentro de cada planeta.
// Neste caso, estamos a ordenar os planetas primeiro e depois os sat�lites,
// mas o inverso tamb�m seria poss�vel. Podemos ordenar as v�rias listas dos
// sat�lites primeiro e depois ordenar os planetas.
// Em resumo:
//  - A fun��o sortBodiesByName vai chamar:
//      - sortPlanetsByCriteria    com o argumento compareByNamePlanet
//      - sortSattelitesByCriteria com o argumento compareByNameSatellite
//
//  - A fun��o sortBodiesByDistance vai chamar
//      - sortPlanetsByCriteria    com o argumento compareByDistancePlanet
//      - sortSattelitesByCriteria com o argumento compareByDistanceSatellite
//
// Aqui se v� que em ambos os casos, a fun��o chamada � sempre a mesma:
//   sortPlanetsByCriteria para ordenar planetas e
//   sortSattelitesByCriteria para ordenar satelites.
// A �nica coisa que muda � a fun��o que � dada para comparar os objectos.

void sortBodiesByName(StructEstrela* pStar)
{
    if (pStar == NULL)
    {
        return;
    }

    // Sort all the planets
    sortPlanetsByCriteria(pStar->pFirstPlanet, compareByNamePlanet);

    // For each planet, sort the sattelites inside it
    StructPlaneta* pPlanet = pStar->pFirstPlanet;
    while (pPlanet)
    {
        sortSattelitesByCriteria(pPlanet->pFirstSattelite, compareByNameSatellite);
        pPlanet = pPlanet->pNextPlanet;
    }
}

void sortBodiesByDistance(StructEstrela* pStar)
{
    if (pStar == NULL)
    {
        return;
    }

    // Sort all the planets
    sortPlanetsByCriteria(pStar->pFirstPlanet, compareByDistancePlanet);

    // For each planet, sort the sattelites inside it
    StructPlaneta* pPlanet = pStar->pFirstPlanet;
    while (pPlanet)
    {
        sortSattelitesByCriteria(pPlanet->pFirstSattelite, compareByDistanceSatellite);
        pPlanet = pPlanet->pNextPlanet;
    }
}

// Leitura do ficheiro

int LinhaRepresentaSatelite(char* linha)
{
    return (linha[0] == '#');
}

// Filtering of the bodies

int ValidarFiltro(
    char* filter,
    float minDistance,
    float maxDistance,
    char* bodyName,
    float bodyDistance)
{
    // Primeiro validar o nome
    if (strcmp(filter, "*") != 0)
    {
        if (strstr(bodyName, filter) == NULL)
        {
            // Texto n�o foi encontrado
            return 0;
        }
    }

    // Filtrar a distancia minima
    if (minDistance >= 0)
    {
        if (bodyDistance < minDistance)
        {
            return 0;
        }
    }

    // Filtrar a distancia m�xima
    if (maxDistance >= 0)
    {
        if (bodyDistance > maxDistance)
        {
            return 0;
        }
    }

    return 1;
}

// Constru��o da Rota

// Fun��o que converte Astrological Unit para dias
// A fun��o ceilf est� em math.h e mais detalhes podem ser encontrados aqui:
// https://en.cppreference.com/w/c/numeric/math/ceil
int convertUAtoDias(float distanceAU)
{
    return (int)ceilf(distanceAU * 30);
}

// Esta fun��o procura um determinado corpo na '�rvore' de corpos celestes.
// Quando o corpo � encontrado, � retornada uma estrutura com todos os items
// necess�rios para chegar ao item.
StructCaminhoParaEstacao* ProcurarBodyPorNome(StructEstrela* pStar, char* nomeBody)
{
    // Inicializar o caminho
    StructCaminhoParaEstacao* pCaminho = malloc(sizeof(StructCaminhoParaEstacao));
    pCaminho->pStar = NULL;
    pCaminho->pPlanet = NULL;
    pCaminho->pSatelitte = NULL;

    // Primeiro passo � ver se o nome � o da estrela
    if (strcmp(pStar->nomeEstrela, nomeBody) == 0)
    {
        pCaminho->pStar = pStar;
        return pCaminho;
    }

    // Se o nome n�o � da estrela, vamos ver se � de um dos planetas
    StructPlaneta* pPlanet = pStar->pFirstPlanet;
    while (pPlanet)
    {
        if (strcmp(pPlanet->nome, nomeBody) == 0)
        {
            pCaminho->pStar = pStar;
            pCaminho->pPlanet = pPlanet;
            return pCaminho;
        }

        pPlanet = pPlanet->pNextPlanet;
    }

    // Se o nome n�o � de um planeta, vamos ver se � de um sat�lite
    pPlanet = pStar->pFirstPlanet;
    while (pPlanet)
    {
        StructSatellite* pSatelitte = pPlanet->pFirstSattelite;
        while (pSatelitte)
        {
            if (strcmp(pSatelitte->nome, nomeBody) == 0)
            {
                pCaminho->pStar = pStar;
                pCaminho->pPlanet = pPlanet;
                pCaminho->pSatelitte = pSatelitte;
                return pCaminho;
            }

            pSatelitte = pSatelitte->pNextSatellite;
        }

        pPlanet = pPlanet->pNextPlanet;
    }

    // Se chagarmos aqui, sabemos que o nome n�o existe.

    free(pCaminho);

    return NULL;
}

// Esta fun��o adiciona um novo sitio � lista de locais da nossa rota
// A �nica considera��o � que o novo local deve ficar no fim da rota
void AdicionarPontoARota(StructPontoRota** pListaRota, char* nomeBody)
{
    // Criar novo ponto na rota

    StructPontoRota* pNovaRota = malloc(sizeof(StructPontoRota));
    strcpy(pNovaRota->nomeBody, nomeBody);
    pNovaRota->pNextPonto = NULL;

    // Adicionar ao fim

    if (*pListaRota == NULL)
    {
        *pListaRota = pNovaRota;
    }
    else
    {
        StructPontoRota* pPonto = (*pListaRota);
        while (pPonto->pNextPonto)
        {
            pPonto = pPonto->pNextPonto;
        }

        pPonto->pNextPonto = pNovaRota;
    }
}

// Esta fun��o adiciona uma nova dura��o de viagem � nossa lista de dura��es.
// Uma considera��o � que o valor providenciado � convertido aqui para dias.
// Tal como na fun��o acima, a nova dist�ncia � guardada no fim da lista.
void AdicionarDistanciaARota(StructDistanciaViagem** pListaDistanciasViagem, float distancia)
{
    // Criar nova
    StructDistanciaViagem* pNovaDistancia = malloc(sizeof(StructDistanciaViagem));
    pNovaDistancia->distancia = convertUAtoDias(distancia);
    pNovaDistancia->pNextDistancia = NULL;

    // Adicionar ao fim
    if (*pListaDistanciasViagem == NULL)
    {
        *pListaDistanciasViagem = pNovaDistancia;
    }
    else
    {
        StructDistanciaViagem* pPonto = (*pListaDistanciasViagem);
        while (pPonto->pNextDistancia)
        {
            pPonto = pPonto->pNextDistancia;
        }

        pPonto->pNextDistancia = pNovaDistancia;
    }
}

// Esta fun��o recebe uma estrutura que indica a parte descendente do caminho.
// Todos os items que est�o nessa estrutura devem ser adicionados.
// Al�m de adicionar os locais, as distancias s�o calculadas e adicionadas
// � lista.
void AdicionarRotaDescendente(StructItenerario* pItenerario, StructCaminhoParaEstacao* pCaminhoDescendente)
{
    if (pCaminhoDescendente->pStar != NULL)
    {
        AdicionarPontoARota(&pItenerario->pPontos, pCaminhoDescendente->pStar->nomeEstrela);
    }

    if (pCaminhoDescendente->pPlanet != NULL)
    {
        AdicionarPontoARota(&pItenerario->pPontos, pCaminhoDescendente->pPlanet->nome);

        // Se a estrela estiver definida, � porque viemos de l�. Adicionar essa dist�ncia � lista
        AdicionarDistanciaARota(&pItenerario->pDistancias, pCaminhoDescendente->pPlanet->distancia);
    }

    if (pCaminhoDescendente->pSatelitte != NULL)
    {
        AdicionarPontoARota(&pItenerario->pPontos, pCaminhoDescendente->pSatelitte->nome);

        // Se o planeta estiver definido, � porque viemos de l�. Adicionar essa dist�ncia � lista
        AdicionarDistanciaARota(&pItenerario->pDistancias, pCaminhoDescendente->pSatelitte->distancia);
    }
}

// Esta fun��o procura os corpos providenciados e cria uma rota e respectivas dist�ncias.
// � ligeiramente mais complexa que a fun��o AdicionarRotaDescendente, porque ao percorrer
// a �rvore do sat�lite para a estrela, temos de saber se o local onde estamos � referenciado
// na viagem descendente
void ConstruirRota(StructItenerario* pItenerario, StructEstrela* pStar, char* nomeOrigem, char* nomeDestino)
{
    // Localizar origem
    StructCaminhoParaEstacao* pOrigem = ProcurarBodyPorNome(pStar, nomeOrigem);
    StructCaminhoParaEstacao* pDestino = ProcurarBodyPorNome(pStar, nomeDestino);

    // Tentar descobrir a rota a tomar
    if (pOrigem == NULL || pDestino == NULL)
    {
        return;
    }

    // Ver se um sat�lite faz parte da nossa rota ascendente

    if (pOrigem->pSatelitte != NULL)
    {
        // Se o sat�lite fizer parte da nossa rota, adicionar o sat�lite
        AdicionarPontoARota(&pItenerario->pPontos, pOrigem->pSatelitte->nome);
    }

    // Ver se um planeta faz parta da nossa rota descendente
    if (pOrigem->pPlanet != NULL)
    {
        // Se o planeta fizer parte da nossa rota, adicionar o planeta
        AdicionarPontoARota(&pItenerario->pPontos, pOrigem->pPlanet->nome);

        // Caso haja um sat�lite na nossa rota, temos de indicar que viemos de l�
        if (pOrigem->pSatelitte != NULL)
        {
            AdicionarDistanciaARota(&pItenerario->pDistancias, pOrigem->pSatelitte->distancia);
        }

        // Ver se este planeta � o mesmo que na rota descendente
        if (pOrigem->pPlanet == pDestino->pPlanet)
        {
            // Como o planeta � partilhado, podemos remover o planeta e a estrela da rota
            pDestino->pStar = NULL;
            pDestino->pPlanet = NULL;

            // Adicionar restante rota
            AdicionarRotaDescendente(pItenerario, pDestino);

            return;
        }
    }

    if (pOrigem->pStar != NULL)
    {
        AdicionarPontoARota(&pItenerario->pPontos, pOrigem->pStar->nomeEstrela);

        // Caso haja um planeta na nossa rota, temos de indicar que viemos de l�
        if (pOrigem->pPlanet)
        {
            AdicionarDistanciaARota(&pItenerario->pDistancias, pOrigem->pPlanet->distancia);
        }

        // Verificar se a estrela � a mesma
        // NOTA: Ser� sempre a mesma porque � a �nica
        if (pOrigem->pStar == pDestino->pStar)
        {
            // Adicionar restante rota
            // Como o planeta � partilhado, podemos remover o planeta da rota
            pDestino->pStar = NULL;

            AdicionarRotaDescendente(pItenerario, pDestino);

            return;
        }
    }
}

// Esta fun��o retorna em dias, a dura��o total da viagem. Para isso, percorre a lista que guarda
// as dist�ncias, acumula essas distancias e a esse valor, acrescenta os valores da descolagem
// e aterragem.
int CalcularDuracaoTotalDaRota(StructItenerario* pItenerario)
{
    if (pItenerario == NULL)
    {
        return 0;
    }

    int totalViagem = 0;

    StructDistanciaViagem* pDistancia = pItenerario->pDistancias;
    while (pDistancia)
    {
        totalViagem += pDistancia->distancia;

        pDistancia = pDistancia->pNextDistancia;
    }

    // Adicionar os dias adicionais para 'descolagem' e 'aterragem'
    totalViagem += 2;

    return totalViagem;
}

// Mostra a localiza�o do corpo celeste. Lista os corpos da estrela para o sat�lite.
void MostrarLocalizacaoCorpo(char* description, StructCaminhoParaEstacao* pCaminho)
{
    if (pCaminho == NULL)
    {
        return;
    }

    printf("%s: ", description);

    if (pCaminho->pStar)
    {
        printf("%s", pCaminho->pStar->nomeEstrela);
    }
    if (pCaminho->pPlanet)
    {
        printf("-%s", pCaminho->pPlanet->nome);
    }
    if (pCaminho->pSatelitte)
    {
        printf("-%s", pCaminho->pSatelitte->nome);
    }

    printf("\n");
}

// Fun��o que mostra a rota a tomar com os nomes dos corpos e distancia entre os mesmos.
// Para fazer isto, temos de percorrer 2 das listas que construimos aquando da constru��o
// da rota.
// - Lista do Pontos
// - Lista de distancias
//
// A lista de distancias ter� sempre 1 valor a menos que a lista de pontos:
// Vamos por exemplo considerar uma viagem com 4 locais:
//     Marte -> Sol -> Terra -> Lua
//
// Na lista de dist�ncias teremos 3 valores:
//   - De Marte a Sol,
//   - De Sol a Terra,
//   - De Terra � Lua,
//
// Estes valores das dist�ncias s�o mostrados entre locais
void MostrarRota(StructItenerario* pItenerario)
{
    // Para mostrar a rota, temos de ler 2 listas em simult�neo (Pontos e Distancias)
    // A lista de dist�ncias ter� sempre um elemento a menos do que a lista de pontos

    StructPontoRota* pPonto = pItenerario->pPontos;
    StructDistanciaViagem* pDistanciaViagem = pItenerario->pDistancias;

    printf("Esta��es: ");

    while (pPonto)
    {
        // Imprimir o nome do ponto
        printf("%s ", pPonto->nomeBody);


        // Temos de testar este apontador porque a lista de distancias
        // vai chegar ao fim primeiro que a lista das posi��es
        if (pDistanciaViagem)
        {
            // Imprimir a dist�ncia
            // Esta dist�ncia � entre o valor imprimido na instru��o acima e o pr�ximo.

            printf("(%d) ", pDistanciaViagem->distancia);
            pDistanciaViagem = pDistanciaViagem->pNextDistancia;
        }

        pPonto = pPonto->pNextPonto;
    }

    printf("\n");
}

// Esta funcao apenas mostra ao utilizador a dura��o da viagem
// formatada correctamente
void MostrarDuracaoDaViagem(int totalDias)
{
    int resto = totalDias;

    // Calcular anos e actualizar o resto
    div_t divAno = div(resto, 30 * 12);
    int anos = divAno.quot;
    resto = divAno.rem;

    // Calcular meses e dias
    div_t divMes = div(resto, 30);
    int meses = divMes.quot;
    int dias = divMes.rem;

    // Apresentar os valores correctamente

    printf("Dura��o: ");

    if (anos > 0)
    {
        char* descricaoAno = anos > 1 ? "anos" : "ano";
        printf("%d %s ", anos, descricaoAno);
    }

    if (meses > 0)
    {
        char* descricaoMes = meses > 1 ? "meses" : "m�s";
        printf("%d %s ", meses, descricaoMes);
    }

    if (dias > 0)
    {
        char* descricaoDias = dias > 1 ? "dias" : "dia";
        printf("%d %s ", dias, descricaoDias);
    }

    printf("\n");
}

// Esta fun��o agrega todas as fun��es de print e chama-as na ordem adequada
void MostrarItenerario(StructItenerario* pItenerario)
{
    // Mostrar origens de origem e de destino
    // Exemplo
    // De: Sol - Urano - Ariel
    // Para: Sol - Netuno
    // Esta��es : Ariel (1) Urano (577) Sol (900) Netuno
    // Dura��o : 4 anos 1 m�s 10 dias

    MostrarLocalizacaoCorpo("De", pItenerario->pOrigem);
    MostrarLocalizacaoCorpo("Para", pItenerario->pDestino);

    // Mostrar a rota
    MostrarRota(pItenerario);

    // Mostrar a dura��o da viagem
    MostrarDuracaoDaViagem(CalcularDuracaoTotalDaRota(pItenerario));
}

int main(int argc, char** argv)
{
    //setlocale(LC_ALL, "Portuguese");

    FILE* file;
    char fileLine[MAXSTR];

    StructEstrela* pStar = NULL;

    int nextLineIsTravelLine = 0;

    file = fopen(argv[1], "rt");
    while (!feof(file))
    {
        if (fgets(fileLine, MAXSTR, file))
        {
            if (pStar == NULL)
            {
                fileLine[strcspn(fileLine, "\n")] = 0;//retira o enter do input
                // Ler a linha que cont�m o nome da estrela
                pStar = createStart(fileLine);
            }
            else
            {
                if (strlen(fileLine) == 1)
                {
                    nextLineIsTravelLine = 1;
                    continue;
                }

                if (nextLineIsTravelLine == 1)
                {
                    // Ler linha da viagem

                    char origem[MAXSTR];
                    char destino[MAXSTR];

                    sscanf(fileLine,
                        "%s %s",
                        origem,
                        destino);

                    // Criar um novo itener�rio para guardar os dados da viagem

                    StructItenerario itenerario;
                    itenerario.pOrigem = ProcurarBodyPorNome(pStar, origem);
                    itenerario.pDestino = ProcurarBodyPorNome(pStar, destino);
                    itenerario.pDistancias = NULL;
                    itenerario.pPontos = NULL;

                    ConstruirRota(&itenerario, pStar, origem, destino);
                    MostrarItenerario(&itenerario);

                    return 0;
                }

                // J� temos a estrela
                // Pode ser um planeta ou sat�lite

                if (LinhaRepresentaSatelite(fileLine))
                {
                    // Ler linha como satelite

                    char nome[MAXSTR];
                    float distancia;

                    sscanf(fileLine, "# %s %f\n", nome, &distancia);

                    CriarSatelite(pStar, nome, distancia);
                }
                else
                {
                    // Ler linhas como planeta

                    char nome[MAXSTR];
                    float distancia;

                    sscanf(fileLine, "%s %f", nome, &distancia);

                    CriarPlaneta(pStar, nome, distancia);
                }
            }
        }
    }

    return 0;
}

