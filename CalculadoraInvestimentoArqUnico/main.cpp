#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QtCore/QLocale>
#include <QtGui/QValidator>
#include <QtGui/QDoubleValidator>
#include <QtGui/QIcon>
#include <QtGui/QFont>
#include <QtGui/QScreen>
#include <cmath>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

class CalculadoraInvestimento : public QMainWindow
{
    Q_OBJECT

public:
    CalculadoraInvestimento(QWidget *parent = nullptr);
    ~CalculadoraInvestimento();

private slots:
    void calcularValorFuturo();
    void limparCampos();
    void preencherExemplo1();
    void preencherExemplo2();

private:
    // Widgets
    QWidget *centralWidget;
    QLineEdit *valorPresenteField;
    QLineEdit *jurosMensalField;
    QLineEdit *numeroMesesField;
    QLineEdit *aporteMensalField;
    QLineEdit *valorFuturoField;

    QPushButton *calcularButton;
    QPushButton *limparButton;
    QPushButton *exemplo1Button;
    QPushButton *exemplo2Button;

    // Métodos auxiliares
    void setupUI();
    void setupConnections();
    void setupValidators();
    double parseDoubleFromField(const QString &text);
    QString formatCurrency(double value);
};

CalculadoraInvestimento::CalculadoraInvestimento(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Calculadora de Investimentos HP 12C");
    setFixedSize(800, 350);

    // Centralizar janela na tela
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    // Tentar carregar o ícone da janela
    QIcon icon(":/imagens/calculadorahp.png");
    //QIcon icon("E:/WorkSpaceCLion/CalculadoraInvestimentoArqUnico/imagens/calculadorahp.png");
    if (!icon.isNull()) {
        setWindowIcon(icon);
    }

    setupUI();
    setupConnections();
    setupValidators();
}

CalculadoraInvestimento::~CalculadoraInvestimento()
{
}

void CalculadoraInvestimento::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layout principal com margens
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(10);

    // Grid layout para os campos de entrada
    QGridLayout *inputLayout = new QGridLayout();
    inputLayout->setVerticalSpacing(15);
    inputLayout->setHorizontalSpacing(10);

    // Valor Presente
    inputLayout->addWidget(new QLabel("Valor Presente (R$):"), 0, 0);
    valorPresenteField = new QLineEdit();
    inputLayout->addWidget(valorPresenteField, 0, 1);

    // Juros ao Mês
    inputLayout->addWidget(new QLabel("Juros ao Mês (%):"), 1, 0);
    jurosMensalField = new QLineEdit();
    inputLayout->addWidget(jurosMensalField, 1, 1);

    // Número de Meses
    inputLayout->addWidget(new QLabel("Número de Meses:"), 2, 0);
    numeroMesesField = new QLineEdit();
    inputLayout->addWidget(numeroMesesField, 2, 1);

    // Valor Aporte Mensal
    inputLayout->addWidget(new QLabel("Valor Aporte Mensal (R$):"), 3, 0);
    aporteMensalField = new QLineEdit();
    inputLayout->addWidget(aporteMensalField, 3, 1);

    // Valor Futuro (resultado)
    inputLayout->addWidget(new QLabel("Valor Futuro (R$):"), 4, 0);
    valorFuturoField = new QLineEdit();
    valorFuturoField->setReadOnly(true);
    valorFuturoField->setStyleSheet("background-color: #f0f0f0;");

    // Fonte em negrito para o resultado
    QFont boldFont = valorFuturoField->font();
    boldFont.setBold(true);
    valorFuturoField->setFont(boldFont);

    inputLayout->addWidget(valorFuturoField, 4, 1);

    mainLayout->addLayout(inputLayout);

    // Layout horizontal para os botões
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);

    // Botões
    calcularButton = new QPushButton("Calcular");
    calcularButton->setIcon(QIcon(":/imagens/calculadora.png"));

    limparButton = new QPushButton("Limpar");
    limparButton->setIcon(QIcon(":/imagens/limpar-limpo.png"));

    exemplo1Button = new QPushButton("Modelo COM Aporte");
    exemplo1Button->setIcon(QIcon(":/imagens/modelocomaporte.png"));

    exemplo2Button = new QPushButton("Modelo SEM Aporte");
    exemplo2Button->setIcon(QIcon(":/imagens/modelosemaporte.png"));

    buttonLayout->addWidget(calcularButton);
    buttonLayout->addWidget(limparButton);
    buttonLayout->addWidget(exemplo1Button);
    buttonLayout->addWidget(exemplo2Button);

    mainLayout->addLayout(buttonLayout);
}

