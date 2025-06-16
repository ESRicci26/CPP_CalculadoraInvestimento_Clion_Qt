# Documentação da Calculadora de Investimentos HP 12C

## Visão Geral
Este projeto é uma calculadora de investimentos inspirada na famosa calculadora financeira HP 12C. Desenvolvida em C++ com Qt, ela permite calcular o valor futuro de investimentos considerando aportes mensais e juros compostos.

## Tecnologias Utilizadas
- **Linguagem**: C++
- **Framework de Interface Gráfica**: Qt 5/6
- **IDE de Desenvolvimento**: CLion
- **Sistema de Build**: CMake (integrado ao CLion)

## Funcionalidades
- Cálculo de valor futuro de investimentos com juros compostos
- Suporte a aportes mensais regulares
- Dois modelos pré-definidos (com e sem aporte)
- Interface intuitiva com validação de entrada
- Formatação automática de valores monetários (R$)

## Estrutura do Código
O projeto está organizado em uma única classe principal `CalculadoraInvestimento` que herda de `QMainWindow` e contém:

### Componentes da Interface
- Campos de entrada para:
  - Valor presente (R$)
  - Taxa de juros mensal (%)
  - Número de meses
  - Aporte mensal (R$)
- Campo de saída para o valor futuro calculado
- Botões de ação:
  - Calcular
  - Limpar campos
  - Preencher exemplos (com e sem aporte)

### Métodos Principais
- `calcularValorFuturo()`: Realiza o cálculo financeiro
- `limparCampos()`: Reseta todos os campos
- `preencherExemplo1()` e `preencherExemplo2()`: Preenchem campos com valores de exemplo
- `parseDoubleFromField()`: Converte texto em número com tratamento de locale
- `formatCurrency()`: Formata valores como moeda brasileira

## Fórmulas Implementadas
1. **Valor futuro sem aportes**:
   ```
   VF = VP * (1 + i)^n
   ```
2. **Valor futuro com aportes**:
   ```
   VF = VP * (1 + i)^n + PMT * [((1 + i)^n - 1) / i]
   ```
   Onde:
   - VF = Valor Futuro
   - VP = Valor Presente
   - i = Taxa de juros mensal (em decimal)
   - n = Número de meses
   - PMT = Aporte mensal

## Requisitos do Sistema
- Qt 5 ou 6 instalado
- Compilador C++ compatível (GCC, Clang, MSVC)
- CMake 3.10+

## Configuração do Ambiente no CLion
1. Certifique-se de ter o Qt instalado e configurado no CLion
2. Configure o kit de ferramentas para usar o compilador adequado
3. Certifique-se que o CMakeLists.txt inclui as bibliotecas necessárias do Qt
4. Configure as variáveis de ambiente para localizar as bibliotecas Qt

## Como Compilar e Executar
1. Abra o projeto no CLion
2. Configure o perfil de execução para usar o executável gerado
3. Build o projeto (Ctrl+F9)
4. Execute (Shift+F10)

## Exemplos de Uso
1. **Investimento sem aportes**:
   - Valor Presente: R$ 32.114,68
   - Juros: 1% ao mês
   - Período: 36 meses
   - Aporte: R$ 0,00

2. **Investimento com aportes**:
   - Valor Presente: R$ 32.114,68
   - Juros: 1% ao mês
   - Período: 36 meses
   - Aporte: R$ 5.000,00/mês

## Licença
Este projeto está licenciado sob a MIT License.

## Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.

## Screenshots
(Incluir imagens da interface em funcionamento)

## Observações
- O projeto utiliza ícones personalizados que devem estar no caminho correto (`:/imagens/`)
- A formatação monetária segue o padrão brasileiro (R$ com vírgula decimal)
- A validação de entrada aceita tanto ponto quanto vírgula como separador decimal

## Melhorias Futuras
- [ ] Adicionar gráficos de evolução do investimento
- [ ] Implementar cálculo de taxas equivalentes (anual/mensal)
- [ ] Adicionar exportação de resultados para PDF/Excel
- [ ] Implementar sistema de histórico de cálculos
