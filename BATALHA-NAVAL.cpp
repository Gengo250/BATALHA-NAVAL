#include <iostream>
#include <ctime>

using namespace std;

void LimpaTela();
void telaInicial();
int Escolhadojogador(int& op);
void jogarsozinho();
void jogardupla();
void iniciatabuleiro(char tabuleiro[10][10],char mascara[10][10]);
void exibetabuleiro(char tabuleiro[10][10],char mascra[10][10], bool MostraGabarito);
void posicionarbarco(char tabuleiro[10][10]);
void pontuacao(char tabuleiro[10][10],int linhajogador,int colunajogador,int& pontos, string& mensagem);
void reiniciar();

int main (){

  srand((unsigned)time(NULL));
  int op = 0;
 
  do{
  LimpaTela();
  telaInicial();


  Escolhadojogador(op);
  
  } while (op < 1 || op > 3 );


  return 0;
}


void LimpaTela(){
  system("CLS");
}
void telaInicial(){
  cout << "BEM VINDO AO JOGO DE BATALHA NAVAL\n";
  cout << "1 - Jogar\n";
  cout << "2 - Sobre\n";
  cout << "3 - Sair\n";

  cout << "Escolha a opçao e tecle ENTER: ";
}
int Escolhadojogador(int& op){

  cin >> op;
  char voltar = 's';
  int escolhajogo = 0;

     switch(op){
        case 1:
            while(escolhajogo < 1 || escolhajogo > 2){
            LimpaTela();
            cout << "Jogo iniciado\n";
            cout << "Gostaria de jogar sozinho ou em dupla?\n";
            cout << "1.Sozinho\n2.Dupla\n";
            cin >> escolhajogo;
          
            if(escolhajogo == 1){
              jogarsozinho();
              break;
            } else if(escolhajogo == 2){
              jogardupla();
              break;
            } 
            } break;
            
            

        case 2:
            do{
                LimpaTela();
                cout << "Este jogo foi feito por Miguel de Castilho Gengo\n"
                     << "Gostaria de voltar ao menu inicial (S / N)? ";
                cin  >> voltar;
                voltar = tolower(voltar);

                if(voltar != 's'){
                    cout << "\nOk, permanecendo aqui.\n"
                         << "Quando quiser voltar, digite S.\n\n";
                    system("pause");
                }
            } while (voltar != 's');   

            op = 0;                   
            break;
           
           
            
           

        case 3:
            cout << "Obrigado por jogar!\n";
            break;
    }
return 0;
}
void jogarsozinho(){
 
  LimpaTela();

  char tabuleiro[10][10];
  char mascara[10][10];
  int linhajogador, colunajogador;
  int pontos = 0;
  string mensagem = "BEM VINDO AO JOGO!";
  int tentativas = 0;
  int maximotentativas = 10;
  char enter;

  iniciatabuleiro(tabuleiro, mascara);
  posicionarbarco(tabuleiro);

  while(tentativas < maximotentativas){
      LimpaTela();

      exibetabuleiro(tabuleiro, mascara, true);
      cout << "Tentativas restantes: " << maximotentativas - tentativas;
      cout << '\n' << mensagem << '\n';
      cout << "Pontuacao: " << pontos << '\n';

      linhajogador = -1;
      colunajogador = -1;

      while((linhajogador < 0 || colunajogador < 0) || (linhajogador > 9 || colunajogador > 9)){
          cout << "Digite uma linha: ";
          cin >>  linhajogador;
          cout << "Digite a coluna: ";
          cin >> colunajogador;
      
      }
      

     
      pontuacao(tabuleiro,linhajogador,colunajogador,pontos, mensagem);
      
     
      

      mascara[linhajogador][colunajogador] = tabuleiro[linhajogador][colunajogador];

      tentativas++;

  }

  cout << "\n";

  cout << "Gostaria de reiniciar o jogo?(S/N)";
  cin >> enter;

  if(enter == 'S' || enter == 's'){
      reiniciar();
  } else {
    cout << "Obrigado por jogar, ate a proxima!\n";
    system("pause");
  }
  

}
void jogardupla(){

    LimpaTela();

   
    string p1, p2;
    cout << "Jogador 1, digite seu nome: ";
    cin  >> p1;
    cout << "Jogador 2, digite seu nome: ";
    cin  >> p2;

    
    char tab1[10][10], mask1[10][10];
    char tab2[10][10], mask2[10][10];

    iniciatabuleiro(tab1, mask1);
    iniciatabuleiro(tab2, mask2);

    posicionarbarco(tab1);
    posicionarbarco(tab2);

    int pontos1 = 0, pontos2 = 0;
    int navios1 = 10, navios2 = 10;

    const int maxTentPorJog = 5;        
    int tent1 = 0, tent2 = 0;            

    string mensagem = "BEM VINDOS!";
    int vez = 1;                         
    int linha, coluna;

    char enter;

    
    while(navios1 > 0 && navios2 > 0 &&
          tent1   < maxTentPorJog &&
          tent2   < maxTentPorJog) {

        LimpaTela();
        cout << "=== BATALHA NAVAL (DUPLA) ===\n\n";

        
        if(vez == 1){
            cout << "Vez de " << p1 << " atacar o tabuleiro de " << p2 << "!\n";
            exibetabuleiro(tab2, mask2, true);
        } else {
            cout << "Vez de " << p2 << " atacar o tabuleiro de " << p1 << "!\n";
            exibetabuleiro(tab1, mask1, true);
        }

        
        cout << "Navios restantes      ->  " << p1 << ": " << navios1
             << "   |   " << p2 << ": " << navios2 << '\n';

        cout << "Tentativas restantes  ->  " << p1 << ": "
             << maxTentPorJog - tent1
             << "   |   " << p2 << ": "
             << maxTentPorJog - tent2 << '\n';

        cout << mensagem << "\n\n";

        linha = -1;
        coluna = -1;

       while((linha < 0 || coluna < 0) || (linha > 9 || coluna > 9)){
           
           cout << "Digite linha (0-9): ";
           cin  >> linha;
           cout << "Digite coluna (0-9): ";
           cin  >> coluna;

       }
       
        
        if(vez == 1){
            pontuacao(tab2, linha, coluna, pontos1, mensagem);
            mask2[linha][coluna] = tab2[linha][coluna];
            if(tab2[linha][coluna] == 'P'){
                tab2[linha][coluna] = 'X';
                navios2--;
            }
            tent1++;      
            vez = 2;
        } else {
            pontuacao(tab1, linha, coluna, pontos2, mensagem);
            mask1[linha][coluna] = tab1[linha][coluna];
            if(tab1[linha][coluna] == 'P'){
                tab1[linha][coluna] = 'X';
                navios1--;
            }
            tent2++;      
            vez = 1;
        }
    }

    
    LimpaTela();
   
    if(navios1 > 0 && navios2 > 0){          
        if(pontos1 == pontos2){
            cout << "Empate! Ninguém afundou todos os navios.\n";
        } else if(pontos1 > pontos2){
            cout << p1 << " vence por pontos!\n";
        } else {
            cout << p2 << " vence por pontos!\n";
        }
    }
    else if(navios2 == 0 && navios1 == 0){
        cout << "Empate! Ambos perderam todos os navios.\n";
    }
    else if(navios2 == 0){
        cout << "Parabéns, " << p1 << "! Você derrotou " << p2 << ".\n";
    }
    else if(navios1 == 0){
        cout << "Parabéns, " << p2 << "! Você derrotou " << p1 << ".\n";
    }


    cout << "\nPontuacao final:\n"
         << p1 << ": " << pontos1 << " pontos\n"
         << p2 << ": " << pontos2 << " pontos\n\n";

    cout << "\n";

    cout << "Gostariam de reiniciar o jogo? (S/N)?";
    cin >> enter;

    if(enter == 'S' || enter == 's'){
      reiniciar();
    } else {
      cout << "Obrigado por jogarem!";
      system("pause");
    }
}
void iniciatabuleiro(char tabuleiro[10][10], char mascara[10][10]){

  int linha,coluna;
   for(linha = 0; linha < 10; linha ++){
    for(coluna = 0; coluna < 10; coluna ++){
      tabuleiro[linha][coluna] = 'A';
      mascara[linha][coluna] = '*';
    }
  }
}
void exibetabuleiro(char tabuleiro[10][10], char mascara[10][10], bool MostraGabarito){
  
  const char* BLUE  = "\033[34m";
  const char* RESET  = "\033[0m";
  const char* RED   = "\033[31m";   



  for(int i= 0; i < 10;i++){
    if(i == 0){
      cout << "        ";
    }
    cout << i <<  "    ";
  }

  cout << "\n";

  for(int i= 0; i < 10;i++){
    if(i == 0){
      cout << "        ";
    }
    cout <<   "|    ";
  }
   cout << "\n";

  
  
  int linha, coluna;
  
  for(linha = 0; linha < 10; linha ++){
    cout << linha << " - ";
    for(coluna = 0; coluna < 10; coluna ++){
    
    switch(mascara[linha][coluna]){
      case 'A':
        cout << BLUE  << "    " << mascara[linha][coluna] << RESET;
       break;
      case 'P':
       cout << RED  << "    " << mascara[linha][coluna] << RESET;
      break;
      default:
       cout << "    " << mascara[linha][coluna];
      break;

    }
     
    }
    cout << "\n";
  }
  if(MostraGabarito == false){
    for(linha = 0; linha < 10; linha ++){
    for(coluna = 0; coluna < 10; coluna ++){
     cout << "    " <<tabuleiro[linha][coluna];
    } 
  cout << "\n";
}
  }

  cout << RESET;      
    
}
void posicionarbarco(char tabuleiro[10][10]){
  int barcos = 10;
  int barcosposicionados = 0;
  while(barcosposicionados < barcos){
    int linhaBarco = rand() % 10;
    int colunaBarco = rand() % 10;

    if(tabuleiro[linhaBarco][colunaBarco] == 'A'){
        tabuleiro[linhaBarco][colunaBarco] = 'P';
        barcosposicionados++;
    }

    
  }

}
void pontuacao(char tabuleiro[10][10],int linhajogador,int colunajogador,int& pontos, string& mensagem){
  if(tabuleiro[linhajogador][colunajogador] == 'P'){
          pontos += 10;
          mensagem = "PARABENS VC ACERTOU!";
      } else {
        mensagem = "QUE PENA, MELHOR NA PROXIMA";
      } 
      
      
}
void reiniciar(){
  
  int op = 0;
  LimpaTela();
  telaInicial();
  Escolhadojogador(op);
 

}