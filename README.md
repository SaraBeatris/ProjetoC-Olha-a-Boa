# Projeto "Olha a Boa" - Gerenciador de Cartelas de Bingo 🎲

Este é um projeto desenvolvido em C++ para gerenciar cartelas de bingo, permitindo criar cartelas, marcar números e verificar padrões como linhas, colunas, ou a cartela inteira (BINGO). Ele foi implementado com base nos requisitos do projeto e inclui funcionalidades extras para melhorar a experiência do usuário.

---

## 🛠️ Funcionalidades

1. **Cadastro de Usuários**: Permite cadastrar jogadores com nomes únicos e IDs gerados automaticamente.
2. **Geração de Cartelas**: Cada cartela segue as regras tradicionais do bingo:
   - 5x5 quadrados.
   - Colunas baseadas na palavra "BINGO".
   - Quadrado central marcado como "FREE".
3. **Marcação de Números**: Possibilidade de marcar números nas cartelas e verificar:
   - Linhas completas (`LINHA`).
   - Colunas completas (`COLUNA`).
   - Bingo completo (`BINGO`).
   - Alerta de "Olha a Boa!" quando faltar apenas 1 número.
4. **Exibição das Cartelas**: Mostra todas as cartelas do usuário no console com destaque para os números marcados.
5. **Relatório de Números Chamados**: Exibe os números já sorteados.
6. **Salvamento em Arquivo**: Cada cartela gerada é salva automaticamente em arquivos de texto separados.
7. **Menu Interativo**: Interface amigável para interagir com o programa.

---

## 📋 Requisitos do Sistema

- **Compilador C++**: Certifique-se de ter um compilador que suporte C++11 ou superior. O programa foi testado no [Programiz C++ Online Compiler](https://www.programiz.com/cpp-programming/online-compiler/).
- Sistema operacional: Funciona em qualquer sistema que suporte C++ (Windows, Linux, macOS).

---

## 🚀 Como Executar

1. **Clonar o Repositório**:
   ```bash
   git clone https://github.com/seu-usuario/projeto-bingo.git
   cd projeto-bingo
