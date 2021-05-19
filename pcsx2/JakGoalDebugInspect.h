#pragma once

#include <array>
#include <stack>
#include <unordered_map>

#include "Pcsx2Types.h"
#include "R5900.h"

constexpr int GOAL_FUNCARG0_REG = 4;
constexpr int GOAL_FUNCARG1_REG = 5;
constexpr int GOAL_FUNCARG2_REG = 6;
constexpr int GOAL_FUNCARG3_REG = 7;
constexpr int GOAL_FUNCARG4_REG = 8;
constexpr int GOAL_FUNCARG5_REG = 9;
constexpr int GOAL_FUNCARG6_REG = 10;
constexpr int GOAL_FUNCARG7_REG = 11;
constexpr int GOAL_SYMTABLE_REG = 23; // s7/r23
constexpr int GOAL_FUNCTION_REG = 25; // t9/r25

extern const char* goalMethodNames[9];
extern bool goalWriteP;

const char* goalGetSymName(u16 sym);
u16 goalGetSymFromPtr(u32 ptr) noexcept(true);
const char* goalGetSymNameFromPtr(u32 ptr);

typedef struct GoalFuncInfo
{
	u32 func_ptr;

	u8 reg_changed = 0;
	u32 arg_count_estimate = 0;
	u128 reg_data[8];
	u128 arg_data[8];
	const char* arg_types[8] = {nullptr};

	GoalFuncInfo(u32 l_func_ptr) noexcept(true)
		: func_ptr(l_func_ptr)
	{
		reg_data[0] = cpuRegs.GPR.r[GOAL_FUNCARG0_REG].UQ;
		reg_data[1] = cpuRegs.GPR.r[GOAL_FUNCARG1_REG].UQ;
		reg_data[2] = cpuRegs.GPR.r[GOAL_FUNCARG2_REG].UQ;
		reg_data[3] = cpuRegs.GPR.r[GOAL_FUNCARG3_REG].UQ;
		reg_data[4] = cpuRegs.GPR.r[GOAL_FUNCARG4_REG].UQ;
		reg_data[5] = cpuRegs.GPR.r[GOAL_FUNCARG5_REG].UQ;
		reg_data[6] = cpuRegs.GPR.r[GOAL_FUNCARG6_REG].UQ;
		reg_data[7] = cpuRegs.GPR.r[GOAL_FUNCARG7_REG].UQ;
	};
};

void goalPushFunc(GoalFuncInfo* func);
void goalPopFunc() noexcept(true);
GoalFuncInfo* goalTopFunc() noexcept(true);
bool goalNoFuncsP() noexcept(true);
void goalWriteAllInfo();
void goalAnalyzeFunc(GoalFuncInfo* func);
void goalValidateTypeMethods(const char* name);
GoalFuncInfo* goalGetTypeMethod(const char* name, u32 m);
void goalSetTypeMethod(const char* name, u32 m, GoalFuncInfo* func);
