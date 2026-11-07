# Library

Gerenciador de biblioteca em linha de comando, escrito em C11: cadastrar, listar, emprestar e devolver livros, com os dados salvos em `library.txt`.

## Como usar

```sh
make run    # compila e executa
make test   # compila e roda os testes
make clean  # apaga a pasta build/
```

## Arquitetura

| Módulo | Responsabilidade |
|---|---|
| `library` | Regras da estante (cadastrar, emprestar, devolver). Sem entrada/saída. |
| `storage` | Leitura e gravação do arquivo, com gravação segura (arquivo temporário + `rename`). |
| `menu` | Toda a interação com o usuário: perguntas, validação de entrada e mensagens. |
| `utils` | Leitura de linha e controle do terminal. |
| `main` | Orquestra: pergunta (`menu`), aplica a regra (`library`), persiste (`storage`), mostra o resultado (`menu`). |

Os testes em `tests/` cobrem `library` e `storage` sem depender de teclado.
