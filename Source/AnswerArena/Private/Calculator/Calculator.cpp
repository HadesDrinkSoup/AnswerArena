// Fill out your copyright notice in the Description page of Project Settings.

#include "Calculator/Calculator.h"
#include "UI/WidgetController/CalculatorWidgetController.h"

FCalculatorData UCalculator::GetCalculatorData() const
{
    return CalculatorData;
}

void UCalculator::GenerateEquation()
{
    if (bGenerateMixedOperator)
    {
        GenerateMixedEquation(m_EquationNumType, m_EquationDigitType);
    }
    else
    {
        if (m_EquationNumType == EEquationNumType::Equation_ThreeNumbers)
        {
            GenerateMixedEquation(m_EquationNumType, m_EquationDigitType);
        }
        else
        {
            switch (m_OperatorType)
            {
            case EOperatorType::Add:
                GenerateAddition(m_EquationNumType, m_EquationDigitType);
                break;
            case EOperatorType::Sub:
                GenerateSubtraction(m_EquationNumType, m_EquationDigitType);
                break;
            case EOperatorType::Mul:
                GenerateMultiplication(m_EquationNumType, m_EquationDigitType);
                break;
            case EOperatorType::Div:
                GenerateDivision(m_EquationNumType, m_EquationDigitType);
                break;
            case EOperatorType::None:
                break;
            }
        }
    }
}

int32 UCalculator::GenerateRandomNumber(const EEquationDigitType& EquationDigitType)
{
    if (EquationDigitType == EEquationDigitType::Equation_OneDigit)
    {
        return FMath::RandRange(1, 9);
    }
    if (EquationDigitType == EEquationDigitType::Equation_TwoDigit)
    {
        return FMath::RandRange(10, 99);
    }
    return 0;
}

// 区分运算符类型（加减/乘除）
bool UCalculator::IsAddSubOperator(EOperatorType OpType)
{
    return OpType == EOperatorType::Add || OpType == EOperatorType::Sub;
}

bool UCalculator::IsMulDivOperator(EOperatorType OpType)
{
    return OpType == EOperatorType::Mul || OpType == EOperatorType::Div;
}

EOperatorType UCalculator::GetRandomOperatorType()
{
    const int32 RandomIndex = FMath::RandRange(0, 3); // 0-3对应加、减、乘、除
    return static_cast<EOperatorType>(RandomIndex);
}

// 获取指定类型的随机运算符
EOperatorType UCalculator::GetRandomOperatorByType(const bool bWantAddSub)
{
    if (bWantAddSub)
    {
        // 随机返回加/减
        return FMath::RandBool() ? EOperatorType::Add : EOperatorType::Sub;
    }
    // 随机返回乘/除
    return FMath::RandBool() ? EOperatorType::Mul : EOperatorType::Div;
}

void UCalculator::GenerateAddition(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType)
{
    if (EquationNumType == EEquationNumType::Equation_TwoNumbers)
    {
        GenerateTwoNumbersEquation(EOperatorType::Add, DigitType);
    }
}

void UCalculator::GenerateSubtraction(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType)
{
    if (EquationNumType == EEquationNumType::Equation_TwoNumbers)
    {
        GenerateTwoNumbersEquation(EOperatorType::Sub, DigitType);
    }
}

void UCalculator::GenerateMultiplication(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType)
{
    if (EquationNumType == EEquationNumType::Equation_TwoNumbers)
    {
        GenerateTwoNumbersEquation(EOperatorType::Mul, DigitType);
    }
}

void UCalculator::GenerateDivision(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType)
{
    if (EquationNumType == EEquationNumType::Equation_TwoNumbers)
    {
        GenerateTwoNumbersEquation(EOperatorType::Div, DigitType);
    }
}

void UCalculator::GenerateMixedEquation(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType)
{
    if (EquationNumType == EEquationNumType::Equation_TwoNumbers)
    {
        EOperatorType Operator1 = GetRandomOperatorType();
        GenerateTwoNumbersEquation(Operator1, DigitType);
    }
    else
    {
        // 三个数混合运算：确保两个运算符类型不同（一个加减，一个乘除）
        const bool bFirstIsAddSub = FMath::RandBool();
        const EOperatorType Operator1 = GetRandomOperatorByType(bFirstIsAddSub);
        const EOperatorType Operator2 = GetRandomOperatorByType(!bFirstIsAddSub);
        
        GenerateThreeNumbersEquation(Operator1, Operator2, DigitType);
    }
}

