// PROJETO - MAIOR CAMINHO DO GRAFO DAS SCCS (SENDO ESTES VERTICES OU CICLOS DE VERTICES)

// main - dois vetores de vetores um para grafo e para outro transposto
//  for i ate E recebe arco para completar grafo, exemplo 3 6 - fazer nome grapho[3-1].pushback(6-1) 
//  outro for a percorrer grafo normal para completar grado transposto
//  chamar função dfs
// dfs - for percorre vertice do grafo e cada loop (if vertice é white) chamar time_do_vertice = dfs_visit(vertice, time_do_vertice)
// dfs visit - declarar pilha (stack com pop empty etc.) e adicionar vertice logo à pilha
//  entrar while a pilha nao tiver vazia, ver se vertice ja foi descoberto (nao tem cor white),
//  se nao (é white), mudar para gray aumentar 1 no time e definier tempo de inicio = time. Depois (num for) ver se vertices adjancentes é white (nao foram descobertos) 
//  se nao tiver sido descoberto adicionar na pilha (stack.push()) mas nao mudo ja a cor. 
//  ver os adjacentes do primeiro que adicionei (a seguir ao antes do while), assim sucessivamente ate um vetice ter tudo adjacente nao white, usar flag.
//  no caso do topo da stack (sempre o que está a ser explorado no for) nao encontrar nenhum adjacente white, posso fechá-lo e torná-lo black e retiro da pilha.
// voltar à dfs até acabar o grafo.
// main - volto à main e (maybe) arranjar agora maneira de realizar o for que vou ter de fazer na dfs_transposta (ou seja maneira de percorrer o grafo transposto... *esta na descrição da dfs transposta*)
//  declarar varável vetor de inteiros que vai ser o caminho máximo de cada SCC
//  chamar função maior_caminho = dfs_transposta, nao esquecendo de lhe dar caminho maximo de cada SCC
// dfs_transposta - for que percorre os vertices do grafo transposto, mas percorre-os pela ordem dos tempos de fim do grafo original (maior para o menor) e em cada loop chamar time_do_vertice = dfs_visit_transposta(vertice, time_do_vertice, caminho maximo de cada SCC)
// dfs visit transposta - cada vez que é chamada, isto corresponde a uma SCC (obvious)
//  esta função é igual à dfs_visit, porém, dentro do for dos adjacentes, (fora do if white) dizer que o caminho do vertice que eu tou lidar agora (desde o while) é igual ao maximo entre ele próprio e o caminho do vertice adjacente + 1 - aqui altera-se a variável caminho_SCC.  
// voltar à dfs_transposta até acabar o grafo transposto e devolver o maior caminho à main.
// voltar à main e dar print do maior caminho.