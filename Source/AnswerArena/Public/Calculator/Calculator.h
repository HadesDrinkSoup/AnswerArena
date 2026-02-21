#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Calculator.generated.h"

UENUM(BlueprintType)
enum class EOperatorType : uint8
{
	Add UMETA(DisplayName = "加法"),
	Sub UMETA(DisplayName = "减法"),
	Mul UMETA(DisplayName = "乘法"),
	Div UMETA(DisplayName = "除法"),
	None UMETA(DisplayName = "无")
};

UENUM(BlueprintType)
enum class EEquationNumType : uint8
{
	Equation_TwoNumbers UMETA(DisplayName = "两个数运算"),
	Equation_ThreeNumbers UMETA(DisplayName = "三个数运算")
};

UENUM(BlueprintType)
enum class EEquationDigitType : uint8
{
	Equation_OneDigit UMETA(DisplayName = "一位数"),
	Equation_TwoDigit UMETA(DisplayName = "两位数")
};

USTRUCT(BlueprintType)
struct FCalculatorData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	int32 Num1 = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	int32 Num2 = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	int32 Num3 = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	float Answer = 0.f;
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	EOperatorType Operator1 = EOperatorType::Add;
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	EOperatorType Operator2 = EOperatorType::Add;
	
	// 余数相关
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	bool bHasRemainder = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	int32 Quotient = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "Calculator")
	int32 Remainder = 0;
};

UCLASS(Blueprintable, BlueprintType)
class ANSWERARENA_API UCalculator : public UObject
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Calculator")
	FCalculatorData GetCalculatorData() const;
	
	UFUNCTION(BlueprintCallable, Category = "Calculator")
	void GenerateEquation();
	
protected:
	FCalculatorData CalculatorData;
	FString CurrentEquation;
	
	// 计算的数字个数
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "c")
	EEquationNumType m_EquationNumType = EEquationNumType::Equation_TwoNumbers;

	// 计算位数
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equation")
	EEquationDigitType m_EquationDigitType = EEquationDigitType::Equation_OneDigit;
	
	// 运算符类型
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equation")
	EOperatorType m_OperatorType = EOperatorType::Add;
	
	// 是否生成混合运算
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equation")
	bool bGenerateMixedOperator = false;
	
	// 是否允许结果为负数（仅对减法有效）
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equation")
	bool bAllowNegativeResult = false;
	
	// 是否允许除法有余数
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equation")
	bool bAllowRemainder = false;

private:
	// 生成指定位数的随机整数
	static int32 GenerateRandomNumber(const EEquationDigitType& EquationDigitType);
	
	// 获取随机运算符类型
	static EOperatorType GetRandomOperatorType();
	
	// 生成加法算式
	void GenerateAddition(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType);
	
	// 生成减法算式
	void GenerateSubtraction(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType);
	
	// 生成乘法算式
	void GenerateMultiplication(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType);
	
	// 生成除法算式
	void GenerateDivision(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType);
	
	// 生成混合运算符算式
	void GenerateMixedEquation(const EEquationNumType& EquationNumType, const EEquationDigitType& DigitType);
	
	// 生成两个数的算式
	void GenerateTwoNumbersEquation(const EOperatorType& OperatorType, const EEquationDigitType& DigitType);
	
	// 生成三个数的算式
	void GenerateThreeNumbersEquation(const EOperatorType& Operator1, const EOperatorType& Operator2, const EEquationDigitType& DigitType);
	
	// 获取指定位数类型的最小值
	static int32 GetMinValueForDigitType(const EEquationDigitType& DigitType);
	
	// 获取指定位数类型的最大值
	static int32 GetMaxValueForDigitType(const EEquationDigitType& DigitType);
};