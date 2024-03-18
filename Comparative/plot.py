import matplotlib.pyplot as plt

#LEITURA DO ARQUIVO
#with abre e fecha o arquivo após a leitura
with open('comparative_file.txt', 'r') as file:
    #lê as linhas do arquivo e adiciona em uma lista 
    lines = file.readlines()

#dicionario com as chaves lista, arvore e o tamanho, que sao listas
data = {'lista': [], 'abb': [], 'tam': []}

#percorre as linhas do arquivo, menos a primeira, pois é so um 'cabeçalho'
#lines[1:] começa a leitura a partir do indíce 1, ou seja, segunda linha 
for line in lines[1:]:
    lista_data, abb_data, tam_data = map(int, line.split()) #1
    data['lista'].append(lista_data) #2
    data['abb'].append(abb_data) #3
    data['tam'].append(tam_data) #4


plt.scatter(data['tam'], data['lista'], label='Linked List', linewidth=1) #5
plt.scatter(data['tam'], data['abb'], label='Binary Search Tree',linewidth=1, color='red') #6
plt.xlabel('ARRAY SIZE', fontsize=12) #7 - bota legenda no eixo X
plt.ylabel('NUMBER OF COMPARISONS', fontsize=12) #8 - bota legenda no eixo X
plt.title('COMPARISON BETWEEN LINKED LIST AND BINARU SEARCH TREE', fontsize=20) #titulo
plt.legend() #adiciona as legendas
plt.grid(True) #adiciona um grade
plt.show() #exibe o grafico

#1: o método split quebra uma string e coloca em uma lista
#então se a linha tem 1 1 1, ele transforma em ['1','1','1']
#e com a função map(int, line.split()) ele transforma essas substrings em inteiros
#depois coloca esses valores dentro das variáveis lista_data, abb_data e tam_data
#ou seja: lista_data = 1, abb_data = 1 e tam_data = 1

#2 adiciono o valor de lista_data, dentro da lista associada a chave lista no dicionario data
#entao tipo, a chave lista, tem uma lista com valor 1 agora:
#'lista'[1]

#isso acontece para o #3 e #4

#5: cria um grafico do tipo DISPERSAO, tamanhosXlista, entao para tal tamanho vou ter quantas comparações dentro da lista
#label é basicamente a legenda
#linewidth so atribui a grossura da linha

#6 cria um grafico do tipo DISPERSAO, tamanhosXarvore, entao para tal tamanho vou ter quantas comparações dentro da arvore
#label é basicamente a legenda
#linewidth so atribui a grossura da linha
#cor: cor da linha