void UCalculator::GenerateTwoNumbersEquation(const EOperatorType& OperatorType, const EEquationDigitType& DigitType)
{
    // 重置余数标志
    CalculatorData.bHasRemainder = false;
    CalculatorData.Quotient = 0;
    CalculatorData.Remainder = 0;
    
    CalculatorData.Num1 = GenerateRandomNumber(DigitType);
    CalculatorData.Num2 = GenerateRandomNumber(DigitType);
    CalculatorData.Operator1 = OperatorType;
    
    if (OperatorType == EOperatorType::Add)
    {
        CalculatorData.Answer = CalculatorData.Num1 + CalculatorData.Num2;
        UE_LOG(LogTemp, Log, TEXT("Calculator: Num1 [%d]   Operator [%hhd]   Num2 [%d]   Answer [%f]"), CalculatorData.Num1, CalculatorData.Operator1, CalculatorData.Num2, CalculatorData.Answer);
    }
    
    if (OperatorType == EOperatorType::Sub)
    {
        if (bAllowNegativeResult)
        {
            CalculatorData.Answer = CalculatorData.Num1 - CalculatorData.Num2;
        }
        else
        {
            if (CalculatorData.Num1 < CalculatorData.Num2) Swap(CalculatorData.Num1, CalculatorData.Num2);
            CalculatorData.Answer = CalculatorData.Num1 - CalculatorData.Num2;
        }
        UE_LOG(LogTemp, Log, TEXT("Calculator: Num1 [%d]   Operator [%hhd]   Num2 [%d]   Answer [%f]"), CalculatorData.Num1, CalculatorData.Operator1, CalculatorData.Num2, CalculatorData.Answer);
    }
    
    if (OperatorType == EOperatorType::Mul)
    {
        CalculatorData.Answer = CalculatorData.Num1 * CalculatorData.Num2;
        UE_LOG(LogTemp, Log, TEXT("Calculator: Num1 [%d]   Operator [%hhd]   Num2 [%d]   Answer [%f]"), CalculatorData.Num1, CalculatorData.Operator1, CalculatorData.Num2, CalculatorData.Answer);
    }
    
    if (OperatorType == EOperatorType::Div)
    {
        CalculatorData.Num2 = FMath::RandRange(1, 99);
        if (CalculatorData.Num1 < CalculatorData.Num2) Swap(CalculatorData.Num1, CalculatorData.Num2);
        
        if (bAllowRemainder)
        {
            // 允许余数：直接计算除法的商和余数
            CalculatorData.Quotient = CalculatorData.Num1 / CalculatorData.Num2;
            CalculatorData.Remainder = CalculatorData.Num1 % CalculatorData.Num2;
            CalculatorData.bHasRemainder = (CalculatorData.Remainder != 0);
            
            // 浮点数答案（用于比较等用途）
            CalculatorData.Answer = static_cast<float>(CalculatorData.Quotient);
            
            // 如果有余数，答案显示为"商...余数"格式
            if (CalculatorData.bHasRemainder)
            {
                CalculatorData.Answer += static_cast<float>(CalculatorData.Remainder) / CalculatorData.Num2;
            }
            UE_LOG(LogTemp, Log, TEXT("Calculator: Num1 [%d]   Operator [%hhd]   Num2 [%d]   Answer [%f]   Remainder [%d]"), CalculatorData.Num1, CalculatorData.Operator1, CalculatorData.Num2, CalculatorData.Answer, CalculatorData.Remainder);
        }
        else
        {
            // 不允许余数（整除）：需要确保 Num1 是 Num2 的倍数
            // 重新生成除数，确保不为0
            
            // 获取位数范围
            const int32 MaxValue = GetMaxValueForDigitType(DigitType);
            
            // 生成一个倍数，确保 Num1 在合理范围内
            int32 Multiplier = 0;
            if (DigitType == EEquationDigitType::Equation_OneDigit)
            {
                // 对于一位数，确保 Num1 也是一位数
                int32 MaxMultiplier = MaxValue / CalculatorData.Num2;
                if (MaxMultiplier < 1) MaxMultiplier = 1;
                Multiplier = FMath::RandRange(1, MaxMultiplier);
            }
            if (DigitType == EEquationDigitType::Equation_TwoDigit)
            {
                const int32 MinValue = GetMinValueForDigitType(DigitType);
                // 对于两位数，确保 Num1 是两位数
                int32 MinMultiplier = FMath::CeilToInt(static_cast<float>(MinValue) / CalculatorData.Num2);
                int32 MaxMultiplier = MaxValue / CalculatorData.Num2;
                if (MinMultiplier < 1) MinMultiplier = 1;
                if (MaxMultiplier < MinMultiplier) Swap(MinMultiplier, MaxMultiplier);
                Multiplier = FMath::RandRange(MinMultiplier, MaxMultiplier);
            }
            CalculatorData.Num1 = CalculatorData.Num2 * Multiplier;
            CalculatorData.Answer = static_cast<float>(Multiplier);
            UE_LOG(LogTemp, Log, TEXT("Calculator: Num1 [%d]   Operator [%hhd]   Num2 [%d]   Answer [%f]"), CalculatorData.Num1, CalculatorData.Operator1, CalculatorData.Num2, CalculatorData.Answer);
        }
    }
}

