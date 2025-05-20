# 🍳 CookLang

## 📋 Descrição do Projeto

**CookLang** é uma linguagem de programação inclusiva inspirada no mundo da gastronomia.  
A ideia é permitir que o programador escreva **programas como se estivesse seguindo uma receita de cozinha**!

Cada comando da linguagem representa ações comuns de uma cozinha, como adicionar ingredientes, misturar massas, assar pratos e servir alimentos.  
A linguagem foi desenvolvida com sintaxe simples e controlada, para facilitar a implementação e a interpretação.

---

## 🎯 Estruturas básicas

A linguagem foi construída com suporte para:

- **variáveis (ingredientes)**
- **condicionais**
- **loops**

---

## 🧩 EBNF da Linguagem

```ebnf
programa       ::= { comando } ;

comando        ::= atribuicao
                 | condicional
                 | loop
                 | acao ;

atribuicao     ::= identificador "=" expressao ";" ;

expressao      ::= termo { ("+" | "-") termo } ;

termo          ::= fator { ("*" | "/") fator } ;

fator          ::= número
                 | identificador
                 | "(" expressao ")" ;

condicional    ::= "se" "(" expressao op_comp expressao ")" "entao" comando ;

loop           ::= "enquanto" "(" expressao op_comp expressao ")" "faca" comando ;

op_comp        ::= "==" | "!=" | "<" | "<=" | ">" | ">=" ;

acao           ::= "adicione" ingrediente quantidade ";"
                 | "misture_ate" condicao_predefinida ";"
                 | "asse" prato ";"
                 | "sirva" prato ";" ;

identificador  ::= letra { letra | dígito | "_" } ;
número         ::= dígito { dígito } ;
letra          ::= "A"… "Z" | "a"… "z" ;
dígito         ::= "0"… "9" ;

```

## 🥣 Exemplos de Comandos

| Comando | Significado |
|:--------|:------------|
| `adicione farinha 500` | Adiciona 500g de farinha |
| `misture até massa uniforme` | Mistura a massa até ficar uniforme |
| `asse bolo` | Assa o prato "bolo" |
| `sirva bolo` | Serve o bolo |
| `se forno quente então asse bolo` | Se o forno estiver quente, asse o bolo |
| `enquanto massa líquida faça misture até massa uniforme` | Enquanto a massa estiver líquida, continue misturando |

---

## 📚 Condições Disponíveis

As condições representam o estado atual da preparação:

| Condição | Descrição |
|:---------|:----------|
| `forno quente` | O forno atingiu a temperatura correta |
| `massa uniforme` | A massa está homogênea |
| `massa líquida` | A massa ainda precisa de mistura ou cozimento |
| `forno desligado` | O forno está apagado |
| `prato pronto` | A receita foi concluída |

---

## ✨ Exemplo de Programa na CookLang

```plaintext
adicione farinha 500
adicione açúcar 200
misture até massa uniforme
se forno quente então asse bolo
enquanto massa líquida faça misture até massa uniforme
sirva bolo
```

---

## 🚦 Como executar o conjunto de testes

1. **Compile o interpretador**  
   ```bash
   bison -d cooklang.y
   flex  cooklang.l
   gcc -o cooklang lex.yy.c cooklang.tab.c ast.c symtab.c -lfl

2. **Acesse a pasta de testes**

    ```bash
    cd tests
    ```

3. **Execute todos os casos**

    ```bash
    ./run_tests.sh
    ```
    Você deverá ver:

    ```text
    === Test actions.cook ===
    ✔ OK

    === Test arithmetic.cook ===
    ✔ OK

    === Test ifwhile.cook ===
    ✔ OK
    ```

4. **Valores das variáveis**

    Ao final da execução, o interpretador imprime todas as variáveis atribuídas.

---

## 📎 Apresentação

Confira os slides da apresentação do CookLang no Google Slides:  

[🔗 Acessar apresentação online](https://docs.google.com/presentation/d/1JdDOKujHEpy-L0jdXjVhxT-QdJGOacbcfXVdRf0dmBA/edit?usp=sharing)