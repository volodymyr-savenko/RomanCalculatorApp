#pragma once

#include <QObject>
#include <QStack>

class CalculatorEngine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString displayText READ displayText NOTIFY displayTextChanged)

    enum Operator {
        Add,
        Substruct,
        Multiply,
        Divide
    };

signals:
    void displayTextChanged();

public:
    Q_INVOKABLE void updateRomanLiteral(const QString& symbol);

    Q_INVOKABLE void add();
    Q_INVOKABLE void substruct();
    Q_INVOKABLE void multiply();
    Q_INVOKABLE void divide();
    Q_INVOKABLE void clear();

    Q_INVOKABLE void evaluate();

    QString displayText() const;

private:
    void addOperator(Operator op, char symbol);
    int calculate(Operator op, int value1, int value2);
    void evaluateLastExpression();
    int romanToDecimal(const QString& romanLiteral);
    QString decimalToRoman(int decimal);

    QString m_displayText;
    QString m_cachedValue;
    bool m_waitingForOperand{true};
    QStack<Operator> m_operatorStack;
    QStack<int> m_operandStack;
    bool m_waitingForlowerPriorityOperand{false};
};