void UCalculator::GenerateThreeNumbersEquation(const EOperatorType& Operator1, const EOperatorType& Operator2, const EEquationDigitType& DigitType)
{
    // 重置余数标志
    CalculatorData.bHasRemainder = false;
    CalculatorData.Quotient = 0;
    CalculatorData.Remainder = 0;
    
    CalculatorData.Operator1 = Operator1;
    CalculatorData.Operator2 = Operator2;
    
    const int32 MinDigit = GetMinValueForDigitType(DigitType);
    const int32 MaxDigit = GetMaxValueForDigitType(DigitType);

    // 简化处理：由于三位数运算复杂，简化逻辑，先生成数字再计算结果
    CalculatorData.Num1 = FMath::RandRange(MinDigit, MaxDigit);
    CalculatorData.Num2 = FMath::RandRange(MinDigit, MaxDigit);
    CalculatorData.Num3 = FMath::RandRange(MinDigit, MaxDigit);
    
    // 只保留混合运算符逻辑（加减 + 乘除），移除纯加减/纯乘除分支
    float FinalAnswer = 0.0f;
    
    // 混合运算符，按照数学优先级计算（乘除优先于加减）
    if (IsMulDivOperator(Operator1) && IsAddSubOperator(Operator2))
    {
        // 情况1：乘除 + 加减 → 先算前两个数，再算加减
        float FirstResult = 0;
        if (Operator1 == EOperatorType::Mul)
        {
            FirstResult = CalculatorData.Num1 * CalculatorData.Num2;
        }
        else if (Operator1 == EOperatorType::Div)
        {
            if (CalculatorData.Num2 == 0) CalculatorData.Num2 = 1;
            if (bAllowRemainder)
            {
                CalculatorData.Quotient = CalculatorData.Num1 / CalculatorData.Num2;
                CalculatorData.Remainder = CalculatorData.Num1 % CalculatorData.Num2;
                CalculatorData.bHasRemainder = (CalculatorData.Remainder != 0);
                FirstResult = CalculatorData.Quotient + static_cast<float>(CalculatorData.Remainder) / CalculatorData.Num2;
            }
            else
            {
                // 调整为整除
                if (CalculatorData.Num1 % CalculatorData.Num2 != 0)
                {
                    CalculatorData.Num1 = CalculatorData.Num2 * FMath::RandRange(1, MaxDigit / CalculatorData.Num2);
                }
                FirstResult = static_cast<float>(CalculatorData.Num1) / CalculatorData.Num2;
            }
        }
        
        if (Operator2 == EOperatorType::Add)
        {
            FinalAnswer = FirstResult + CalculatorData.Num3;
        }
        else if (Operator2 == EOperatorType::Sub)
        {
            FinalAnswer = FirstResult - CalculatorData.Num3;
        }
    }
    else if (IsAddSubOperator(Operator1) && IsMulDivOperator(Operator2))
    {
        // 情况2：加减 + 乘除 → 先算后两个数，再算加减
        float SecondResult = 0;
        if (Operator2 == EOperatorType::Mul)
        {
            SecondResult = CalculatorData.Num2 * CalculatorData.Num3;
        }
        else if (Operator2 == EOperatorType::Div)
        {
            if (CalculatorData.Num3 == 0) CalculatorData.Num3 = 1;
            if (bAllowRemainder)
            {
                int32 TempQuotient = CalculatorData.Num2 / CalculatorData.Num3;
                int32 TempRemainder = CalculatorData.Num2 % CalculatorData.Num3;
                CalculatorData.bHasRemainder = (TempRemainder != 0);
                CalculatorData.Quotient = TempQuotient;
                CalculatorData.Remainder = TempRemainder;
                SecondResult = TempQuotient + static_cast<float>(TempRemainder) / CalculatorData.Num3;
            }
            else
            {
                // 调整为整除
                if (CalculatorData.Num2 % CalculatorData.Num3 != 0)
                {
                    CalculatorData.Num2 = CalculatorData.Num3 * FMath::RandRange(1, MaxDigit / CalculatorData.Num3);
                }
                SecondResult = static_cast<float>(CalculatorData.Num2) / CalculatorData.Num3;
            }
        }
        
        if (Operator1 == EOperatorType::Add)
        {
            FinalAnswer = CalculatorData.Num1 + SecondResult;
        }
        else if (Operator1 == EOperatorType::Sub)
        {
            FinalAnswer = CalculatorData.Num1 - SecondResult;
        }
    }
    
    CalculatorData.Answer = FinalAnswer;
    
    UE_LOG(LogTemp, Log, TEXT("Calculator: Num1 [%d]   Operator1 [%hhd]   Num2 [%d]   Operator2 [%hhd]   Num3 [%d]   Answer [%f]   Remainder [%d]"), 
           CalculatorData.Num1, CalculatorData.Operator1, CalculatorData.Num2, CalculatorData.Operator2, CalculatorData.Num3, CalculatorData.Answer, CalculatorData.Remainder);
}

int32 UCalculator::GetMinValueForDigitType(const EEquationDigitType& DigitType)
{
    switch (DigitType)
    {
        case EEquationDigitType::Equation_OneDigit: return 1;
        case EEquationDigitType::Equation_TwoDigit: return 10;
        default: return 1;
    }
}

int32 UCalculator::GetMaxValueForDigitType(const EEquationDigitType& DigitType)
{
    switch (DigitType)
    {
        case EEquationDigitType::Equation_OneDigit: return 9;
        case EEquationDigitType::Equation_TwoDigit: return 99;
        default: return 9;
    }
}