#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <map>

using namespace llvm;

namespace {

struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    std::map<std::string, std::tuple<std::string, int, int>> branchDictionary;
    int branchNumber = 0;

    for (Function &F : M.functions()) {
      LLVMContext &Ctx = F.getContext();
      FunctionCallee logFunc = setupLogFunction(F);

      bool functionHasBranch = processFunctionBranches(F, branchDictionary, branchNumber, logFunc);

      if (functionHasBranch) {
        printFunctionInfo(F);
      }
    }

    printBranchDictionary(branchDictionary);

    return PreservedAnalyses::all();
  }

private:
  FunctionCallee setupLogFunction(Function &F) {
    LLVMContext &Ctx = F.getContext();
    std::vector<Type *> paramTypes = {Type::getInt8PtrTy(Ctx)};
    Type *retType = Type::getVoidTy(Ctx);
    FunctionType *logFuncType = FunctionType::get(retType, paramTypes, false);
    return F.getParent()->getOrInsertFunction("logPrint", logFuncType);
  }

  bool processFunctionBranches(Function &F, std::map<std::string, std::tuple<std::string, int, int>> &branchDictionary, int &branchNumber, FunctionCallee logFunc) {
    bool functionHasBranch = false;

    for (BasicBlock &B : F) {
      std::string fileName = F.getParent()->getSourceFileName();

      for (Instruction &I : B) {
        if (auto *BI = dyn_cast<BranchInst>(&I)) {
          if (BI->isConditional()) {
            const DebugLoc &Loc = BI->getDebugLoc();

            if (Loc) {
              functionHasBranch = true;
              std::string opcodeName = BI->getOpcodeName();
              int startLine = Loc.getLine();

              for (int i = 0; i < BI->getNumSuccessors(); ++i) {
                BasicBlock *branch = BI->getSuccessor(i);
                std::string branchID = opcodeName + "_" + std::to_string(branchNumber);

                int targetLine = branch->getFirstNonPHI()->getDebugLoc().getLine();
                branchDictionary[branchID] = std::make_tuple(fileName, startLine, targetLine);
                branchNumber += 1;

                IRBuilder<> builder(&*branch->getFirstInsertionPt());
                Value *args[] = {builder.CreateGlobalStringPtr(branchID)};
                builder.CreateCall(logFunc, args);
              }
            }
          }
        }
      }
    }

    return functionHasBranch;
  }

  void printFunctionInfo(const Function &F) {
    errs() << F.getName() << ": func_" << &F << "\n";
  }

  void printBranchDictionary(const std::map<std::string, std::tuple<std::string, int, int>> &branchDictionary) {
    errs() << "Branch Dictionary:\n";
    for (const auto &entry : branchDictionary) {
      const std::string &branchID = entry.first;
      const std::tuple<std::string, int, int> &location = entry.second;
      errs() << branchID << ": " << std::get<0>(location) << ", "
             << std::get<1>(location) << ", " << std::get<2>(location) << "\n";
    }
  }
};

} // namespace

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {.APIVersion = LLVM_PLUGIN_API_VERSION,
          .PluginName = "Skeleton pass",
          .PluginVersion = "v0.1",
          .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level) {
                  MPM.addPass(SkeletonPass());
                });
          }};
}