void CalculadoraInvestimento::setupConnections()
{
    connect(calcularButton, &QPushButton::clicked, this, &CalculadoraInvestimento::calcularValorFuturo);
    connect(limparButton, &QPushButton::clicked, this, &CalculadoraInvestimento::limparCampos);
    connect(exemplo1Button, &QPushButton::clicked, this, &CalculadoraInvestimento::preencherExemplo1);
    connect(exemplo2Button, &QPushButton::clicked, this, &CalculadoraInvestimento::preencherExemplo2);
}

void CalculadoraInvestimento::setupValidators()
{
    // Validator para aceitar números decimais com vírgula ou ponto
    QRegularExpression regex("^[0-9]+([,.][0-9]{0,2})?$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);

    // Aplicar validadores aos campos numéricos
    valorPresenteField->setValidator(validator);
    jurosMensalField->setValidator(validator);
    numeroMesesField->setValidator(validator);
    aporteMensalField->setValidator(validator);
}

void CalculadoraInvestimento::calcularValorFuturo()
{
    try {
        // Obter valores dos campos
        double valorPresente = parseDoubleFromField(valorPresenteField->text());
        double jurosMensal = parseDoubleFromField(jurosMensalField->text()) / 100.0; // Converter para decimal
        int numeroMeses = static_cast<int>(parseDoubleFromField(numeroMesesField->text()));
        double aporteMensal = parseDoubleFromField(aporteMensalField->text());

        // Calcular valor futuro
        double valorFuturo = valorPresente * std::pow(1 + jurosMensal, numeroMeses);

        // Se houver aporte mensal, calcular o montante dos aportes com juros
        if (aporteMensal > 0) {
            // Fórmula para soma dos termos de uma PG para os aportes mensais
            double montanteAportes = aporteMensal * ((std::pow(1 + jurosMensal, numeroMeses) - 1) / jurosMensal);
            valorFuturo += montanteAportes;
        }

        // Exibir resultado formatado
        valorFuturoField->setText(formatCurrency(valorFuturo));

    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Erro",
            "Erro ao calcular. Verifique se todos os campos estão preenchidos corretamente.\n"
            "Use ponto ou vírgula como separador decimal.");
    }
}

double CalculadoraInvestimento::parseDoubleFromField(const QString &text)
{
    if (text.isEmpty()) {
        return 0.0;
    }

    QString cleanText = text;

    // Remove símbolos de moeda e espaços
    cleanText.remove(QRegularExpression("[R$\\s]"));

    // Remove pontos (separador de milhar) e substitui vírgula por ponto
    cleanText.remove('.');
    cleanText.replace(',', '.');

    bool ok;
    double value = cleanText.toDouble(&ok);

    if (!ok) {
        throw std::runtime_error("Valor inválido");
    }

    return value;
}

QString CalculadoraInvestimento::formatCurrency(double value)
{
    QLocale locale(QLocale::Portuguese, QLocale::Brazil);
    return locale.toCurrencyString(value);
}

void CalculadoraInvestimento::limparCampos()
{
    valorPresenteField->clear();
    jurosMensalField->clear();
    numeroMesesField->clear();
    aporteMensalField->clear();
    valorFuturoField->clear();
}

void CalculadoraInvestimento::preencherExemplo1()
{
    // Preenche os campos com os valores do exemplo 1
    valorPresenteField->setText("32114,68");
    jurosMensalField->setText("1,00");
    numeroMesesField->setText("36,00");
    aporteMensalField->setText("5000,00");
    valorFuturoField->clear();
}

void CalculadoraInvestimento::preencherExemplo2()
{
    // Preenche os campos com os valores do exemplo 2
    valorPresenteField->setText("32114,68");
    jurosMensalField->setText("1,00");
    numeroMesesField->setText("36,00");
    aporteMensalField->setText("0,00");
    valorFuturoField->clear();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Definir o estilo nativo do sistema
    app.setStyle("Fusion");

    CalculadoraInvestimento window;
    window.show();

    return app.exec();
}

#include "main.moc"