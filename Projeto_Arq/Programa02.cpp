#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <cstdio>



#define n_lin_cache 256
#define n_col_cache 32
#define n_linha_por_conjunto 4
#define n_conjuntos 64
#define n_int_por_bloco 32

#define n_tam_imagem 12988791
#define n_acessos 10000


short int cache[n_lin_cache][n_col_cache];
int tag[n_lin_cache];

using namespace std;
int ndb(int mem){ //Calcula o numero do bloco a qual aquele endereço pertence:
    return (mem/n_int_por_bloco);
}

int ndc(int mem){ // converter endereço de memoria para numero de conjunto da cache
    return (ndb(mem)%n_conjuntos);
}

bool bdt(int mem){ // busca se há a tag naquele conjunto
    for(int i=0;i<n_linha_por_conjunto;i++){
        if(tag[ndc(mem)*n_linha_por_conjunto+i] == ndb(mem)){
            return true;
        }
    }
    return false;
}

int main(){

    int proxLocal[n_conjuntos];
    int* imagem = new int[n_tam_imagem];
    char b[100];
    int acertos=0;
    int erros=0;

    //preenche todos marcadores de prox local com 0
    for(int i=0;i<n_conjuntos;i++){
        proxLocal[i]=0;
    }

    ifstream arqImagem;
    ifstream arqAcessos;

    arqImagem.open("imagem.asc");
    if(arqImagem.is_open()){
        //Ler cabeçalho:
        for(int i=0;i<12;i++){
            arqImagem >> b;
            //cout << b << endl;
        }
        //Ler arquivo de imagem e armazena no vetor:
        for(int i=0;i<n_tam_imagem;i++){ //endoffile
            arqImagem >> b;
            imagem[i] = atoi(b);
            //cout << imagem[i] << endl;
        }
        arqImagem.close();
    }else{
        cout<< "Erro ao ler o arquivo de imagem.. " << endl;
        delete imagem;
        return -1;
    }

    arqAcessos.open("acessos.dat");
    if(arqAcessos.is_open()){
        for(int i=0;i<n_acessos;i++){ // TODO : end of file
            arqAcessos >> b;
            int endMem = atoi(b);
            int numdecol = ndc(endMem);
            int numdeblo = ndb(endMem);
            if(bdt(endMem)){
                acertos++;
            }else{
                erros++;
                tag[numdecol*n_linha_por_conjunto + proxLocal[numdecol]] = numdeblo;
                for(int i=0;i<n_int_por_bloco;i++){
                    cache[numdecol*n_linha_por_conjunto + proxLocal[numdecol]][i] = imagem[numdeblo*n_int_por_bloco+i];
                }
                proxLocal[numdecol]++;
                if(proxLocal[numdecol]==n_linha_por_conjunto)  proxLocal[numdecol] = 0;
            }
        }
    }else{
        cout<< "Erro ao ler arquivo Acessos.." << endl;
        delete imagem;
        return -1;
    }

    cout << "Numero de acertos: " <<  acertos << endl;
    cout << "Numero de erros: " << erros << endl;
    cout << "Porcentagem de acertos: " << ((float)acertos/n_acessos)*100.0 << endl;
    cout << "Porcentagem de erros: " << ((float)erros/n_acessos)*100.0 << endl;

    delete imagem;
    return 0;
}
