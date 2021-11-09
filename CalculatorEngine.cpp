#include <QMap>

#include "CalculatorEngine.h"

void CalculatorEngine::updateRomanLiteral(const QString& symbol)
{
    if (m_waitingForOperand && m_operandStack.isEmpty()) {
        m_displayText.clear();
    }
    m_displayText += symbol;
    m_cachedValue += symbol;
    m_waitingForOperand = false;
    emit displayTextChanged();
}

void CalculatorEngine::add()
{
    addOperator(Operator::Add, '+');
}

void CalculatorEngine::substruct()
{
    addOperator(Operator::Substruct, '-');
}

void CalculatorEngine::multiply()
{
    addOperator(Operator::Multiply, '*');
}

void CalculatorEngine::divide()
{
    addOperator(Operator::Divide, '/');
}

void CalculatorEngine::clear()
{
    m_operandStack.clear();
    m_operatorStack.clear();

    m_cachedValue.clear();
    m_displayText.clear();
    emit displayTextChanged();
}

QString CalculatorEngine::displayText() const
{
    return m_displayText;
}

void CalculatorEngine::addOperator(Operator op, char symbol)
{
    if (m_waitingForOperand == true)
        return;

    m_operandStack.push(romanToDecimal(m_cachedValue));

    m_cachedValue.clear();
    m_waitingForOperand = true;

    if (!m_operatorStack.isEmpty() &&
        (m_operatorStack.top() == Operator::Multiply || m_operatorStack.top() == Operator::Divide)) {
            evaluateLastExpression();
    }

    m_operatorStack.push(op);
    m_displayText += symbol;

    emit displayTextChanged();
}

void CalculatorEngine::evaluate()
{
    if (m_waitingForOperand) {
        return;
    } else {
        m_displayText.clear();
        m_operandStack.push(romanToDecimal(m_cachedValue));
        m_cachedValue.clear();

        while (!m_operatorStack.empty()) {
            evaluateLastExpression();
        }

        m_displayText = decimalToRoman(m_operandStack.pop());

        m_waitingForOperand = true;
        emit displayTextChanged();
    }
}

void CalculatorEngine::evaluateLastExpression()
{
    Operator op = m_operatorStack.pop();
    int value2 = m_operandStack.pop();
    int value1 = m_operandStack.pop();

    m_operandStack.push(calculate(op, value1, value2));
}

int CalculatorEngine::calculate(Operator op, int value1, int value2)
{
    switch (op) {
        case Operator::Add:
            return value1 + value2;
        case Operator::Substruct:
            return value1 - value2;
        case Operator::Multiply:
            return value1 * value2;
        case Operator::Divide:
            return value1 / value2;
        default:
            return -1;
    }
}

int CalculatorEngine::romanToDecimal(const QString& romanLiteral)
{
    static QMap<QChar, int> romanToDecimalMapping {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };

    int result = 0;

    for (int i = 0; i < romanLiteral.length(); i++) {
        int s1 = romanToDecimalMapping[romanLiteral[i]];

        if (i < romanLiteral.length() - 1) {
            int s2 = romanToDecimalMapping[romanLiteral[i + 1]];
            if (s1 >= s2) {
                result = result + s1;
            } else {
                result = result + s2 - s1;
                i++;
            }
        } else {
            result = result + s1;
        }
    }
    return result;
}

QString CalculatorEngine::decimalToRoman(int decimal)
{
    if (decimal > 3999) {
        return "LIMIT";
    }

    static QVector< QPair<int, QString> > decimalToRomanMapping {
        {1000, "M"},
        {900,  "CM"},
        {500,  "D"},
        {400,  "CD"},
        {100,  "C"},
        {90,   "XC"},
        {50,   "L"},
        {40,   "XL"},
        {10,   "X"},
        {9,    "IX"},
        {5,    "V"},
        {4,    "IV"},
        {1,    "I"}
    };

    int index = 0;

    QString result;

    while (decimal > 0) {
        int div = decimal / decimalToRomanMapping[index].first;
        decimal = decimal % decimalToRomanMapping[index].first;
        while (div--) {
            result += decimalToRomanMapping[index].second;
        }
        ++index;
    }

    return result;
}

